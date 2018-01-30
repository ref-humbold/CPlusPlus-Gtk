module delay_signal(output reg[23:0] out, input clk, input[23:0] data, input wren);
	always @(posedge clk)
	begin
		if(wren)
			out <= data;
	end
endmodule
