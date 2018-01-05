
module mixer (
	audio_external_ADCDAT,
	audio_external_ADCLRCK,
	audio_external_BCLK,
	audio_external_DACDAT,
	audio_external_DACLRCK,
	clk_clk,
	reset_reset_n,
	audio_config_extern_SDAT,
	audio_config_extern_SCLK,
	gain_hex_new_signal,
	gain_key_new_signal);	

	input		audio_external_ADCDAT;
	input		audio_external_ADCLRCK;
	input		audio_external_BCLK;
	output		audio_external_DACDAT;
	input		audio_external_DACLRCK;
	input		clk_clk;
	input		reset_reset_n;
	inout		audio_config_extern_SDAT;
	output		audio_config_extern_SCLK;
	output	[6:0]	gain_hex_new_signal;
	input	[1:0]	gain_key_new_signal;
endmodule
