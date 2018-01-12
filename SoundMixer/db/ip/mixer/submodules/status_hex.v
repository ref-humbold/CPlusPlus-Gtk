module status_hex(output reg[6:0] hex, input lsource_ready, input rsource_ready, input lsink_valid, input rsink_valid);
	always @*
	casez({lsink_valid, lsource_ready, rsource_ready, rsink_valid})
		4'hF: hex = 7'b1001001;
		4'hE: hex = 7'b1001011;
		4'hD: hex = 7'b1001101;
		4'hC: hex = 7'b1001111;
		4'hB: hex = 7'b1011001;
		4'hA: hex = 7'b1011011;
		4'h9: hex = 7'b1011101;
		4'h8: hex = 7'b1011111;
		4'h7: hex = 7'b1101001;
		4'h6: hex = 7'b1101011;
		4'h5: hex = 7'b1101101;
		4'h4: hex = 7'b1101111;
		4'h3: hex = 7'b1111001;
		4'h2: hex = 7'b1111011;
		4'h1: hex = 7'b1111101;
		4'h0: hex = 7'b1111111;
	endcase
endmodule
