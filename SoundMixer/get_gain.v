module get_gain(output reg[3:0] gain, input clk, input up, input down);
	always @(posedge clk)
	if(up & ~down)
		gain <= gain == 4'b0111 ? gain : gain + 4'b0001;
	else if(down & ~up)
		gain <= gain == 4'b1000 ? gain : gain - 4'b0001;
	else
		gain <= gain;
endmodule
