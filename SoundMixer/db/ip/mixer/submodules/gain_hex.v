module gain_hex(output reg[6:0] hex, input[3:0] gain);
	always @*
	case(gain)
		4'b1000: hex = 7'b0110110;
		4'b1001: hex = 7'b1100011;
		4'b1010: hex = 7'b1110011;
		4'b1011: hex = 7'b1100111;
		4'b1100: hex = 7'b1110111;
		4'b1101: hex = 7'b1101011;
		4'b1110: hex = 7'b1111011;
		4'b1111: hex = 7'b1101111;
		4'b0000: hex = 7'b0111111;
		4'b0001: hex = 7'b1011111;
		4'b0010: hex = 7'b1111101;
		4'b0011: hex = 7'b1011101;
		4'b0100: hex = 7'b1111110;
		4'b0101: hex = 7'b1011110;
		4'b0110: hex = 7'b1111100;
		4'b0111: hex = 7'b1011100;
	endcase
endmodule
