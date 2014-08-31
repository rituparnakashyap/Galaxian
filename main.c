#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

/* ////////////////////////////////// A QUEUE THAT STORES THE CO-ORDINATE OF THE FIRE AT ANY INSTANT //////////////////////////////// */

struct queqe
{
	int arr[2][46];                            
	int front,rear;
}*q;
char key;
time_t t_skull1[4],t_skull2[4];
int timecon_skull[2][4]={1,1,1,1,1,1,1,1},skullloop[4]={0,0,0,0};
int skull_x_pos[4],damage[5]={10,10,10,10,100},score=0;
int mainloop=0,gnballx,gnbally,rdballx,rdbally,bnballx,bnbally;
int yeballx,yebally,mgballx,mgbally,wtballx,wtbally,cyballx,cybally,blballx,blbally;
int levels;

/* /////////////////////////////////////FUNCTION POTOTYPE DETAILS IN THE HELP FILE/////////////////////////////////////////////////// */

void hitman(void);
void fire(int pos);
void skullpic(int);
void tank(int pos);
void loading(int i);
void credit(void);
void damage_count(int j);
void gameover(int i);
void col_ball(void);
void level(void);
int hig_scr(void);
void main()
{
	int i,gd,gm;
	gd=DETECT;
	q->front=0;
	q->rear=0;
	initgraph(&gd,&gm,"C:\\TC\\BGI");                   /* DIRECTORY OF THE TC */
	setbkcolor(BLACK);
	setcolor(RED);
	rectangle(3,3,getmaxx()-5,getmaxy()-2);             /* BOUNDARY OF THE GAME */ 
	setcolor(CYAN);
	settextstyle(0, HORIZ_DIR, 9);
	outtextxy(40,20,"GALAXIAN");
	settextstyle(4,HORIZ_DIR,2);
	outtextxy(300,100,"v1.0.1");
	for(i=0;i<100;i++)
	{
		loading(i);
	}
	i=1000;
	do
	{
		setcolor(GREEN);
		setviewport(5,250,getmaxx()-7,400,4);
		outtextxy(250,50,"GAME");
		outtextxy(250,75,"CREDIT");
		outtextxy(250,100,"EXIT");
		setcolor(RED);
		rectangle(245,(i%3)*25+45,300,(i%3)*25+65);           /* RED SQURE BOX IN THE MENU */
		key=getch();
		if(key=='w')
		{
			i--;
		}
		if(key=='s')
		{
			i=i++;
		}
		clearviewport();
	}while(key!='f');
	switch(i%3)
	{
		case 0:
			level();
			break;
		case 1:
			credit();
			break;
		case 2:
			exit(1);
	}
	closegraph();
}
void hitman(void)
{
	int gd,gm=1,pos=319,i,j,shot_pos[46];

   
/* ///////////////////// pos IS INITIALISED TO THE MIDDLE OF THE SCREEN WHERE THE TANK IS FIRST LOCATED ////////////////////////// */


	gd=0;
	damage[0]=10;                                                /* INITIALISATION OF EFFICIENCY OF SKULL TO 10 */                              damage[1]=10;
	damage[2]=10;
	damage[3]=10;
	damage[4]=100;                                                /* INITIALISATION OF TANK EFFIENCY TO 100 */                          
	score=0;                                                      /* SCORE INITIALISED TO 0 */
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	setbkcolor(BLACK);
	setcolor(CYAN);
	outtextxy(270,5,"GALAXIAN v1.0.1");
	setcolor(RED);
	rectangle(3,3,getmaxx()-5,getmaxy()-2);
	do
	{
		gotoxy(2,2);
		printf("Tanks effiency is %3d%%",damage[4]);                 /* PRINTING THE EFFIENCY OF TANK IN THE SCREEN */
		gotoxy(65,2);
		printf("Score %3d",score);                                   /* PRINTING THE SCORE IN THE SCREEN */  
		if(mainloop==300)
		{
			damage_count(4);
			mainloop=0;
			randomize();                                           /* SETTING A RANDOM CO-ORDINATES IN THE SCREEN OF BALLS */
			gnballx=random(10)*20;
			gnbally=random(10)*10;
			rdballx=400-random(10)*20;
			rdbally=random(10)*10;
			bnballx=600-random(10)*20;
			bnbally=random(10)*10;
			yeballx=200+random(10)*20;
			yebally=random(10)*10;
			mgballx=140+random(10)*20;
			mgbally=random(10)*10;
			wtballx=500-random(10)*20;
			wtbally=random(10)*10;
			cyballx=50+random(10)*20;
			cybally=random(10)*10;
			blballx=300+random(10)*10;
			blbally=random(10)*10;

		}
		for(i=0;i<4;i++)
		{
			if(timecon_skull[1][i]==1 && timecon_skull[0][i]==1)       /* TEST TO SET THE t_skull[i] VARIABLES */
			{
				t_skull1[i]=time(NULL);
				timecon_skull[1][i]=0;
			}
		}
		if(q->front==q->rear)                                              /* IF THERE IS NO FIRE OF TANK IN THE SCREEN */
		{
			q->front=0;
			q->rear=0;
			setviewport(5,150,getmaxx()-7,430,3);
			col_ball();                                                /* CALL TO THE col_ball() FUNCTION */    
			delay(50/levels);
			clearviewport();

		}
		else                                                                /* IF THERE PRESENT ANY FIRE OF TANK IN SCREEN */
		{
			setviewport(5,150,getmaxx()-7,430,3);
			col_ball();
			for(i=q->front;i<=q->rear;i++)
			{
/* ///////////////////////////////////////////DISPLAYING THE TANK FIRE IN THE SCREEN ////////////////////////////////////////////// */
				if(q->arr[1][i]!=0)
				{
					setcolor(GREEN);
					rectangle(q->arr[0][i]-5,q->arr[1][i],q->arr[0][i]+2-5,q->arr[1][i]+10);
					floodfill(((q->arr[0][i]-5)+(q->arr[0][i]+2-5))/2,((q->arr[1][i])+(q->arr[1][i]+10))/2,GREEN);
					q->arr[1][i]=q->arr[1][i]-10;
				}
				else
				{
					for(j=0;j<4;j++)                   /* LOOKING FOR CONDITION IF THE IS ANY HIT OF FIRE WITH SKULL */
					{
						if((q->arr[0][q->front]<=skull_x_pos[j]+40) && (q->arr[0][q->front]>=skull_x_pos[j]-40) && timecon_skull[0][j]==1)
						{
							damage_count(j);
						}
					}
					q->front=(q->front+1);
				}
			}
			delay(50/levels);
			clearviewport();
		}

/* /////////////////////////////////LOOKING FOR THE CONDITION IF THE IS ANY HIT OF COLORED BALL WITH THE TANK ////////////////////// */

		if(gnbally==280)
		{
			if(gnballx>=pos-25 && gnballx<=pos+25)
			{
				damage_count(4);
			}
		}
		if(rdbally==280)
		{
			if(rdballx>=pos-25 && rdballx<=pos+25)
			{
				damage_count(4);
			}
		}
		if(yebally==280)
		{
			if(yeballx>=pos-25 && yeballx<=pos+25)
			{
				damage_count(4);
			}
		}
		if(bnbally==280)
		{
			if(bnballx>=pos-25 && bnballx<=pos+25)
			{
				damage_count(4);
			}
		}
		if(mgbally==280)
		{
			if(mgballx>=pos-25 && mgballx<=pos+25)
			{
				damage_count(4);
			}
		}
		if(wtbally==280)
		{
			if(wtballx>=pos-25 && wtballx<=pos+25)
			{
				damage_count(4);
			}
		}
		if(cybally==280)
		{
			if(cyballx>=pos-25 && cyballx<=pos+25)
			{
				damage_count(4);
			}
		}
		if(blbally==280)
		{
			if(blballx>=pos-25 && blballx<=pos+25)
			{
				damage_count(4);
			}
		}
		for(i=0;i<4;i++)
		{
			if(timecon_skull[0][i]==1)
			{
				skullpic(i);
			}
		}
		key='o';
		if(kbhit()!=0)                                       /* CONSIDERING ANY KEYBOARD HIT */
		{
			key=getch();
			if(key == 'd')
			{
				if(pos>605)
					pos=pos;
				else
					pos=pos+4;
				key='p';
			}
			if(key == 'a')
			{
				if(pos<35)
					pos=pos;
				else
					pos=pos-4;
				key='p';
			}
			if(key == 'k')
			{
				fire(pos);
				key='p';
			}
		}

		tank(pos);                                     /* //////////////////// CALLING THE TANK FUNCTION ///////////////// */


		if(damage[0]==0 && damage[1]==0 && damage[2]==0 && damage[3]==0)   /* ///// CONSIDERING THE WINNING CONDITION //////// */ 
		{
			gameover(0);
		}
		if(damage[4]<=0)                               /*  /////////////////CONSIDERING THE LOSSING CONDITION ///////////  */
		{
			gameover(1);
		}
		mainloop++;
	}while(key!='q');
	if(key=='q')                                          /* ///////////////// CONSIDERING THE PREMATURE EXIT //////////////// */
	{
		gameover(2);
	}
	closegraph();
}
void tank(int pos)
{
	setcolor(BLUE);
	setviewport(pos-20,430,pos+20,460,2);
	ellipse(20,20,0,360,4,6);
	rectangle(21,0,20,20);
	rectangle(10,10,30,30);
	if(key=='p')
	{
		clearviewport();
	}
}
void fire(int pos)
{
	int tem,i;
	tem=(q->rear+1);
	if(tem!=q->front)
	{
		q->rear=tem;
		q->arr[0][q->rear]=pos;                      /* INILISATION OF THE X AND Y CO-ORDINATE OF THE FIRE OF THE TANK */
		q->arr[1][q->rear]=280;
	}

}
void skullpic(int i)
{
	int j,x,y,skull_pos;
	if(skullloop[i]>=1000)
	{
		skullloop[i]=0;
	}
	if((skullloop[i]%3)>1)
	{
		skull_pos=skullloop[i]%3-1;
	}
	else
	{
		skull_pos=skullloop[i]%3-1;
	}
	x=100+i*150+skull_pos*12;
	skull_x_pos[i]=x;
	y=100;
	setviewport(x-50,y-35,x+50,y+50,1);
	clearviewport();

/* //////////////////////////////////////////// SHOWING THE DAMAGE STATUS OF THE SKULL //////////////////////////////////// */
	switch(damage[i])
	{
		case 10:
		case 9:
		case 8:
		case 7:
			setcolor(GREEN);
			rectangle(30,10,70,20);
			for(j=1;j<10;j++)
			{
				moveto(30+j*4,10);
				linerel(0,10);
			}
			break;
		case 6:
		case 5:
		case 4:
			setcolor(CYAN);
			rectangle(30,10,54,20);
			for(j=1;j<6;j++)
			{
				moveto(30+j*4,10);
				linerel(0,10);
			}
			break;
		case 3:
		case 2:
		case 1:
			setcolor(RED);
			rectangle(30,10,42,20);
			for(j=1;j<3;j++)
			{
				moveto(30+j*4,10);
				linerel(0,10);
			}
			break;
	}
	setcolor(MAGENTA);
	arc(50,50,300,240,10);
	line(50+10*0.5,50+10*0.8660,50+10*0.5,50+10*0.8660+2);
	line(50-10*0.5,50+10*0.8660,50-10*0.5,50+10*0.8660+2);
	line(50-10*0.5+2,50+10*0.8660,50-10*0.5+2,50+10*0.8660+2);
	line(50-10*0.5+4,50+10*0.8660,50-10*0.5+4,50+10*0.8660+2);
	line(50-10*0.5+6,50+10*0.8660,50-10*0.5+6,50+10*0.8660+2);
	line(50-10*0.5+8,50+10*0.8660,50-10*0.5+8,50+10*0.8660+2);
	line(50-10*0.5+10,50+10*0.8660,50-10*0.5+10,50+10*0.8660+2);
	circle(50+3,50-2,2);
	circle(50-3,50-2,2);
	moveto(50,50+3);
	linerel(-1,sqrt(3.0));
	linerel(2,0);
	lineto(50,50+3);
	moveto(50-18,50);
	linerel(30,30);
	circle(50-19,50,2);
	moveto(50-20,50);
	linerel(30,30);
	circle(50+11,50+30,2);
	moveto(50+18,50);
	linerel(-30,30);
	circle(50+19,50,2);
	moveto(50+20,50);
	linerel(-30,30);
	circle(50-11,50+30,2);
	t_skull2[i]=time(NULL);

/* ///////////////////////////////////////////// CONSIDERING THE OPENING AND THE CLOSING OF THE JAWS OF THE SKULL ///////////////////// */

	if(skullloop[i]%2==0)
	{
		moveto(50+5,50+14);
		linerel(-10,0);
		for(j=0;j<6;j++)
		{
			moveto(50-5+j*2,50+14);
			linerel(0,-2);
		}
		if(difftime(t_skull2[i],t_skull1[i])>=1)         /* DETERMINING IF THE TIME DIFFRERENCE IN 1 SEC */
		{
			skullloop[i]++;
			timecon_skull[1][i]=1;
			clearviewport();
		}
	}
	else
	{
		moveto(50+5,50+13);
		linerel(-10,0);
		for(j=0;j<6;j++)
		{
			moveto(50-5+j*2,50+13);
			linerel(0,-2);
		}
		if(difftime(t_skull2[i],t_skull1[i])>=1)
		{
			skullloop[i]++;
			timecon_skull[1][i]=1;
			clearviewport();
		}
      }
}
void loading(int i)
{
	int j;
	setviewport(5,275,getmaxx()-7,375,1);                 /* SETTING THE LOADING VIEW PORT */
	setcolor(GREEN);
	outtextxy(240,40,"LOADING.......");
	rectangle(200,50,400,75);
	setcolor(RED);
	rectangle(201,51,200+i*2,74);
	for(j=1;j<i*2;j++)
	{
		moveto(201+j,51);
		linerel(0,23);
	}
	settextstyle(0,HORIZ_DIR,1);
	setcolor(GREEN);
	delay(40);
	clearviewport();
}
void credit(void)
{
	int i,gd,gm;
	gd=DETECT;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	setbkcolor(BLACK);
	setcolor(RED);
	rectangle(3,3,getmaxx()-5,getmaxy()-2);
	setcolor(CYAN);
	settextstyle(0, HORIZ_DIR, 9);
	outtextxy(40,20,"GALAXIAN");
	settextstyle(4,HORIZ_DIR,2);
	outtextxy(300,100,"v1.0.1");
	setcolor(RED);
	settextstyle(3,HORIZ_DIR,2);
	for(i=5;i<500;i++)
	{
		rectangle(4,200,i,450);
		floodfill((4+i)/2,400,RED);
		delay(6);
	}
	setcolor(CYAN);
	for(i=20;i<200;i++)
	{
		circle(i,230,10);
		floodfill(i,220,CYAN);
		delay(10);
	}
	setcolor(BLUE);
	outtextxy(50,215,"Created By .....");
	setcolor(CYAN);
	for(i=400;i>150;i--)
	{
		circle(i,350,10);
		floodfill(i,350,CYAN);
		delay(10);
	}
	setcolor(BLUE);
	outtextxy(200,335,"Rituparna Kashyap.");
	setcolor(CYAN);
	for(i=400;i>150;i--)
	{
		circle(i,375,10);
		floodfill(i,375,CYAN);
		delay(10);
	}
	setcolor(BLUE);
	outtextxy(200,360,"C.S.E 2nd Year.");
	setcolor(CYAN);
	for(i=400;i>150;i--)
	{
		circle(i,400,10);
		floodfill(i,400,CYAN);
		delay(10);
	}
	setcolor(BLUE);
	outtextxy(200,385,"U.I.T,B.U.");
	setcolor(CYAN);
	for(i=400;i>150;i--)
	{
		circle(i,425,10);
		floodfill(i,425,CYAN);
		delay(10);
	}
	setcolor(BLUE);
	outtextxy(200,410,"Batch 2006-10.");
	delay(10000);
	closegraph();
}
void damage_count(int i)
{
	int x,y;
	damage[i]--;
	if(i!=4)
	{
		score=score+10;
	}
	else
	{
		score=score-7;                           /* SCORE REDUCED BY 7 IF BEING HIT */
		damage[4]=damage[4]-4;
	}
/* /////////////////////////////////////CLEARING THE VIEW PORT OF THE SKULL IF DISTROYED //////////////////////////////// */
	if(damage[i]==0)
	{
		timecon_skull[0][i]=0;
		x=100+i*150;
		y=100;
		setviewport(x-55,y-40,x+55,y+50,1);
		clearviewport();
	}

}
void gameover(int choice)
{
	int gd=DETECT,gm,i,j,randnum;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	setcolor(RED);
	rectangle(1,3,getmaxx()-5,getmaxy()-2);
	setcolor(CYAN);
	randomize();
	for(i=4;i<getmaxx()-6;i++)
	{
		randnum=random(i);
		rectangle(randnum,4,randnum+4,getmaxy()-3);
		floodfill((randnum+randnum+4)/2,(4+getmaxy()-3)/2,CYAN);
		delay(10);
	}
	setcolor(GREEN);
	for(i=0;i<500;i++);
	{
		for(j=0;j<i;j++)
		{
			moveto(j,150);
			linerel(0,250);
			delay(4);
		}
	}
	setcolor(BLUE+BLINK);
	settextstyle(8, HORIZ_DIR, 5);
	outtextxy(150,175,"GAME OVER");
	if(choice==0)
	{
		setcolor(MAGENTA);
		settextstyle(6, HORIZ_DIR, 4);
		outtextxy(125,250,"Congratulation You Won!!!");
	}
	if(choice==1)
	{
		setcolor(MAGENTA);
		settextstyle(6, HORIZ_DIR, 4);
		outtextxy(160,250,"Sorry You Lose !!!");
	}
	if(choice==2)
	{
		setcolor(MAGENTA);
		settextstyle(6, HORIZ_DIR, 4);
		outtextxy(150,250,"Are You Tired???");
	}
	setcolor(MAGENTA);
	outtextxy(175,285,"Your Score:");
	settextstyle(1, HORIZ_DIR, 3);
	gotoxy(43,20);
	printf("%d",score);
	settextstyle(1, HORIZ_DIR, 3);
	outtextxy(175,328,"Higest Score:");
	gotoxy(43,22);
	printf("%d",hig_scr());
	delay(6000);
	exit(1);
	closegraph();
}
void col_ball(void)
{
	setcolor(GREEN);
	circle(gnballx++,gnbally++,10);
	setcolor(RED);
	circle(rdballx--,rdbally++,10);
	setcolor(BROWN);
	circle(bnballx--,bnbally++,10);
	setcolor(YELLOW);
	circle(yeballx++,yebally++,10);
	setcolor(MAGENTA);
	circle(mgballx++,mgbally++,10);
	setcolor(WHITE);
	circle(wtballx--,wtbally++,10);
	setcolor(CYAN);
	circle(cyballx++,cybally++,10);
	setcolor(BLUE);
	circle(blballx++,blbally++,10);
}
int hig_scr(void)
{
	FILE *fp;
	int higscr;
	fp=fopen("HIGSCR.TXT","r");                             /* OPENING THE HIGSCR.TXT FILE */
	higscr=getw(fp);
	fclose(fp);
	if(higscr>=score)
	{
		return(higscr);
	}
	else
	{
		fp=fopen("HIGSCR.TXT","w");                      /* WRITING OVER THE HIGSCR.TXT IF HIGEST SCORE IS BROKEN */
		putw(score,fp);
		fclose(fp);
		return(score);
	}
}
void level(void)
{
	int i=1000;
	do
	{
		setcolor(GREEN);
		setviewport(5,250,getmaxx()-7,400,4);
		outtextxy(250,50,"LEVEL 1");
		outtextxy(250,75,"LEVEL 2");
		outtextxy(250,100,"LEVEL 3");
		setcolor(RED);
		rectangle(245,(i%3)*25+45,310,(i%3)*25+65);
		key=getch();
		if(key=='w')
		{
			i--;
		}
		if(key=='s')
		{
			i++;
		}
		clearviewport();
	}while(key!='f');

/* ///////////////////////////////////////////// CALLING HITMAN FUNCTION WITH DIFFERENT LEVELS//////////////////////////////// */

	switch(i%3)
	{
		case 0:
			levels=1;
			hitman();
			break;
		case 1:
			levels=2;
			hitman();
			break;
		case 2:
			levels=3;
			hitman();
			break;
	}
}
