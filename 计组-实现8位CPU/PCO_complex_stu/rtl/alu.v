/*算术逻辑单元*/
module alu(alus,ac, bus, dout);
input [3:0] alus;
input [7:0] ac,bus;
output reg [7:0] dout;

always@(ac or bus or alus)
begin
case(alus[3:0])
	4'b0000:
		begin 
		dout <= ac + bus;
		end
	4'b0001:
		begin
		dout <= ac - bus;
		end
	4'b0010:
		begin
		dout <= ac + 8'b00000001;
		end
	4'b0011:
		begin
		dout <= 8'b00000000;
		end
	4'b0100:
		begin	
		dout <= ac & bus;
		end
	4'b0101:
		begin	
		dout <= ac | bus;
		end
	4'b0110:
		begin	
		dout <= ac ^ bus;
		end
	4'b0111:
		begin
		dout <= ~ac;
		end
	default:
		begin	
		dout <= ac;
		end
endcase
end
endmodule
