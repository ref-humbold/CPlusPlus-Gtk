module move_avg (output reg[23:0] out_data, output reg out_valid, input out_ready, input[23:0] in_data, input in_valid, input clk, input reset, input filter_on);
	wire[23:0] conn[5:0];
	
	delay d0(conn[0], clk, in_data);
	delay d1(conn[1], clk, conn[0]);
	delay d2(conn[2], clk, conn[1]);
	delay d3(conn[3], clk, conn[2]);
	delay d4(conn[4], clk, conn[3]);
	delay d5(conn[5], clk, conn[4]);
	
	always @(posedge clk)
	if(reset)
	begin
		out_data <= 0;
		out_valid <= 1'b0;
	end
	else if(in_valid & out_ready)
	begin
		if(filter_on)
		begin
			out_data <= (($signed(conn[0]) + $signed(conn[1]) + $signed(conn[2])) / $signed(3)
							+ ($signed(conn[3]) + $signed(conn[4]) + $signed(conn[5])) / $signed(3))
							/ $signed(2);
			out_valid <= 1'b1;
		end
		else
		begin
			out_data <= $signed(in_data);
			out_valid <= 1'b1;
		end
	end
	else
	begin
		out_data <= 0;
		out_valid <= 1'b0;
	end
endmodule
