#include <REGX52.H>		//程序核心：始终显示num，操作改变num
void display(int num1);			//显示函数
void DelayXms(unsigned int x);	//延时函数
void keyScan();					//按键扫描
void keyAdd();					//数字多位输入
void pd();						//判断
int n1, n2, n3, n4, numKey=10000, num=0, num0=0;//显示的个十百千位  键值，显示值，存储值1
char fuhao='0',fuhao0='0';		//键入的符号值,存储的符号值
unsigned char duan[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
void main(){
	while(1){
		keyScan();				//扫描键值
		pd();					//判断键值情况
		display(num);			//显示函数
	}
}
void keyAdd(){
	if(numKey<10000){
		num=num*10+numKey;
		numKey=10000;
	}
}
void pd(){
	keyAdd();				//判断为数字，则为数字输入
	if(fuhao=='c'){			//清零
		num=0;
		num0=0;
		fuhao0='0';
		fuhao='0';
	}
	if(fuhao=='+'){			//加法
		fuhao0='+';			//将符号'+'存到变量fuhao0
		fuhao='0';			//符号清零
		num0=num;			//将加数0存到变量num0
		num=0;
	}
	if(fuhao=='-'){			//减法		
		fuhao0='-';
		fuhao='0';
		num0=num;
		num=0;
	}	
	if(fuhao=='*'){			//乘法		
		fuhao0='*';
		fuhao='0';
		num0=num;
		num=0;
	}	
	if(fuhao=='/'){			//除法
		fuhao0='/';
		fuhao='0';
		num0=num;
		num=0;
	}
	if(fuhao=='='){			//检测到符号为等号，则进行运算
		if(fuhao0=='+')num=num0+num;
		else if(fuhao0=='-')num=num0-num;
		else if(fuhao0=='*')num=num0*num;
		else if(fuhao0=='/')num=num0/num;
		fuhao='0';
		num0=0;
	}
}
void keyScan(){
	P3=0xef;//1110 1111
	if(!P3_3){numKey=7;while(!P3_3);}if(!P3_2){numKey=8;while(!P3_2);}if(!P3_1){numKey=9;while(!P3_1);}if(!P3_0){fuhao='+';while(!P3_0);}
	P3=0xdf;
	if(!P3_3){numKey=4;while(!P3_3);}if(!P3_2){numKey=5;while(!P3_2);}if(!P3_1){numKey=6;while(!P3_1);}if(!P3_0){fuhao='-';while(!P3_0);}
	P3=0xbf;
	if(!P3_3){numKey=1;while(!P3_3);}if(!P3_2){numKey=2;while(!P3_2);}if(!P3_1){numKey=3;while(!P3_1);}if(!P3_0){fuhao='*';while(!P3_0);}
	P3=0x7f;
	if(!P3_3){fuhao='c';while(!P3_3);}if(!P3_2){numKey=0;while(!P3_2);}if(!P3_1){fuhao='=';while(!P3_1);}if(!P3_0){fuhao='/';while(!P3_0);}
}
void display(int num1){
	n4=num1%10;
	n3=num1/10%10;
	n2=num1/100%10;
	n1=num1/1000%10;
	P2=0x01;
	P0=duan[n1];
	DelayXms(4);
	P2=0x02;
	P0=duan[n2];
	DelayXms(4);
	P2=0x04;
	P0=duan[n3];
	DelayXms(4);
	P2=0x08;
	P0=duan[n4];
	DelayXms(4);
}
void DelayXms(unsigned int x)		//@12.000MHz
{	unsigned char i, j;
	while(x--)
	{	i = 2;
		j = 239;
		do{while (--j);
		}while (--i);
	}
}
