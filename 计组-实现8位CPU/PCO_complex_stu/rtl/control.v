/*组合逻辑控制单元，根据时钟生成为控制信号和内部信号*/
/*
输入：
       din：指令，8位，来自IR；
       clk：时钟信号，1位，上升沿有效；
       rst：复位信号，1位，与cpustate共同组成reset信号；
       cpustate：当前CPU的状态（IN，CHECK，RUN），2位；
       z：零标志，1位，零标志寄存器的输出，如果指令中涉及到z，可加上，否则可去掉；
输出：
      clr：清零控制信号
     自行设计的各个控制信号
*/
//省略号中是自行设计的控制信号，需要自行补充，没用到z的话也可去掉z
module control(din,clk,rst,z,cpustate,alus,pcload,drload,pcbus,pcinc,drlbus,drhbus,irload,membus,busmem,write,read,trload,trbus,arload,rbus,rload,acload,acbus,zload,zbus,irbus,clr);
input [7:0]din;
input clk;
input rst,z;
input [1:0] cpustate;

output write,pcload,drload,pcbus,pcinc,drlbus,drhbus,irload,membus,busmem,read,trload,trbus,arload,rbus,rload,acload,acbus,zload,zbus,irbus,clr;
output reg [3:0] alus;
//parameter's define
/*-------*/
wire reset;
/*-------*/
//在下方加上自行定义的状态
wire fetch1,fetch2,fetch3,nop1,ldac1,ldac2,ldac3,ldac4,ldac5,stac1,stac2,stac3,stac4,stac5,movac1,movr1,jump1,jump2,jump3,jump4;
wire jmpz1,jmpz2,jmpz3,jmpz4,jpnz1,jpnz2,jpnz3,jpnz4,add1,add2,sub1,sub2,iinac1,iinac2,clac1,clac2,and1,and2,or1,or2,xor1,xor2,not1,not2;

//加上自行设计的指令，这里是译码器的输出，所以nop指令经译码器输出后为inop。
//类似地，add指令指令经译码器输出后为iadd；inac指令经译码器输出后为iinac，......
reg inop,ildac,istac,imovac,imovr,ijump,ijmpz,ijpnz,iadd,isub,iinac,iclac,iand,ior,ixor,inot;

//时钟节拍，8个为一个指令周期，t0-t2分别对应fetch1-fetch3，t3-t7分别对应各指令的执行周期，当然不是所有指令都需要5个节拍的。例如add指令只需要一个t3
reg t0,t1,t2,t3,t4,t5,t6,t7; 

// signals for the counter, 内部信号：clr清零，inc自增
wire clr;
wire inc;
assign reset = rst&(cpustate == 2'b11);
// assign signals for the cunter

//clr信号是每条指令执行完毕后必做的清零，下面赋值语句要修改，需要“或”各指令的最后一个周期
assign clr=nop1||ldac5||stac5||movac1||movr1||jump4||(z&&jmpz4)||((!z)&&jpnz4)||((!z)&&jmpz3)||(z&&jpnz3)||add2||sub2||iinac2||clac2||and2||or2||xor2||not2;
assign inc=~clr;
	
//generate the control signal using state information
//...
//取公过程
assign fetch1=t0;
assign fetch2=t1;
assign fetch3=t2;
//各指令状态的表达式
assign nop1=inop&&t3;//inop表示nop指令，nop1是nop指令的执行周期的第一个状态也是最后一个状态，因为只需要1个节拍t3完成
assign ldac1=ildac&&t3,ldac2=ildac&&t4,ldac3=ildac&&t5,ldac4=ildac&&t6,ldac5=ildac&&t7;
assign stac1=istac&&t3,stac2=istac&&t4,stac3=istac&&t5,stac4=istac&&t6,stac5=istac&&t7;
assign movac1=imovac&&t3;
assign movr1=imovr&&t3;
assign jump1=ijump&&t3,jump2=ijump&&t4,jump3=ijump&&t5,jump4=ijump&&t6;
assign jmpz1=ijmpz&&t3,jmpz2=ijmpz&&t4,jmpz3=ijmpz&&t5,jmpz4=ijmpz&&t6&&(z);
assign jpnz1=ijpnz&&t3,jpnz2=ijpnz&&t4,jpnz3=ijpnz&&t5,jpnz4=ijpnz&&t6&&(!z);
assign add1=iadd&&t3,add2=iadd&&t4;
assign sub1=isub&&t3,sub2=isub&&t4;
assign iinac1=iinac&&t3,iinac2=iinac&&t4;
assign clac1=iclac&&t3,clac2=iclac&&t4;
assign and1=iand&&t3,and2=iand&&t4;
assign or1=ior&&t3,or2=ior&&t4;
assign xor1=ixor&&t3,xor2=ixor&&t4;
assign not1=inot&&t3,not2=inot&&t4;

//the next grade assign
//以下给出了pcbus的逻辑表达式，写出其他控制信号的逻辑表达式
assign irbus=0;
assign pcbus=fetch1||fetch3||ldac2||stac2||jump2||jmpz2||jpnz2;
assign pcload=jump4||jmpz4||jpnz4;
assign arload=fetch1||fetch3||ldac2||ldac4||stac2||stac4||jump2||jmpz2||jpnz2;
assign read=fetch2||ldac1||ldac3||ldac5||stac1||stac3||jump1||jump3||jmpz1||jmpz3||jpnz1||jpnz3;
assign write=stac5;
assign membus=fetch2||ldac1||ldac3||ldac5||stac1||stac3||jump1||jump3||jmpz1||jmpz3||jpnz1||jpnz3;
assign busmem=stac5;
assign drload=fetch2||ldac1||stac1||jump1||jmpz1||jpnz1;
assign drhbus=ldac4||stac4||jump4||jmpz4||jpnz4;
assign drlbus=0;
assign pcinc=fetch2||ldac1||ldac3||stac1||stac3||jump1||jump3||jmpz1||jmpz3||jpnz1||jpnz3;
assign irload=fetch3;
assign trload=ldac3||stac3||jump3||jmpz3||jpnz3;
assign trbus=ldac4||stac4||jump4||jmpz4||jpnz4;
assign acload=ldac5||add2||sub2||iinac2||clac2||or2||xor2||and2||not2;
assign acbus=stac5||movac1||movr1;
assign rload=movac1;
assign rbus=movr1||and1||sub1||or1||add1||xor1||not1||iinac1;
assign zload=add1||sub1||iinac1||clac1||or1||xor1||and1||not1;
assign zbus=sub2||iinac2||clac2||and2||or2||add2||xor2||not2;

//the finite state

always@(posedge clk or negedge reset)
begin
if(!reset)
	begin//各指令清零，以下已为nop指令清零，请补充其他指令，为其他指令清零
		inop<=0;
		ildac<=0;
		istac<=0;
		imovac<=0;
		imovr<=0;
		ijump<=0;
		ijmpz<=0;
		ijpnz<=0;
		iadd<=0;
		isub<=0;
		iinac<=0;
		iclac<=0;
		iand<=0;
		ior<=0;
		ixor<=0;
		inot<=0;
	end
else 
begin
	//alus初始化为x，加上将alus初始化为x的语句，后续根据不同指令为alus赋值//
	alus=4'bxxxx;
	if(din[7:4]==0000)//译码处理过程
	begin
		case(din[3:0])
		0:  begin//指令低4位为0，应该是nop指令，因此这里inop的值是1，而其他指令应该清零，请补充为其他指令清零的语句
			inop<=1;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		1:  begin
			//指令低4位为0001，应该是ildac指令，因此ildac指令为1，其他指令都应该是0。
			//该指令需要做一个加0运算，详见《示例机的设计Quartus II和使用说明文档》中“ALU的设计”，因此这里要对alus赋值
			//后续各分支类似，只有一条指令为1，其他指令为0，以下分支都给出nop指令的赋值，需要补充其他指令，注意涉及到运算的都要对alus赋值
			inop<=0;
			ildac<=1;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		2:  begin
			inop<=0;
			ildac<=0;
			istac<=1;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		3:  begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=1;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		4:  begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=1;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		5:  begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=1;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		6:	 begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=1;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		7:	 begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=1;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			end
		8:	 begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=1;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			alus=4'b0000;
			end
		9:	 begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=1;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			alus=4'b0001;
			end
		10: begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=1;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			alus=4'b0010;
			end
		11: begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=1;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=0;
			alus=4'b0011;
			end
		12: begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=1;
			ior<=0;
			ixor<=0;
			inot<=0;
			alus=4'b0100;
			end
		13: begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=1;
			ixor<=0;
			inot<=0;
			alus=4'b0101;
			end
		14: begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=1;
			inot<=0;
			alus=4'b0110;
			end
		15: begin
			inop<=0;
			ildac<=0;
			istac<=0;
			imovac<=0;
			imovr<=0;
			ijump<=0;
			ijmpz<=0;
			ijpnz<=0;
			iadd<=0;
			isub<=0;
			iinac<=0;
			iclac<=0;
			iand<=0;
			ior<=0;
			ixor<=0;
			inot<=1;
			alus=4'b0111;
			end	
		endcase
	end
end
end

/*——————8个节拍t0-t7————*/
always @(posedge clk or negedge reset)
begin
if(!reset) //reset清零
begin
	t0<=1;
	t1<=0;
	t2<=0;
	t3<=0;
	t4<=0;
	t5<=0;
	t6<=0;
	t7<=0;
end
else
begin
	if(inc) //运行
	begin
	t7<=t6;
	t6<=t5;
	t5<=t4;
	t4<=t3;
	t3<=t2;
	t2<=t1;
	t1<=t0;
	t0<=0;
	end
	else if(clr) //清零
	begin
	t0<=1;
	t1<=0;
	t2<=0;
	t3<=0;
	t4<=0;
	t5<=0;
	t6<=0;
	t7<=0;
	end
end

end
/*—————结束—————*/
endmodule
	
		