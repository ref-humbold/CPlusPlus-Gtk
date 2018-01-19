module gain_led(output reg[9:0] led, input[3:0] gain);
	always @*
	casez(gain)
		4'h7: led = 10'b0011111111;
		4'h6: led = 10'b0001111111;
		4'h5: led = 10'b0000111111;
		4'h4: led = 10'b0000011111;
		4'h3: led = 10'b0000001111;
		4'h2: led = 10'b0000000111;
		4'h1: led = 10'b0000000011;
		4'h0: led = 10'b1000000001;
		4'hF: led = 10'b1100000000;
		4'hE: led = 10'b1110000000;
		4'hD: led = 10'b1111000000;
		4'hC: led = 10'b1111100000;
		4'hB: led = 10'b1111110000;
		4'hA: led = 10'b1111111000;
		4'h9: led = 10'b1111111100;
		4'h8: led = 10'b0000000000;
	endcase
endmodule
