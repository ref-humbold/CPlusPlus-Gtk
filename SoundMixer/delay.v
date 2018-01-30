module delay(output reg[23:0] out_data, output reg out_valid, input[23:0] in_data, input wren, input clk, input reset, input on);
	localparam D = 4096;
	wire[23:0] conn[D:0];
	assign conn[0] = in_data;
	genvar i;
	
	generate
		for(i = 0; i < D; i = i + 1)
		begin: delay_gen
			delay_signal d(conn[i + 1], clk, conn[i], wren);
		end
	endgenerate
	
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
			out_data <= ($signed(conn[1]) >>> 1) + ($signed(conn[D]) >>> 1);
			out_valid <= 1'b1;
		end
		else
		begin
			out_data <= $signed(conn[1]);
			out_valid <= 1'b1;
		end
	end
	else
	begin
		out_data <= $signed(in_data);
		out_valid <= 1'b0;
	end
endmodule
