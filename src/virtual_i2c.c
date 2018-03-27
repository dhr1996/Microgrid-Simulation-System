#include "virtual_i2c.h"
#include "DSP28x_Project.h"
#include "DSP2833x_GPIO.h"
#include "DSP2833x_Device.h"
#include "My_oledfont.h"			//oled字库

extern const unsigned char F6x8[][6];
extern const unsigned char F8X16[];
extern const unsigned char Hzk[][32];
/*******************OLED_Gpiosetup************************/
void OLED_Gpioset(void)
{
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;			//GPIO3233通用IO
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;			//配置为输出引脚
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;
    EDIS;
}

/*********************OLED_Init************************************/
1
{
/*
	delay(1000);
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x20);//--Set Memory Addressing Mode
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0xb0);//--set page address
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0???? 0xa1??
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0???? 0xc8??
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //
	OLED_Set_Pos(0,0);
*/
	/*	OLED_WrCmd(0xAE);   //display off
		OLED_WrCmd(0x20);	//Set Memory Addressing Mode
		OLED_WrCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
		OLED_WrCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
		OLED_WrCmd(0xc8);	//Set COM Output Scan Direction
		OLED_WrCmd(0x00);//---set low column address
		OLED_WrCmd(0x10);//---set high column address
		OLED_WrCmd(0x40);//--set start line address
		OLED_WrCmd(0x81);//--set contrast control register
		OLED_WrCmd(0xdf);
		OLED_WrCmd(0xa1);//--set segment re-map 0 to 127
		OLED_WrCmd(0xa6);//--set normal display
		OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
		OLED_WrCmd(0x3F);//
		OLED_WrCmd(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
		OLED_WrCmd(0xd3);//-set display offset
		OLED_WrCmd(0x00);//-not offset
		OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
		OLED_WrCmd(0xf0);//--set divide ratio
		OLED_WrCmd(0xd9);//--set pre-charge period
		OLED_WrCmd(0x22); //
		OLED_WrCmd(0xda);//--set com pins hardware configuration
		OLED_WrCmd(0x12);
		OLED_WrCmd(0xdb);//--set vcomh
		OLED_WrCmd(0x20);//0x20,0.77xVcc
		OLED_WrCmd(0x8d);//--set DC-DC enable
		OLED_WrCmd(0x14);//
		OLED_WrCmd(0xaf);//--turn on oled panel
*/
		Delay(1000);
		OLED_WrCmd(0xAE);//--display off
		OLED_WrCmd(0x00);//---set low column address
		OLED_WrCmd(0x10);//---set high column address
		OLED_WrCmd(0x40);//--set start line address
		OLED_WrCmd(0xB0);//--set page address
		OLED_WrCmd(0x81); // contract control
		OLED_WrCmd(0xFF);//--128
		OLED_WrCmd(0xA1);//set segment remap
		OLED_WrCmd(0xA6);//--normal / reverse
		OLED_WrCmd(0xA8);//--set multiplex ratio(1 to 64)
		OLED_WrCmd(0x3F);//--1/32 duty
		OLED_WrCmd(0xC8);//Com scan direction
		OLED_WrCmd(0xD3);//-set display offset
		OLED_WrCmd(0x00);//

		OLED_WrCmd(0xD5);//set osc division
		OLED_WrCmd(0x80);//

		OLED_WrCmd(0xD8);//set area color mode off
		OLED_WrCmd(0x05);//

		OLED_WrCmd(0xD9);//Set Pre-Charge Period
		OLED_WrCmd(0xF1);//

		OLED_WrCmd(0xDA);//set com pin configuartion
		OLED_WrCmd(0x12);//

		OLED_WrCmd(0xDB);//set Vcomh
		OLED_WrCmd(0x30);//

		OLED_WrCmd(0x8D);//set charge pump enable
		OLED_WrCmd(0x14);//

		OLED_WrCmd(0xAF);//--turn on oled panel
}

/*********************OLED************************************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xB0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
			OLED_WrDat(0);
	}
}

/*********************OLED************************************/
void OLED_Fill(unsigned char bmp_dat)			//显示图片
{
	unsigned char y,x;
	for(y = 0;y < 8; y++)
	{
		OLED_WrCmd(0xB0+y);
		OLED_WrCmd(0x00);
		OLED_WrCmd(0x10);
		for(x = 0; x < X_WIDTH; x++)
			OLED_WrDat(bmp_dat);
	}
}

/*********************OLED坐标设置************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
	OLED_WrCmd(0xB0+y);
	OLED_WrCmd(((x&0xF0)>>4)|0x10);
	OLED_WrCmd(x&0x0F);
}

/********************OLED开启显示****************************/
void OLED_Display_On(void)
{
	OLED_WrCmd(0X8D);  //SET DCDC命令
	OLED_WrCmd(0X14);  //DCDC ON
	OLED_WrCmd(0XAF);  //DISPLAY ON
}
/********************OLED关闭显示****************************/
void OLED_Display_Off(void)
{
	OLED_WrCmd(0X8D);  //SET DCDC命令
	OLED_WrCmd(0X10);  //DCDC OFF
	OLED_WrCmd(0XAE);  //DISPLAY OFF
}
//清屏函数
void OLED_Clear(void)
{
	unsigned char i,n;
	for(i=0;i<8;i++)
	{
		OLED_WrCmd (0xB0+i);    //设置页地址(0-7)
		OLED_WrCmd (0x00);      //设置显示位置-列低地址
		OLED_WrCmd (0x10);      //设置显示位置-列高地址
		for(n=0;n<128;n++)OLED_WrDat(0);
	} //更新显示
}
void OLED_On(void)
{
	unsigned char i,n;
	for(i=0;i<8;i++)
	{
		OLED_WrCmd (0xB0+i);    //设置页地址(0-7)
		OLED_WrCmd (0x00);      //设置显示位置-列低地址
		OLED_WrCmd (0x10);      //设置显示位置-列高地址
		for(n=0;n<128;n++)OLED_WrDat(1);
	} //更新显示
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:????×?ì? 16/12
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size)
{
	unsigned char c=0,i=0;
		c=chr-' ';//得到偏移后的值
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
		{
			OLED_Set_Pos(x,y);
			for(i=0;i<8;i++)
			OLED_WrDat(F8X16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WrDat(F8X16[c*16+i+8]);
		}
		else
		{
			OLED_Set_Pos(x,y);
			for(i=0;i<6;i++)
			OLED_WrDat(F6x8[c][i]);
		}
}

/***************显示一个字符号串******************/
void OLED_ShowString(unsigned char x,unsigned char y, char *chr,unsigned char Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
/*******显示数字**************/

void OLED_ShowNum(unsigned char x,unsigned char y,float num,unsigned char size2)
{
	Uint16 sum,one,two,three,four,five;
	if(num<10)
	{
		sum=num*1000;
		four=sum%10;
		three=(sum/10)%10;
		two=(sum/100)%10;
		one=(sum/1000)%10;
		OLED_ShowChar(x+(size2/2)*1,y,one+'0',size2);
		OLED_ShowChar(x+(size2/2)*2,y,0x2E,size2);
		OLED_ShowChar(x+(size2/2)*3,y,two+'0',size2);
		OLED_ShowChar(x+(size2/2)*4,y,three+'0',size2);
		OLED_ShowChar(x+(size2/2)*5,y,four+'0',size2);
	}
	if(num>10||num==10)
	{
		sum=num*1000;
		five=sum%10;
		four=(sum/10)%10;
		three=(sum/100)%10;
		two=(sum/1000)%10;
		one=(sum/10000)%10;
		OLED_ShowChar(x+(size2/2)*1,y,one+'0',size2);
		OLED_ShowChar(x+(size2/2)*2,y,two+'0',size2);
		OLED_ShowChar(x+(size2/2)*3,y,0x2E,size2);
		OLED_ShowChar(x+(size2/2)*4,y,three+'0',size2);
		OLED_ShowChar(x+(size2/2)*5,y,four+'0',size2);
		OLED_ShowChar(x+(size2/2)*6,y,five+'0',size2);
	}
}


/*********************OLED写命令************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);     //Slave address,SA0=0
	Write_IIC_Byte(0x00);			//write command
	Write_IIC_Byte(IIC_Command);
	IIC_Stop();
}

/*********************OLED写数据************************************/
void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Byte(IIC_Data);
	IIC_Stop();
}

/**********************************************
// ??I2C???????
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{

	I2C_SendByte(IIC_Byte);

}
/**********************************************
//IIC Stop
**********************************************/

void IIC_Stop(void)
{
	I2C_Stop();
}


/**********************************************
//IIC Start
**********************************************/
void IIC_Start(void)
{
	I2C_Start();
}

void Delay(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void I2C_Delay(void)
{
	Uint16 i		= 15;
	while(i--);
}

void I2C_SendByte(Uint16 data)
{
	Uint16 i	= 8;
	while(i--)
	{
		if(data&0x80)
		{
			SDA_H = 1;
			//SDA_H = 0;
			I2C_Delay();
		}
		else
		{
			SDA_H = 0;
			//SDA_H = 1;
			I2C_Delay();
		}

		SCL_H = 1;			//上升沿
		I2C_Delay();
		SCL_H = 0;
		data <<= 1;
	}
	SDA_H = 1;
	I2C_Delay();
	SCL_H = 1;
	I2C_Delay();
	SCL_H = 0;
}

void I2C_Start(void)
{
	SCL_H = 1;
	I2C_Delay();
	SDA_H = 1;
	I2C_Delay();
	SDA_H = 0;
	I2C_Delay();
	SCL_H = 0;
}
void I2C_Stop(void)
{
	SCL_H = 0;
	I2C_Delay();
	SDA_H = 0;
	I2C_Delay();
	SCL_H = 1;
	I2C_Delay();
	SDA_H = 1;
}
void I2C_Ack(void)
{
	SCL_H = 0;
	I2C_Delay();
	SDA_H = 0;
	I2C_Delay();
	SCL_H = 1;
	I2C_Delay();
	SCL_H = 0;
	I2C_Delay();
	SCL_H = 1;
	SDA_H = 1;
}
void I2C_NoAck(void)
{
	SCL_H = 0;
	I2C_Delay();
	SDA_H = 1;
	I2C_Delay();
	SCL_H = 1;
	I2C_Delay();
	SCL_H = 0;
	I2C_Delay();
	SCL_H = 1;
	SDA_H = 1;
}

void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{
	unsigned char t,adder=0;
	OLED_Set_Pos(x,y);
    for(t=0;t<16;t++)
		{
				OLED_WrDat(Hzk[2*no][t]);
				adder+=1;
     }
	OLED_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
			{
				OLED_WrDat(Hzk[2*no+1][t]);
				adder+=1;
      }
}

void OLED_Show1()
{
//	Content:
	    OLED_ShowString(40,0,"Content",16);
		OLED_ShowString(0,2,"1.independ",16);
		OLED_ShowString(80,2,".....",16);
		OLED_ShowString(120,2,"A",16);

		OLED_ShowString(0,5,"2.parallel",16);
		OLED_ShowString(80,5,".....",16);
		OLED_ShowString(120,5,"B",16);
}
void OLED_Show2()
{
//	A:
	    OLED_ShowString(40,0,"A.independ",16);

		OLED_ShowString(0,4,"2.V_Ref:  ",16);
		OLED_ShowNum(65,4,24,16);
		OLED_ShowString(121,4,"v",16);

		OLED_ShowString(73,7,"return",8);
}
void OLED_Show3(float32 m,float32 n)
{
//	B:
	    OLED_ShowString(40,0,"B.Boost",16);
		OLED_ShowString(0,2,"1.V_Ref:",16);
		OLED_ShowNum(81,2,m,16);
		OLED_ShowString(121,2,"V",16);

		OLED_ShowString(0,4,"2.vol:",16);
		OLED_ShowNum(65,4,n,16);
		OLED_ShowString(121,4,"V",16);

		OLED_ShowString(73,7,"return",8);
}
