#include <graphics.h>
#include <conio.h>
#include<stdio.h>

#define MAX_STAR 100
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_STEP   5
#define MAX_RADIUS 3

//星星的状态
enum STATUS{
  STOP=0,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  RANDOM,
  ALL_STATUS
};

struct STAR{
	int x;
	int y;
	enum STATUS stat;  //状态
	unsigned radius;   //星星的半径
	int step;          //每次跳跃的间隔
	int  color;         //星星的颜色
};
struct STAR star[MAX_STAR];
/**************************************
*功能:初始化星星
* 输入参数:
*     i-星星在全局数组中的下标
* 返回值: 无
****************************************/
void initStar(int i){
	int rgb=0;
	if (i<0 ||i>MAX_STAR){
	 fprintf(stderr,"老司机,你的传的值i[%d]我接受不了!",i);//log日志
	   return ;
	}
	star[i].x=rand() % SCREEN_WIDTH;     //x 范围 0-639  //639 % 640 = 639 //641 % 640=1
	star[i].y=rand() % SCREEN_HEIGHT;    //y 范围 0-479
	star[i].stat =(enum STATUS)(rand() % ALL_STATUS);
	star[i].radius=1+rand() % MAX_RADIUS;
	star[i].step=rand() % MAX_STEP+1;
	rgb=255 * star[i].step/(MAX_STEP+1);  //0-255
	star[i].color=RGB(rgb , rgb ,rgb); 

}
void MoveStar(int i){
	if(star[i].stat == STOP ) return ;

	//擦除原来的星星
	setfillcolor(BLACK); 
	solidcircle(star[i].x, star[i].y,star[i].radius);

	 if(star[i].stat==DOWN){
		star[i].y=star[i].y + star[i].step;
		if(star[i].y>SCREEN_HEIGHT)  star[i].y=0;
	}else if(star[i].stat==UP){
		star[i].y-=star[i].step;
		if(star[i].y<0) star[i].y= SCREEN_HEIGHT;
	}else if(star[i].stat==LEFT){
		star[i].x-=star[i].step;
		if(star[i].x<0) star[i].x=SCREEN_WIDTH ;
	}else if(star[i].stat== RIGHT){
		star[i].x+=star[i].step;
		if(star[i].x>SCREEN_WIDTH) star[i].x= 0;
	}

	setfillcolor(star[i].color);
	solidcircle(star[i].x, star[i].y, star[i].radius);
}


int main(){

	initgraph(SCREEN_WIDTH ,SCREEN_HEIGHT);

	for(int i=0; i<MAX_STAR; i++){
	initStar(i);
	}
	bool quit= false;

	do{

	for(int i=0; i<MAX_STAR; i++){
	MoveStar(i);
	}
	Sleep(30);
	}while(!quit);
	
	closegraph();
	system("pause");
	return 0;
	
	}