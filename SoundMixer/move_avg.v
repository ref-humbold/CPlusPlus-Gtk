module move_avg(output reg[23:0] out_data, input[23:0] in_data, input clk);
	wire[23:0] conn01;
	wire[23:0] conn12;
	wire[23:0] conn23;
	wire[23:0] conn34;
	wire[23:0] conn4x;
	
	delay d0(conn01, clk, in_data);
	delay d1(conn12, clk, conn01);
	delay d2(conn23, clk, conn12);
	delay d3(conn34, clk, conn23);
	delay d4(conn4x, clk, conn34);
	
	always @(posedge clk)
	begin
		// out_data <= 
	end
endmodule
