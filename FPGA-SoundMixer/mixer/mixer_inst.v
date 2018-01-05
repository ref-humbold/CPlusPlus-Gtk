	mixer u0 (
		.audio_external_ADCDAT    (<connected-to-audio_external_ADCDAT>),    //      audio_external.ADCDAT
		.audio_external_ADCLRCK   (<connected-to-audio_external_ADCLRCK>),   //                    .ADCLRCK
		.audio_external_BCLK      (<connected-to-audio_external_BCLK>),      //                    .BCLK
		.audio_external_DACDAT    (<connected-to-audio_external_DACDAT>),    //                    .DACDAT
		.audio_external_DACLRCK   (<connected-to-audio_external_DACLRCK>),   //                    .DACLRCK
		.clk_clk                  (<connected-to-clk_clk>),                  //                 clk.clk
		.reset_reset_n            (<connected-to-reset_reset_n>),            //               reset.reset_n
		.audio_config_extern_SDAT (<connected-to-audio_config_extern_SDAT>), // audio_config_extern.SDAT
		.audio_config_extern_SCLK (<connected-to-audio_config_extern_SCLK>), //                    .SCLK
		.gain_hex_new_signal      (<connected-to-gain_hex_new_signal>),      //            gain_hex.new_signal
		.gain_key_new_signal      (<connected-to-gain_key_new_signal>)       //            gain_key.new_signal
	);
