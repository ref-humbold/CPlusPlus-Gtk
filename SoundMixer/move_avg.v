module move_avg (output reg[23:0] out_data, output reg out_valid, input[23:0] in_data, input wren, input clk, input reset, input on);
	wire[23:0] conn[8:0];
	
	delay_signal d0(conn[0], clk, in_data, wren);
	delay_signal d1(conn[1], clk, conn[0], wren);
	delay_signal d2(conn[2], clk, conn[1], wren);
	delay_signal d3(conn[3], clk, conn[2], wren);
	delay_signal d4(conn[4], clk, conn[3], wren);
	delay_signal d5(conn[5], clk, conn[4], wren);
	delay_signal d6(conn[6], clk, conn[5], wren);
	delay_signal d7(conn[7], clk, conn[6], wren);
	
	always @(posedge clk)
	if(reset)
	begin
		out_data <= 0;
		out_valid <= 1'b0;
	end
	else if(wren)
	begin
		if(on)
		begin
			out_data <= ((((($signed(conn[0]) + $signed(conn[1])) >>> 1)
							+ (($signed(conn[2]) + $signed(conn[3])) >>> 1)) >>> 1)
							+ (((($signed(conn[4]) + $signed(conn[5])) >>> 1)
							+ (($signed(conn[6]) + $signed(conn[7])) >>> 1)) >>> 1)) >>> 1;
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
