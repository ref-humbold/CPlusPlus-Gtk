module amplifier(output sound_out, input sound_in, input[3:0] gain);
	always @*
	case(gain)
		4'b1000: sound_out = 0;
		4'b1001: sound_out = sound_in / 2 - sound_in / 16;
		4'b1010: sound_out = sound_in / 2;
		4'b1011: sound_out = sound_in - sound_in / 4 - sound_in / 8 - sound_in / 16;
		4'b1100: sound_out = sound_in - sound_in / 4 - sound_in / 8;
		4'b1101: sound_out = sound_in - sound_in / 4 - sound_in / 16;
		4'b1110: sound_out = sound_in - sound_in / 8 - sound_in / 16;
		4'b1111: sound_out = sound_in - sound_in / 8;
		4'b0000: sound_out = sound_in;
		4'b0001: sound_out = sound_in + sound_in / 8;
		4'b0010: sound_out = sound_in + sound_in / 4;
		4'b0011: sound_out = sound_in + sound_in / 4 + sound_in / 8 + sound_in / 16;
		4'b0100: sound_out = sound_in + sound_in / 2 + sound_in / 8;
		4'b0101: sound_out = sound_in + sound_in / 2 + sound_in / 4 + sound_in / 16;
		4'b0110: sound_out = sound_in + sound_in;
		4'b0111: sound_out = sound_in + sound_in + sound_in /4;
	endcase
endmodule
