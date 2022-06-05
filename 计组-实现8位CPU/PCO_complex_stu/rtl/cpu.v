/*CPU*/
//省略号中是自行设计的控制信号，需要自行补充
module cpu(data_in,clk_quick,clk_slow,clk_delay,rst,SW_choose,A1,cpustate,addr,data_out,write,acdbus,rdbus,zdbus,pcinc,alus,pcload,drload,pcbus,drlbus,drhbus,irload,irbus,membus,busmem,read,trload,trbus,arload,rbus,rload,acload,acbus,zload,zbus,clr);
// 哈这到底要输出什么啊救命，说好的控制信号呢
input[7:0] data_in;
input clk_quick,clk_slow,clk_delay;
input rst;
input SW_choose,A1;
input [1:0] cpustate;

output [15:0] addr;//不懂这是什么好像是输出ar里的地址到M里去
output [7:0] data_out;
output [7:0] acdbus;//AC寄存器的输出
output [7:0] rdbus;//R寄存器的输出
output [7:0] zdbus;//R寄存器的输出
output [3:0] alus;
output pcload,drload,pcbus,pcinc,drlbus,drhbus,irload,membus,busmem,read,write,trload,trbus,arload,rbus,rload,acload,acbus,zload,zbus,irbus,clr;
//补充自行设计的控制信号的端口说明，都是output

wire [3:0] alus;
wire clk_choose,clk_run;
wire[15:0] dbus,pcdbus;
wire[7:0]drdbus,trdbus,rdbus,acdbus,irdbus,ardbus,aluout,zdbus;

//定义一些需要的内部信号

//qtsj(clk_quick,clk_slow,clk_delay,clr,rst,SW_choose,A1,cpustate,clk_run,clk_choose);qtsj实例化
qtsj qtdl(.clk_quick(clk_quick),.clk_slow(clk_slow),.clk_delay(clk_delay),.clr(clr),.rst(rst),.SW_choose(SW_choose),.A1(A1),.cpustate(cpustate),.clk_run(clk_run),.clk_choose(clk_choose));
//ar(din, clk, rst,arload, arinc, dout);ar实例化
ar mar(.din(dbus),.clk(clk_choose),.rst(rst),.arload(arload),.dout(addr));
//pc(din, clk, rst,pcload, pcinc, dout);pc实例化
pc mpc(.din(dbus),.clk(clk_choose),.rst(rst),.pcload(pcload),.pcinc(pcinc),.dout(pcdbus));
//dr(din, clk,rst, drload, dout);补充dr实例化语句
dr mdr(.din(dbus[7:0]),.clk(clk_choose),.rst(rst),.drload(drload),.dout(drdbus));

//tr(din, clk,rst, trload, dout);补充tr实例化语句，如果需要tr的话
tr mtr(.din(dbus[7:0]),.clk(clk_choose),.rst(rst),.trload(trload),.dout(trdbus));

//ir(din,clk,rst,irload,dout);补充ir实例化语句
ir mir(.din(drdbus),.clk(clk_choose),.rst(rst),.irload(irload),.dout(irdbus));

//r(din, clk, rst,rload, dout);补充r实例化语句
r mr(.din(dbus[7:0]),.clk(clk_choose),.rst(rst),.rload(rload),.dout(rdbus));

//ac(din, clk, rst,acload, dout);补充ac实例化语句
ac mac(.din(dbus[7:0]),.clk(clk_choose),.rst(rst),.acload(acload),.dout(acdbus));

//alu(alus,ac, bus, dout);补充alu实例化语句
alu malu(.alus(alus),.ac(acdbus),.bus(dbus[7:0]),.dout(aluout));

//z(din,clk,rst, zload,dout);补充z实例化语句，如果需要的话
z mz(.din(aluout),.clk(clk_choose),.rst(rst),.zload(zload),.dout(zdbus));

//control(din,clk,rst,z,cpustate,read,...,clr);补充control实例化语句
control mcontrol(.din(irdbus),.clk(clk_run),.rst(rst),.z(zdbus),.cpustate(cpustate),.alus(alus),.read(read),.write(write),.pcinc(pcinc),.pcload(pcload),.drload(drload),.pcbus(pcbus),.drlbus(drlbus),.drhbus(drhbus),.irload(irload),.irbus(irbus),.membus(membus),.busmem(busmem),.trload(trload),.trbus(trbus),.arload(arload),.rbus(rbus),.rload(rload),.acload(acload),.acbus(acbus),.zload(zload),.zbus(zbus),.clr(clr));

//allocate dbus
assign dbus[15:0]=(pcbus)?pcdbus[15:0]:16'bzzzzzzzzzzzzzzzz;
assign dbus[15:8]=(drhbus)?drdbus[7:0]:8'bzzzzzzzz;
assign dbus[7:0]=(drlbus)?drdbus[7:0]:8'bzzzzzzzz;
assign dbus[7:0]=(trbus)?trdbus[7:0]:8'bzzzzzzzz;
assign dbus[7:0]=(acbus)?acdbus[7:0]:8'bzzzzzzzz;
assign dbus[7:0]=(rbus)?rdbus[7:0]:8'bzzzzzzzz;
assign dbus[7:0]=(zbus)?zdbus[7:0]:8'bzzzzzzzz;
//如果需要tr的话，补充dbus接收tr的输出trdbus

  
//如果没有存储器-寄存器传送指令，可通过如下方式为ac和r赋值
//assign dbus[7:0]=(rbus)?((alus==7'd1)?8'b00000001:rdbus[7:0]):8'bzzzzzzzz;
//assign dbus[7:0]=(acbus)?((alus==7'd1)?8'b00000010:acdbus[7:0]):8'bzzzzzzzz;
//如果有存储器-寄存器传送指令，则通过如下方式为ac和r赋值
assign dbus[7:0]=(rbus)?rdbus[7:0]:8'bzzzzzzzz;
assign dbus[7:0]=(acbus)?acdbus[7:0]:8'bzzzzzzzz;

assign dbus[7:0]=(membus)?data_in[7:0]:8'bzzzzzzzz;
assign data_out=(busmem)?dbus[7:0]:8'bzzzzzzzz;



endmodule
