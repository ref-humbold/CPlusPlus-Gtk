// moving_average_filter.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ps / 1 ps
module moving_average_filter (
		input  wire        clock_clk,                 //               clock.clk
		input  wire        reset_reset,               //               reset.reset
		input  wire [23:0] avalon_left_sink_data,     //    avalon_left_sink.data
		output wire        avalon_left_sink_ready,    //                    .ready
		input  wire        avalon_left_sink_valid,    //                    .valid
		input  wire [23:0] avalon_right_sink_data,    //   avalon_right_sink.data
		output wire        avalon_right_sink_ready,   //                    .ready
		input  wire        avalon_right_sink_valid,   //                    .valid
		output wire [23:0] avalon_right_source_data,  // avalon_right_source.data
		input  wire        avalon_right_source_ready, //                    .ready
		output wire        avalon_right_source_valid, //                    .valid
		output wire [23:0] avalon_left_source_data,   //  avalon_left_source.data
		input  wire        avalon_left_source_ready,  //                    .ready
		output wire        avalon_left_source_valid   //                    .valid
	);

	// TODO: Auto-generated HDL template

	assign avalon_left_sink_ready = 1'b0;

	assign avalon_right_sink_ready = 1'b0;

	assign avalon_right_source_valid = 1'b0;

	assign avalon_right_source_data = 24'b000000000000000000000000;

	assign avalon_left_source_valid = 1'b0;

	assign avalon_left_source_data = 24'b000000000000000000000000;

endmodule
