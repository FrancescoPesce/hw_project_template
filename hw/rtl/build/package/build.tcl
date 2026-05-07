set script_args [lrange $argv 0 end]

if {[llength $script_args] != 3} {
    puts "Usage: vivado -mode batch -source build.tcl -tclargs <KERNEL> <PROJ_ROOT> <PART_NAME>"
    puts "You passed [llength $script_args] arguments."
    exit 1
}

set KERNEL    [lindex $script_args 0]
set PROJ_ROOT [lindex $script_args 1]
set PART_NAME [lindex $script_args 2]

puts "DEBUG: PROJECT ROOT = '$PROJ_ROOT'"
puts "DEBUG: KERNEL = '$KERNEL'"
puts "DEBUG: PART_NAME = '$PART_NAME'"
flush stdout

create_project -force $PROJ_ROOT $PROJ_ROOT -part xcu250-figd2104-2L-e
add_files "$PROJ_ROOT/${KERNEL}.v"
update_compile_order -fileset sources_1

# Package as RTL kernel
ipx::package_project -root_dir $PROJ_ROOT/ip_repo -vendor user.org -library user -taxonomy /KernelIP -import_files -set_current false

ipx::unload_core $PROJ_ROOT/ip_repo/component.xml
ipx::edit_ip_in_project -upgrade true -name tmp_edit_project -directory $PROJ_ROOT/tmp_edit_project $PROJ_ROOT/ip_repo/component.xml

set core [ipx::current_core]

# Set kernel properties
set_property core_revision 2 $core
set_property sdx_kernel true $core
set_property sdx_kernel_type rtl $core

# Associate clock/reset
ipx::associate_bus_interfaces -busif s_axis -clock ap_clk $core
ipx::associate_bus_interfaces -busif m_axis -clock ap_clk $core

# =========================
# S_AXIS (slave)
# =========================
set s_axis_if [ipx::add_bus_interface s_axis $core]
set_property interface_mode slave $s_axis_if
set_property abstraction_type_vlnv xilinx.com:interface:axis_rtl:1.0 $s_axis_if
set_property bus_type_vlnv xilinx.com:interface:axis:1.0 $s_axis_if

# =========================
# M_AXIS (master)
# =========================
set m_axis_if [ipx::add_bus_interface m_axis $core]
set_property interface_mode master $m_axis_if
set_property abstraction_type_vlnv xilinx.com:interface:axis_rtl:1.0 $m_axis_if
set_property bus_type_vlnv xilinx.com:interface:axis:1.0 $m_axis_if

# Save IP
ipx::save_core $core
ipx::unload_core $core

# Package into XO
package_xo \
    -kernel_name $KERNEL \
    -ip_directory $PROJ_ROOT/ip_repo \
    -xo_path $KERNEL.xo \
    -ctrl_protocol ap_ctrl_none

puts "XO generated: $KERNEL.xo"

exit