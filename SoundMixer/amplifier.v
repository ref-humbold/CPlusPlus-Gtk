module amplifier(output reg[23:0] out_data, output reg out_valid, input out_ready, input[23:0] in_data, input in_valid, input clk, input reset, input[3:0] gain);
	always @(posedge clk or posedge reset)
	if(reset)
	begin
		out_data <= 0;
		out_valid <= 1'b0;
	end
	else if(in_valid & out_ready)
	begin
		casez(gain)
			4'b1000: out_data <= 0;
			4'b0000: out_data <= $signed(in_data);
			default: out_data <= $signed(in_data) + ($signed(in_data) >>> 3) * $signed(gain);
		endcase
		
		out_valid <= 1'b1;
	end
	else
	begin
		out_data <= 0;
		out_valid <= 1'b0;
	end
endmodule
