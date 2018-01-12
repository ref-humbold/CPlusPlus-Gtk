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
		.hex_hex_signal_0         (<connected-to-hex_hex_signal_0>),         //                 hex.hex_signal_0
		.hex_hex_signal_1         (<connected-to-hex_hex_signal_1>),         //                    .hex_signal_1
		.key_key_signal           (<connected-to-key_key_signal>),           //                 key.key_signal
		.reset_reset_n            (<connected-to-reset_reset_n>)             //               reset.reset_n
	);

