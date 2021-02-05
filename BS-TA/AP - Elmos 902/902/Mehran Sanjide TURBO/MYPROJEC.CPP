#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>



union REGS i,o;
//----------------------------------------------
       void show_mouse()      {
	i.x.ax=1;
	int86(0x33,&i,&o);
      }
//----------------------------------------------
     void hide_mouse()    {
       i.x.ax=2;
       int86(0x33,&i,&o);
	}
//----------------------------------------------
     void get_mouse_pos(int *x,int *y,int *button1,int *button2)    {
       i.x.ax=3;
       int86(0x33,&i,&o);
	    *x=o.x.cx;
	   *y=o.x.dx;
	   *button1=o.x.bx&1;
	   *button2=o.x.bx&2;
     }
//-----------------------------------------------

void show(int a,int b,int l,int t,int kol[16][30],int w,int h,int &count);
void main()
{
newgame:
int count=0;
int mines=0,height=0,width=0;
int gd=DETECT,gm,button1=0,button2=0;
initgraph(&gd,&gm,"c:\\bgi");
i.x.ax=0;
int86(0x33,&i,&o);
if(o.x.ax==0)      {
cout<<"No Mouse is available..";
exit(0);
restorecrtmode();
}
settextstyle(TRIPLEX_FONT,HORIZ_DIR,6);
outtextxy(150,70,"Mine Sweeper");
settextstyle(8,HORIZ_DIR,1);
outtextxy(70,200,"Select your game:");
outtextxy(555,435,"EXIT");
rectangle(80,240,300,280);
rectangle(80,290,300,330);
rectangle(80,340,300,380);
rectangle(80,390,300,430);
rectangle(540,430,620,470);
outtextxy(90,250,"Beginner");
outtextxy(90,300,"Intermediat");
outtextxy(90,350,"Advanced");
outtextxy(90,400,"Custom");
//for(int i=0;i<=16;i++)
setbkcolor(1); // delay(1500);}
rectangle(5,5,635,475);
int x1=0,y1=0;
int flag=1;
int kol[16][30];
for(int ii=0;ii<=15;ii++) for(int jj=0;jj<=29;jj++) kol[ii][jj]=0;
//------------------------- 1 ------------------------------------
while(!kbhit() && flag)
{
show_mouse();
get_mouse_pos(&x1,&y1,&button1,&button2);
if(button1==1) { hide_mouse();
	if(x1>540 && x1<620 && y1>430 && y1<470) exit(0);
	if(x1>80 && x1<300 && y1>240 && y1<280){mines=10; height=9; width=9; flag=0;}
	if(x1>80 && x1<300 && y1>290 && y1<330){mines=40; height=16; width=16; flag=0;}
	if(x1>80 && x1<300 && y1>340 && y1<380){mines=99; height=16; width=30; flag=0;}
	if(x1>80 && x1<300 && y1>390 && y1<430){

						 line(300,410,380,410);
						 line(380,410,380,260);
						 line(380,260,385,260);
						 line(380,310,385,310);
						 line(380,360,385,360);
						 outtextxy(390,248,"Width  :");
						 outtextxy(390,296,"Height :");
						 outtextxy(390,344,"Mines  :");

						 gotoxy(65,17); cin>>width;
						 gotoxy(65,20); cin>>height;
						 gotoxy(65,23); cin>>mines;

						 if(width<5 || width>30)       {outtextxy(200,140,"WIDTH ERROR(5 - 30)"); setbkcolor(4);  delay(5000);  goto newgame;}
						 if(height<5 || height>16)     {outtextxy(200,140,"HEIGHT ERROR(5 - 16)"); setbkcolor(4);  delay(5000);  goto newgame;}
						 if(mines<5)                   {outtextxy(200,140,"MINES ARE VERY FEW!"); setbkcolor(4);  delay(5000);  goto newgame;}
						 if((width*height)*(0.2)<mines){outtextxy(250,240,"Your mines are so much"); setbkcolor(4); delay(5000);  goto newgame;}
						 flag=0;
					       }
		 }
	}
//----------------------------- 2 ----------------------------
int i=0,j=0;
randomize();
for(int qq=0;qq<mines; )
{
i=rand()%height;
j=rand()%width;
if(kol[i][j]!=9) {	  kol[i][j]=9;     qq++;
			  if(i+1<=height-1 && j+1<=width-1 && kol[i+1][j+1]!=9) kol[i+1][j+1]++;
			  if(j+1<=width-1 && kol[i][j+1]!=9)                  kol[i][j+1]++;
			  if(i+1<=height-1 && kol[i+1][j]!=9)                 kol[i+1][j]++;
			  if(i-1>=0 && j+1<=width-1 && kol[i-1][j+1]!=9)        kol[i-1][j+1]++;
			  if(i+1<=height-1 && j-1>=0 && kol[i+1][j-1]!=9)       kol[i+1][j-1]++;
			  if(i-1>=0 && j-1>=0 && kol[i-1][j-1]!=9)              kol[i-1][j-1]++;
			  if(i-1>=0 && kol[i-1][j]!=9)                        kol[i-1][j]++;
			  if(j-1>=0 && kol[i][j-1]!=9)                        kol[i][j-1]++;
		  }
}
for(int iii=0;iii<=height-1;iii++){cout<<endl; for(int jjj=0;jjj<=width-1;jjj++) cout<<kol[iii][jjj];}
getch();
char saat[5];
char min[5];
button1=0; button2=0;
//---------------------- 3 -----------------------
cleardevice();
int mco=mines;
setbkcolor(6);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,6);
outtextxy(150,15,"Mine Sweeper");
for(int t=0;t<height;t++) {for(int y=0;y<width;y++)   rectangle(((30-width)/2+y)*(20)+15,((20-height)/2+t)*(20)+40,((30-width)/2+y)*(20)+15+20,((20-height)/2+t)*(20)+40+20);}
int top=((20-height)/2)*(20)+40,left=((30-width)/2)*(20)+15; //left & top!
settextstyle(8,HORIZ_DIR,1);
outtextxy(555,435,"EXIT");
rectangle(540,430,620,470);
outtextxy(25,435,"New Game");
rectangle(20,430,140,470);
outtextxy(248,435,"Time  :");
outtextxy(248,415,"Mines :");
flag=1;
int flag1=1,flag2=1;
int atime=0;
time_t tcount;
tcount=time(NULL);
itoa(mco,min,10);     outtextxy(340,417,min);
while(!kbhit() && flag)
	{
	 if(count==(width*height-mines)){setfillstyle(1,4); bar(250,210,390,270); outtextxy(260,220,"Success! "); flag=0; outtextxy(260,240," Time:"); outtextxy(360,240,saat);}
	 show_mouse();
	 get_mouse_pos(&x1,&y1,&button1,&button2);
	 if(button2==2) {hide_mouse();
			 if(x1>left && x1<left+(width*20) && y1>top && y1<top+(height*20))
							{
							 int cx=(x1-left)/20;
							 int cy=(y1-top)/20;
							 if(kol[cy][cx]<10){
								settextstyle(TRIPLEX_FONT,0,1);
								outtextxy(left+20*cx+10,top+20*cy-4,"!");
								kol[cy][cx]=kol[cy][cx]+10;
								mco--;bar(320,420,400,440);     itoa(mco,min,10);     outtextxy(340,417,min);
												}
							 else if(kol[cy][cx]!=21){
								setfillstyle(1,getbkcolor());
								bar(left+20*cx+10,top+20*cy+1,left+20*cx+13,top+20*cy+17);
								kol[cy][cx]=kol[cy][cx]-10;
								mco++;bar(320,420,400,440);     itoa(mco,min,10);     outtextxy(340,417,min);
												}
							}
			}
	 while(button2==2){ get_mouse_pos(&x1,&y1,&button1,&button2);  if(tcount!=time(NULL)){tcount=time(NULL); atime++; itoa(atime,saat,10); bar(320,440,400,460);  outtextxy(340,437,saat);}}
	 if(button1==1) { hide_mouse();
			 if(x1>540 && x1<620 && y1>430 && y1<470) exit(0);
			 if(x1>20 && x1<140 && y1>430 && y1<470) goto newgame;
			 if(x1>left && x1<left+(width*20) && y1>top && y1<top+(height*20))
				 {
				   int cx=(x1-left)/20;
				   int cy=(y1-top)/20;
				 //first click != 9!!!!!!!!!
				   if(flag1 && kol[cy][cx]==9)
							    {
							     kol[cy][cx]=0;
							     if(cy-1>=0 && cx-1>=0){
										    if(kol[cy-1][cx-1]==9) kol[cy][cx]++;
										    else                   kol[cy-1][cx-1]--;
										   }
							     if(cy+1<height && cx+1<width){
										    if(kol[cy+1][cx+1]==9) kol[cy][cx]++;
										    else                   kol[cy+1][cx+1]--;
										   }
							     if(cy-1>=0 && cx+1<width){
										    if(kol[cy-1][cx+1]==9) kol[cy][cx]++;
										    else                   kol[cy-1][cx+1]--;
										   }
							     if(cy+1<height && cx-1>=0){
										    if(kol[cy+1][cx-1]==9) kol[cy][cx]++;
										    else                   kol[cy+1][cx-1]--;
										   }
							     if(cy-1>=0){
										    if(kol[cy-1][cx]==9) kol[cy][cx]++;
										    else                   kol[cy-1][cx]--;
										   }
							     if(cx-1>=0){
										    if(kol[cy][cx-1]==9) kol[cy][cx]++;
										    else                   kol[cy][cx-1]--;
										   }
							     if(cy+1<height){
										    if(kol[cy+1][cx]==9) kol[cy][cx]++;
										    else                   kol[cy+1][cx]--;
										   }
							     if(cx+1<width){
										    if(kol[cy][cx+1]==9) kol[cy][cx]++;
										    else                   kol[cy][cx+1]--;
										   }
							     Again:

							     randomize();
							     i=rand()%height;
							     j=rand()%width;
							     if(kol[i][j]!=9 && flag2) {	  kol[i][j]=9;  flag2=0;
								  if(i+1<=height-1 && j+1<=width-1 && kol[i+1][j+1]!=9) kol[i+1][j+1]++;
								  if(j+1<=width-1 && kol[i][j+1]!=9)                  kol[i][j+1]++;
								  if(i+1<=height-1 && kol[i+1][j]!=9)                 kol[i+1][j]++;
								  if(i-1>=0 && j+1<=width-1 && kol[i-1][j+1]!=9)        kol[i-1][j+1]++;
								  if(i+1<=height-1 && j-1>=0 && kol[i+1][j-1]!=9)       kol[i+1][j-1]++;
								  if(i-1>=0 && j-1>=0 && kol[i-1][j-1]!=9)              kol[i-1][j-1]++;
								  if(i-1>=0 && kol[i-1][j]!=9)                        kol[i-1][j]++;
								  if(j-1>=0 && kol[i][j-1]!=9)                        kol[i][j-1]++;
											}
							     if(flag2)  goto Again;
							    }
				   show(cx,cy,left,top,kol,width,height,count);
				   flag1=0;
				 }
		       }

	 if(tcount!=time(NULL) && !flag1){tcount=time(NULL); atime++; itoa(atime,saat,10); bar(320,440,400,460);  outtextxy(340,437,saat);}
	}
getch();
cout<<count;//for(iii=0;iii<=height-1;iii++){cout<<endl; for(int jjj=0;jjj<=width-1;jjj++) cout<<kol[iii][jjj];}
getch();
closegraph();
}


void show(int a,int b,int l,int t,int kol[16][30],int w,int h,int &count)
{
 if(kol[b][a]==0){
			setfillstyle(HATCH_FILL,7);
			bar(l+20*a,t+20*b,l+20*a+20,t+20*b+20);
			kol[b][a]=21;   //adade khonsa ===21
			count++;
			if(kol[b-1][a]<9 && b-1>=0)  show(a,b-1,l,t,kol,w,h,count);
			if(kol[b][a-1]<9 && a-1>=0)  show(a-1,b,l,t,kol,w,h,count);
			if(kol[b+1][a]<9 && b+1<h)  show(a,b+1,l,t,kol,w,h,count);
			if(kol[b][a+1]<9 && a+1<w)  show(a+1,b,l,t,kol,w,h,count);
			if(kol[b+1][a+1]<9 && a+1<w && b+1<h) show(a+1,b+1,l,t,kol,w,h,count);
			if(kol[b-1][a+1]<9 && a+1<w && b-1>=0) show(a+1,b-1,l,t,kol,w,h,count);
			if(kol[b+1][a-1]<9 && a-1>=0 && b+1<h) show(a-1,b+1,l,t,kol,w,h,count);
			if(kol[b-1][a-1]<9 && a-1>=0 && b-1>=0) show(a-1,b-1,l,t,kol,w,h,count);
		 }
 if(kol[b][a]==9){
			{setfillstyle(1,4); bar(250,210,390,270); outtextxy(260,220,"You Lose! ");  outtextxy(260,240,"Thank You!"); delay(5000); exit(0);}
		 }
 if(kol[b][a]>=0 && kol[b][a]<=8)
		 {
			char adad[3];   itoa(kol[b][a],adad,10);
			outtextxy(l+20*a+5,t+20*b-4,adad);
			kol[b][a]=21;
			count++;               //adade  khonsa====21
		 }
}
