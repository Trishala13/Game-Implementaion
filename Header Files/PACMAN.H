//Structure for board
struct path_pac
{
int coin;
char bk1,bk2;
}board_pac[13][13]={0,'\0','\0'};

//Structure for position of pacman and demons
struct pos_pac
{
int posx,posy,life;
}pac={8,6,3},demon[4]={{4,5,0},{4,7,0},{6,5,0},{6,7,0}};

//Function to initialise the Pacman board
void init_board_pac()
{
ifstream f("PACMAN_BOARD.dat",ios::binary);
int size=sizeof(path_pac);
for(int i=0;i<13;i++)
	for(int j=0;j<13;j++)
		f.read((char*)&board_pac[i][j],size);
}

//Function to draw the Pacman and demons at position(x,y)
void draw_creature_pac(int x,int y,int color)
{

	setcolor(color);
	setfillstyle(1,color);
	int n=50+28*x+14,k=50+28*y+14;
	circle(k,n,7);
	floodfill(k,n,color);
	setcolor(15);
	circle(k-3,n-3,2);
	circle(k+3,n-3,2);
	setfillstyle(1,15);
	floodfill(k-3,n-3,15);
	floodfill(k+3,n-3,15);
	setcolor(0);
	circle(k-3,n-3,2);
	circle(k+3,n-3,2);
	setcolor(0);
	line(k-3,n+3,k+3,n+3);
}

//Function to draw lines for obstructions and * for food
void draw_board_pac()
{
cleardevice();
setcolor(15);
rectangle(50,50,50+28*13,50+28*13);
for(int i=0;i<13;i++)
	for(int j=0;j<13;j++)
	{
	int x[2];
	x[0]=board_pac[i][j].bk1;
	x[1]=board_pac[i][j].bk2;
	setcolor(15);
	for(int k=0;k<2;k++)
	switch(x[k])
	{
	case 'A':line(50+28*j,50+28*i,50+28*j,50+28*(i+1));
		break;
	case 'S':line(50+28*j,50+28*(i+1),50+28*(j+1),50+28*(i+1));
		break;
	case 'W':line(50+28*j,50+28*i,50+28*(j+1),50+28*i);
		break;
	case 'D':line(50+28*(j+1),50+28*i,50+28*(j+1),50+28*(i+1));
		break;
	}

	setcolor(9);
	if(board_pac[i][j].coin==1)
		outtextxy(50+28*j+10,50+28*i+10,"*");
	}
	draw_creature_pac(pac.posx,pac.posy,14);
	setcolor(15);
	outtextxy(50+28*14-10,50+28*4-15,"LIVES REMAINING: ");
	switch(pac.life)
	{
		case 3:draw_creature_pac(4,14,14);
		case 2:draw_creature_pac(4,15,14);
		case 1:draw_creature_pac(4,16,14);
	}
	for(i=0;i<4;i++)
		draw_creature_pac(demon[i].posx,demon[i].posy,3+i);
}

//Function to check whether the pacman lost a life after every move
void chk_life_pac()
{
     for(int i=0;i<4;i++)
		if(demon[i].posx==pac.posx && demon[i].posy==pac.posy)
			{
			pac.life--;
			setcolor(15);
			outtextxy(50+28*14-10,50+28*7-10,"LOST A LIFE..");
			pac.posx=8;
			pac.posy=6;
			getch();
			}
}

//Function to check if the game is over
int check_pac(int pts,char *name)
{
	if(pts==164)
		{
		cleardevice();
		settextstyle(4,HORIZ_DIR,8);
		setcolor(5);
		outtextxy(100,35,name);
		outtextxy(240,175,"WINS");
		getch();
		cleardevice();
		return 1;
		}
	else if(!pac.life)
		{
		cleardevice();
		settextstyle(4,HORIZ_DIR,8);
		setcolor(5);
		outtextxy(100,35,name);
		outtextxy(240,175,"LOSES");
		getch();
		cleardevice();
		return 0;
		}
	return -1;
}

//Function to check if pacman or demon can move left
int move_a(int i,int x,int y,char bk1,char bk2)
{

	if(bk1=='A'|| bk2=='A'||demon[i].posy==0)
		return 0;
	for(int j=0;j<4;j++)
		if(demon[j].posy==y-1&&demon[j].posx==x)
				return 0;
	demon[i].posy--;
	return 1;

}

//Function to check if pacman or demon can move down
int move_s(int i,int x,int y,char bk1,char bk2)
{

if(bk1=='S'||bk2=='S'||demon[i].posx==12)
		return 0;
	for(int j=0;j<4;j++)
		if(demon[j].posx==x+1&&demon[j].posy==y)
				return 0;
	demon[i].posx++;
	return 1;
}

//Function to check if pacman or demon can move right
int move_d(int i,int x,int y,char bk1,char bk2)
{
if(bk1=='D'||bk2=='D'||demon[i].posy==12)
		return 0;
	for(int j=0;j<4;j++)
		if(demon[j].posy==y+1&& demon[j].posx==x )
					return 0;
	demon[i].posy++;
	return 1;
}

//Function to check if pacman or demon can move up
int move_w(int i,int x,int y,char bk1,char bk2)
{
if(bk1=='W'||bk2=='W'||demon[i].posx==0)
		return 0;
	for(int j=0;j<4;j++)
		if(demon[j].posy==x-1&&demon[j].posy==y)
				return 0;
	demon[i].posx--;
	return 1;
}

//function to move demons
void demon_move()
{
for(int i=0;i<4;i++)
	{
	int x=demon[i].posx,y=demon[i].posy,j=0,ck[4]={0};
	char bk[3];
	bk[0]=board_pac[x][y].bk1;
	bk[1]=board_pac[x][y].bk2;
	if(x==4 && y==6)
		j=move_w(i,x,y,bk[0],bk[1]);
	while(j!=1)
		{
		label:
		int n=random(4);
		if(ck[n]==1)
			goto label;
		switch(n)
		  {
		  case 0:j=move_a(i,x,y,bk[0],bk[1]);
			 ck[0]=1;
			 break;
		  case 1:j=move_s(i,x,y,bk[0],bk[1]);
			 ck[1]=1;
			 break;
		  case 2:j=move_d(i,x,y,bk[0],bk[1]);
			 ck[2]=1;
			 break;
		  case 3:j=move_w(i,x,y,bk[0],bk[1]);
			 ck[3]=1;
			 break;
		  }
		}
	}
}
//Function to move pacman
int move_pac(int &n,char &ch,int &pts,char *name)
{
	int x,y;
	do
	{
	x=pac.posx;
	y=pac.posy;
	if(board_pac[x][y].bk1!=ch&&board_pac[x][y].bk2!=ch)
	{
	switch(ch)
		{
		case 'A':if(y!=0)
				pac.posy--;
			 break;
		case 'S':if(x!=12)
				pac.posx++;
			 break;
		case 'D':if(y!=12)
				pac.posy++;
			 break;
		case 'W':if(x!=0)
				pac.posx--;
			 break;
		}
	}
	if(board_pac[x][y].coin)
		{
		board_pac[x][y].coin=0;
		pts++;
		}
	n=check_pac(pts,name);
	if(n==1||n==0)
		return n;
	chk_life_pac();
	demon_move();
	draw_board_pac();
	chk_life_pac();
	delay(400);
	}while(!kbhit());
	ch=getche();
	ch=toupper(ch);
	if(ch==27)
		return 0;
	return -1;
}

//Function to play the game
int pacman(char *a)
{
	int n;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	char ch='S',player[30];
	setcolor(12);

	settextstyle(4,HORIZ_DIR,9);
	outtextxy(105,150,"PACMAN");

	strcpy(player,a);
	delay(1000);
	cleardevice();
	settextstyle(4,HORIZ_DIR,7);
	outtextxy(50,20,"INSTRUCTIONS");
	gotoxy(1,10);
	cout<<"1.USE 'A' TO MOVE LEFT, 'S' TO MOVE DOWN";
	cout<<"\n\n\nUSE 'D' TO MOVE RIGHT AND 'W' TO MOVE UP";
	cout<<"\n\n\n2.THREE LIVES ARE GIVEN TO GUESS THE WORD.\n";
	cout<<"\n\n3.YOU LOSE A LIFE WHEN A GHOST EATS THE PACMAN";
	cout<<"\n\n\n4.POINTS SCORED IS DETERMINED BY ";
	cout<<"THE NUMBER OF DOTS EATEN";
	cout<<"\n\n\n5.PRESS ESC TO QUIT THE GAME.";
	getch();
	cleardevice();
	closegraph();
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	init_board_pac();
	draw_board_pac();

	int pt=0;
	do
	{
	n=move_pac(n,ch,pt,player);
	}while(n!=1&&n!=0);
	return pt;
}