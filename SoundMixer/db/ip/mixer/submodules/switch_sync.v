module switch_sync(output reg out, input clk, input data);
	always @(posedge clk)
	begin
		out <= data;
	end
endmodule
