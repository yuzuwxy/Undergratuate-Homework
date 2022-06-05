/*指令寄存器，存储要执行的指令*/
//注意：该寄存器是时钟的下降沿有效
/*输入din：指令输入；8位，来自于数据寄存器
   输入clk：时钟信号，进行时序控制；1位，来自qtsj.v的输出clk_choose；
   输入rst：复位信号，该位为1时系统正常工作，为0时系统复位；1位，来自控制器；
   输入irload：载入信号，该位为1时该部件工作，为0时该部件不工作；1位，来自控制器；
   输出dout：指令输出；实际上不与总线或其他部件相连
*/
module ir(din,clk,rst,irload,dout);
input[7:0] din;
input clk,rst,irload;
output [7:0]dout;
reg [7:0]dout;
always@(negedge clk or negedge rst)
if(!rst)
	dout<=0;
else if(irload)
	dout<=din;
endmodule