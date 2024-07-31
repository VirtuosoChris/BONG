#include <windows.h>
#include "bong.h"

//#define DEBUGGING

int topcoll = 0;
int leftcoll = 0;
int rightcoll = 0;
int bottomcoll = 0;


float paddlexex;
float paddlewidthex;

double abc;
float percvec;

extern ball PaddleBall;

extern int scores[2];
extern int gameRound;
extern int resWidth;
extern int resHeight;
extern paddle bluepaddle;
extern goal redgoals[3000];
extern goal bluegoals[3000];
extern brick bricks[3000];
extern brick blocks[3000];
//extern paddle rpaddles[4];
//extern paddle bpaddles[4];
extern paddle redpaddle;//eventually add ability to add more paddles
extern bouncer bouncers[3000];
extern essence redessences[3000];
extern essence blueessences[3000];
extern ball balls[500];
extern paddle bluepaddlelast;
extern ball MainBall;
extern int MAPBARRIER;


extern ball PaddleBall;
extern ball PaddleBallRed;
extern ball rPaddleBall[4];
extern ball bPaddleBall[4];
extern paddle redpaddlelast;
//extern paddle rpaddleslast[4];
//extern paddle bpaddleslast[4];

bool passed = false;

FILE *fp;

ball cBall;
float highx, highy, lowx,lowy = 0;
float m;
float b;
float fltSaveDist;
extern double rTime;
ball bBall;

//fprintf(fp, "Old distance = %f\n",fltSaveDist);


ball doCollision(ball tBall){

	
brick *pBrick;
brick *pBlock;
essence *pRedEssence;
essence *pBlueEssence;
bouncer *pBouncer;
goal *pRedGoal;
goal *pBlueGoal;
paddle *pPaddle;

pBrick = NULL;
pBlock = NULL;
pRedEssence = NULL;
pBlueEssence= NULL;
pBouncer = NULL;
pRedGoal = NULL;
pBlueGoal = NULL;
pPaddle = NULL;




#ifdef DEBUGGING
fp = fopen("Collisionlog.txt","a");
fprintf(fp, "%s\n", "Hello World");
#endif

if	((float)tBall.x-(float)tBall.lx == 0) {
		m = ((float)tBall.y-(float)tBall.ly)/((float)tBall.x-(float)tBall.lx+0);
	} else {
		m = ((float)tBall.y-(float)tBall.ly)/((float)tBall.x-(float)tBall.lx);
	}

b = (float)tBall.y-((float)tBall.x*m);

if(tBall.lx >= tBall.x){highx = tBall.lx; lowx = tBall.x;}
if(tBall.lx <  tBall.x){highx = tBall.x; lowx = tBall.lx;}
if(tBall.ly >= tBall.y){highy = tBall.ly; lowy = tBall.y;}
if(tBall.ly <  tBall.y){highy = tBall.y; lowy = tBall.ly;}


cBall = tBall;
fltSaveDist = sqrt((((float)tBall.lx-(float)tBall.x)*((float)tBall.lx-(float)tBall.x))+
		(((float)tBall.ly - (float)tBall.y)*((float)tBall.ly - (float)tBall.y))
		);

ballpaddlecollision(tBall, bluepaddle, PaddleBall,bluepaddlelast);
if(passed){

	//cBall.x = cBall.x + (PaddleBall.xVec*rTime);

				pBrick = NULL;
				pBlock = NULL;
				pRedEssence = NULL;
				pBlueEssence= NULL;
				pBouncer = NULL;
				pRedGoal = NULL;
				pBlueGoal = NULL;
				pPaddle = &bluepaddle;
	//}
}
passed = false;
passed = false;
if(redpaddle.x){
ballpaddlecollision(tBall, redpaddle, PaddleBallRed,redpaddlelast);
if(passed){
				pBrick = NULL;
				pBlock = NULL;
				pRedEssence = NULL;
				pBlueEssence= FALSE;
				pBouncer = NULL;
				pRedGoal = NULL;
				pBlueGoal = NULL;
				pPaddle = &redpaddle;
			}
}
passed = false;




for(int i = 0; i < 3000; i++){//for each brick
	 if(bricks[i].round == 4 || bricks[i].round == gameRound)
	 {//if block is in correct round
		cBall = objectCollision(tBall, (float)bricks[i].x, (float)bricks[i].y, (float)bricks[i].width, (float)bricks[i].height);
		if(passed){
			pBrick = &bricks[i];
			pBlock = NULL;
			pRedEssence = NULL;
			pBlueEssence= NULL;
			pBouncer = NULL;
			pRedGoal = NULL;
			pBlueGoal = NULL;
			pPaddle = NULL;
		}
		passed = false;
	 }
}

for(int i = 0; i < 3000; i++){//for each block
	 if(blocks[i].round == 4 || blocks[i].round == gameRound){//if block is in correct round
		 if(blocks[i].broken == false){
			cBall =  objectCollision(tBall, (float)blocks[i].x, (float)blocks[i].y, (float)blocks[i].width, (float)blocks[i].height);
			//if(passed){blocks[i].broken = true;}
			if(passed){
				pBrick = NULL;
				pBlock = &blocks[i];
				pRedEssence = NULL;
				pBlueEssence= NULL;
				pBouncer = NULL;
				pRedGoal = NULL;
				pBlueGoal = NULL;
				pPaddle = NULL;
			}
			passed = false;
		 }
	 }
}

for(int i = 0; i < 3000; i++){//for each red goal
	 if(redgoals[i].round == 4 || redgoals[i].round == gameRound){//if block is in correct round
		cBall =  objectCollision(tBall, (float)redgoals[i].x, (float)redgoals[i].y, (float)redgoals[i].width, (float)redgoals[i].height);
		if(passed){
				pBrick = NULL;
				pBlock = NULL;
				pRedEssence = NULL;
				pBlueEssence= NULL;
				pBouncer = NULL;
				pRedGoal = &redgoals[i];
				pBlueGoal = NULL;
				pPaddle = NULL;
			}
		passed = false;
	 }
}

for(int i = 0; i < 3000; i++){//for each blue goal
	 if(bluegoals[i].round == 4 || bluegoals[i].round == gameRound){//if block is in correct round
		cBall =  objectCollision(tBall, (float)bluegoals[i].x, (float)bluegoals[i].y, (float)bluegoals[i].width, (float)bluegoals[i].height);
		if(passed){
				pBrick = NULL;
				pBlock = NULL;
				pRedEssence = NULL;
				pBlueEssence= NULL;
				pBouncer = NULL;
				pRedGoal = NULL;
				pBlueGoal = &bluegoals[i];
				pPaddle = NULL;
			}
		passed = false;
	 }
}



for(int i = 0; i < 3000; i++)
{	//for each bouncer
	 if(bouncers[i].round == 4 || bouncers[i].round == gameRound){//if block is in correct round
		circlecollision(tBall, bouncers[i].x, bouncers[i].y, bouncers[i].radius, WHITE);
		if(passed){
				pBrick = NULL;
				pBlock = NULL;
				pRedEssence = NULL;
				pBlueEssence= NULL;
				pBouncer = &bouncers[i];
				pRedGoal = NULL;
				pBlueGoal = NULL;
				pPaddle = NULL;
			}
		passed = false;
	 }
}


for(int i = 0; i < 3000; i++)
{//for each resse
	 if(redessences[i].round == 4 || redessences[i].round == gameRound)
	 {//if block is in correct round
		circlecollision(tBall, redessences[i].x, redessences[i].y, redessences[i].radius, RED);
		if(passed){
				//pBrick = NULL;
				//pBlock = NULL;
				//pRedEssence = &redessences[i];
				//pBlueEssence= NULL;
				//pBouncer = NULL;
				//pRedGoal = NULL;
				//pBlueGoal = NULL;
				//pPaddle = NULL;
			}
		passed = false;
	 }
}

for(int i = 0; i < 3000; i++)
{	//for each besse
	 if(blueessences[i].round == 4 || blueessences[i].round == gameRound)
	 {
		 //if block is in correct round
		circlecollision(tBall, blueessences[i].x, blueessences[i].y, blueessences[i].radius, BLUE);
		if(passed){
				//pBrick = NULL;
				//pBlock = NULL;
				//pRedEssence = NULL;
				//pBlueEssence= &blueessences[i];
				//pBouncer = NULL;
				//pRedGoal = NULL;
			//	pBlueGoal = NULL;
			//	pPaddle = NULL;
			}
		passed = false;
	 }
}






//ball-ball for mainball
if(MainBall.round == gameRound || MainBall.round == 4){
	bBall = tBall;
	bBall.xVec = (tBall.xVec - MainBall.xVec)*rTime;
	bBall.yVec = (tBall.yVec - MainBall.yVec)*rTime;
	circlecollision(bBall, MainBall.x, MainBall.y, MainBall.radius, WHITE);
	if(passed){
		percvec = (sqrt(pow((double)bBall.xVec,2)+pow((double)bBall.yVec,2)))/
			(sqrt(pow((double)tBall.xVec,2)+pow((double)tBall.yVec,2)));
		
	//	cBall.xVec = (cBall.xVec*percvec)+-MainBall.xVec;//neg
	//cBall.yVec = (cBall.yVec*percvec)+-MainBall.yVec;

		//MainBall.xVec = -MainBall.xVec;//+cBall.xVec;
		//MainBall.yVec = -MainBall.yVec;//+cBall.yVec;

		cBall.xVec = -cBall.xVec; //* ((float)MainBall.radius/(float)cBall.radius);
		cBall.xVec = cBall.xVec  + MainBall.xVec;// * ((float)MainBall.radius/(float)cBall.radius);

		cBall.yVec = -cBall.yVec;//*((float)MainBall.radius/(float)cBall.radius);
		cBall.yVec = cBall.yVec + MainBall.yVec;//* ((float)MainBall.radius/(float)cBall.radius);

		abc = sqrt(pow((double)cBall.xVec,2)+pow((double)cBall.yVec,2));
		cBall.xVec = (cBall.xVec/abc)*cBall.speed;
		cBall.yVec = (cBall.yVec/abc)*cBall.speed;


		MainBall.xVec = -MainBall.xVec; //* ((float)MainBall.radius/(float)cBall.radius);
		MainBall.xVec = cBall.xVec  + MainBall.xVec; //* ((float)MainBall.radius/(float)cBall.radius);

		MainBall.yVec = -MainBall.yVec;//*((float)MainBall.radius/(float)cBall.radius);
		MainBall.yVec = cBall.yVec + MainBall.yVec; 

		abc = sqrt(pow((double)MainBall.xVec,2)+pow((double)MainBall.yVec,2));
		MainBall.xVec = (MainBall.xVec/abc)*MainBall.speed;
		MainBall.yVec = (MainBall.yVec/abc)*MainBall.speed;

	
		
	}
	passed = false;
}


//ball-ball for balls[i]
for(int i = 0; i <500; i++){
	
	if(balls[i].round == gameRound || balls[i].round == 4){
	bBall = tBall;
	bBall.xVec = (tBall.xVec - balls[i].xVec)*rTime;;
	bBall.yVec = (tBall.yVec - balls[i].yVec)*rTime;;
	circlecollision(bBall, balls[i].x, balls[i].y, balls[i].radius, WHITE);
		if(passed){
		percvec = (sqrt(pow((double)bBall.xVec,2)+pow((double)bBall.yVec,2)))/
			(sqrt(pow((double)tBall.xVec,2)+pow((double)tBall.yVec,2)));
		
		//cBall.xVec = (cBall.xVec*percvec)+-balls[i].xVec;//neg
		//cBall.yVec = (cBall.yVec*percvec)+-balls[i].yVec;

		//balls[i].xVec = -balls[i].xVec;//+cBall.xVec;
		//balls[i].yVec = -balls[i].yVec;//+cBall.yVec;

		cBall.xVec = -cBall.xVec; //* ((float)balls[i].radius/(float)cBall.radius);
		cBall.xVec = cBall.xVec  + balls[i].xVec; //* ((float)balls[i].radius/(float)cBall.radius);

		cBall.yVec = -cBall.yVec;//*((float)balls[i].radius/(float)cBall.radius);
		cBall.yVec = cBall.yVec + balls[i].yVec; //* ((float)balls[i].radius/(float)cBall.radius);
		
		
		balls[i].xVec = -balls[i].xVec; //* ((float)balls[i].radius/(float)cBall.radius);
		balls[i].xVec = cBall.xVec  + balls[i].xVec; //* ((float)balls[i].radius/(float)cBall.radius);

		balls[i].yVec = -balls[i].yVec;//*((float)balls[i].radius/(float)cBall.radius);
		balls[i].yVec = cBall.yVec + balls[i].yVec; 


		abc = sqrt(pow((double)cBall.xVec,2)+pow((double)cBall.yVec,2));
		cBall.xVec = (cBall.xVec/abc)*cBall.speed;
		cBall.yVec = (cBall.yVec/abc)*cBall.speed;

		abc = sqrt(pow((double)balls[i].xVec,2)+pow((double)balls[i].yVec,2));
		balls[i].xVec = (balls[i].xVec/abc)*balls[i].speed;
		balls[i].yVec = (balls[i].yVec/abc)*balls[i].speed;
		
		}
	passed = false;	
	
	}

}



//fprintf(fp, "New distance = %f\n",(float)fltSaveDist);
//fprintf(fp, "New Vector = %f, %f\n",(float)cBall.xVec,cBall.yVec);
//fprintf(fp, "New Position = %f, %f\n",(float)cBall.x,cBall.y);

#ifdef DEBUGGING
fclose(fp);
#endif

if(pBrick){
	//slow down ball that hits brick
	//cBall.xVec = cBall.xVec/cBall.speed;
	//cBall.yVec = cBall.yVec/cBall.speed;
	//cBall.speed = cBall.speed - 1;
	//cBall.xVec = cBall.xVec*cBall.speed;
	//cBall.yVec = cBall.yVec*cBall.speed;
	//PlaySound("boing.wav",NULL,0x0001);
}



if(pBlock){//five points
	///////////////////////////////////
	if(tBall.belongsTo != WHITE){
		makeParticle(pBlock->x,pBlock->y);
		makeScore(pBlock->x, pBlock->y, tBall.belongsTo, 5);
		pBlock->broken = true;	
		scores[tBall.belongsTo] = scores[tBall.belongsTo]+5;
		extern int lastBroken;
		lastBroken = tBall.belongsTo;


		PlaySound("break.wav",NULL,0x0001);
	//////////////////
	}//else PlaySound("boing.wav",NULL,0x0001);

	


}

//if(pRedEssence){}

//if(pBlueEssence){}

if(pBouncer){
	if(cBall.belongsTo != WHITE){
	//one point for hitting a bouncer
	scores[cBall.belongsTo]++;
	makeScore(pBouncer->x, pBouncer->y, cBall.belongsTo,1);
	}
}
/*
//steal 2 points for hitting a goal
if(pRedGoal){
	if(cBall.belongsTo == BLUE){	
		scores[BLUE] = scores[BLUE] + 2;
		scores[RED] = scores[RED]-2;
	}
}

if(pBlueGoal){
	if(cBall.belongsTo == RED){	
		scores[BLUE] = scores[BLUE] - 2;
		scores[RED] = scores[RED]+2;	
	}
}
*/
if(pPaddle){
	//if(pPaddle->x){

	cBall.belongsTo = pPaddle->color;
		
		//gets vector from collision point to center
		double iX = cBall.x - pPaddle->x;
		double iY = cBall.y - pPaddle->y;
		//adds the reflection and position vectors
	cBall.xVec = cBall.xVec+iX;
	cBall.yVec = cBall.yVec+iY;
		//normalizes the final reflection vector
	cBall.speed = sqrt(pow((double)cBall.xVec,2)+pow((double)cBall.yVec,2));
	cBall.xVec = cBall.xVec/cBall.speed;
	cBall.yVec = cBall.yVec/cBall.speed;
		//if(cBall.speed < MAXBALLSPEED){cBall.speed = cBall.speed;}
		//sets its length to original length plus one
	//cBall.xVec = cBall.xVec*tBall.speed;
	//cBall.yVec = cBall.yVec*tBall.speed;
	cBall.speed = sqrt(pow((double)cBall.xVec,2)+pow((double)cBall.yVec,2));
	cBall.xVec = cBall.xVec/cBall.speed;
	cBall.yVec = cBall.yVec/cBall.speed;
	cBall.speed = tBall.speed;//+sqrt(pow((double)PaddleBall.xVec,2)+pow((double)PaddleBall.yVec,2));
	cBall.xVec = cBall.xVec*cBall.speed;
	cBall.yVec = cBall.yVec*cBall.speed;

	PlaySound("clang.wav",NULL,0x0001);
}
//}//?

int brkCol = WHITE;
for(int i = 0; i <3000; i++)
{
	if(bricks[i].round == 4 || bricks[i].round == gameRound){
	if(cBall.x > bricks[i].x - bricks[i].width && cBall.x < bricks[i].x+bricks[i].width){
		if(cBall.y > bricks[i].y - bricks[i].height &&cBall.y < bricks[i].y + bricks[i].height){
		  cBall.round = 0;
		  makeParticle(cBall.x, cBall.y);
		  
		  if(cBall.y > MAPBARRIER/2){brkCol = BLUE;}
		  else{brkCol = RED;}
            scores[brkCol] += 50;
		  makeScore(cBall.x,cBall.y,brkCol,50);
		  return cBall;
////////////////////////////////
		  ///////////////////////
		  //////////////////////////////
		  ///////////

		}
	}
	}
}

return cBall;

}





//collision for square objects
ball objectCollision(ball tBall, float px, float py, float pwidth, float pheight){
	
float xlol;
float ylol;

float TOP;
float BOTTOM;
float LEFT;
float RIGHT;

float topint[2];
float bottomint[2];
float leftint[2];
float rightint[2];

float distleft = 100000;
float distright = 100000;
float disttop = 100000;
float distbottom = 100000;



TOP = py - pheight - tBall.radius;
BOTTOM = py + pheight + tBall.radius;
LEFT = px - pwidth - tBall.radius;
RIGHT = px + pwidth + tBall.radius;

#ifdef DEBUGGING
fprintf(fp, "TOP = %f   py = %f - pheight = %f - tBall.radius = %f\n",(float)TOP,(float)py,(float)pheight, (float)tBall.radius );
fprintf(fp, "BOTTOM = %f   py = %f + pheight = %f + tBall.radius = %f\n",(float)TOP,(float)py,(float)pheight, (float)tBall.radius );
fprintf(fp, "LEFT = %f   px = %f - pheight = %f - tBall.radius = %f\n",(float)TOP,(float)px,(float)pwidth, (float)tBall.radius );
fprintf(fp, "RIGHT = %f   px = %f - pheight = %f - tBall.radius = %f\n",(float)TOP,(float)px,(float)pwidth, (float)tBall.radius );
#endif
//TOP
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
			xlol = ((float)TOP - b) / m;
			topint[0] = xlol;
			topint[1] = TOP;
			
			//tballs last to intersection point
			disttop = sqrt( (((float)tBall.lx - (float)topint[0])*((float)tBall.lx - (float)topint[0]))      
					+(((float)tBall.ly - (float)topint[1])*((float)tBall.ly - (float)topint[1]))
					);
#ifdef DEBUGGING		
				fprintf(fp, "Testing TOP L1 ~~~  LEFT = %f  xlol = %f  RIGHT = %f\n",(float)LEFT,(float)xlol,(float)RIGHT );
#endif
				if((LEFT <= xlol) && (xlol <=RIGHT)){
				// if(xlol >= LEFT && xlol <= RIGHT){//				
				//if(LEFT <= xlol <=RIGHT){
#ifdef DEBUGGING
					fprintf(fp, "TOP L1 TEST IS TRUE\n" );
					fprintf(fp, "Testing TOP L2 ~~~  lowx = %f  xlol = %f  highx = %f\n",(float)lowx,(float)xlol,(float)highx );
#endif
					//if(lowx <= xlol <= highx){
					if((lowx <= xlol) && (xlol <= highx)){
#ifdef DEBUGGING
						fprintf(fp, "TOP L2 TEST IS TRUE\n" );
						fprintf(fp, "Testing TOP L3 ~~~  lowy = %f  TOP = %f  highy = %f\n",(float)lowy,(float)TOP,(float)highy );
#endif 
						//if( lowy <= TOP <= highy){
						if((lowy <= TOP) && (TOP <= highy)){

#ifdef DEBUGGING
							fprintf(fp, "TOP L3 TEST IS TRUE\n" );
#endif
					//if(xlol >= lowx){
						//if(xlol <= highx){
						//	if(TOP >= lowy){
							//	if(TOP <= highy){
					
							if (disttop<fltSaveDist){
								
				

								
								fltSaveDist = disttop;

								
							
								cBall.xVec = tBall.xVec;//*1.05;
								cBall.yVec = -tBall.yVec;//*1.05;
								
								cBall.x = topint[0];//+(cBall.xVec*rTime);
								cBall.y = topint[1]-BUFFERDIST;//+(cBall.yVec*rTime);
								topcoll++;
								//fprintf(fp, "New Vector = %f, %f\n",cBall.xVec,cBall.yVec);
								//fprintf(fp, "New Position = %f, %f\n",cBall.x,cBall.y);
								passed = true;
								

							}
							//	}}
						}
					}
				}
///////////////////////////////////////////////////////////			
////////////////////////////////////////////////////////////			
		xlol = ((float)BOTTOM - b)/m;
			bottomint[0] = xlol;
			bottomint[1] = BOTTOM;
			distbottom = sqrt( (((float)tBall.lx - (float)bottomint[0])*((float)tBall.lx - (float)bottomint[0]))      
					+(((float)tBall.ly - (float)bottomint[1])*((float)tBall.ly - (float)bottomint[1]))
					);


#ifdef DEBUGGING
			fprintf(fp, "Testing BOTTOM  L1 ~~~  LEFT = %f  xlol = %f  RIGHT = %f\n",(float)LEFT,(float)xlol,(float)RIGHT );
#endif			
			
			if((xlol >= LEFT) && (xlol <= RIGHT)){//
				

#ifdef DEBUGGING
				fprintf(fp, "BOTTOM L1 TEST IS TRUE\n" );
				fprintf(fp, "Testing BOTTOM L2 ~~~  lowx = %f  xlol = %f  highx = %f\n",(float)lowx,(float)xlol,(float)highx );
#endif				
				
				//if(LEFT<=xlol<=RIGHT){
				if((lowx <= xlol) && (xlol <= highx)) {

#ifdef DEBUGGING
					fprintf(fp, "BOTTOM L2 TEST IS TRUE\n" );
					fprintf(fp, "Testing BOTTOM L3 ~~~  lowy = %f  TOP = %f  highy = %f\n",(float)lowy,(float)TOP,(float)highy );
#endif					
					
					//if(lowx <= xlol <= highx){
						if((lowy <= BOTTOM) && (BOTTOM <= highy)){	
						//if(lowy <= BOTTOM <= highy){	

#ifdef DEBUGGING
							fprintf(fp, "BOTTOM L3 TEST IS TRUE\n" );
#endif
				//if(xlol >= lowx){
						//if(xlol <= highx){
						//	if(BOTTOM >= lowy){
						//		if(BOTTOM <= highy){
						if (distbottom<fltSaveDist){
								
						//	fprintf(fp, "Old distance = %f\n",fltSaveDist);
							
							fltSaveDist = distbottom;

							//fprintf(fp, "New distance = %f\n",fltSaveDist);
								
								cBall.xVec = tBall.xVec;
								cBall.yVec = -tBall.yVec;
								cBall.x = bottomint[0];
								cBall.y = bottomint[1]+BUFFERDIST;//+(cBall.yVec*rTime);
								bottomcoll++;
								passed = true;
								
							}
							// }}
						}
					}
				}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
ylol = (m*(float)RIGHT) + b;
	rightint[0] = RIGHT;
	rightint[1] = ylol;
	distright = sqrt( (((float)tBall.lx - (float)rightint[0])*((float)tBall.lx - (float)rightint[0]))      
					+(((float)tBall.ly - (float)rightint[1])*((float)tBall.ly - (float)rightint[1]))
					);


#ifdef DEBUGGING
	fprintf(fp, "Testing RIGHT  L1 ~~~  TOP = %f  ylol = %f  BOTTOM = %f\n",(float)TOP,(float)ylol,(float)BOTTOM );
#endif	
	
	if((ylol >= TOP) && (ylol <= BOTTOM)) {//		
	//if(TOP<=ylol<=BOTTOM){
		
#ifdef DEBUGGING		
		fprintf(fp, "RIGHT L1 TEST IS TRUE\n" );
		fprintf(fp, "Testing RIGHT L2 ~~~  lowy = %f  ylol = %f  highy = %f\n",(float)lowy,(float)ylol,(float)highy );
#endif

		if((lowy <= ylol) && (ylol <= highy)) {

#ifdef DEBUGGING
			fprintf(fp, "RIGHT L2 TEST IS TRUE\n" );
			fprintf(fp, "Testing RIGHT L3 ~~~  lowx = %f  RIGHT = %f  highx = %f\n",(float)lowx,(float)RIGHT,(float)highx );			
#endif

			if((lowx <= RIGHT) && (RIGHT <= highx)){
			//if( lowx <= RIGHT <= highx){

#ifdef DEBUGGING
				fprintf(fp, "RIGHT L3 TEST IS TRUE\n" );
#endif
		//if(ylol >= lowy){
					///	if(ylol <= highy){
					//		if(RIGHT >= lowx){
					//			if(RIGHT <= highx){

				if (distright<fltSaveDist){


								//fprintf(fp, "Old distance = %f\n",fltSaveDist);

								fltSaveDist = distright;

								//fprintf(fp, "New distance = %f\n",fltSaveDist);
							
								cBall.xVec = -tBall.xVec;
								cBall.yVec = tBall.yVec;

								cBall.x =rightint[0]+BUFFERDIST;//+(cBall.xVec*rTime);
								cBall.y =rightint[1];
								rightcoll++;
								passed = true;
							//	fprintf(fp, "New Vector = %f, %f\n",cBall.xVec,cBall.yVec);
								//fprintf(fp, "New Position = %f, %f\n",cBall.x,cBall.y);
							}
							//	}}
			}
		}
	}
//////////////////////////////////////////////////////
/////////////////////////////////////////////////////
ylol = (m*(float)LEFT) + b;
	leftint[0] = LEFT;
	leftint[1] = ylol;
	distleft = sqrt((((float)tBall.lx - (float)leftint[0])*((float)tBall.lx - (float)leftint[0]))      
					+(((float)tBall.ly - (float)leftint[1])*((float)tBall.ly -(float)leftint[1]))
					);

#ifdef DEBUGGING
	fprintf(fp, "Testing LEFT  L1 ~~~  TOP = %f  ylol = %f  BOTTOM = %f\n",(float)TOP,(float)ylol,(float)BOTTOM );
#endif
	
	if(ylol >= TOP && ylol <= BOTTOM){//		
	//if(TOP<=ylol<=BOTTOM){
		
#ifdef DEBUGGING
		fprintf(fp, "LEFT L1 TEST IS TRUE\n" );
		fprintf(fp, "Testing LEFT L2 ~~~  lowy = %f  ylol = %f  highy = %f\n",(float)lowy,(float)ylol,(float)highy );
#endif
		
		if((lowy <= ylol) && (ylol <= highy)){
		//if(lowy <= ylol <= highy){
			
#ifdef DEBUGGING
			fprintf(fp, "LEFT L2 TEST IS TRUE\n" );
			fprintf(fp, "Testing LEFT L3 ~~~  lowx = %f  RIGHT = %f  highx = %f\n",(float)lowx,(float)RIGHT,(float)highx );			
#endif

			if(( lowx <= LEFT) && (LEFT <= highx)){ 
			//if( lowx <= LEFT <= highx){

#ifdef DEBUGGING
				fprintf(fp, "LEFT L3 TEST IS TRUE\n" );
#endif

				if (distleft<fltSaveDist){

							fltSaveDist = distleft;

							cBall.xVec = -tBall.xVec;
							cBall.yVec = tBall.yVec;
							cBall.x = leftint[0]-BUFFERDIST;//+(cBall.xVec*rTime);
							cBall.y = leftint[1];
							leftcoll++;
							passed = true;
						//	fprintf(fp, "New Vector = %f, %f\n",cBall.xVec,cBall.yVec);
						//	fprintf(fp, "New Position = %f, %f\n",cBall.x,cBall.y);
				}
			}
						//}}
		}
	}
	
return cBall;
}





ball circlecollision(ball tBall, int circlex, int circley, int circleradius, int pcolor){
		//make sure all ball positions are lx and ly or it will bug like a motherfucker
		int sumradii =(tBall.radius + circleradius);
		double distcircles = 	sqrt( ((tBall.lx - circlex)*(tBall.lx - circlex))+
			((tBall.ly - circley)*(tBall.ly - circley)));
		double ballspeed = sqrt(pow((double)tBall.xVec,2)+pow((double)tBall.yVec,2));
		//if ball moving fast enough for a collision
		if(tBall.speed >= (distcircles - sumradii)){
			
		double dotproduct = ((tBall.xVec/ballspeed)*(circlex-tBall.lx))+
							((tBall.yVec/ballspeed)*(circley-tBall.ly));

		//if ball moving towards
			 if(dotproduct > 0){
     
			//hehe
			  double d = ((circlex-tBall.lx)*(tBall.xVec/ballspeed)) + 
				  ((circley-tBall.ly)*(tBall.yVec/ballspeed));
			  double f = (distcircles*distcircles) - (d*d);
				 if(sqrt(f) < (double)sumradii){
	
					double newmagnitude;
						newmagnitude = (sumradii*sumradii)- f;
						if(newmagnitude >= 0){
						newmagnitude = d - sqrt(newmagnitude);

							if(newmagnitude <= ballspeed){
	  
							 float newx;
							 float newy;
	
							newx = tBall.lx + ((tBall.xVec/ballspeed)*newmagnitude);
							newy = tBall.ly + ((tBall.yVec/ballspeed)*newmagnitude);  
	
							double distcollision = sqrt( 
								    ((tBall.lx - newx)*(tBall.lx - newx))+
									((tBall.ly - newy)*(tBall.ly - newy))
									);

							 if(distcollision < fltSaveDist){
								
								 if(pcolor == WHITE){ 
								cBall.x = newx;
								cBall.y = newy;
								cBall.xVec = -tBall.xVec;
								cBall.yVec = -tBall.yVec;
								passed = true;
								 }else{
									cBall.belongsTo = pcolor;
									passed = true;
								 }
						
							 }
							}
						}
				 }
			 }
		}

return cBall;

}


ball ballpaddlecollision(ball tBall, paddle testPaddle, ball PaddleBall, paddle lastpad){
	
	//modify the response code.  YAY!!!!!!1111one
	
float xlol;
float ylol;

float TOP;
float BOTTOM;
float LEFT;
float RIGHT;

float topint[2];
float bottomint[2];
float leftint[2];
float rightint[2];

float distleft = 100000;
float distright = 100000;
float disttop = 100000;
float distbottom = 100000;


paddle extruded = testPaddle;
extruded.x = ((float)extruded.x + (float)lastpad.x)/2;
extruded.width = (extruded.width + abs((testPaddle.x)- extruded.x));

//paddlexex= extruded.x;
//paddlewidthex=extruded.width;

TOP = extruded.y - extruded.height - tBall.radius;
BOTTOM = extruded.y + extruded.height + tBall.radius;
LEFT = extruded.x - extruded.width - tBall.radius;
RIGHT = extruded.x + extruded.width+ tBall.radius;


//TOP
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
			xlol = ((float)TOP - b) / m;
			topint[0] = xlol;
			topint[1] = TOP;
			
			disttop = sqrt( (((float)tBall.lx - (float)topint[0])*((float)tBall.lx - (float)topint[0]))      
					+(((float)tBall.ly - (float)topint[1])*((float)tBall.ly - (float)topint[1]))
					);

				if((LEFT <= xlol) && (xlol <=RIGHT)){
					if((lowx <= xlol) && (xlol <= highx)){
						if((lowy <= TOP) && (TOP <= highy)){
							//if (disttop<fltSaveDist){
								fltSaveDist = disttop;
								
								

								cBall.xVec = tBall.xVec;
								
								cBall.yVec = -tBall.yVec;
							
								cBall.x = topint[0];
								cBall.y = topint[1]-BUFFERDIST;
								//cBall.xVec = PaddleBall.xVec + cBall.xVec;
								//cBall.yVec = PaddleBall.yVec + cBall.yVec;
								passed = true;
								

							//}
							
						}
					}
				}
///////////////////////////////////////////////////////////			
////////////////////////////////////////////////////////////			
		xlol = ((float)BOTTOM - b)/m;
			bottomint[0] = xlol;
			bottomint[1] = BOTTOM;
			distbottom = sqrt( (((float)tBall.lx - (float)bottomint[0])*((float)tBall.lx - (float)bottomint[0]))      
					+(((float)tBall.ly - (float)bottomint[1])*((float)tBall.ly - (float)bottomint[1]))
					);
			
			if((xlol >= LEFT) && (xlol <= RIGHT)){//				
				if((lowx <= xlol) && (xlol <= highx)) {
					if((lowy <= BOTTOM) && (BOTTOM <= highy)){	
					//	if (distbottom<fltSaveDist){
								fltSaveDist = distbottom;

							
								
								cBall.xVec = tBall.xVec;
								cBall.yVec = -tBall.yVec;
								cBall.x = bottomint[0];
								cBall.y = bottomint[1]+BUFFERDIST;//+(cBall.yVec*rTime);
					
								//cBall.xVec = PaddleBall.xVec + cBall.xVec;
								//cBall.yVec = PaddleBall.yVec + cBall.yVec;
								passed = true;
								
							//}
							
						}
					}
				}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
ylol = (m*(float)RIGHT) + b;
	rightint[0] = RIGHT;
	rightint[1] = ylol;
	distright = sqrt( (((float)tBall.lx - (float)rightint[0])*((float)tBall.lx - (float)rightint[0]))      
					+(((float)tBall.ly - (float)rightint[1])*((float)tBall.ly - (float)rightint[1]))
					);

if((ylol >= TOP) && (ylol <= BOTTOM)) {//		
	if((lowy <= ylol) && (ylol <= highy)) {
		if((lowx <= RIGHT) && (RIGHT <= highx)){
				//if (distright<fltSaveDist){

								fltSaveDist = distright;

								
								
								cBall.xVec = -tBall.xVec;
								if(cBall.xVec < 0){bBall.xVec *= -1;}

								cBall.yVec = -tBall.yVec;

								cBall.x =rightint[0]+BUFFERDIST;//+(cBall.xVec*rTime);
								cBall.y =rightint[1];
							
								//cBall.xVec = PaddleBall.xVec + cBall.xVec;
								//cBall.yVec = PaddleBall.yVec + cBall.yVec;
								passed = true;
							
							//}
			}
		}
	}
//////////////////////////////////////////////////////
/////////////////////////////////////////////////////
ylol = (m*(float)LEFT) + b;
	leftint[0] = LEFT;
	leftint[1] = ylol;
	distleft = sqrt((((float)tBall.lx - (float)leftint[0])*((float)tBall.lx - (float)leftint[0]))      
					+(((float)tBall.ly - (float)leftint[1])*((float)tBall.ly -(float)leftint[1]))
					);

if(ylol >= TOP && ylol <= BOTTOM){//		
	if((lowy <= ylol) && (ylol <= highy)){
		if(( lowx <= LEFT) && (LEFT <= highx)){ 
				//if (distleft<fltSaveDist){

							fltSaveDist = distleft;

							cBall.xVec = -tBall.xVec;
							if(cBall.xVec >0){cBall.xVec *= -1;}

							cBall.yVec = -tBall.yVec;
							cBall.x = leftint[0]-BUFFERDIST;//+(cBall.xVec*rTime);
							cBall.y = leftint[1];
							
								//cBall.xVec = PaddleBall.xVec + cBall.xVec;
								//cBall.yVec = PaddleBall.yVec + cBall.yVec;
							passed = true;
					//}
			}
						
		}
	}
	
//cBall.xVec = (cBall.xVec/(sqrt(pow((double)cBall.xVec,2)+pow((double)cBall.yVec,2))))*tBall.speed;
//cBall.yVec = (cBall.yVec/(sqrt(pow((double)cBall.xVec,2)+pow((double)cBall.yVec,2))))*tBall.speed;

//if not passed

disttop = sqrt( (((float)tBall.x - (float)topint[0])*((float)tBall.x - (float)topint[0]))      
					+(((float)tBall.y - (float)topint[1])*((float)tBall.y - (float)topint[1]))
					);

distright = sqrt( (((float)tBall.x - (float)rightint[0])*((float)tBall.x - (float)rightint[0]))      
					+(((float)tBall.y - (float)rightint[1])*((float)tBall.y - (float)rightint[1]))
					);

distleft = sqrt((((float)tBall.x - (float)leftint[0])*((float)tBall.x - (float)leftint[0]))      
					+(((float)tBall.y - (float)leftint[1])*((float)tBall.y -(float)leftint[1]))
					);

distbottom = sqrt( (((float)tBall.x - (float)bottomint[0])*((float)tBall.x - (float)bottomint[0]))      
					+(((float)tBall.y - (float)bottomint[1])*((float)tBall.y - (float)bottomint[1]))
					);



if(cBall.x >= LEFT && cBall.x <= RIGHT){
	if(cBall.y >= TOP && cBall.y <= BOTTOM){
		if(distleft < distright //&& distleft <= disttop && distleft <= distbottom
			){
							cBall.xVec = tBall.xVec;
							if(cBall.xVec/std::abs(cBall.xVec) != PaddleBall.xVec/std::abs(PaddleBall.xVec)){
								cBall.xVec = -cBall.xVec;
							}
							
							/////////////////////////////
							cBall.yVec = -tBall.yVec;
							//////////////////////////////

							cBall.x = leftint[0]-BUFFERDIST;//+(cBall.xVec*rTime);
							//cBall.y = leftint[1];
							passed = true;
		}
		if(distright <= distleft //&& distright <= disttop && distright <= distbottom
			){
							cBall.xVec = tBall.xVec;
							if(cBall.xVec/abs(cBall.xVec) != PaddleBall.xVec/abs(PaddleBall.xVec)){
								cBall.xVec = -cBall.xVec;
							}
							
							////////////////////////
							cBall.yVec = -tBall.yVec;
							///////////////////////////////

							cBall.x =rightint[0]+BUFFERDIST;//+(cBall.xVec*rTime);
							//cBall.y =rightint[1];
							passed = true;
		}

		passed = TRUE;
	}
}


if(cBall.y > MAPBARRIER/2 && cBall.yVec >0 && passed){cBall.yVec*=-1;}
if(cBall.y < MAPBARRIER/2 && cBall.yVec <0 && passed){cBall.yVec*=-1;}

return cBall;


}
