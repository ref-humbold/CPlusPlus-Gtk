
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
	hex_amplif_hex_signal,
	key_amplif_key_signal,
	led_amplif_led_signal,
	reset_reset_n,
	switch_avg_switch_signal,
	switch_delay_switch_signal,
	switch_noise_switch_signal);	

	inout		audio_config_extern_SDAT;
	output		audio_config_extern_SCLK;
	input		audio_external_ADCDAT;
	input		audio_external_ADCLRCK;
	input		audio_external_BCLK;
	output		audio_external_DACDAT;
	input		audio_external_DACLRCK;
	output		audio_pll_clk_clk;
	input		clk_clk;
	output	[6:0]	hex_amplif_hex_signal;
	input	[1:0]	key_amplif_key_signal;
	output	[9:0]	led_amplif_led_signal;
	input		reset_reset_n;
	input		switch_avg_switch_signal;
	input		switch_delay_switch_signal;
	input		switch_noise_switch_signal;
endmodule
