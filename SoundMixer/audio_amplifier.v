// audio_amplifier.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ps / 1 ps
module audio_amplifier #(parameter BITS = 24) (
		input wire clock_clk,
		input wire  reset_reset,
		input wire[BITS - 1:0] avalon_left_sink_data,
		output wire avalon_left_sink_ready,
		input wire avalon_left_sink_valid,
		input wire [BITS - 1:0] avalon_right_sink_data,
		output wire avalon_right_sink_ready,
		input wire avalon_right_sink_valid,
		output wire[6:0] hex_signal,
		input wire[1:0] key_signal,
		output wire[BITS - 1:0] avalon_left_source_data,
		input wire avalon_left_source_ready,
		output wire avalon_left_source_valid,
		output wire[BITS - 1:0] avalon_right_source_data,
		input wire avalon_right_source_ready,
		output wire avalon_right_source_valid
	);
	wire[3:0] gain;
	wire change_up, change_down;
	
	assign avalon_left_sink_ready = 1'b1;
	assign avalon_right_sink_ready = 1'b1;
	assign avalon_left_source_valid = 1'b1;
	assign avalon_right_source_valid = 1'b1;
	
	gain_key key_up(change_up, clock_clk, key_signal[0]);
	gain_key key_down(change_down, clock_clk, key_signal[1]);
	get_gain get(gain, clock_clk, {change_up, change_down});
	gain_hex hex(hex_signal, gain);
	amplifier amp_left(avalon_left_source_data, avalon_left_sink_data, gain);
	amplifier amp_right(avalon_right_source_data, avalon_right_sink_data, gain);
endmodule
