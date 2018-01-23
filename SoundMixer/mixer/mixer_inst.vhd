	component mixer is
		port (
			audio_config_extern_SDAT   : inout std_logic                    := 'X';             -- SDAT
			audio_config_extern_SCLK   : out   std_logic;                                       -- SCLK
			audio_external_ADCDAT      : in    std_logic                    := 'X';             -- ADCDAT
			audio_external_ADCLRCK     : in    std_logic                    := 'X';             -- ADCLRCK
			audio_external_BCLK        : in    std_logic                    := 'X';             -- BCLK
			audio_external_DACDAT      : out   std_logic;                                       -- DACDAT
			audio_external_DACLRCK     : in    std_logic                    := 'X';             -- DACLRCK
			audio_pll_clk_clk          : out   std_logic;                                       -- clk
			clk_clk                    : in    std_logic                    := 'X';             -- clk
			hex_amplif_hex_signal      : out   std_logic_vector(6 downto 0);                    -- hex_signal
			key_amplif_key_signal      : in    std_logic_vector(1 downto 0) := (others => 'X'); -- key_signal
			led_amplif_led_signal      : out   std_logic_vector(9 downto 0);                    -- led_signal
			reset_reset_n              : in    std_logic                    := 'X';             -- reset_n
			switch_avg_switch_signal   : in    std_logic                    := 'X';             -- switch_signal
			switch_delay_switch_signal : in    std_logic                    := 'X'              -- switch_signal
		);
	end component mixer;

	u0 : component mixer
		port map (
			audio_config_extern_SDAT   => CONNECTED_TO_audio_config_extern_SDAT,   -- audio_config_extern.SDAT
			audio_config_extern_SCLK   => CONNECTED_TO_audio_config_extern_SCLK,   --                    .SCLK
			audio_external_ADCDAT      => CONNECTED_TO_audio_external_ADCDAT,      --      audio_external.ADCDAT
			audio_external_ADCLRCK     => CONNECTED_TO_audio_external_ADCLRCK,     --                    .ADCLRCK
			audio_external_BCLK        => CONNECTED_TO_audio_external_BCLK,        --                    .BCLK
			audio_external_DACDAT      => CONNECTED_TO_audio_external_DACDAT,      --                    .DACDAT
			audio_external_DACLRCK     => CONNECTED_TO_audio_external_DACLRCK,     --                    .DACLRCK
			audio_pll_clk_clk          => CONNECTED_TO_audio_pll_clk_clk,          --       audio_pll_clk.clk
			clk_clk                    => CONNECTED_TO_clk_clk,                    --                 clk.clk
			hex_amplif_hex_signal      => CONNECTED_TO_hex_amplif_hex_signal,      --          hex_amplif.hex_signal
			key_amplif_key_signal      => CONNECTED_TO_key_amplif_key_signal,      --          key_amplif.key_signal
			led_amplif_led_signal      => CONNECTED_TO_led_amplif_led_signal,      --          led_amplif.led_signal
			reset_reset_n              => CONNECTED_TO_reset_reset_n,              --               reset.reset_n
			switch_avg_switch_signal   => CONNECTED_TO_switch_avg_switch_signal,   --          switch_avg.switch_signal
			switch_delay_switch_signal => CONNECTED_TO_switch_delay_switch_signal  --        switch_delay.switch_signal
		);

