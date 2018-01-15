module status_hex(output reg[6:0] hex, input lsource_ready, input rsource_ready, input lsink_valid, input rsink_valid);
	always @*
	begin
		hex = {1'b1, lsink_valid, lsource_ready, 1'b1, rsource_ready, rsink_valid, 1'b1};
	end
endmodule
