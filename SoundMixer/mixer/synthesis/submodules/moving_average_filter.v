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
		output wire        avalon_left_source_valid,  //                    .valid
		input  wire        switch_signal              //              switch.switch_signal
	);

	assign avalon_left_sink_ready = avalon_left_source_ready;
	assign avalon_right_sink_ready = avalon_right_source_ready;
	wire on;
	
	switch_sync sw(on, clock_clk, switch_signal);
	move_avg lavg(avalon_left_source_data, avalon_left_source_valid, avalon_left_sink_data, avalon_left_sink_valid & avalon_left_source_ready, clock_clk, reset_reset, on);
	move_avg ravg(avalon_right_source_data, avalon_right_source_valid, avalon_right_sink_data, avalon_right_sink_valid & avalon_right_source_ready, clock_clk, reset_reset, on);
endmodule
