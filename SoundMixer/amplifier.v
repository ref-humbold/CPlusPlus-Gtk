module amplifier #(parameter BITS = 24) (output reg[BITS - 1:0] sound_out, input[BITS - 1:0] sound_in, input[3:0] gain);
	always @*
	casez(gain)
		4'b0101: sound_out = 0;
		4'b0000: sound_out = sound_in;
		4'b1???: sound_out = sound_in + ((sound_in >> 2) - (sound_in >> 4)) * (~gain + 4'b0001)
		4'b0???: sound_out = sound_in - ((sound_in >> 2) - (sound_in >> 4)) * gain;
	endcase
endmodule
