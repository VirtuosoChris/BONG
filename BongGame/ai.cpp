#include <windows.h>
#include "bong.h"

#define FAST 1.5
#define SLOW 1
#define AISPD 8

extern paddle redpaddle;
//extern paddle rpaddles[4];
extern ball MainBall;
extern ball balls[500];
extern double rTime;
extern int gameRound;
extern ball PaddleBallRed;
extern ball rPaddleBall[4];
extern paddle redpaddlelast;
extern paddle rpaddleslast[4];


void followballs(){

if(redpaddle.x){
redpaddlelast = redpaddle;

PaddleBallRed.radius = 1;
PaddleBallRed.xVec= redpaddle.x - redpaddlelast.x;
PaddleBallRed.yVec= redpaddle.y - redpaddlelast.y;
redpaddle = doai(redpaddle);

}
}




paddle doai(paddle tPaddle){

float distClose = 0;
float distQuery = 0;
float dist = 0;
float padrate = FAST;


	//by default follow the mainball, follow another if its closer on the y axis
	ball cBall = MainBall;
	distClose = cBall.y;
	if(MainBall.round == 0){distClose = -1;}

	for(int i = 0; i <500;i++){
		if(balls[i].round == gameRound || balls[i].round == 4){
		if(balls[i].y > distClose){
			cBall = balls[i];
			distClose = cBall.y;}
		}
	}
		
	
	if(cBall.yVec>=0){padrate = FAST;}
	else{padrate = SLOW;}

		int AIMOVEAMT = -20;
		float aipadmove;

		if(tPaddle.x){
			
			if(cBall.x > tPaddle.x){
				tPaddle.x += AISPD;}
			if(cBall.x < tPaddle.x){tPaddle.x -= AISPD;}

		/*
			if(tPaddle.x > cBall.x){
			 aipadmove = tPaddle.x-cBall.speed*rTime;//;*padrate*rTime;
					
			 tPaddle.x = //cBall.x;}
				 aipadmove;}
			
			if(tPaddle.x < cBall.x){
				aipadmove = tPaddle.x+cBall.speed*rTime;//*padrate*rTime;
				
				
				tPaddle.x = //cBall.x;}
					aipadmove;
			}*/
			
			
			if(tPaddle.x <= 0){tPaddle.x = 1;}

		}
	



////////////////////////////////////////	
	return tPaddle;
}

