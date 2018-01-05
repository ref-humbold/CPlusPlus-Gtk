	component mixer is
		port (
			audio_external_ADCDAT    : in    std_logic                    := 'X';             -- ADCDAT
			audio_external_ADCLRCK   : in    std_logic                    := 'X';             -- ADCLRCK
			audio_external_BCLK      : in    std_logic                    := 'X';             -- BCLK
			audio_external_DACDAT    : out   std_logic;                                       -- DACDAT
			audio_external_DACLRCK   : in    std_logic                    := 'X';             -- DACLRCK
			clk_clk                  : in    std_logic                    := 'X';             -- clk
			reset_reset_n            : in    std_logic                    := 'X';             -- reset_n
			audio_config_extern_SDAT : inout std_logic                    := 'X';             -- SDAT
			audio_config_extern_SCLK : out   std_logic;                                       -- SCLK
			gain_hex_new_signal      : out   std_logic_vector(6 downto 0);                    -- new_signal
			gain_key_new_signal      : in    std_logic_vector(1 downto 0) := (others => 'X')  -- new_signal
		);
	end component mixer;

	u0 : component mixer
		port map (
			audio_external_ADCDAT    => CONNECTED_TO_audio_external_ADCDAT,    --      audio_external.ADCDAT
			audio_external_ADCLRCK   => CONNECTED_TO_audio_external_ADCLRCK,   --                    .ADCLRCK
			audio_external_BCLK      => CONNECTED_TO_audio_external_BCLK,      --                    .BCLK
			audio_external_DACDAT    => CONNECTED_TO_audio_external_DACDAT,    --                    .DACDAT
			audio_external_DACLRCK   => CONNECTED_TO_audio_external_DACLRCK,   --                    .DACLRCK
			clk_clk                  => CONNECTED_TO_clk_clk,                  --                 clk.clk
			reset_reset_n            => CONNECTED_TO_reset_reset_n,            --               reset.reset_n
			audio_config_extern_SDAT => CONNECTED_TO_audio_config_extern_SDAT, -- audio_config_extern.SDAT
			audio_config_extern_SCLK => CONNECTED_TO_audio_config_extern_SCLK, --                    .SCLK
			gain_hex_new_signal      => CONNECTED_TO_gain_hex_new_signal,      --            gain_hex.new_signal
			gain_key_new_signal      => CONNECTED_TO_gain_key_new_signal       --            gain_key.new_signal
		);

