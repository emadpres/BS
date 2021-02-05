#include <graphics.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
// sry for my dirty code :ds
using namespace std;


//***********************   define main project data structure

int map[22][22];//1=close 2=bomb-close 3=open  4=flag |||| 6===>1 7==>2 8==>3 9==>4 10 ==>5
int temp[22][22];
int flag=1;



//*********************** declration of the functions

int mainpage(int *, int * , int*);
int secondpage();
int createmap(int [][22],int,int);
bool updatemap(int ,int , int ,bool , bool ,bool *);
int mainprocess(int [][22],int , int,int);
bool finditem(int [],int ,int);
int gettime(int );
int getpos(int *, int *,int ,int ,bool * , bool *);
int drawmap(int [][22],int ,int);
int detailmap(int , int,bool);
bool checkwin(int , int);






//************************ define main function




int main()
{
    int mainenter=0,size=5,number=5;
    mainpage(&mainenter,&size,&number);
    while(flag)
    {
        int start=time(0);
        createmap(map,size,number);
        system("cls");
        flag=mainprocess(map,size,number,start);
        if (flag)
            {
               system("cls");
               closegraph();
            }

    }


}

//*************************** definition of the functions
int mainpage(int *x,int *y, int *z)
{
    int flag1=0;
    cout<<"\n\n\n\n\t\t\t HELLO AND WELCOME TO THE MINE GAME";
    cout<<"\n\nplease choose the difficulty of the game";
    cout<<"\n\nenter '1' to select easy   (9*9)";
    cout<<"\nenter '2' to select normal (15*15)";
    cout<<"\nenter '3' to select hard   (20*20)";
    cout<<"\nor enter '4' to select custom size ";
    cout<<"\n\nyou enter   :";
    cin >>*x;
    if (*x==4)
    {do{
        cout<<"\n\nenter the size of the map(3-20)   :";
        cin>>*y;
        int temp=((*y) * (*y))*3/5;
        cout<<"\nenter the number of mine (5-"<<temp<<")  :";
        cin>>*z;
        if (*y>21 || *y<3)flag=1;
        else if( *z<5 || *z>temp)flag1=1;
        else flag1=0;
        if(flag1==1)cout<<"\n\nwrong input!!!";
        }
        while(flag1);

     }
    else if (*x==1){*y=9;*z=10;}
    else if (*x==2){*y=15;*z=40;}
    else if (*x==3){*y=20;*z=99;}
    else {cout<<"\nwrong input .restart the program!!!";flag=0;cin.get();cin.get();exit(0);}
        system("cls");
    cout<<"\t\t\t\t\t*hint*"<<endl<<endl;
    cout<<"left click ==>open the box"<<endl;
    cout<<"by  right click on the box you can flag and unflag it"<<endl;
    cout<<"and at the end of the game you can repeat that by click on the greenbox"<<endl;
    cout<<"\n\n\t\t\t enjoy the game";
    cout<<"\n\n\t\t***********    ramin fahimi 90522229    **********"<<endl;
    cout<<"\n\n\tloading";
    for(int i=0;i<5;i++)
    {
            cout<<".";
            delay(200);
    }
    cout<<"\n\n\n\n\n\n\t\t\tpress any key to continue...";
    cin.get();
    cin.get();

}

//*************************************


//**************************************
int mainprocess(int m[][22],int a,int b,int start)
{
    bool flag=true; // flag vaghti false mishe ke bazande beshim ya barande
    int posx=0,posy=0;
    int parcham=0;
    bool left=false,right=false,end=false;
    bool win=false,first=true;



    int gdriver = EGA, gmode = EGAHI, errorcode;
    initgraph(&gdriver, &gmode, "");


    drawmap(m,a,b);
    detailmap(a,b,end);
    while(flag)
    {

        getpos(&posx,&posy,a,start,&left,&right);
        end=updatemap(a,posx,posy,left,right,&first);
        drawmap(m,a,b);
        detailmap(a,b,end);
        if (end==true)flag=false;
        win=checkwin(a,b);
        if (win && end)outtextxy(350, 100, "you win the game !!");
        else if (!win && end)outtextxy(350, 100, "you hit a mine !!");

    }

    outtextxy(350, 120, "repeat?");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    setbkcolor(GREEN);
    outtextxy(350, 200, "YES");
    setcolor(BLACK);
    setbkcolor(RED);
    outtextxy(450, 200, "NO");
    while(true)
    {
         int x=0,y=0;
         if (ismouseclick(WM_LBUTTONDBLCLK))
         {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if (getpixel(x,y)==GREEN || getpixel(x,y)==WHITE){return true;}
            else if (getpixel(x,y)==RED || getpixel(x,y)==BLACK)return false;
         }
     }



}

//************************************
int createmap(int a[][22],int y,int z)
{
    //amade kardane base map
    for(int i=0;i<22;i++)
    {
       for(int j=0;j<=22;j++)
       {

               if (i>0 && i<=y && j>0 && j<=y )a[i][j]=temp[i][j]=1;
               else a[i][j]=temp[i][j]=0;
       }
    }
    //amade kardane map ba chidane randome min ha
    srand(time(0));
    int number=0,list[z],count=0;
    for(int i=0;;i++)
    {
       number=rand()%(y * y);
       if (finditem(list,z,number))
       {
           a[(number/y)+1][(number%y)+1]=temp[(number/y)+1][(number%y)+1]=2;
           list[count]=number;
           count++;
       }
       if (count==z)break;
    }
}
//********************************
bool updatemap(int size,int x,int y,bool left, bool right,bool *first)
{

    if (*first && map[y][x]==2){map[y][x]=1;*first=false;}
    if (right && x<=size && y<=size)
    {
            if(map[y][x]==4)map[y][x]=temp[y][x];
            else if (map[y][x]==2 || map[y][x]==1)map[y][x]=4;

    }
    if (left && x<=size && y<=size)
    {
        if (map[y][x]==2)return true;
        else if(map[y][x]==1)
        {
             int counter=0,bomb=0;
             if (map[y-1][x-1]!=2){counter++;}else bomb++;
             if (map[y][x-1]!=2){counter++;}else bomb++;
             if (map[y+1][x-1]!=2){counter++;}else bomb++;
             if (map[y-1][x]!=2){counter++;}else bomb++;
             if (map[y+1][x]!=2){counter++;}else bomb++;
             if (map[y-1][x+1]!=2){counter++;}else bomb++;
             if (map[y][x+1]!=2){counter++;}else bomb++;
             if (map[y+1][x+1]!=2){counter++;}else bomb++;

             if (counter==8)
             {
                 int cnt=0;
                 for(int j=y-1;j<y+2;j++)
                 {
                     for (int i=x-1;i<x+2;i++)
                     {
                         for(int ja=j-1;ja<j+2;ja++)
                         {
                             for(int ia=i-1;ia<i+2;ia++)
                             {
                                 if (map[ja][ia]==2)cnt++;
                             }

                         }
                         switch(cnt)
                         {
                                 case 0:{map[j][i]=3;break;}
                                 case 1:{map[j][i]=6;break;}
                                 case 2:{map[j][i]=7;break;}
                                 case 3:{map[j][i]=8;break;}
                                 case 4:{map[j][i]=9;break;}
                                 case 5:{map[j][i]=10;break;}
                         }
                         cnt=0;
                     }
                 }
                 map[y][x]=3;
              }
             else
             {

                  if (bomb==1)map[y][x]=6;
                  if (bomb==2)map[y][x]=7;
                  if (bomb==3)map[y][x]=8;
                  if (bomb==4)map[y][x]=9;
                  if (bomb==5)map[y][x]=10;

             }
		}

	}
	return false;
}
//*******************************

bool finditem(int d[],int size,int item)
{
     for(int i=0;i<size;i++)
     {
             if (d[i]==item)return false;
     }

     return true;

}

//********************************
int gettime(int base)
{
    int dif=time(0)-base;
    return dif;
}
//********************************
int getpos(int *x , int *y,int size,int base,bool *left ,bool * right)
{
    char msg[80];

     while (true)
    {

     if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, *x, *y);
            if (size<10){*x/=35;*y/=35;(*x)++;(*y)++;}
            else {*x/=17;*y/=17;(*x)++;(*y)++;}
            *left=true;
            *right=false;
            break;
        }

     else if (ismouseclick(WM_RBUTTONDOWN))
        {
             getmouseclick(WM_RBUTTONDOWN, *x,*y);
             if (size<10){*x/=35;*y/=35;(*x)++;(*y)++;}
             else {*x/=17;*y/=17;(*x)++;(*y)++;}
             *right=true;
             *left=false;
             break;
        }

     int time;
     time=gettime(base);
     sprintf(msg, "time: %d", time);
     outtextxy(500,50, msg);

    }
}
//********************************
int drawmap(int map[][22],int size,int number)
{
    cleardevice();
    setbkcolor(9);
    cleardevice();
    int posx=0,posy=0;

    if (size<10)
        {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
               setcolor(0);
               rectangle(posx,posy,posx+35,posy+35);
               posx+=35;
            }
            posx=0;
            posy+=35;
        }
    }
    if (size>10)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
               setcolor(0);
               rectangle(posx,posy,posx+17,posy+17);
               posx+=17;
            }
            posx=0;
            posy+=17;
        }
    }
}


//**************************************
int detailmap(int size,int bomb,bool end)
{
    for(int i=0;i<size;i++)
    {
       for(int j=0;j<size;j++)
       {
          if (map[i+1][j+1]==3)
          {
             if(size<10)
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "X");
             }
             else
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5, "X");
             }
          }
          if (map[i+1][j+1]==4)
          {
             if(size<10)
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "F");
             }
             else
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5, "F");
             }
          }
          if (end && map[i+1][j+1]==2)
          {
             if(size<10)
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "#");
             }
             else
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5,"#");
             }

          }
		  if (map[i+1][j+1]==6)

          {
             if(size<10)

             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "1");
             }

             else

             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5, "1");
             }
          }
		  if (map[i+1][j+1]==7)
          {
             if(size<10)
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "2");
             }
             else
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5, "2");
             }
          }
          if (map[i+1][j+1]==8)
          {
             if(size<10)
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "3");
             }
             else
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5, "3");
             }
          }
          if (map[i+1][j+1]==9)
          {
             if(size<10)
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "4");
             }
             else
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5, "4");
             }
          }
          if (map[i+1][j+1]==10)
          {
             if(size<10)
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                 outtextxy(35*j+10, 35*i+10, "5");
             }
             else
             {
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                 outtextxy(17*j+5, 17*i+5, "5");
             }
          }

       }
     }
}


//**************************
bool checkwin(int size,int bomb)
{
     int counter=0;
     for (int i=1;i<=size;i++)
     {
         for (int j=1;j<=size;j++)
         {
             if (map[i][j]!=2)counter++;

         }
     }
     if (counter==((size*size)-bomb))return true;
     else
          return false;

}
