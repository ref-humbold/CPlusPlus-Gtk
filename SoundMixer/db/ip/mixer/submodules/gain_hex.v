module gain_hex(output reg[6:0] hex, input[3:0] gain);
	always @*
	casez(gain)
		4'h7: hex = 7'b1111000;
		4'h6: hex = 7'b0000010;
		4'h5: hex = 7'b0010010;
		4'h4: hex = 7'b0011001;
		4'h3: hex = 7'b0110000;
		4'h2: hex = 7'b0100100;
		4'h1: hex = 7'b1111001;
		4'h0: hex = 7'b1000000;
		4'hF: hex = 7'b0001000;
		4'hE: hex = 7'b0000011;
		4'hD: hex = 7'b0100111;
		4'hC: hex = 7'b0100001;
		4'hB: hex = 7'b0000110;
		4'hA: hex = 7'b0001110;
		4'h9: hex = 7'b1000010;
		4'h8: hex = 7'b0111111;
	endcase
endmodule
