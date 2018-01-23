module delay_signal(output reg[23:0] out, input clk, input[23:0] data);
	always @(posedge clk)
	begin
		out <= data;
	end
endmodule
