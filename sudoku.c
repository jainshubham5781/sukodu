///*******++++++*************** SUDOKU ********++++++++++***********\\\


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<malloc.h>
union REGS ip,op;
int initmouse()
{
	ip.x.ax = 0;
	int86(0X33,&ip,&op);
	return(op.x.ax);
}
void showmouseptr()
{
	ip.x.ax = 1;
	int86(0X33,&ip,&op);
}
void hidemouseptr()
{
	ip.x.ax = 2;
	int86(0X33,&ip,&op);
}

struct node
{
	int arr;
	int xx;
	int yy;
	int count;
	struct node *down;
	struct node *link;
};
struct coord
{
	int x;
	int y;
}pope;
struct stack
{
	struct coord *a;
	int top;
}s;

void undo(struct coord);    //undo
void pusho();               //undo
void push(int , int );      //undo

void move(char ch);               //move up down lft rit
void checking();                  // process of chekng
void loss();                     // game over
void win();                     // win
//void thanku();                     //last page
void allfilled();                   /// 1check allfilling
void grid1();                      // front page grid
void front();                     // front page
void grid();                       // sudoku grig
void f3(char ch,int x,int y);        // scanning
void pprint();                          //printing
struct node *create1(struct node *end);           //linking row
struct node *create2(struct node *start);        // matrix making
struct node *create();                           // crete down
int check();                                //2 check row/colm
void block();                               // 3 check block
void winlossbutton();                      // exit/main menu button
int bcheck(int a[9]);                       //  chcking
void display(int a,int x,int y);            // handwriting no.
void button();                             // buttons
void second();                                   // mainmenu page
void level();                                // selct level
void thankyou();                             //   last page
void credit();                             // credit
void instructions();                           // instruction
void one(int x,int y);                      //numbers
void two(int x,int y);
void three(int x,int y);
void five(int x,int y);
void six(int x,int y);
void seven(int x,int y);
void four(int x,int y);
void eight(int x,int y);
void nine(int x,int y);

char ch;
int x,y,all=0,p=5;

struct node *temp,*start=NULL,*end;
struct node *temp1,*start1=NULL,*end1,*temp2;

void easy();                            // levels
void medium();
void hard();


void main()
{
	int gdriver=0,gmode,a,c;
      //	int x=140,y=80;
	initgraph(&gdriver,&gmode,"C:\\TURBOC3\\BGI");
	cleardevice();
	front();
	s.top=0;
	pusho();
	start=create();
	start=create2(start);

	second();
	setcolor(2);
	getch();
	clrscr();
}


void pusho()                                   // push stack
{
	if((s.top)<5)
	{
		(s.a+(s.top))->x=99;
		(s.a+(s.top))->y=99;
		(s.top)++;
		pusho();
	}

}


void push(int x,int y)                    // pushing num
{
	int i;
	if(s.top-1==4)
	{
	for(i=0;i<4;i++)
	{
		((s.a)+i)->x=((s.a)+(i+1))->x;
		((s.a)+i)->y=((s.a)+(i+1))->y;
	}
	}
	if((s.top-1)<4)
	(s.top)++;
	((s.a)+(s.top-1))->x=x;
	((s.a)+(s.top-1))->y=y;

}

struct coord pop()                                  //poping
{
	pope.x=((s.a)+(s.top-1))->x;
	pope.y=((s.a)+(s.top-1))->y;
	s.top=s.top-1;
	return pope;
}

//////////////////////////undo////////////////////////////
void undo(struct coord pope)                     // undoo
{
	struct node *ttemp,*tttemp;
	int x1,y1,i,j;

	cleardevice();
		grid();
		pprint();

		setcolor(5);
		setfillstyle(11,1);
		setlinestyle(0,1,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-210,140+(8*34)+150,80+(8*34)+60-210,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-210,"HECK");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-210,"C");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-210,140+(8*34)+84,80+(8*34)+55-210);
		settextstyle(11,0,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-130,140+(8*34)+150,80+(8*34)+60-130,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-130,"ACK");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-130,"B");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-130,140+(8*34)+84,80+(8*34)+55-130);
		settextstyle(11,0,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-50,140+(8*34)+150,80+(8*34)+60-50,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-50,"XIT");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-50,"E");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-50,140+(8*34)+84,80+(8*34)+55-50);
		settextstyle(11,0,1);

		 setcolor(1);
		setfillstyle(11,1);
		bar(140+(8*34)+50+3,80+(8*34)+30-300+3,140+(8*34)+150-3,80+(8*34)+60-300-3);
		settextstyle(2,0,6);
		setcolor(15);
		outtextxy(140+(8*34)+67+10,80+(8*34)+21-285,"Undo");
		settextstyle(1,0,1);
		setcolor(5);
			delay(700);

		button();

	x1=pope.x;
	y1=pope.y;

      ttemp=start;
      tttemp=start;
      for(i=0;i<9;i++)
      {
	tttemp=ttemp;
	for(j=0;j<9;j++)
	{
		if(ttemp->xx==x1&&ttemp->yy==y1)
		{
			ttemp->arr=99;
			ttemp->count=0;
			break;
		}
		else
			ttemp=ttemp->link;
	 }
	ttemp=tttemp->down;
	}

}
////////////////////////////easy level////////////////////////
void easy()
{

	struct node*temp,*temp1,*temp2,*tempr;
	  grid();
	  p=5;
	  rectangle(140-17,80-17,140+17,80+17);
	temp=start;
	settextstyle(11,0,1);
	tempr=start;
	temp1=start;
	setcolor(RED);
	temp->arr=3;
	temp->count=2;

	outtextxy(140,80,"3");
	temp=temp->link;

	 temp->arr=1;
	 temp->count=2;

       outtextxy(174,80,"1");
	temp=temp->link;

	temp->arr=2;
		temp->count=2;

	outtextxy(208,80,"2");
	temp=temp->link->link;

	  temp->arr=9;
		temp->count=2;


	  outtextxy(276,80,"9");
	  temp=temp->link;

	  temp->arr=5;
		temp->count=2;

	outtextxy(310,80,"5");
	temp=temp->link->link;

	temp->arr=7;
		temp->count=2;

	outtextxy(378,80,"7");
	temp=temp->link;

	temp->arr=6;
	temp->count=2;
	outtextxy(412,80,"6");

	tempr=tempr->down;
	temp=tempr;

	temp->arr=5;
	temp->count=2;
	outtextxy(140,114,"5");
	temp=temp->link->link;

	temp->arr=9;
	temp->count=2;
	outtextxy(208,114,"9");
	temp=temp->link;

	temp->arr=1;
	temp->count=2;
	outtextxy(242,114,"1");
	temp=temp->link->link;

	 temp->arr=7;
	temp->count=2;
	outtextxy(310,114,"7");
	temp=temp->link->link;

	 temp->arr=8;
	temp->count=2;
	outtextxy(378,114,"8");
	temp=temp->link;

	temp->arr=2;
	temp->count=2;
	outtextxy(412,114,"2");

	tempr=tempr->down;
	temp=tempr;

	temp->arr=4;
	temp->count=2;
	outtextxy(140,148,"4");
	temp=temp->link->link;

	temp->arr=7;
	temp->count=2;
	outtextxy(208,148,"7");
	temp=temp->link;

	temp->arr=2;
	temp->count=2;
	outtextxy(242,148,"2");
	temp=temp->link;

	temp->arr=6;
	temp->count=2;
	outtextxy(276,148,"6");
	temp=temp->link;

	temp->arr=3;
	temp->count=2;
	outtextxy(310,148,"3");
	temp=temp->link;

	temp->arr=5;
	temp->count=2;
	outtextxy(344,148,"5");

	tempr=tempr->down;
	temp=tempr;

	temp->arr=9;
	temp->count=2;
	outtextxy(140,182,"9");
	temp=temp->link->link->link;

	temp->arr=7;
	temp->count=2;
	outtextxy(242,182,"7");
	temp=temp->link->link->link;


	temp->arr=2;
	temp->count=2;
	outtextxy(344,182,"2");
	temp=temp->link;

	temp->arr=4;
	temp->count=2;
	outtextxy(378,182,"4");

	tempr=tempr->down;
	 temp=tempr;

	 temp=temp->link;
	 temp->arr=2;
	temp->count=2;
	outtextxy(174,216,"2");
	temp=temp->link;


	 temp->arr=8;
	temp->count=2;
	outtextxy(208,216,"8");
	temp=temp->link->link;

	temp->arr=1;
	temp->count=2;
	outtextxy(276,216,"1");
	temp=temp->link->link->link;

	temp->arr=9;
	temp->count=2;
	outtextxy(378,216,"9");
	temp=temp->link;


	temp->arr=3;
	temp->count=2;
	outtextxy(412,216,"3");

	tempr=tempr->down;
	temp=tempr;

	temp=temp->link;

	temp->arr=3;
	temp->count=2;
	outtextxy(174,250,"3");
	temp=temp->link->link;

		temp->arr=9;
	temp->count=2;
	outtextxy(242,250,"9");
	temp=temp->link;

		temp->arr=8;
	temp->count=2;
	outtextxy(276,250,"8");
	temp=temp->link;

		temp->arr=2;
	temp->count=2;
	outtextxy(310,250,"2");
	temp=temp->link->link;

		temp->arr=5;
	temp->count=2;
	outtextxy(378,250,"5");
	temp=temp->link;

		temp->arr=7;
	temp->count=2;
	outtextxy(412,250,"7");

	tempr=tempr->down;
	temp=tempr;

	temp=temp->link;

		temp->arr=4;
	temp->count=2;
	outtextxy(174,284,"4");
	temp=temp->link;

		temp->arr=5;
	temp->count=2;
	outtextxy(208,284,"5");
	temp=temp->link;

		temp->arr=6;
	temp->count=2;
	outtextxy(242,284,"6");
	temp=temp->link->link->link->link;

		temp->arr=3;
	temp->count=2;
	outtextxy(378,284,"3");
	temp=temp->link;

		temp->arr=1;
	temp->count=2;
	outtextxy(412,284,"1");

	tempr=tempr->down;
	temp=tempr;

		temp->arr=1;
	temp->count=2;
	outtextxy(140,318,"1");
	temp=temp->link;

		temp->arr=7;
	temp->count=2;
	outtextxy(174,318,"7");
	temp=temp->link->link;

		temp->arr=3;
	temp->count=2;
	outtextxy(242,318,"3");
	temp=temp->link;

		temp->arr=5;
	temp->count=2;
	outtextxy(276,318,"5");
	temp=temp->link;

		temp->arr=8;
	temp->count=2;
	outtextxy(310,318,"8");
	temp=temp->link;

		temp->arr=9;
	temp->count=2;
	outtextxy(344,318,"9");
	temp=temp->link->link;

		temp->arr=4;
	temp->count=2;
	outtextxy(412,318,"4");


	tempr=tempr->down;
	temp=tempr;

		temp->arr=8;
	temp->count=2;
	outtextxy(140,352,"8");
	temp=temp->link->link;

		temp->arr=3;
	temp->count=2;
	outtextxy(208,352,"3");
	temp=temp->link;

		temp->arr=4;
	temp->count=2;
	outtextxy(242,352,"4");
	temp=temp->link;

		temp->arr=2;
	temp->count=2;
	outtextxy(276,352,"2");
	temp=temp->link->link;

	temp->arr=7;
	temp->count=2;
	outtextxy(344,352,"7");
	temp=temp->link->link;

		temp->arr=5;
	temp->count=2;
	outtextxy(412,352,"5");


     delay(1000);
       move(ch);
	pprint();
	 getch();
 }

///////////////////////////////////medium level/////////////////////////////
void medium()
{
struct node*temp,*temp1,*temp2,*tempr;
	grid();
	p=5;
	rectangle(140-17,80-17,140+17,80+17);
	temp=start;
	tempr=start;
	setcolor(2);
	 temp->count=2;

	temp->arr=9;
	temp->count=2;
	outtextxy(140,80,"9");
	temp=temp->link->link;

	temp->arr=5;
	temp->count=2;
	outtextxy(208,80,"5");
	temp=temp->link->link->link->link->link->link;

	temp->arr=8;
	temp->count=2;
	outtextxy(412,80,"8");

	tempr=tempr->down;

	temp=tempr;

	temp->arr=4;
	temp->count=2;
	outtextxy(140,114,"4");
	temp=temp->link->link->link;

	temp->arr=5;
	temp->count=2;
	outtextxy(242,114,"5");
	temp=temp->link;

	temp->arr=7;
	temp->count=2;
	outtextxy(276,114,"7");
	temp=temp->link->link;

	temp->arr=1;
	temp->count=2;
	outtextxy(344,114,"1");
	temp=temp->link->link;

     temp->arr=6;
     temp->count=2;
	outtextxy(412,114,"6");
	temp=temp->link->link;

      tempr=tempr->down;
      temp=tempr;

      temp=temp->link;

      temp->arr=2;
      temp->count=2;
	outtextxy(174,148,"2");
	temp=temp->link;

      temp->arr=7;
      temp->count=2;
	outtextxy(208,148,"7");
	temp=temp->link;

	temp->arr=6;
	temp->count=2;
	outtextxy(242,148,"6");
	temp=temp->link->link->link->link;

	temp->arr=4;
	temp->count=2;
	outtextxy(378,148,"4");
	temp=temp->link;

	tempr=tempr->down;
	temp=tempr;
	temp=temp->link;

	temp->arr=9;
	temp->count=2;
	outtextxy(174,182,"9");
	temp=temp->link;

	temp->arr=6;
	temp->count=2;
	outtextxy(208,182,"6");
	temp=temp->link->link->link;

		temp->arr=3;
		temp->count=2;
	outtextxy(310,182,"3");
	temp=temp->link;

		temp->arr=5;
		temp->count=2;
	outtextxy(344,182,"5");
	temp=temp->link;

		temp->arr=1;
		temp->count=2;
	outtextxy(378,182,"1");
	temp=temp->link;

		temp->arr=2;
		temp->count=2;
	outtextxy(412,182,"2");
	temp=temp->link;

	tempr=tempr->down;
	temp=tempr;


		temp->arr=7;
		temp->count=2;
	outtextxy(140,216,"7");
	temp=temp->link->link;

		temp->arr=4;
		temp->count=2;
	outtextxy(208,216,"4");
	temp=temp->link->link;

		temp->arr=1;
		temp->count=2;
	outtextxy(276,216,"1");
	temp=temp->link->link;

		temp->arr=3;
		temp->count=2;
	outtextxy(344,216,"3");
	tempr=tempr->down;
	temp=tempr;

		temp->arr=2;
		temp->count=2;
	outtextxy(140,250,"2");
	temp=temp->link;

		temp->arr=1;
		temp->count=2;
	outtextxy(174,250,"1");
	temp=temp->link->link;

		temp->arr=9;
		temp->count=2;
	outtextxy(242,250,"9");
	temp=temp->link;

		temp->arr=8;
		temp->count=2;
	outtextxy(278,250,"8");
	temp=temp->link->link->link->link;


		temp->arr=4;
		temp->count=2;
	outtextxy(412,250,"4");

       tempr=tempr->down;
       temp=tempr;

	temp=temp->link;
	temp->arr=8;
	temp->count=2;
	outtextxy(174,284,"8");
	temp=temp->link;

	temp->arr=1;
	temp->count=2;
	outtextxy(208,284,"1");
	temp=temp->link->link->link;

	temp->arr=4;
	temp->count=2;
	outtextxy(310,284,"4");
	temp=temp->link->link;

	temp->arr=9;
	temp->count=2;
	outtextxy(378,284,"9");


	tempr=tempr->down;
	temp=tempr;

	temp->arr=3;
	temp->count=2;
	outtextxy(140,318,"3");
	temp=temp->link->link->link;

	temp->arr=8;
	temp->count=2;
	outtextxy(242,318,"8");
	temp=temp->link->link->link->link;

	temp->arr=5;
	temp->count=2;
	outtextxy(378,318,"5");
	temp=temp->link;

	temp->arr=1;
	temp->count=2;
	outtextxy(412,318,"1");


	tempr=tempr->down;
	temp=tempr;
	temp=temp->link->link;


	temp->arr=2;
	temp->count=2;
	outtextxy(208,352,"2");
	temp=temp->link->link->link;

	temp->arr=7;
	temp->count=2;
	outtextxy(310,352,"7");
	temp=temp->link->link;

	temp->arr=6;
	temp->count=2;
	outtextxy(378,352,"6");


     delay(1000);
       move(ch);
	pprint();
	 getch();

  }

//////////////////////////////hard level////////////////////////////
void hard()
{
struct node*temp,*tempr;

temp=start;
tempr=start;
grid();
p=5;
rectangle(140-17,80-17,140+17,80+17);

setcolor(MAGENTA);

temp=temp->link;

	temp->arr=7;
	temp->count=2;
	outtextxy(174,80,"7");
	temp=temp->link->link;

	temp->arr=5;
	temp->count=2;
	outtextxy(242,80,"5");
	temp=temp->link;

	temp->arr=9;
	temp->count=2;
	outtextxy(276,80,"9");
	temp=temp->link->link;

	temp->arr=2;
	temp->count=2;
	outtextxy(344,80,"2");
	temp=temp->link;

	temp->arr=6;
	temp->count=2;
	outtextxy(378,80,"6");

 tempr=tempr->down;
       temp=tempr;

      temp=temp->link->link;

	  temp->arr=2;
	  temp->count=2;
	outtextxy(208,114,"2");
	temp=temp->link->link;

      temp->arr=1;
      temp->count=2;
	outtextxy(276,114,"1");

       tempr=tempr->down;
	temp=tempr;

	temp->arr=8;
	temp->count=2;
	outtextxy(140,148,"8");
	temp=temp->link;

	temp->arr=9;
	temp->count=2;
	outtextxy(174,148,"9");
	temp=temp->link->link->link->link;

	temp->arr=7;
	temp->count=2;
	outtextxy(310,148,"7");
	temp=temp->link;

	temp->arr=4;
	temp->count=2;
	outtextxy(344,148,"4");

	tempr=tempr->down;
	temp=tempr;
	temp=temp->link;


	temp=temp->link->link;

	temp->arr=8;
	temp->count=2;
	outtextxy(174+68,148+34,"8");
	temp=temp->link->link;


	temp->arr=3;
	temp->count=2;
	outtextxy(140+34*5,148+34,"3");
	temp=temp->link->link;


		temp->arr=1;
		temp->count=2;
	outtextxy(412-34,148+34,"1");

	tempr=tempr->down;
	temp=tempr;
	temp=temp->link;

		temp->arr=3;
		temp->count=2;
	outtextxy(140+34,148+34*2,"3");
	temp=temp->link->link->link;

		temp->arr=6;
		temp->count=2;
	outtextxy(140+34*4,148+34*2,"6");
	temp=temp->link->link;

		temp->arr=5;
		temp->count=2;
	outtextxy(140+34*6,148+34*2,"5");
	temp=temp->link->link;

		temp->arr=7;
		temp->count=2;
	outtextxy(412,148+34*2,"7");

	tempr=tempr->down;
	temp=tempr;

		temp->arr=5;
		temp->count=2;
	outtextxy(140,148+34*3,"5");
	temp=temp->link;

		temp->arr=2;
		temp->count=2;
	outtextxy(140+34,148+34*3,"2");
	temp=temp->link->link->link->link;

		temp->arr=1;
		temp->count=2;
	outtextxy(140+34*5,148+34*3,"1");
	temp=temp->link->link;

		temp->arr=4;
		temp->count=2;
	outtextxy(412-34,148+34*3,"4");

	tempr=tempr->down;
	temp=tempr;

		temp->arr=3;
		temp->count=2;
	outtextxy(140,148+34*4,"3");
	temp=temp->link;

		temp->arr=4;
		temp->count=2;
	outtextxy(140+34,148+34*4,"4");
	temp=temp->link->link;

		temp->arr=2;
		temp->count=2;
	outtextxy(140+34*3,148+34*4,"2");
	temp=temp->link;

		temp->arr=8;
		temp->count=2;
	outtextxy(140+34*4,148+34*4,"8");
	temp=temp->link->link;

		temp->arr=1;
		temp->count=2;
	outtextxy(140+34*6,148+34*4,"1");
	temp=temp->link;

		temp->arr=9;
		temp->count=2;
	outtextxy(140+34*7,148+34*4,"9");

	tempr=tempr->down;
	temp=tempr;
	temp=temp->link->link->link->link;

		temp->arr=4;
		  temp->count=2;
	outtextxy(140+34*4,148+34*5,"4");
	temp=temp->link->link;

	temp=temp->link;

		temp->arr=5;
		temp->count=2;
	outtextxy(140+34*7,148+34*5,"5");


	tempr=tempr->down;
	temp=tempr;

		temp->arr=9;
		temp->count=2;
	outtextxy(140,148+34*6,"9");
	temp=temp->link;

		temp->arr=8;
		temp->count=2;
	outtextxy(140+34,148+34*6,"8");
	temp=temp->link->link->link->link;

		temp->arr=6;
		temp->count=2;
	outtextxy(140+34*5,148+34*6,"6");

    delay(1000);
       move(ch);
	pprint();
	 getch();




}
////////////////////////////hand writing no./////////////////////////////////////
void two(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<13;i++)
	{
	putpixel(132+i+m,69+n,WHITE);
	delay(20);
	}
	for(j=0;j<12;j++)
	{
	putpixel(144+m,69+j+n,WHITE);
	delay(20);
	//putpixel(110+i,139,WHITE);
	}
	for(i=0;i<12;i++)
	{
	putpixel(144-i+m,81+n,WHITE);
	delay(20);
	}
	for(i=0;i<11;i++)
	{
	putpixel(132+m,81+i+n,WHITE);
	delay(20);
	}
	for(i=0;i<12;i++)
	{
	putpixel(132+i+m,91+n,WHITE);
	delay(20);
	}
}



void four(int x, int y)
{
	int i,j;

	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<13;i++)
	{
	putpixel(m+127+i,80-i+n,WHITE);
	delay(20);
	}
	for(j=0;j<23;j++)
	{
	putpixel(m+140,69+j+n,WHITE);
	delay(20);
	//putpixel(110+i,139,WHITE);
	}
	for(i=0;i<22;i++)
	{
	putpixel(m+127+i,81+n,WHITE);
	delay(20);
	}
}
void one(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=6;i<13;i++)
	{
	putpixel(m+127+i,80-i+n,WHITE);
	delay(20);
	}
	for(j=0;j<23;j++)
	{
	putpixel(m+140,69+j+n,WHITE);
	delay(20);
	//putpixel(110+i,139,WHITE);
	}
	for(i=3;i<23;i++)
	{
	putpixel(m+127+i,91+n,WHITE);
	delay(20);
	}
}
void three(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,69+n,WHITE);
	delay(20);
	}
	for(j=0;j<23;j++)
	{
	putpixel(m+144,69+j+n,WHITE);
	delay(20);
	//putpixel(110+i,139,WHITE);
	}
	for(i=0;i<12;i++)
	{

	putpixel(m+132+i,91+n,WHITE);
	delay(20);
	}
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,81+n,WHITE);
	delay(20);
	}

}
void eight(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,69+n,WHITE);
	delay(20);
	}
	for(j=0;j<23;j++)
	{
	putpixel(m+144,69+j+n,WHITE);
	delay(20);
	//putpixel(110+i,139,WHITE);
	}
	for(i=0;i<12;i++)
	{
	putpixel(m+144-i,91+n,WHITE);
	delay(20);
	}
	for(i=0;i<23;i++)
	{
	putpixel(m+132,91-i+n,WHITE);
	delay(20);
	}
	for(i=0;i<12;i++)
	{
	putpixel(m+132+i,81+n,WHITE);
	delay(20);
	}
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,81+n,WHITE);
	delay(20);
	}
	for(i=0;i<11;i++)
	{
	putpixel(m+144,81+i+n,WHITE);
	delay(20);
	}

}
void nine(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<12;i++)
	{
	putpixel(m+144-i,81+n,WHITE);
	delay(20);
	}
	for(i=0;i<13;i++)
	{
	putpixel(m+132,81-i+n,WHITE);
	delay(20);
	}
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,69+n,WHITE);
	delay(20);
	}
	for(j=0;j<23;j++)
	{
	putpixel(m+144,69+j+n,WHITE);
	delay(20);
	//putpixel(110+i,139,WHITE);
	}
	for(i=0;i<12;i++)
	{
	putpixel(m+144-i,91+n,WHITE);
	delay(20);
	}
}
void five(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,69+n,WHITE);
	delay(20);
	}

	for(i=0;i<13;i++)
	{
	putpixel(m+132,69+i+n,WHITE);
	delay(20);
	}

	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,81+n,WHITE);
	delay(20);
	}
	for(i=0;i<11;i++)
	{
	putpixel(m+144,81+i+n,WHITE);
	delay(20);
	}
	for(i=0;i<12;i++)
	{
	putpixel(m+144-i,91+n,WHITE);
	delay(20);
	}
}
void six(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,69+n,WHITE);
	delay(20);
	}
	for(j=0;j<23;j++)
	{
	putpixel(m+132,69+j+n,WHITE);
	delay(20);
	//putpixel(110+i,139,WHITE);
	}
	for(i=0;i<12;i++)
	{
	putpixel(m+132+i,91+n,WHITE);
	delay(20);
	}
	for(i=0;i<11;i++)
	{
	putpixel(m+144,91-i+n,WHITE);
	delay(20);
	}
	for(i=0;i<13;i++)
	{
	putpixel(m+144-i,81+n,WHITE);
	delay(20);
	}

}
void seven(int x, int y)
{
	int i,j;
	int m,n;
	m=x-140;n=y-80;
	for(i=0;i<13;i++)
	{
	putpixel(m+132+i,69+n,WHITE);
	delay(20);
	}
	for(i=0;i<23;i++)
	{
	putpixel(m+144,69+i+n,WHITE);
	delay(20);
	}
	for(i=0;i<15;i++)
	{
	putpixel(m+137+i,81+n,WHITE);
	delay(20);
	}
}



///////////////////////// linking matrix/////////////////////////
struct node *create2(struct node *start)    //colm
{
int i=1,j=1;
temp=start;
while(j<9)
{

	temp2=temp->link;
	end=temp->down;
	temp1=end->link;
	temp2->down=NULL;
	temp1->down=NULL;
	i=1;
	while(i<9)
	{
		temp2->down=NULL;
		temp1->down=NULL;
		temp2->down=temp1;
		temp2=temp2->link;
		temp1=temp1->link;
		i++;

	}
	temp=temp->down;
	j++;
}
return start;
}


/////////////////////////linking rows///////////////////////////////
struct node *create1(struct node *end) //row
{
	int j;
	start1=NULL;
	temp1=NULL;
	for(j=1;j<9;j++)
	{
		 x=x+(2*17);
		temp1=(struct node*)malloc(sizeof(struct node));
		temp1->link=NULL;
		temp1->arr=99;
		temp1->xx=x;
		temp1->yy=y;
		temp1->count=0;

		if(j==1)
		{
			start1=temp1;
			end1=temp1;
		}
		else
		{
			end1->link=temp1;
			end1=temp1;
		}
	}
return start1;
}
//////////////////////////////linking down////////////////////////
struct node *create()      //down
{
	int i=0;
	x=140;
	y=80;
	for(i=0;i<9;i++)
	{
		temp=(struct node*)malloc(sizeof(struct node));
		temp->link=NULL;
		temp->down=NULL;
		temp->arr=99;
		temp->xx=x;
		temp->yy=y;
			temp->count=0;

		if(i==0)
		{
			start=temp;
			end=temp;
		}
		else
		{

			end->down=temp;
			end=temp;
		}
		end->link=create1(end);
		y=y+(17*2);
		x=140;
		}
	return start;
}

/////////////////////////////////////printing numbers//////////////////////
void pprint()           //print
{
	int i,j;
	int u,l;
	struct node *tempm,*endm;
	char v[50];
	u=140;
	l=80;
	tempm=start;
	setcolor(3);

	for(i=0;i<9;i++)
	{
		endm=tempm;
		for(j=0;j<9;j++)
		{
			if(tempm->arr<=9&&tempm->arr>0)
			{
			   if(tempm->count==2)
				setcolor(RED);
			   else if(tempm->count==0||tempm->count==1)
				setcolor(CYAN);
			   sprintf(v,"%d",tempm->arr);
			   outtextxy(u,l,v);
			}

			tempm=tempm->link;
			u=u+(2*17);
		}
		u=140;
		l=l+(2*17);
			tempm=endm->down;
	}

}

//////////////////////printing handwritten numbers/////////////////////////
void display(int a,int x,int y)
{
	switch(a)
	{
		case 1: one(x,y);
			break;
		case 2: two(x,y);
			break;
		case 3: three(x,y);
			break;
		case 4: four(x,y);
			break;
		case 5: five(x,y);
			break;
		case 6: six(x,y);
			break;
		case 7: seven(x,y);
			break;
		case 8: eight(x,y);
			break;
		case 9: nine(x,y);
			break;

}              }

//////////////////////// taking no. from user./////////////////////////////
void f3(char ch,int x,int y)
{
      int a,i,j;
      struct node *ttemp,*tttemp;
      a=ch-48;
	  if(ch-48>9||ch-48<=0)
       {	outtextxy(500,200,"INVALID");
      }
    else
     {
     push(x,y);
     ttemp=(struct node*)malloc(sizeof(struct node));
      ttemp=start;
      tttemp=start;
     for(i=0;i<9;i++)
      {
	tttemp=ttemp;
	for(j=0;j<9;j++)
	{
		if(ttemp->xx==x&&ttemp->yy==y)
		{
			if(ttemp->count==1||ttemp->count==2)
			outtextxy(10,10,"Can't be Overwrite");
			else
			{
			ttemp->arr=a;
			ttemp->count=1;
			display(a,x,y);
			break;
			}
		}
		else
			ttemp=ttemp->link;
	 }
	ttemp=tttemp->down;
       }
       }
	ch=getche();
	move(ch);
}

///////////////////////// suduko grid///////////////////////////
void grid()
{
	int i=0,j=0,k=0;
	cleardevice();
	setbkcolor(BLACK);
	settextstyle(11,0,1);
	for(i=140;i<=440;i+=34)
	{
		k=0;
		for(j=80;j<=380;j+=34)
		{
			k++;
			if(k<=3)
			{
				setcolor(6);
			}
			else
				if(k>3&&k<=6)
					setcolor(BLUE);
				else
					if(k>6&&k<=9)
						setcolor(RED);
			rectangle(i-15,j-15,i+15,j+15);

		}
	}
		 setcolor(CYAN);
		rectangle(140+(2*34)+17,80-17,140+(5*34)+17,80+(2*34)+17);
		rectangle(140-17,80-17,140+(2*34)+17,80+(2*34)+17);
		rectangle(140-17,80+(5*34)+17,140+(2*34)+17,80+(8*34)+17);
		rectangle(140+(5*34)+17,80+(5*34)+17,140+(8*34)+17,80+(8*34)+17);
		rectangle(140+(5*34)+17,80-17,140+(8*34)+17,80+(2*34)+17);

		rectangle(140+(2*34)+17,80+(5*34)+17,140+(5*34)+17,80+(8*34)+17);
		rectangle(140-17,80+(2*34)+17,140+(2*34)+17,80+(5*34)+17);
		rectangle(140+(5*34)+17,80+(2*34)+17,140+(8*34)+17,80+(5*34)+17);
}


////////////////////////////// movind up down lft rit//////////////////
void move(char ch)
{
	static int x=140,y=80;
	setcolor(3);
	if(ch=='w')
	{
		cleardevice();
		grid();
		y=y-(2*17);
		button();
		setcolor(2);

		rectangle(x-17,y-17,x+17,y+17);
		pprint();
		putpixel(x,y,WHITE);
	}
	if(ch=='d')
	{
		cleardevice();
		grid();
		button();
		x=x+(2*17);
		setcolor(2);
		rectangle(x-17,y-17,x+17,y+17);
		pprint();
		putpixel(x,y,WHITE);
	 }
	if(ch=='a')
	{
		cleardevice();
		grid();
		x=x-(2*17);
		button();
		setcolor(2);

		rectangle(x-17,y-17,x+17,y+17);
		pprint();
		putpixel(x,y,WHITE);
	}
	if(ch=='s')
	{
		cleardevice();
		grid();
		button();
		y=y+(2*17);
		setcolor(2);
		rectangle(x-17,y-17,x+17,y+17);
		pprint();
		putpixel(x,y,WHITE);
	}

	 initmouse();
	showmouseptr();
		while(!kbhit())
	{
		ip.x.ax=3;
		int86(0X33,&ip,&op);
		if(op.x.cx>=462&&op.x.cx<=550)
		{

			if(op.x.dx>=172&&op.x.dx<=220)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					allfilled();
			       }
			   }
		   }


	       if(op.x.cx>=462&&op.x.cx<=550)
		{

			if(op.x.dx>=252&&op.x.dx<=320)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					second();
			       }
			   }
		   }

		if(op.x.cx>=462&&op.x.cx<=550)
		{

			if(op.x.dx>=332&&op.x.dx<=370)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					thankyou();
			       }
			   }
		   }

		if(op.x.cx>=462&&op.x.cx<=550)
		{

			if(op.x.dx>=82&&op.x.dx<=125)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					 p--;
					if(p>=0)
					{
			sound(1000);
			delay(50);
			sound(1020);
				delay(50);
			sound(800);
				delay(50);
			sound(960);
				delay(50);
			sound(1000);
				delay(50);
				nosound();
				pope=pop();
				undo(pope);
		//		pprint();
					}
		else if(p==5)
			outtextxy(10,10,"Sorry, Please enter digit for UNDO");
		else
		outtextxy(10,10,"Sorry, Your undo chances are over");
			}

			       }
			   }
       }

		cleardevice();
		grid();
		button();
		pprint();
      ch=getche();

      if(ch-48<=9&&ch-48>0)
	f3(ch,x,y);
       else if(ch=='n')
       exit(1);
      else
	move(ch);


}
////////////// 1 check//////////////////////
///**************allfilled check**********************
void allfilled()
{
int i=0,j=0;
struct node*temp,*temp1,*tempr;

	 sound(1000);
	delay(50);
	sound(1020);
	delay(50);
	sound(800);
	delay(50);
	sound(960);
	delay(50);
	sound(1000);
	delay(50);
	nosound();

	cleardevice();
		grid();
		pprint();

		setcolor(5);
		setfillstyle(11,1);
		setlinestyle(0,1,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-300,140+(8*34)+150,80+(8*34)+60-300,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-300,"NDO");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-300,"U");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-300,140+(8*34)+84,80+(8*34)+55-300);
		settextstyle(11,0,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-130,140+(8*34)+150,80+(8*34)+60-130,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-130,"ACK");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-130,"B");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-130,140+(8*34)+84,80+(8*34)+55-130);
		settextstyle(11,0,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-50,140+(8*34)+150,80+(8*34)+60-50,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-50,"XIT");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-50,"E");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-50,140+(8*34)+84,80+(8*34)+55-50);
		settextstyle(11,0,1);

		setcolor(1);
		setfillstyle(11,1);
		bar(140+(8*34)+50+3,80+(8*34)+30-210+3,140+(8*34)+150-3,80+(8*34)+60-210-3);
		settextstyle(2,0,6);
		setcolor(15);
		outtextxy(140+(8*34)+77,80+(8*34)+32-207,"Check");
		settextstyle(1,0,1);
		setcolor(5);
		delay(700);
		button();


checking();
temp=start;
temp1=temp;

while(temp!=NULL)
{
   temp1=temp;
   while(temp1!=NULL)
   {
	if(temp1->arr>9)
	{
	   outtextxy(400,400,"INCOMPLETE");
	   return;

	}
      temp1=temp1->link;
     }
     temp=temp->down;


}
check();
}

////////// storing values of linklist and sending to checking block//////////
void block()                      //3 check
{
int i,j,blck[9],k=0,c;
struct node*temp,*temp1,*tempr;

temp=start;
tempr=start;
temp1=temp;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
c=bcheck(blck);
if(c==1)
{
k=0;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
c=bcheck(blck);
if(c==1)
{
k=0;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
c=bcheck(blck);
if(c==1)
{
i=0;
tempr=start;
while(i<3)
{
	tempr=tempr->link;
	i=i+1;
}
temp=tempr;
k=0;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
c=bcheck(blck);
if(c==1)
{
k=0;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
c=bcheck(blck);
if(c==1)
{
k=0;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
c=bcheck(blck);
if(c==1)
{
i=0;
tempr=start;
while(i<3)
{
	tempr=tempr->link;
	i=i+1;
}
k=0;
temp=tempr;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
c=bcheck(blck);
if(c==1)
{
k=0;
temp1=temp;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
if(c==1)
{
c=bcheck(blck);
k=0;
temp1=temp;
for(i=0;i<3;i++)
{       temp1=temp;
	for(j=0;j<3;j++)
	{
		blck[k]=temp1->arr;
		k=k+1;
		temp1=temp1->link;
	}
temp=temp->down;
}
}
c=bcheck(blck);
if(c==1)
{
win();
}
}


//////////////////////////////// block checking///////////////////
int bcheck(int blck[9])         //   4 check
{
int i,j;
for(i=0;i<9;i++)
{
for(j=i+1;j<9;j++)
{
if(blck[i]==blck[j])
{


  loss();
  return 0;
}
}
}
return 1;
}



///////////////////////////////// row-colmn check ////////////////////
int check()               //2 check
{
struct node*temp,*temp1,*tempr;
int c=0,i,j;

//check

temp=start;
tempr=start;
while(tempr!=NULL)
{
if(c>0)                   //colm
{
temp=tempr;
}
while(temp!=NULL)
{
	temp1=temp->down;
	while(temp1!=NULL)
	{
		if(temp->arr==temp1->arr)
		{        loss();
		       //	outtextxy(400,400,"INVALID");
			 return 0;
		}
	   else
	   {
	   temp1=temp1->down;
	   }

	 }
	 temp=temp->down;

}
tempr=tempr->link;
c=c+1;
}
temp=start;
tempr=start;
while(tempr!=NULL)
{                       //row
if(i>0)
{
temp=tempr;
}
while(temp!=NULL)
{
	temp1=temp->link;
	while(temp1!=NULL)
	{
		if(temp->arr==temp1->arr)
		{     loss();
		    //	outtextxy(400,400,"INVALID");
			 return 0;
		}
	   else
	   {
	   temp1=temp1->link;
	   }

	 }
	 temp=temp->link;

}
tempr=tempr->down;
i++;
}
		 block();
}



////////////////////////main menu page ///////// ////////**********
void second()                         //sec page
{
	int x,y,k;
	create();
	start=create2(start);
       setbkcolor(2);
       setcolor(WHITE);
	for(x=0;x<310;x=x+7)
	{
		cleardevice();
		settextstyle(10,0,6);
		bar3d(130,40,480,180,20,1);
		setfillstyle(3,6);
		bar(133,43,477,177);

		outtextxy(150,40,"SUDOKU");
		settextstyle(7,0,4);
		outtextxy(x,200,"NEW GAME");
		delay(12);
	 }

	  setbkcolor(6);
	 for(x=640;x>170;x=x-7)
	{
		cleardevice();
		settextstyle(10,0,6);
		bar3d(130,40,480,180,20,1);
		setfillstyle(3,6);
		bar(133,43,477,177);

		outtextxy(150,40,"SUDOKU");
		settextstyle(7,0,3);
		outtextxy(250,200,"NEW GAME");
		settextstyle(7,0,4);
		outtextxy(x,250,"CREDIT");
			delay(12);

	 }
	  setbkcolor(9);
	 for(x=0;x<310;x=x+7)
	{
		cleardevice();
		settextstyle(10,0,6);
		bar3d(130,40,480,180,20,1);
		setfillstyle(3,6);
		bar(133,43,477,177);

		outtextxy(150,40,"SUDOKU");
		settextstyle(7,0,3);
		outtextxy(250,200,"NEW GAME");
		outtextxy(270,250,"CREDIT");
		settextstyle(7,0,4);
		outtextxy(x,300,"INSTRUCTIONS");
			delay(12);

	 }
	  setbkcolor(8);
	 for(x=640;x>170;x=x-7)
	{
		cleardevice();
		settextstyle(10,0,6);
		bar3d(130,40,480,180,20,1);
		setfillstyle(3,6);
		bar(133,43,477,177);

		outtextxy(150,40,"SUDOKU");
		settextstyle(7,0,3);
		outtextxy(250,200,"NEW GAME");
		outtextxy(270,250,"CREDIT");
		outtextxy(227,300,"INSTRUCTIONS");
		settextstyle(7,0,4);
		outtextxy(x,350,"EXIT");
			delay(12);

	 }
		setbkcolor(1);
		cleardevice();
		bar3d(130,40,480,180,20,1);
		setfillstyle(3,6);
		bar(133,43,477,177);
		settextstyle(1,0,12);
	setcolor(YELLOW);
	bar3d(70,40,140,300-130,15,1);
	outtextxy(80,150-130,"S");
	setcolor(LIGHTGRAY);
	bar3d(150,40,220,300-130,15,1);
	outtextxy(150,150-130,"U");
	setcolor(LIGHTGREEN);
	bar3d(230,170-130,300,300-130,15,1);
	outtextxy(230,150-130,"D");
	setcolor(MAGENTA);
	bar3d(310,170-130,380,300-130,15,1);
	outtextxy(310,150-130,"O");
	setcolor(CYAN);
	bar3d(390,170-130,460,300-130,15,1);
	outtextxy(390,150-130,"K");
	setcolor(LIGHTBLUE);
	bar3d(470,170-130,540,300-130,15,1);
	outtextxy(470,150-130,"U");
		setcolor(3);
		settextstyle(7,0,3);
		outtextxy(250,200,"NEW GAME");
		outtextxy(270,250,"CREDITS");
		outtextxy(227,300,"INSTRUCTIONS");
		outtextxy(280,350,"EXIT");

     initmouse();
	showmouseptr();
		while(!kbhit())
	{
		ip.x.ax=3;
		int86(0X33,&ip,&op);
		if(op.x.cx>=250&&op.x.cx<=350)
		{

			if(op.x.dx>=200&&op.x.dx<=240)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					level();
			       }
			   }
		   }

		if(op.x.cx>=280&&op.x.cx<=390)
		{

			if(op.x.dx>=350&&op.x.dx<=410)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					thankyou();
			       }
			   }
		   }


		if(op.x.cx>=270&&op.x.cx<=340)
		{

			if(op.x.dx>=250&&op.x.dx<=285)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					credit();
			       }
			   }
		   }



		if(op.x.cx>=227&&op.x.cx<=370)
		{

			if(op.x.dx>=295&&op.x.dx<=340)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					instructions();
			       }
			   }
		   }

	   }

}


///////////////// undo check exit back buttons////////////////////////
void button()
{
		int q=0;
			char b[20];
		setcolor(5);
		setfillstyle(11,1);
		setlinestyle(0,1,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-300,140+(8*34)+150,80+(8*34)+60-300,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-300,"NDO");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-300,"U");
		setcolor(5);
		if(p>0)
		{
			sprintf(b,"(%d)",p);
		outtextxy(140+(8*34)+86+100,80+(8*34)+32-310,b);
		 }
		 else
		 {
		 outtextxy(140+(8*34)+86+100,80+(8*34)+32-310,"(0)");
		 }
		line(140+(8*34)+67,80+(8*34)+55-300,140+(8*34)+84,80+(8*34)+55-300);
		settextstyle(11,0,1);


		bar3d(140+(8*34)+50,80+(8*34)+30-210,140+(8*34)+150,80+(8*34)+60-210,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-210,"HECK");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-210,"C");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-210,140+(8*34)+84,80+(8*34)+55-210);
		settextstyle(11,0,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-130,140+(8*34)+150,80+(8*34)+60-130,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-130,"ACK");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-130,"B");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-130,140+(8*34)+84,80+(8*34)+55-130);
		settextstyle(11,0,1);

		bar3d(140+(8*34)+50,80+(8*34)+30-50,140+(8*34)+150,80+(8*34)+60-50,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86,80+(8*34)+32-50,"XIT");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67,80+(8*34)+21-50,"E");
		setcolor(5);
		line(140+(8*34)+67,80+(8*34)+55-50,140+(8*34)+84,80+(8*34)+55-50);
		settextstyle(11,0,1);
}

//////////////// processing for checking//////////////////////////////
void checking()
{
	int i;
	setcolor(YELLOW);
	settextstyle(7,0,2);
	outtextxy(420-300,400,"Checking");
	rectangle(530-300,415,620-300,463-40);
	setcolor(LIGHTGRAY);
	for(i=0;i<90;i++)
	{
	line(530+i-300,455-40,530+i-300,463-40);
	delay(50);
	}
	sound(1000);
	delay(500);
	nosound();

}

/////////////////// if u win//////////////////////////
void win()
{
	int i;
	for(i=0;i<4;i++)
	{
	cleardevice();
	setbkcolor(RED);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,i+1);
	outtextxy(140,130,"CONGRATULATIONS !!!");
	delay(250);
	}
	for(i=0;i<5;i++)
	{
		cleardevice();
		settextstyle(TRIPLEX_FONT,HORIZ_DIR,i+1);
		outtextxy(200,190,"You");
		delay(250);
	}
	for(i=0;i<9;i++)
	{
		cleardevice();
		settextstyle(TRIPLEX_FONT,HORIZ_DIR,i+1);
		outtextxy(220,210,"Won :)");
		delay(250);
	}


	cleardevice();
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);
	outtextxy(100,130,"CONGRATULATIONS !!!");

	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(200,220,"You ");
	outtextxy(250,220,"Won The Game ............ :)");
	settextstyle(5,0,1);
	setcolor(3);
	outtextxy(110,320,"Thank You For Playing !!");
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,8);

	for(i=0;i<15;i++)
	{
	setcolor(i);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);
	outtextxy(100,130,"CONGRATULATIONS !!!");
	delay(70);
	}
	winlossbutton();


     initmouse();
	showmouseptr();
		while(!kbhit())
	{
		ip.x.ax=3;
		int86(0X33,&ip,&op);
		if(op.x.cx>=462&&op.x.cx<=540)
		{

			if(op.x.dx>=392&&op.x.dx<=460)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					thankyou();
			       }
			   }
		   }

	      if(op.x.cx>=82&&op.x.cx<=190)
		{

			if(op.x.dx>=392&&op.x.dx<=460)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					second();
			       }
			   }
		   }
	   }
}




///////////////////////////////// if u lost the game//////////////////////////
void loss()
{
	int i;
	for(i=0;i<6;i++)
	{
	cleardevice();
	setbkcolor(RED);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,i+1);
	outtextxy(140,130,"SORRY !!!");
	delay(250);
	}
	for(i=0;i<4;i++)
	{
		cleardevice();
		settextstyle(TRIPLEX_FONT,HORIZ_DIR,i+1);
		outtextxy(160,150,"-_-");
		delay(250);
	}
	for(i=0;i<5;i++)
	{
		cleardevice();
		settextstyle(TRIPLEX_FONT,HORIZ_DIR,i+1);
		outtextxy(200,190,"You");
		delay(250);
	}
	for(i=0;i<7;i++)
	{
		cleardevice();
		settextstyle(TRIPLEX_FONT,HORIZ_DIR,i+1);
		outtextxy(220,210,"Lost :(");
		delay(250);
	}


	cleardevice();
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);
	outtextxy(140,130,"SORRY !!!");
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(200,190,"You ");
	outtextxy(250,190,"Lost The Game ............ :(");

	settextstyle(TRIPLEX_FONT,HORIZ_DIR,8);
	for(i=0;i<15;i++)
	{
	setcolor(i);
	outtextxy(100,270,"GAME OVER");
	delay(50);
	}
	winlossbutton();


     initmouse();
	showmouseptr();
		while(!kbhit())
	{
		ip.x.ax=3;
		int86(0X33,&ip,&op);
		if(op.x.cx>=462&&op.x.cx<=540)
		{

			if(op.x.dx>=392&&op.x.dx<=460)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					thankyou();
			       }
			   }
		   }

	      if(op.x.cx>=82&&op.x.cx<=190)
		{

			if(op.x.dx>=392&&op.x.dx<=460)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					second();
			       }
			   }
		   }

	   }

}


//////////////////////////last page/////////////////////////////
void thankyou()
{
   int i,area, temp1, temp2, left = 25, top = 75;
   void *p;

    setbkcolor(2);
    for(i=0;i<15;i++)
   {
//  cleardevice();
   settextstyle(1,0,i);
   outtextxy(60,160,"!! THANK YOU !!");
    delay(20);
  }
  delay(100);
   for(i=0;i<8;i++)
   {
  cleardevice();
   settextstyle(1,0,i);
   outtextxy(70,160,"!! THANK YOU !!");
  delay(100);
  }

  cleardevice();
   setcolor(YELLOW);
   circle(50,100,25);
   setfillstyle(SOLID_FILL,YELLOW);
   floodfill(50,100,YELLOW);

   setcolor(BLACK);
   setfillstyle(SOLID_FILL,BLACK);
   fillellipse(44,85,2,6);
   fillellipse(56,85,2,6);

   ellipse(50,100,205,335,20,9);
   ellipse(50,100,205,335,20,10);
   ellipse(50,100,205,335,20,11);

   area = imagesize(left, top, left + 50, top + 50);
   p = malloc(area);

    setcolor(WHITE);
   settextstyle(10,HORIZ_DIR,2);
   outtextxy(80,410,"!! T  H  A  N  K      Y  O  U !!");

   setcolor(BLUE);
   rectangle(0,0,639,449);
 i=0;
   while(!kbhit())
   {
       setcolor(i);
   settextstyle(10,0,2);
   outtextxy(80,410,"!! T  H  A  N  K      Y  O  U !!");

      temp1 = 1 + random ( 588 );
      temp2 = 1 + random ( 380 );

      getimage(left, top, left + 50, top + 50, p);
      putimage(left, top, p, XOR_PUT);
      putimage(temp1 , temp2, p, XOR_PUT);
      delay(310);
      left = temp1;
      top = temp2;
      i++;
   }
 exit(1);
}

//////////////// main menu and exit butoon on win-loss page//////////////
 void winlossbutton()
{
//exit button
	setcolor(5);
		setfillstyle(11,1);
		setlinestyle(0,1,1);
		bar3d(140+(8*34)+50-30,80+(8*34)+30-50+60,140+(8*34)+150-30-20,80+(8*34)+60-50+60,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86-30,80+(8*34)+32-50+60,"XIT");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67-30,80+(8*34)+21-50+60,"E");
		setcolor(5);
		line(140+(8*34)+67-30,80+(8*34)+55-50+60,140+(8*34)+84-30,80+(8*34)+55-50+60);
		settextstyle(11,0,1);



//main menu
		setcolor(5);
		setfillstyle(11,1);
		setlinestyle(0,1,1);

		setfillstyle(11,1);
		setlinestyle(0,1,1);
		bar3d(140+(8*34)+50-30-350,80+(8*34)+30-50+60,140+(8*34)-290+150-30-20,80+(8*34)+60-50+60,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86-30-350,80+(8*34)+32-50+60,"AIN MENU");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67-30-350,80+(8*34)+21-50+60,"M");
		setcolor(5);
		line(140+(8*34)+67-30-350,80+(8*34)+55-50+60,140+(8*34)+84-30-350,80+(8*34)+55-50+60);
		settextstyle(11,0,1);


}

////////////////////////// credits///////////////////////////
void credit()
{
	int i;
	cleardevice();
	setbkcolor(BLACK);
	i=350;
	while(i!=0)
	{
	 cleardevice();
	rectangle(140,30,500,50);
	rectangle(180,30+20,460,500);
	settextstyle(1,0,7);
	outtextxy(200,60,"CREDITS");
	line(192+6,130,450-6,130);
	line(192+6,130+5,450-6,130+5);
	  settextstyle(1,0,3);
	  outtextxy(200+50+15-5+7+5,160+i-30,"CODERS");
	  line(200+48,210+i-50,400-20-5,210-50+i);
	  settextstyle(7,0,1);
	  outtextxy(200+30+20,220+i-50,"Shubham Jain");
	  outtextxy(200+10+20,250+i-50,"Ananyaa Agarwala");
	  outtextxy(200+30+20,280+i-50,"Neeti Kavathia");

	  settextstyle(1,0,3);
	  outtextxy(200+57+7,160+i+160-50,"SUPPORT");
	  line(200+40,210+i+160-70,400-20,210+i+160-70);
	  settextstyle(7,0,1);
	  outtextxy(200+30+20-10,220+i+160-70,"Dr. Vikas Sakxena");
	  outtextxy(200+30+20-10,250+i+160-70,"Ms. Arpita Jadav");
	  outtextxy(200+30+15+20-10,280+i+160-70,"Ms. Arti Jain");


	  settextstyle(1,0,3);
	  outtextxy(200+57+7,160+i+240-4,"MENTOR");
	  line(200+40,170+i+260-4,400-20,170+i+260-4);
	  settextstyle(7,0,1);
	  outtextxy(200+30+20,190+i+260-19-3,"Abhay Gupta");
	   outtextxy(200+10-5,190+i+260-3,"------*-------*-------");
	  delay(50);

	  i=i-10;

	}

//back button
	setcolor(5);
		setfillstyle(11,1);
		setlinestyle(0,1,1);
		bar3d(140+(8*34)+50-30,80+(8*34)+30-50+60,140+(8*34)+150-30-20,80+(8*34)+60-50+60,7,1);
		settextstyle(1,0,1);
		setcolor(15);
		outtextxy(140+(8*34)+86-30,80+(8*34)+32-50+60,"ACK");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67-30,80+(8*34)+21-50+60,"B");
		setcolor(5);
		line(140+(8*34)+67-30,80+(8*34)+55-50+60,140+(8*34)+84-30,80+(8*34)+55-50+60);
		settextstyle(11,0,1);


     initmouse();
	showmouseptr();
		while(!kbhit())
	{
		ip.x.ax=3;
		int86(0X33,&ip,&op);
		if(op.x.cx>=462&&op.x.cx<=540)
		{

			if(op.x.dx>=392&&op.x.dx<=460)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					second();
			       }
			   }
		   }
	 }

}



/////////////////////////// instructions////////////////////////////
void instructions()
{

	int i;
	setbkcolor(BLACK);
	for(i=600;i>450;i--)
	{
		setcolor(BLUE);
		settextstyle(7,0,2);
		cleardevice();
		outtextxy(i,55,"I");
		setcolor(6);
		outtextxy(i,85,"N");
		setcolor(8);
		outtextxy(i,115,"S");
		setcolor(MAGENTA);
		outtextxy(i,145,"T");
		setcolor(10);
		outtextxy(i,175,"R");
		setcolor(13);
		outtextxy(i,205,"U");
		setcolor(14);
		outtextxy(i,235,"C");
		setcolor(1);
		outtextxy(i,265,"T");
		setcolor(2);
		outtextxy(i,295,"I");
		setcolor(5);
		outtextxy(i,325,"O");
		setcolor(4);
		outtextxy(i,355,"N");
		setcolor(3);
		outtextxy(i,385,"S");
		delay(2);

	}
	for(i=400;i>30;i--)
	{
		setcolor(RED);
		delay(2);
		line(i,60,i,80);
	}
		delay(500);
		setcolor(BLACK);
		settextstyle(6,0,1);
		outtextxy(35,55,"1.It is a single player game");
		delay(500);

	for(i=400;i>30;i--)
	{
		delay(2);
		setcolor(2);
		settextstyle(6,0,3);
		line(i,90,i,110);
	}
	delay(500);
	setcolor(BLACK);
	settextstyle(6,0,1);
	outtextxy(35,85,"2.There are 3 levels");
	for(i=400;i>30;i--)
	{
	       //	clrscr();
		delay(2);
		setcolor(3);
		settextstyle(6,0,3);
		line(i,120,i,140);
	}
	delay(500);
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,115,"3.You can enter no. from 1 to 9 only");
		delay(500);

	for(i=400;i>30;i--)
	{
	       //	clrscr();
		delay(2);
		setcolor(7);
		settextstyle(6,0,3);
		line(i,150,i,170);
	}
	delay(500);
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,145,"4.No number should be repeated in a row ");
		delay(500);

	for(i=400;i>30;i--)
	{
		//clrscr();
		delay(2);
		setcolor(5);
		settextstyle(6,0,3);
		line(i,180,i,200);
	}
	delay(500);
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,175,"5.No number should be repeated in a column");
		delay(500);

	for(i=400;i>30;i--)
	{
	       //	clrscr();
		delay(2);
		setcolor(6);
		settextstyle(6,80,3);
		line(i,210,i,230);
	}
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,205,"6.No number should be repeated in a block");
		delay(500);

	for(i=400;i>30;i--)
	{
	       //	clrscr();
		delay(2);
		setcolor(8);
		settextstyle(6,0,3);
		line(i,240,i,260);
	}
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,235,"7.UNDO can be done only 5 times");
		delay(500);

	for(i=400;i>30;i--)
	{

		delay(2);
		setcolor(10);
		settextstyle(6,0,3);
	       line(i,270,i,290);
	}
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,265,"8.You CANNOT overwrite any number");
		delay(500);

	for(i=400;i>30;i--)
	{

		delay(2);
		setcolor(13);
		settextstyle(6,0,3);
		line(i,300,i,320);
	}
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,295,"9.You can move the block right by 'D'");
		delay(500);

	for(i=400;i>30;i--)
	{

		delay(2);
		setcolor(14);
		settextstyle(6,0,3);
		line(i,330,i,350);
	}
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,325,"10.You can move the block left by 'A'");
		delay(500);

	for(i=400;i>30;i--)
	{

		delay(2);
		setcolor(15);
		settextstyle(6,0,3);
		line(i,360,i,380);
	}
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,355,"11.You can move the block up by 'W'");
		delay(500);


	delay(500);
	for(i=400;i>30;i--)
	{

		delay(2);
		setcolor(5);
		settextstyle(6,0,3);
		line(i,390,i,410);
	}
		setcolor(BLACK);
		settextstyle(6,0,1);

		outtextxy(35,385,"12.You can move the block down by 'S'");
		delay(500);
	setcolor(5);
		setfillstyle(11,1);
		setlinestyle(0,1,1);
		bar3d(140+(8*34)+50-30,80+(8*34)+30-50+60,140+(8*34)+150-30-20,80+(8*34)+60-50+60,7,1);
		settextstyle(1,0,1);
		//BACK
		setcolor(15);
		outtextxy(140+(8*34)+86-30,80+(8*34)+32-50+60,"ACK");
		settextstyle(1,0,4);
		setcolor(3);
		outtextxy(140+(8*34)+67-30,80+(8*34)+21-50+60,"B");
		setcolor(5);
		line(140+(8*34)+67-30,80+(8*34)+55-50+60,140+(8*34)+84-30,80+(8*34)+55-50+60);
		settextstyle(11,0,1);


     initmouse();
	showmouseptr();
		while(!kbhit())
	{
		ip.x.ax=3;
		int86(0X33,&ip,&op);
		if(op.x.cx>=462&&op.x.cx<=540)
		{

			if(op.x.dx>=392&&op.x.dx<=460)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					second();
			       }
			   }
		   }
	 }
}

//////////////////////////// choose level/////////////////////
void level()
{

	int ch,k;
	int j=0,i=0;
	setbkcolor(BLACK);
	sound(1000);
	delay(50);
	sound(1020);
	delay(50);
	sound(800);
	delay(50);
	sound(960);
	delay(50);
	sound(1000);
	delay(50);
	nosound();
	for(k=0;k<500;k+=10)
	{
		line(10,70,60,70);
		line(10,70,10,120);
		line(10,120,35,120);
		line(35,120,35,85);
		line(60,85,60,70);
		line(60,75,75,75);
		line(75,75,75,80);
		line(60,80,75,80);
		line(35,85,60,85);
		settextstyle(TRIPLEX_FONT,0,1);
		outtextxy(75+k,70,"L");
		if(k<100)
		delay(150);
		else
		delay(1);
		j++;
		cleardevice();
	}j=0;
	sound(1000);
	delay(50);
	sound(1020);
	delay(50);
	sound(800);
	delay(50);
	sound(960);
	delay(50);
	sound(1000);
	delay(50);
	nosound();

	for(k=0;k<490;k+=10)
	{
		outtextxy(574,70,"L");
		line(10,70,60,70);
		line(10,70,10,120);
		line(10,120,35,120);
		line(35,120,35,85);
		line(60,85,60,70);
		line(60,75,75,75);
		line(75,75,75,80);
		line(60,80,75,80);
		line(35,85,60,85);
		settextstyle(TRIPLEX_FONT,0,1);
		outtextxy(75+k,70,"E");
		if(k<100)
		delay(150);
		else
		delay(1);
		j++;
		cleardevice();
	}    j=0;
	sound(1000);
	delay(50);
	sound(1020);
	delay(50);
	sound(800);
	delay(50);
	sound(960);
	delay(50);
	sound(1000);
	delay(50);
	nosound();

	for(k=0;k<480;k+=10)
	{
		outtextxy(574,70,"L");
		outtextxy(564,70,"E");
		line(10,70,60,70);
		line(10,70,10,120);
		line(10,120,35,120);
		line(35,120,35,85);
		line(60,85,60,70);
		line(60,75,75,75);
		line(75,75,75,80);
		line(60,80,75,80);
		line(35,85,60,85);
		settextstyle(TRIPLEX_FONT,0,1);
		outtextxy(75+k,70,"V");
		if(k<100)
		delay(150);
		else
		delay(1);
		j++;
		cleardevice();
	}
	j=0;
	sound(1000);
	delay(50);
	sound(1020);
	delay(50);
	sound(800);
	delay(50);
	sound(960);
	delay(50);
	sound(1000);
	delay(50);
	nosound();

	for(k=0;k<470;k+=10)
	{
		outtextxy(574,70,"L");
		outtextxy(564,70,"E");
		outtextxy(554,70,"V");
		line(10,70,60,70);
		line(10,70,10,120);
		line(10,120,35,120);
		line(35,120,35,85);
		line(60,85,60,70);
		line(60,75,75,75);
		line(75,75,75,80);
		line(60,80,75,80);
		line(35,85,60,85);
		settextstyle(TRIPLEX_FONT,0,1);
		outtextxy(75+k,70,"E");
		j++;
		if(k<100)
		delay(150);
		else
		delay(1);
		cleardevice();
	}            j=0;
	sound(1000);
	delay(50);
	sound(1020);
	delay(50);
	sound(800);
	delay(50);
	sound(960);
	delay(50);
	sound(1000);
	delay(50);
	nosound();

	for(k=0;k<460;k+=10)
	{
		cleardevice();
		outtextxy(574,70,"L");
		outtextxy(564,70,"E");
		outtextxy(554,70,"V");
		outtextxy(544,70,"E");
		line(10,70,60,70);
		line(10,70,10,120);
		line(10,120,35,120);
		line(35,120,35,85);
		line(60,85,60,70);
		line(60,75,75,75);
		line(75,75,75,80);
		line(60,80,75,80);
		line(35,85,60,85);
		settextstyle(TRIPLEX_FONT,0,1);
		outtextxy(75+k,70,"L");
		j++;
		if(k<100)
		delay(150);
		else
		delay(1);
	}
	cleardevice();
	outtextxy(574,220,"L");
	outtextxy(564,220,"E");
	outtextxy(554,220,"V");
	outtextxy(544,220,"E");
	outtextxy(534,220,"L");
	j=1;
		cleardevice();
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(574,70,"L");
	outtextxy(564,70,"E");
	outtextxy(554,70,"V");
	outtextxy(544,70,"E");
	outtextxy(534,70,"L");
	rectangle(250,190,370,220);
	settextstyle(7,0,2);
	outtextxy(255,190," EASY ");
	rectangle(250,250,370,280);
	outtextxy(255,250," MEDIUM ");
	rectangle(250,310,370,340);
	outtextxy(255,310," HARD ");

	 initmouse();
	showmouseptr();
		while(!kbhit())
	{
		ip.x.ax=3;
		int86(0X33,&ip,&op);
		if(op.x.cx>=255&&op.x.cx<=340)
		{

			if(op.x.dx>=190&&op.x.dx<=240)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					easy();
			       }
			   }
		   }


	 if(op.x.cx>=255&&op.x.cx<=340)
		{

			if(op.x.dx>=250&&op.x.dx<=300)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					medium();
			       }
			   }
		   }


	 if(op.x.cx>=255&&op.x.cx<=340)
		{

			if(op.x.dx>=310&&op.x.dx<=350)
			{

				if(op.x.bx==1)
				{
					hidemouseptr();
					hard();
			       }
			   }
		   }
	 }

 }


/////////////////////////// starting page//////////////////////////////
void front()
{        int i;
	int col=600,row=450,color=15;
	grid1();
	setfillstyle(0,YELLOW);
	for(i=1;i<15;i++)
	{
	cleardevice();
	grid1();
	settextstyle(1,0,i);
	setcolor(YELLOW);
	bar3d(70,170,140,300,15,1);
	outtextxy(80,150,"S");
	setcolor(LIGHTGRAY);
	bar3d(150,170,220,300,15,1);
	outtextxy(150,150,"U");
	setcolor(LIGHTGREEN);
	bar3d(230,170,300,300,15,1);
	outtextxy(230,150,"D");
	setcolor(MAGENTA);
	bar3d(310,170,380,300,15,1);
	outtextxy(310,150,"O");
	setcolor(CYAN);
	bar3d(390,170,460,300,15,1);
	outtextxy(390,150,"K");
	setcolor(LIGHTBLUE);
	bar3d(470,170,540,300,15,1);
	outtextxy(470,150,"U");


	delay(60);
	}
	setcolor(MAGENTA);
	settextstyle(7,0,2);
	outtextxy(420,445,"Loading");
	rectangle(530,455,620,463);
	setcolor(LIGHTGRAY);
	for(i=0;i<90;i++)
	{
	line(530+i,455,530+i,463);
	delay(25);
	}
	while(!kbhit())
	{
		settextstyle(1,0,1);

		setcolor(random(color));
		outtextxy(random(col),random(row),"8");
		outtextxy(random(col),random(row),"9");
		outtextxy(random(col),random(row),"0");
		outtextxy(random(col),random(row),"1");
		outtextxy(random(col),random(row),"2");
		outtextxy(random(col),random(row),"3");
		outtextxy(random(col),random(row),"4");
		outtextxy(random(col),random(row),"5");
		outtextxy(random(col),random(row),"7");
		outtextxy(random(col),random(row),"0");
		outtextxy(random(col),random(row),"6");
		delay(500);
	}

	getch();
}



////////////////////// starting page grid/////////////////////////////////
void grid1()
{
	int i=0,j=0,k=0;
	for(i=20;i<=600;i+=34)
	{
		k=0;
		for(j=50;j<=440;j+=34)
		{
			k++;
			if(k<=4)
			{
				setcolor(GREEN);
			}
			else
				if(k>4&&k<=8)
					setcolor(RED);
				else
					if(k>8&&k<=12)
						setcolor(BLUE);
			rectangle(i-15,j-15,i+15,j+15);
		}
	}
}

//******************************  end **********************************//