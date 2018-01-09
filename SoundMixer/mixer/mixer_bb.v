
module mixer (
	audio_config_extern_SDAT,
	audio_config_extern_SCLK,
	audio_external_ADCDAT,
	audio_external_ADCLRCK,
	audio_external_BCLK,
	audio_external_DACDAT,
	audio_external_DACLRCK,
	clk_clk,
	gain_hex_new_signal,
	gain_key_new_signal,
	reset_reset_n,
	audio_pll_clk_clk);	

	inout		audio_config_extern_SDAT;
	output		audio_config_extern_SCLK;
	input		audio_external_ADCDAT;
	input		audio_external_ADCLRCK;
	input		audio_external_BCLK;
	output		audio_external_DACDAT;
	input		audio_external_DACLRCK;
	input		clk_clk;
	output	[6:0]	gain_hex_new_signal;
	input	[1:0]	gain_key_new_signal;
	input		reset_reset_n;
	output		audio_pll_clk_clk;
endmodule
