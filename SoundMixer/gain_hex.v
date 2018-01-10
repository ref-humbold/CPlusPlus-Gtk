module gain_hex(output reg[6:0] hex, input[3:0] gain);
	always @*
	case(gain)
		4'b1000: hex = 7'b0000000;
		4'b1001: hex = 7'b1111000;
		4'b1010: hex = 7'b0000010;
		4'b1011: hex = 7'b0010010;
		4'b1100: hex = 7'b0011001;
		4'b1101: hex = 7'b0110000;
		4'b1110: hex = 7'b0100100;
		4'b1111: hex = 7'b1111001;
		4'b0000: hex = 7'b1000000;
		4'b0001: hex = 7'b0001000;
		4'b0010: hex = 7'b0000011;
		4'b0011: hex = 7'b0100111;
		4'b0100: hex = 7'b0100001;
		4'b0101: hex = 7'b0111111;
	endcase
endmodule
