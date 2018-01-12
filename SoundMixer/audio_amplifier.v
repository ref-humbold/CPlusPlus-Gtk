// audio_amplifier.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ps / 1 ps
module audio_amplifier (
		input  wire        clock_clk,                 //               clock.clk
		input  wire        reset_reset,               //               reset.reset
		input  wire [23:0] avalon_left_sink_data,     //    avalon_left_sink.data
		output wire        avalon_left_sink_ready,    //                    .ready
		input  wire        avalon_left_sink_valid,    //                    .valid
		input  wire [23:0] avalon_right_sink_data,    //   avalon_right_sink.data
		output wire        avalon_right_sink_ready,   //                    .ready
		input  wire        avalon_right_sink_valid,   //                    .valid
		output wire [23:0] avalon_left_source_data,   //  avalon_left_source.data
		input  wire        avalon_left_source_ready,  //                    .ready
		output wire        avalon_left_source_valid,  //                    .valid
		output wire [23:0] avalon_right_source_data,  // avalon_right_source.data
		input  wire        avalon_right_source_ready, //                    .ready
		output wire        avalon_right_source_valid, //                    .valid
		output wire [6:0]  hex_signal_0,              //                 hex.hex_signal_0
		output wire [6:0]  hex_signal_1,              //                    .hex_signal_1
		input  wire [1:0]  key_signal                 //                 key.key_signal
	);

	wire[3:0] gain;
	wire change_up, change_down;
	
	assign avalon_left_sink_ready = avalon_left_source_ready;
	assign avalon_right_sink_ready = avalon_right_source_ready;
	
	gain_key key_up(change_up, clock_clk, ~key_signal[0]);
	gain_key key_down(change_down, clock_clk, ~key_signal[1]);
	get_gain get(gain, clock_clk, change_up, change_down);
	gain_hex ghex(hex_signal_1, gain);
	status_hex shex(hex_signal_0, avalon_left_source_ready, avalon_right_source_ready, avalon_left_sink_valid, avalon_right_sink_valid);
	amplifier amp_left(avalon_left_source_data, avalon_left_source_valid, avalon_left_source_ready, avalon_left_sink_data, avalon_left_sink_valid, clock_clk, reset_reset, gain);
	amplifier amp_right(avalon_right_source_data, avalon_right_source_valid, avalon_right_source_ready, avalon_right_sink_data, avalon_right_sink_valid, clock_clk, reset_reset, gain);

endmodule
