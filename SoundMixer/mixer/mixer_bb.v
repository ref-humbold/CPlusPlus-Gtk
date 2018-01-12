
module mixer (
	audio_config_extern_SDAT,
	audio_config_extern_SCLK,
	audio_external_ADCDAT,
	audio_external_ADCLRCK,
	audio_external_BCLK,
	audio_external_DACDAT,
	audio_external_DACLRCK,
	audio_pll_clk_clk,
	clk_clk,
	hex_hex_signal_0,
	hex_hex_signal_1,
	key_key_signal,
	reset_reset_n);	

	inout		audio_config_extern_SDAT;
	output		audio_config_extern_SCLK;
	input		audio_external_ADCDAT;
	input		audio_external_ADCLRCK;
	input		audio_external_BCLK;
	output		audio_external_DACDAT;
	input		audio_external_DACLRCK;
	output		audio_pll_clk_clk;
	input		clk_clk;
	output	[6:0]	hex_hex_signal_0;
	output	[6:0]	hex_hex_signal_1;
	input	[1:0]	key_key_signal;
	input		reset_reset_n;
endmodule
