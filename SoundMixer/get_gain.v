module get_gain(output reg[3:0] gain, input clk, input[1:0] change);
	always @(posedge clk)
	case(change)
		2'b10: gain <= gain == 4'b0101 ? gain : gain - 1;
		2'b01: gain <= gain == 4'b1000 ? gain : gain + 1;
		default: gain <= gain;
	endcase
endmodule
