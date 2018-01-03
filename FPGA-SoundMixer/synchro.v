module synchro(output reg out, input clk, input data);
	reg old = 0;
	
	always @(posedge clk)
	begin
		out <= data ? data != old : 0;
		old <= data;
	end
endmodule
