/*数据暂存器,处理双字节指令时使用，用来存储低八位的地址或数值*/
/*输入din：数据输入；8位，来自于总线的低八位
   输入clk：时钟信号，进行时序控制；1位，来自qtsj.v的输出clk_choose；
   输入rst：复位信号，该位为1时系统正常工作，为0时系统复位；1位，来自控制器；
   输入trload：载入信号，该位为1时该部件工作，为0时该部件不工作；1位，来自控制器；
   输出dout：数据输出；8位，送往总线的低八位；
*/
module tr(din, clk,rst, trload, dout);
input[7:0] din;
input clk,rst,trload;
output [7:0]dout;
reg [7:0]dout;
always@(posedge clk or negedge rst)
if(!rst)
	dout<=0;
else if(trload)
	dout<=din;
endmodule