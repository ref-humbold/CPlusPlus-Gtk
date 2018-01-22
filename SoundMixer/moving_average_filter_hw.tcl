# TCL File Generated by Component Editor 17.1
# Mon Jan 22 10:36:08 CET 2018
# DO NOT MODIFY


# 
# moving_average_filter "moving_average_filter" v1.0
#  2018.01.22.10:36:07
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module moving_average_filter
# 
set_module_property DESCRIPTION ""
set_module_property NAME moving_average_filter
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME moving_average_filter
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL moving_average_filter
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE true
add_fileset_file moving_average_filter.v VERILOG PATH moving_average_filter.v TOP_LEVEL_FILE
add_fileset_file delay.v VERILOG PATH delay.v
add_fileset_file move_avg.v VERILOG PATH move_avg.v
add_fileset_file switch_sync.v VERILOG PATH switch_sync.v


# 
# parameters
# 


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clock_clk clk Input 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset_reset reset Input 1


# 
# connection point avalon_left_sink
# 
add_interface avalon_left_sink avalon_streaming end
set_interface_property avalon_left_sink associatedClock clock
set_interface_property avalon_left_sink associatedReset reset
set_interface_property avalon_left_sink dataBitsPerSymbol 8
set_interface_property avalon_left_sink errorDescriptor ""
set_interface_property avalon_left_sink firstSymbolInHighOrderBits true
set_interface_property avalon_left_sink maxChannel 0
set_interface_property avalon_left_sink readyLatency 0
set_interface_property avalon_left_sink ENABLED true
set_interface_property avalon_left_sink EXPORT_OF ""
set_interface_property avalon_left_sink PORT_NAME_MAP ""
set_interface_property avalon_left_sink CMSIS_SVD_VARIABLES ""
set_interface_property avalon_left_sink SVD_ADDRESS_GROUP ""

add_interface_port avalon_left_sink avalon_left_sink_data data Input 24
add_interface_port avalon_left_sink avalon_left_sink_ready ready Output 1
add_interface_port avalon_left_sink avalon_left_sink_valid valid Input 1


# 
# connection point avalon_right_sink
# 
add_interface avalon_right_sink avalon_streaming end
set_interface_property avalon_right_sink associatedClock clock
set_interface_property avalon_right_sink associatedReset reset
set_interface_property avalon_right_sink dataBitsPerSymbol 8
set_interface_property avalon_right_sink errorDescriptor ""
set_interface_property avalon_right_sink firstSymbolInHighOrderBits true
set_interface_property avalon_right_sink maxChannel 0
set_interface_property avalon_right_sink readyLatency 0
set_interface_property avalon_right_sink ENABLED true
set_interface_property avalon_right_sink EXPORT_OF ""
set_interface_property avalon_right_sink PORT_NAME_MAP ""
set_interface_property avalon_right_sink CMSIS_SVD_VARIABLES ""
set_interface_property avalon_right_sink SVD_ADDRESS_GROUP ""

add_interface_port avalon_right_sink avalon_right_sink_data data Input 24
add_interface_port avalon_right_sink avalon_right_sink_ready ready Output 1
add_interface_port avalon_right_sink avalon_right_sink_valid valid Input 1


# 
# connection point avalon_right_source
# 
add_interface avalon_right_source avalon_streaming start
set_interface_property avalon_right_source associatedClock clock
set_interface_property avalon_right_source associatedReset reset
set_interface_property avalon_right_source dataBitsPerSymbol 8
set_interface_property avalon_right_source errorDescriptor ""
set_interface_property avalon_right_source firstSymbolInHighOrderBits true
set_interface_property avalon_right_source maxChannel 0
set_interface_property avalon_right_source readyLatency 0
set_interface_property avalon_right_source ENABLED true
set_interface_property avalon_right_source EXPORT_OF ""
set_interface_property avalon_right_source PORT_NAME_MAP ""
set_interface_property avalon_right_source CMSIS_SVD_VARIABLES ""
set_interface_property avalon_right_source SVD_ADDRESS_GROUP ""

add_interface_port avalon_right_source avalon_right_source_data data Output 24
add_interface_port avalon_right_source avalon_right_source_ready ready Input 1
add_interface_port avalon_right_source avalon_right_source_valid valid Output 1


# 
# connection point avalon_left_source
# 
add_interface avalon_left_source avalon_streaming start
set_interface_property avalon_left_source associatedClock clock
set_interface_property avalon_left_source associatedReset reset
set_interface_property avalon_left_source dataBitsPerSymbol 8
set_interface_property avalon_left_source errorDescriptor ""
set_interface_property avalon_left_source firstSymbolInHighOrderBits true
set_interface_property avalon_left_source maxChannel 0
set_interface_property avalon_left_source readyLatency 0
set_interface_property avalon_left_source ENABLED true
set_interface_property avalon_left_source EXPORT_OF ""
set_interface_property avalon_left_source PORT_NAME_MAP ""
set_interface_property avalon_left_source CMSIS_SVD_VARIABLES ""
set_interface_property avalon_left_source SVD_ADDRESS_GROUP ""

add_interface_port avalon_left_source avalon_left_source_data data Output 24
add_interface_port avalon_left_source avalon_left_source_ready ready Input 1
add_interface_port avalon_left_source avalon_left_source_valid valid Output 1


# 
# connection point switch
# 
add_interface switch conduit end
set_interface_property switch associatedClock clock
set_interface_property switch associatedReset ""
set_interface_property switch ENABLED true
set_interface_property switch EXPORT_OF ""
set_interface_property switch PORT_NAME_MAP ""
set_interface_property switch CMSIS_SVD_VARIABLES ""
set_interface_property switch SVD_ADDRESS_GROUP ""

add_interface_port switch switch_signal switch_signal Input 1

