/*#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
Uint16 temp =0;
//
void gpio_init(void)
{
 EALLOW;
 GpioCtrlRegs.GPBMUX2.all=0x0000;
 GpioCtrlRegs.GPBDIR.bit.GPIO51=1;	//48 49 50 51三列
 GpioCtrlRegs.GPBDIR.bit.GPIO50=1;
 GpioCtrlRegs.GPBDIR.bit.GPIO49=1;
 GpioCtrlRegs.GPBDIR.bit.GPIO48=1;
 GpioCtrlRegs.GPBPUD.bit.GPIO54=0; 	//54 55 56 57三行
 GpioCtrlRegs.GPBPUD.bit.GPIO55=0;
 GpioCtrlRegs.GPBPUD.bit.GPIO56=0;
 GpioCtrlRegs.GPBPUD.bit.GPIO57=0;
// GpioCtrlRegs.GPBPUD.bit.GPIO51=0;
 GpioCtrlRegs.GPBDIR.bit.GPIO54=0;
 GpioCtrlRegs.GPBDIR.bit.GPIO55=0;
 GpioCtrlRegs.GPBDIR.bit.GPIO56=0;
 GpioCtrlRegs.GPBDIR.bit.GPIO57=0;
// GpioCtrlRegs.GPBDIR.bit.GPIO51=0;
//GpioCtrlRegs.GPAMUX1.all=0x0000;
//GpioCtrlRegs.GPADIR.all=0xffff;
 EDIS;
}
void delay2(void)
{
 long int i,j;
 for(i=0;i<40;i++)
  for(j=0;j<20;j++);
}

void delay1(void)
{
 long int i,j;
 for(i=0;i<200;i++)
  for(j=0;j<400;j++);
}
void all_on(void)
{
	 GpioDataRegs.GPBCLEAR.bit.GPIO51=1;
	 GpioDataRegs.GPBCLEAR.bit.GPIO50=1;
	 GpioDataRegs.GPBCLEAR.bit.GPIO49=1;
	 GpioDataRegs.GPBCLEAR.bit.GPIO48=1;
}
Uint16 matrix_key(void)
{
	Uint16 m;
	temp = 0;
	 all_on();
	 if(GpioDataRegs.GPBDAT.bit.GPIO54==0)
	 {
		  delay1();
		  if(GpioDataRegs.GPBDAT.bit.GPIO54==0)
		  {
			  GpioDataRegs.GPBSET.bit.GPIO48=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO54==1)
				  temp=1;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO49=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO54==1)
				  temp=2;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO50=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO54==1)
				  temp=3;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO51=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO54==1)
				  temp=4;
			  else temp=temp;
		  }
		 }
		 all_on();
	 if(GpioDataRegs.GPBDAT.bit.GPIO55==0)
	 {
		  delay1();
		  if(GpioDataRegs.GPBDAT.bit.GPIO55==0)
		  {
			  GpioDataRegs.GPBSET.bit.GPIO48=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO55==1)
				  temp=5;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO49=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO55==1)
				  temp=6;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO50=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO55==1)
				  temp=7;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO51=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO55==1)
				  temp=8;
			  else temp=temp;
		  }
	 }
	 all_on();
	 if(GpioDataRegs.GPBDAT.bit.GPIO56==0)
	 {
		  delay1();
		  if(GpioDataRegs.GPBDAT.bit.GPIO56==0)
		  {
			  GpioDataRegs.GPBSET.bit.GPIO48=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO56==1)
				  temp=9;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO49=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO56==1)
				  temp=10;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO50=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO56==1)
				  temp=11;
			  else temp=temp;
			  all_on();
			  GpioDataRegs.GPBSET.bit.GPIO51=1;
			  delay2();
			  if(GpioDataRegs.GPBDAT.bit.GPIO56==1)
				  temp=12;
			  else temp=temp;
		  }
	 }
	 all_on();
	 	 if(GpioDataRegs.GPBDAT.bit.GPIO57==0)
	 	 {
	 		  delay1();
	 		  if(GpioDataRegs.GPBDAT.bit.GPIO57==0)
	 		  {
	 			  GpioDataRegs.GPBSET.bit.GPIO48=1;
	 			  delay2();
	 			  if(GpioDataRegs.GPBDAT.bit.GPIO57==1)
	 				  temp=13;
	 			  else temp=temp;
	 			  all_on();
	 			  GpioDataRegs.GPBSET.bit.GPIO49=1;
	 			  delay2();
	 			  if(GpioDataRegs.GPBDAT.bit.GPIO57==1)
	 				  temp=14;
	 			  else temp=temp;
	 			  all_on();
	 			  GpioDataRegs.GPBSET.bit.GPIO50=1;
	 			  delay2();
	 			  if(GpioDataRegs.GPBDAT.bit.GPIO57==1)
	 				  temp=15;
	 			  else temp=temp;
	 			  all_on();
	 			  GpioDataRegs.GPBSET.bit.GPIO51=1;
	 			  delay2();
	 			  if(GpioDataRegs.GPBDAT.bit.GPIO57==1)
	 				  temp=16;
	 			  else temp=temp;
	 		  }
	 	 }
	return temp;
}*/

/********************************************************************
* 文件名： 	按键扫描程序
* 描述:  	运行程序，按下按键，观测变量Key的值（该值从从1~9)。

**********************************************************************/
/********************************************************************
程序说明：按键扫描原理：1、3列对应的IO设置为输出,3行对应的IO设置为输入。
					2、若无按键按下，3行输入IO，均为高电平（因为有外部上拉电阻）
					3、若按键按下，对应行IO被拉低（假设为第X行），检测为低电平。按键所在行（X行），被鉴别出来。
					4、此时，依次改变3列的输出为高，当遇到按键所在列时，第X行电平重新变为高。按键所在列。被鉴别出来。
********************************************************************/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

/**************************************宏定义************************************************/
/*#define SET_KY4			GpioDataRegs.GPBSET.bit.GPIO51 = 1						//Y4拉高
#define RST_KY4			GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1						//Y4拉低
#define SET_KY3			GpioDataRegs.GPBSET.bit.GPIO50 = 1						//Y3拉高
#define RST_KY3			GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1						//Y3拉低
#define SET_KY2			GpioDataRegs.GPBSET.bit.GPIO49 = 1						//Y2拉高
#define RST_KY2			GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1						//Y2拉低
#define SET_KY1			GpioDataRegs.GPBSET.bit.GPIO48 = 1						//Y1拉高
#define RST_KY1			GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1						//Y1拉低

#define KX4_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO57							//X4状态
#define KX3_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO56							//X3状态
#define KX2_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO55							//X2状态
#define KX1_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO54							//X1状态

/**************************************函数声明************************************************/
/*void Init_KeyGpio(void);							//初始化按键IO
void delay(Uint32 t);								//延时函数
void ResetAllKY(void);								//4列全部输出低电平
void KX_AllStatus(void);							//读取4行IO电平状态
void Read_KX(Uint16 x);								//读取按键所在行
void Set_KY(Uint16 x);								//设置任意列输出高电平
void Rst_KY(Uint16 x);								//设置任意列输出低电平
void Read_KY(Uint16 x);								//读取按键所在列
/**************************************变量定义************************************************/
Uint16 Keys[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};//数据表，与16个按键对应
Uint16 Key = 0;												//实时按键信息变量
extern Uint16 Read_Key;
Uint16 KX_On = 0;
Uint16 KX_Tim[5] = {0};
Uint16 KX_Status[5]={0};
Uint16 KY_On = 0;
/*****************************************************************************************************/
/*********************************************延时函数************************************************/
/*void delay(Uint32 t)
{
	Uint32 i = 0;
	for (i = 0; i < t; i++);
}


//4列全部输出低电平
void ResetAllKY(void)
{
	RST_KY4	;
	RST_KY3	;
	RST_KY2	;
	RST_KY1	;
}

//读取4行IO电平状态
void KX_AllStatus(void)
{
	KX_Status[1] = KX1_STATUS;
	KX_Status[2] = KX2_STATUS;
	KX_Status[3] = KX3_STATUS;
	KX_Status[4] = KX4_STATUS;
}


//读取按键行位置
void Read_KX(Uint16 x)
{
	KX_AllStatus();
	if(KX_Status[x] == 0)
	{
		 KX_Tim[x]++;
		 if(KX_Tim[x] >= 6000)
		 {
			 KX_On = x;
			 KX_Tim[1]= 0;
			 KX_Tim[2]=0;
			 KX_Tim[3]=0;
			 KX_Tim[4]=0;
		 }
	}
}

//指定列输出高电平
void Set_KY(Uint16 x)
{
	if(x==1){SET_KY1;}
	if(x==2){SET_KY2;}
	if(x==3){SET_KY3;}
	if(x==4){SET_KY4;}
}

//指定列输出低电平
void Rst_KY(Uint16 x)
{
	if(x==1){RST_KY1;}
	if(x==2){RST_KY2;}
	if(x==3){RST_KY3;}
	if(x==4){RST_KY4;}
}

//读取按键列位置
void Read_KY(Uint16 x)
{

	if(!KX_Status[KX_On] && KX_On)
	{
		Set_KY(x);
		delay(200);
		KX_AllStatus();
		if(KX_Status[KX_On])
		{
			KY_On = x;
			Key = Keys[KX_On-1][KY_On-1];
			KY_On = 0;
			KX_On = 0;

		}
		Rst_KY(x);
	}
}


//按键IO初始化
void Init_KeyGpio(void)
{

	EALLOW;

	//////////////////////////////以下四个IO口设置为输出，作为列扫描////////////////////////////

//	KY4: 对应PCB端子 KEY_MATRIX：IO23
	GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;   									// Enable pullup on GPIO11
    GpioDataRegs.GPBSET.bit.GPIO51= 1;   									// Load output latch
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;  									// GPIO11 = GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;   									// GPIO11 = output

	//KY3: 对应PCB端子 KEY_MATRIX：IO24
	GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;   									// Enable pullup on GPIO11
    GpioDataRegs.GPBSET.bit.GPIO50 = 1;   									// Load output latch
    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;  									// GPIO11 = GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;   									// GPIO11 = output

	//KY2: 对应PCB端子 KEY_MATRIX：IO25
	GpioCtrlRegs.GPBPUD.bit.GPIO49 = 0;   									// Enable pullup on GPIO11
    GpioDataRegs.GPBSET.bit.GPIO49 = 1;   									// Load output latch
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;  									// GPIO11 = GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;   									// GPIO11 = output

	//KY1: 对应PCB端子 KEY_MATRIX：IO26
    GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;   									// Enable pullup on GPIO11
    GpioDataRegs.GPBSET.bit.GPIO48 = 1;   									// Load output latch
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;  									// GPIO11 = GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;   									// GPIO11 = output


	//////////////////////////////以下四个IO口设置为输入，作为行扫描////////////////////////////

	//KX4: 对应PCB端子 KEY_MATRIX：IO27
    GpioCtrlRegs.GPBPUD.bit.GPIO57= 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPBDIR.bit.GPIO57  = 0;   									// IO口方向为输入

	//KX3: 对应PCB端子 KEY_MATRIX：IO28
    GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPBDIR.bit.GPIO56  = 0;   									// IO口方向为输入

 	//KX2: 对应PCB端子 KEY_MATRIX：IO29
    GpioCtrlRegs.GPBPUD.bit.GPIO55= 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPBDIR.bit.GPIO55  = 0;   									// IO口方向为输入

	//KX1: 对应PCB端子 KEY_MATRIX：IO30
    GpioCtrlRegs.GPBPUD.bit.GPIO54= 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPBMUX2.bit.GPIO54  = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPBDIR.bit.GPIO54   = 0;   									// IO口方向为输入

    EDIS;
 	ResetAllKY();
}




Uint16 Key_Scan(void)
{
	Init_KeyGpio();
//	if(KX4_STATUS||KX3_STATUS||KX2_STATUS||KX1_STATUS !=0)
//	{
//		delay(50);
		if(KX4_STATUS||KX3_STATUS||KX2_STATUS||KX1_STATUS !=0)
		{
			Key = 0;
										//初始化拨码开关IO
			Read_KX(1);
			Read_KX(2);
			Read_KX(3);
			Read_KX(4);
			Read_KY(1);
			Read_KY(2);
			Read_KY(3);
			Read_KY(4);
		}
//	}
	return Key;

}
*/

//五键

#define KX5_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO61							//X5状态
#define KX4_STATUS	 	GpioDataRegs.GPADAT.bit.GPIO19							//X4状态
#define KX3_STATUS	 	GpioDataRegs.GPADAT.bit.GPIO17							//X3状态
#define KX2_STATUS	 	GpioDataRegs.GPBDAT.bit.GPIO62							//X2状态
#define KX1_STATUS	 	GpioDataRegs.GPADAT.bit.GPIO22							//X1状态

void Init_KeyGpio(void)
{

	EALLOW;
	//////////////////////////////以下四个IO口设置为输入，作为行扫描////////////////////////////
	//KX4: 对应PCB端子 KEY_MATRIX：IO27
	 GpioCtrlRegs.GPBPUD.bit.GPIO61= 0;   									// Enable pullup on GPIO11
	 GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;  									// 设置为一般IO口
	 GpioCtrlRegs.GPBDIR.bit.GPIO61  = 0;   									// IO口方向为输入

	//KX4: 对应PCB端子 KEY_MATRIX：IO27
    GpioCtrlRegs.GPAPUD.bit.GPIO19= 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPADIR.bit.GPIO19  = 0;   									// IO口方向为输入

	//KX3: 对应PCB端子 KEY_MATRIX：IO28
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPADIR.bit.GPIO17  = 0;   									// IO口方向为输入

 	//KX2: 对应PCB端子 KEY_MATRIX：IO29
    GpioCtrlRegs.GPBPUD.bit.GPIO62= 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPBDIR.bit.GPIO62  = 0;   									// IO口方向为输入

	//KX1: 对应PCB端子 KEY_MATRIX：IO30
    GpioCtrlRegs.GPAPUD.bit.GPIO22= 0;   									// Enable pullup on GPIO11
    GpioCtrlRegs.GPAMUX2.bit.GPIO22  = 0;  									// 设置为一般IO口
    GpioCtrlRegs.GPADIR.bit.GPIO22   = 0;   									// IO口方向为输入

    EDIS;
}
void KX_AllStatus(void)
{
	KX_Status[0] = KX1_STATUS;
	KX_Status[1] = KX2_STATUS;
	KX_Status[2] = KX3_STATUS;
	KX_Status[3] = KX4_STATUS;
	KX_Status[4] = KX5_STATUS;
}


//读取按键行位置
void Read_KX(Uint16 x)
{
	KX_AllStatus();
	if(KX_Status[x-1] == 0)
	{
		 KX_Tim[x-1]++;
		 if(KX_Tim[x-1] >= 6000)
		 {
			 Key = x;
			 KX_Tim[0]= 0;
			 KX_Tim[1]= 0;
			 KX_Tim[2]=0;
			 KX_Tim[3]=0;
			 KX_Tim[4]=0;
		 }
	}
}

void Key_Scan(void)
{

/*	Init_KeyGpio();
	if(KX5_STATUS||KX4_STATUS||KX3_STATUS||KX2_STATUS||KX1_STATUS !=0)
	{
		Key = 0;
							//初始化拨码开关IO
		Read_KX(1);
		Read_KX(2);
		Read_KX(3);
		Read_KX(4);
		Read_KX(5);
	}
	while(KX5_STATUSKX4_STATUSKX3_STATUS||KX2_STATUS||KX1_STATUS);
	return Key;
*/
	while(1)
	{
			Read_KX(1);
			Read_KX(2);
			Read_KX(3);
			Read_KX(4);
			Read_KX(5);

			if(Key != 0)				//检测到按键按下
			{
				Read_Key=Key;
				Key=0;
				//Key的值可以在这里读取
				while(!(KX1_STATUS&&KX2_STATUS&&KX3_STATUS&&KX4_STATUS&&KX5_STATUS) == 1);
				break;
				//return Read_Key;
			}
	}
}
//===========================================================================
// No more.
//===========================================================================


