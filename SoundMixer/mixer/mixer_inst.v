	mixer u0 (
		.audio_config_extern_SDAT (<connected-to-audio_config_extern_SDAT>), // audio_config_extern.SDAT
		.audio_config_extern_SCLK (<connected-to-audio_config_extern_SCLK>), //                    .SCLK
		.audio_external_ADCDAT    (<connected-to-audio_external_ADCDAT>),    //      audio_external.ADCDAT
		.audio_external_ADCLRCK   (<connected-to-audio_external_ADCLRCK>),   //                    .ADCLRCK
		.audio_external_BCLK      (<connected-to-audio_external_BCLK>),      //                    .BCLK
		.audio_external_DACDAT    (<connected-to-audio_external_DACDAT>),    //                    .DACDAT
		.audio_external_DACLRCK   (<connected-to-audio_external_DACLRCK>),   //                    .DACLRCK
		.audio_pll_clk_clk        (<connected-to-audio_pll_clk_clk>),        //       audio_pll_clk.clk
		.clk_clk                  (<connected-to-clk_clk>),                  //                 clk.clk
		.hex_amplif_hex_signal    (<connected-to-hex_amplif_hex_signal>),    //          hex_amplif.hex_signal
		.key_amplif_key_signal    (<connected-to-key_amplif_key_signal>),    //          key_amplif.key_signal
		.led_amplif_led_signal    (<connected-to-led_amplif_led_signal>),    //          led_amplif.led_signal
		.reset_reset_n            (<connected-to-reset_reset_n>),            //               reset.reset_n
		.switch_avg_switch_signal (<connected-to-switch_avg_switch_signal>)  //          switch_avg.switch_signal
	);

