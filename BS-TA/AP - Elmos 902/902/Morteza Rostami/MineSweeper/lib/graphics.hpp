#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include </home/emancipator/MineSweeper/lib/non-graphics.hpp>

using namespace sf;

int Start(int,int,int);
void ShowEmptyBlocks(int,int,int,int,int,Sprite,Sprite,Sprite,const Image,const Image,const Image,const Image,const Image,const Image,const Image,const Image,const Image);
string Updater(int);
int IfFinished(int,int,int,int *,int,Sprite,Sprite);
int SelectLevel();
void Custom();
int MainMenu();


///////////////////////////////////////////////////////////////////////////////////////

int MainMenu()
{
	RenderWindow mainmenu(VideoMode(400,450),"MineSweeper");

	Font arial;
	arial.LoadFromFile("data/arial.ttf",50);

	Image menupic;
	menupic.LoadFromFile("data/menupic.png");

	Sprite smenupic;
	smenupic.SetImage(menupic);
	smenupic.Move(80,72);

	String title("MineSweeper",arial,50);
	title.SetColor(Color(255,255,255));
	title.Move(50,14);

	String play("Play",arial,30);
	play.SetColor(Color(255,255,255));
	play.Move(14,400);

	String exit("Exit",arial,30);
	exit.SetColor(Color(255,255,255));
	exit.Move(336,400);


	while(mainmenu.IsOpened())
	{
		Event event;
		while(mainmenu.GetEvent(event))
		{
			if(event.Type==Event::Closed)
				mainmenu.Close();
			if(event.Type==Event::MouseButtonPressed)
			{
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=14 && event.MouseButton.X<=100 && event.MouseButton.Y>=400 && event.MouseButton.Y<=430)
				{	
					mainmenu.Close();
					SelectLevel();
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=336 && event.MouseButton.X<=400 && event.MouseButton.Y>=400 && event.MouseButton.Y<=430)
				{	
					mainmenu.Close();
				}
			}
			if(event.MouseMove.X>=14 && event.MouseMove.X<=100 && event.MouseMove.Y>=400 && event.MouseMove.Y<=430)
				play.SetColor(Color(255,255,0));
			else
				play.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=336 && event.MouseMove.X<=400 && event.MouseMove.Y>=400 && event.MouseMove.Y<=430)
				exit.SetColor(Color(255,255,0));
			else
				exit.SetColor(Color(255,255,255));
		}
		mainmenu.Clear();
		mainmenu.Draw(smenupic);
		mainmenu.Draw(title);
		mainmenu.Draw(play);
		mainmenu.Draw(exit);
		mainmenu.Display();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int SelectLevel()
{
	RenderWindow submenu(VideoMode(400,450),"MineSweeper");

	Font arial;
	arial.LoadFromFile("data/arial.ttf",50);

	Image menupic;
	menupic.LoadFromFile("data/menupic.png");

	Sprite smenupic;
	smenupic.SetImage(menupic);
	smenupic.Move(80,72);

	String title("MineSweeper",arial,50);
	title.SetColor(Color(255,255,255));
	title.Move(50,14);

	String easy("Easy",arial,30);
	easy.SetColor(Color(255,255,255));
	easy.Move(14,342);

	String normal("Normal",arial,30);
	normal.SetColor(Color(255,255,255));
	normal.Move(150,342);

	String hard("Hard",arial,30);
	hard.SetColor(Color(255,255,255));
	hard.Move(315,342);

	String custom("Custom",arial,30);
	custom.SetColor(Color(255,255,255));
	custom.Move(147,380);

	String mainmenu("Main Menu",arial,20);
	mainmenu.SetColor(Color(255,255,255));
	mainmenu.Move(14,410);

	String exit("Exit",arial,20);
	exit.SetColor(Color(255,255,255));
	exit.Move(336,410);

	while(submenu.IsOpened())
	{
		Event event;
		while(submenu.GetEvent(event))
		{
			if(event.Type==Event::Closed)
				submenu.Close();
			if(event.Type==Event::MouseButtonPressed)
			{
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=14 && event.MouseButton.X<=115 && event.MouseButton.Y>=410 && event.MouseButton.Y<=430)
				{	
					submenu.Close();
					MainMenu();
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=336 && event.MouseButton.X<=370 && event.MouseButton.Y>=410 && event.MouseButton.Y<=430)
				{	
					submenu.Close();
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=14 && event.MouseButton.X<=80 && event.MouseButton.Y>=342 && event.MouseButton.Y<=372)
				{
					submenu.Close();
					Start(9,9,10);
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=150 && event.MouseButton.X<=245 && event.MouseButton.Y>=342 && event.MouseButton.Y<=372)
				{
					submenu.Close();
					Start(16,16,40);
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=315 && event.MouseButton.X<=380 && event.MouseButton.Y>=342 && event.MouseButton.Y<=372)
				{
					submenu.Close();
					Start(30,16,99);
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=147 && event.MouseButton.X<=245 && event.MouseButton.Y>=380 && event.MouseButton.Y<=410)
				{
					submenu.Close();
					Custom();
				}
			}
			if(event.MouseMove.X>=14 && event.MouseMove.X<=80 && event.MouseMove.Y>=342 && event.MouseMove.Y<=372)
				easy.SetColor(Color(255,255,0));
			else
				easy.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=150 && event.MouseMove.X<=245 && event.MouseMove.Y>=342 && event.MouseMove.Y<=372)
				normal.SetColor(Color(255,255,0));
			else
				normal.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=315 && event.MouseMove.X<=380 && event.MouseMove.Y>=342 && event.MouseMove.Y<=372)
				hard.SetColor(Color(255,255,0));
			else
				hard.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=150 && event.MouseMove.X<=245 && event.MouseMove.Y>=380 && event.MouseMove.Y<=410)
				custom.SetColor(Color(255,255,0));
			else
				custom.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=14 && event.MouseMove.X<=115 && event.MouseMove.Y>=410 && event.MouseMove.Y<=430)
				mainmenu.SetColor(Color(255,255,0));
			else
				mainmenu.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=336 && event.MouseMove.X<=370 && event.MouseMove.Y>=410 && event.MouseMove.Y<=430)
				exit.SetColor(Color(255,255,0));
			else
				exit.SetColor(Color(255,255,255));
		}
		submenu.Clear();
		submenu.Draw(title);
		submenu.Draw(smenupic);
		submenu.Draw(easy);
		submenu.Draw(normal);
		submenu.Draw(hard);
		submenu.Draw(custom);
		submenu.Draw(mainmenu);
		submenu.Draw(exit);
		submenu.Display();
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

void ShowEmptyBlocks(int xpos,int ypos,int x,int y,int bmap[30][16],Sprite map[30][16],Sprite sblock2,Sprite sflag,const Image *block2,const Image *one,const Image *two,const Image *three,const Image *four,const Image *five,const Image *six,const Image *seven,const Image *eight)
{
	if(map[xpos][ypos].GetImage()!=sflag.GetImage() && xpos>=0 && xpos<x && ypos>=0 && ypos<y)
	{
		switch(bmap[xpos][ypos])
		{
			case 0:
				bmap[xpos][ypos]=-2;
				map[xpos][ypos].SetImage(*block2);
				for(int i=xpos-1;i<xpos+2;i++)
					for(int j=ypos-1;j<ypos+2;j++)
						ShowEmptyBlocks(i,j,x,y,bmap,map,sblock2,sflag,&*block2,&*one,&*two,&*three,&*four,&*five,&*six,&*seven,&*eight);
				break;
			case 1:
				map[xpos][ypos].SetImage(*one);
				break;
			case 2:
				map[xpos][ypos].SetImage(*two);
				break;
			case 3:
				map[xpos][ypos].SetImage(*three);
				break;
			case 4:
				map[xpos][ypos].SetImage(*four);
				break;
			case 5:
				map[xpos][ypos].SetImage(*five);
				break;
			case 6:
				map[xpos][ypos].SetImage(*six);
				break;
			case 7:
				map[xpos][ypos].SetImage(*seven);
				break;
			case 8:
				map[xpos][ypos].SetImage(*eight);
				break;
		}
	}
	return;
}
////////////////////////////////////////////////////////////////////////////////////////////

string Updater(int timer)
{  
	string time;  
	stringstream out;  
	out << timer;  
	time = out.str();
	return time;
}  
/////////////////////////////////////////////////////////////////////////////////////////

void IfFinished(int x,int y,int minenum,int *finished,int bmap[30][16],Sprite map[30][16],Sprite sflag)
{
	int counter=0;
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			if(bmap[i][j]==-1 && map[i][j].GetImage()==sflag.GetImage())
				counter++;
	if(counter==minenum)
		*finished=1;
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////
int Start(int x,int y,int minenum)
{
	int bmap[30][16],counter=minenum,firstmove=1,reset=1,finished=0;
	MineLayer(minenum,x,y,bmap);
	MapAnalyser(x,y,bmap);

	RenderWindow game(VideoMode(40+x*16,82+y*16),"MineSweeper");

	Font arial;
	arial.LoadFromFile("data/arial.ttf",50);

	Clock clock;
	int timer=0;

	String Time("",arial,20);
	Time.Move(52,10);

	String Counter("",arial,20);
	Counter.SetText(Updater(counter));
	Counter.Move(40+x*16-70,10);

	String playagain("Play Again",arial,30);
	playagain.SetColor(Color::Red);
	playagain.Move(8*x-52,8*y+26);

	String mainmenu("Main Menu",arial,15);
	mainmenu.SetColor(Color(255,255,255));
	mainmenu.Move(10,82+y*16-20);

	String exit("Exit",arial,15);
	exit.SetColor(Color(255,255,255));
	exit.Move(40+x*16-35,82+y*16-20);

	Image block1,block2,one,two,three,four,five,six,seven,eight,mine,exmine,flag,fflag,clockpic,minepic;
	block1.LoadFromFile("data/block1.jpeg");
	block2.LoadFromFile("data/block2.jpeg");
	one.LoadFromFile("data/1.jpeg");
	two.LoadFromFile("data/2.jpeg");
	three.LoadFromFile("data/3.jpeg");
	four.LoadFromFile("data/4.jpeg");
	five.LoadFromFile("data/5.jpeg");
	six.LoadFromFile("data/6.jpeg");
	seven.LoadFromFile("data/7.jpeg");
	eight.LoadFromFile("data/8.jpeg");
	mine.LoadFromFile("data/mine.jpeg");
	exmine.LoadFromFile("data/ex-mine.jpeg");
	flag.LoadFromFile("data/flag.jpeg");
	fflag.LoadFromFile("data/false-flag.jpeg");
	clockpic.LoadFromFile("data/clock.png");
	minepic.LoadFromFile("data/mine.png");

	Sprite sblock1,sblock2,sflag,sfflag,sclock,sminepic,smine;
	sblock1.SetImage(block1);
	sblock2.SetImage(block2);
	sflag.SetImage(flag);
	sfflag.SetImage(fflag);
	sclock.SetImage(clockpic);
	sminepic.SetImage(minepic);
	smine.SetImage(mine);

	sclock.Move(5,5);
	sminepic.Move(40+x*16-37,5);

	Sprite map[30][16];
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
		{
			map[i][j].Move(20+16*i,50+16*j);
			map[i][j].SetImage(block1);
		}
	clock.Reset();
	while(game.IsOpened())
	{
		if(reset)
			clock.Reset();
		else
			timer=clock.GetElapsedTime();
		Event event;
		while(game.GetEvent(event))
		{
			if(reset)
				clock.Reset();
			else
				timer=clock.GetElapsedTime();
			if(event.Type==Event::Closed)
				game.Close();
			if(event.MouseMove.X>=10 && event.MouseMove.X<=90 && event.MouseMove.Y>=82+y*16-20 && event.MouseMove.Y<=82+y*16)
				mainmenu.SetColor(Color(255,255,0));
			else
				mainmenu.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=8*x-52 && event.MouseMove.X<=8*x+90 && event.MouseMove.Y>=26+y*8 && event.MouseMove.Y<=56+y*8)
				playagain.SetColor(Color::Yellow);
			else
				playagain.SetColor(Color::Red);
			if(event.MouseMove.X>=40+x*16-35 && event.MouseMove.X<=40+x*16 && event.MouseMove.Y>=82+y*16-20 && event.MouseMove.Y<=82+y*16)
				exit.SetColor(Color(255,255,0));
			else
				exit.SetColor(Color(255,255,255));
			if (event.Type==Event::MouseButtonPressed)
			{
				if(finished)
					if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=8*x-52 && event.MouseButton.X<=8*x+90 && event.MouseButton.Y>=26+y*8 && event.MouseButton.Y<=56+y*8)
					{	
						game.Close();
						Start(x,y,minenum);
					}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=10 && event.MouseButton.X<=90 && event.MouseButton.Y>=82+y*16-20 && event.MouseButton.Y<=82+y*16)
				{	
					game.Close();
					MainMenu();
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=40+x*16-35 && event.MouseButton.X<=40+x*16 && event.MouseButton.Y>82+y*16-20 && event.MouseButton.Y<=82+y*16)
					game.Close();
				if(event.MouseButton.Button==Mouse::Left)
				{
					for(int i=0;i<x;i++)
						for(int j=0;j<y;j++)
							if(event.MouseButton.X>=20+16*i && event.MouseButton.X<20+16*(i+1) && event.MouseButton.Y>=50+16*j && event.MouseButton.Y<50+16*(j+1) && !finished)
							{
								if(map[i][j].GetImage()!=sflag.GetImage() && map[i][j].GetImage()!=sfflag.GetImage() && map[i][j].GetImage()!=smine.GetImage())
								{											
									if(firstmove)
									{
										FirstMove(i,j,x,y,bmap,minenum);
										firstmove=0;
									}								
									switch(bmap[i][j])
									{
										case -1:
											reset=1;
											finished=1;
											for(int k=0;k<x;k++)
												for(int l=0;l<y;l++)
												{	
													if(map[k][l].GetImage()!=sflag.GetImage())
														switch(bmap[k][l])
														{
															case -1:
																map[k][l].SetImage(mine);
																break;
															case 0:
																map[k][l].SetImage(block2);
																break;
															case 1:
																map[k][l].SetImage(one);
																break;
															case 2:
																map[k][l].SetImage(two);
																break;
															case 3:
																map[k][l].SetImage(three);
																break;	
															case 4:
																	map[k][l].SetImage(four);		
																break;
															case 5:
																map[k][l].SetImage(five);
																break;
															case 6:
																map[k][l].SetImage(six);
																break;	
															case 7:
																map[k][l].SetImage(seven);
																break;
															case 8:
																map[k][l].SetImage(eight);
																break;
														}
												if(map[k][l].GetImage()==sflag.GetImage() && bmap[k][l]!=-1)
														map[k][l].SetImage(fflag);
												}
											map[i][j].SetImage(exmine);
											break;
										case 0:
											if(!finished)
												reset=0;
											ShowEmptyBlocks(i,j,x,y,bmap,map,sblock2,sflag,&block2,&one,&two,&three,&four,&five,&six,&seven,&eight);
											break;
										case 1:
											if(!finished)
												reset=0;
											map[i][j].SetImage(one);
											break;
										case 2:
											if(!finished)
												reset=0;
											map[i][j].SetImage(two);
											break;
										case 3:
											if(!finished)
												reset=0;
											map[i][j].SetImage(three);
											break;
										case 4:
											if(!finished)
												reset=0;
											map[i][j].SetImage(four);
											break;
										case 5:
											if(!finished)
												reset=0;
											map[i][j].SetImage(five);
											break;
										case 6:
											if(!finished)
												reset=0;
											map[i][j].SetImage(six);
											break;
										case 7:
											if(!finished)
												reset=0;
											map[i][j].SetImage(seven);
											break;
										case 8:
											if(!finished)
												reset=0;
											map[i][j].SetImage(eight);
											break;
									}
								}
							}
				}
				if(event.MouseButton.Button==Mouse::Right)
					for(int i=0;i<x;i++)
						for(int j=0;j<y;j++)
							if(event.MouseButton.X>=20+16*i && event.MouseButton.X<20+16*(i+1) && event.MouseButton.Y>=50+16*j && event.MouseButton.Y<50+16*(j+1))
							{
								if(map[i][j].GetImage()==sblock1.GetImage() && counter>0)
									{
										map[i][j].SetImage(flag);
										counter--;
										Counter.SetText(Updater(counter));
									}
								else
									if(map[i][j].GetImage()==sflag.GetImage())
									{
										map[i][j].SetImage(block1);
										counter++;
										Counter.SetText(Updater(counter));
									}
							}
      }
		}

	game.Clear();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			game.Draw(map[i][j]);
	game.Draw(mainmenu);
	Time.SetText(Updater(timer));
	game.Draw(Time);
	game.Draw(sclock);
	game.Draw(sminepic);
	game.Draw(exit);
	game.Draw(Counter);
	IfFinished(x,y,minenum,&finished,bmap,map,sflag);
	if(finished)
	{		
		reset=1;
		game.Draw(playagain);
	}
	game.Display();
	}


	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Custom()
{
	RenderWindow custommenu(VideoMode(400,450),"MineSweeper");

	int minenum=40,widthnum=16,heightnum=16;
		
	Font arial;
	arial.LoadFromFile("data/arial.ttf",50);

	Image menupic;
	menupic.LoadFromFile("data/menupic.png");

	Image up;
	up.LoadFromFile("data/up.png");

	Image down;
	down.LoadFromFile("data/down.png");

	Sprite sup[3],sdown[3];
	sup[0].SetImage(up);
	sup[0].Move(40,360);
	sup[1].SetImage(up);
	sup[1].Move(192,360);
	sup[2].SetImage(up);
	sup[2].Move(368,360);
	sdown[0].SetImage(down);
	sdown[0].Move(40,375);
	sdown[1].SetImage(down);
	sdown[1].Move(192,375);
	sdown[2].SetImage(down);
	sdown[2].Move(368,375);

	Sprite smenupic;
	smenupic.SetImage(menupic);
	smenupic.Move(80,72);

	String title("MineSweeper",arial,50);
	title.SetColor(Color(255,255,255));
	title.Move(50,14);

	String mainmenu("Main Menu",arial,20);
	mainmenu.SetColor(Color(255,255,255));
	mainmenu.Move(14,410);

	String exit("Exit",arial,20);
	exit.SetColor(Color(255,255,255));
	exit.Move(336,410);

	String width("Width",arial,15);
	width.SetColor(Color(255,255,255));
	width.Move(14,336);

	String Nwidth("30",arial,20);
	Nwidth.SetColor(Color(255,255,255));
	Nwidth.Move(14,362);

	String height("Height",arial,15);
	height.SetColor(Color(255,255,255));
	height.Move(165,336);

	String Nheight("16",arial,20);
	Nheight.SetColor(Color(255,255,255));
	Nheight.Move(165,362);

	String mine("Mine",arial,15);
	mine.SetColor(Color(255,255,255));
	mine.Move(336,336);

	String Nmine("99",arial,20);
	Nmine.SetColor(Color(255,255,255));
	Nmine.Move(336,362);

	String play("Play",arial,20);
	play.SetColor(Color(255,255,255));
	play.Move(190,410);

	while(custommenu.IsOpened())
	{
		Event event;
		while(custommenu.GetEvent(event))
		{
			if(event.Type==Event::Closed)
				custommenu.Close();
			if(event.Type==Event::MouseButtonPressed)
			{
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=14 && event.MouseButton.X<=115 && event.MouseButton.Y>=410 && event.MouseButton.Y<=430)
				{	
					custommenu.Close();
					MainMenu();
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=190 && event.MouseButton.X<=240 && event.MouseButton.Y>=410 && event.MouseButton.Y<=430)
				{	
					custommenu.Close();
					Start(widthnum,heightnum,minenum);
				}
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=336 && event.MouseButton.X<=370 && event.MouseButton.Y>=410 && event.MouseButton.Y<=430)	
					custommenu.Close();
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=40 && event.MouseButton.X<=55 && event.MouseButton.Y>=360 && event.MouseButton.Y<375)
					if(widthnum<30)	
						widthnum++;
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=192 && event.MouseButton.X<=207 && event.MouseButton.Y>=360 && event.MouseButton.Y<375)
					if(heightnum<16)
						heightnum++;
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=368 && event.MouseButton.X<=383 && event.MouseButton.Y>=360 && event.MouseButton.Y<375)
					if(minenum<(widthnum*heightnum))
						minenum++;
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=40 && event.MouseButton.X<=55 && event.MouseButton.Y>=375 && event.MouseButton.Y<=390)	
					if(widthnum>9)
						widthnum--;
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=192 && event.MouseButton.X<=207 && event.MouseButton.Y>=375 && event.MouseButton.Y<=390)	
					if(heightnum>9)
						heightnum--;
				if(event.MouseButton.Button==Mouse::Left && event.MouseButton.X>=368 && event.MouseButton.X<=383 && event.MouseButton.Y>=375 && event.MouseButton.Y<=390)
					if(minenum>1)
						minenum--;
			}
			if(event.MouseMove.X>=14 && event.MouseMove.X<=115 && event.MouseMove.Y>=410 && event.MouseMove.Y<=430)
				mainmenu.SetColor(Color(255,255,0));
			else
				mainmenu.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=336 && event.MouseMove.X<=370 && event.MouseMove.Y>=410 && event.MouseMove.Y<=430)
				exit.SetColor(Color(255,255,0));
			else
				exit.SetColor(Color(255,255,255));
			if(event.MouseMove.X>=190 && event.MouseMove.X<=240 && event.MouseMove.Y>=410 && event.MouseMove.Y<=430)
				play.SetColor(Color(255,255,0));
			else
				play.SetColor(Color(255,255,255));
		}
		custommenu.Clear();
		custommenu.Draw(mainmenu);
		custommenu.Draw(exit);
		custommenu.Draw(title);
		custommenu.Draw(smenupic);
		custommenu.Draw(width);
		custommenu.Draw(height);
		custommenu.Draw(mine);
		custommenu.Draw(Nwidth);
		custommenu.Draw(Nheight);
		custommenu.Draw(Nmine);
		custommenu.Draw(play);
		for(int i=0;i<3;i++)
		{
			custommenu.Draw(sup[i]);
			custommenu.Draw(sdown[i]);
		}
		Nwidth.SetText(Updater(widthnum));
		Nheight.SetText(Updater(heightnum));
		Nmine.SetText(Updater(minenum));
		custommenu.Display();
	}
return;
}