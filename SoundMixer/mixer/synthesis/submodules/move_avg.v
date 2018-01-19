module move_avg(output reg[23:0] out_data, output reg out_valid, input out_ready, input[23:0] in_data, input in_valid, input clk, input reset, input switch);
	wire[23:0] conn01;
	wire[23:0] conn12;
	wire[23:0] conn23;
	wire[23:0] conn34;
	wire[23:0] conn45;
	wire[23:0] conn56;
	wire[23:0] conn6x;
	
	delay d0(conn01, clk, in_data);
	delay d1(conn12, clk, conn01);
	delay d2(conn23, clk, conn12);
	delay d3(conn34, clk, conn23);
	delay d4(conn45, clk, conn34);
	delay d5(conn56, clk, conn45);
	delay d6(conn6x, clk, conn56);
	
	always @(posedge clk)
	if(reset)
	begin
		out_data <= 0;
		out_valid <= 1'b0;
	end
	else if(in_valid & out_ready)
	begin
		if(switch)
		begin
			out_data <= ($signed(conn01) + $signed(conn12) + $signed(conn23) + $signed(conn34) + $signed(conn45) + $signed(conn56) + $signed(conn6x)) / $signed(7);
			out_valid <= 1'b1;
		end
		else
		begin
			out_data <= $signed(conn6x);
			out_valid <= 1'b1;
		end
	end
	else
	begin
		out_data <= 0;
		out_valid <= 1'b0;
	end
endmodule
