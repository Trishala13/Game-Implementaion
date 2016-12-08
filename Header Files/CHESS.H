//structure for chess board

struct  board_chess
{
	int i;
	char type[3];
}c,coin[8][8]={0,"\0"},r={0,"\0"};

char name[2][20];

//Function to check valid move for bush
int bush(int i, int j,int d,int e)
{
	if(abs(d)!=abs(e))
		return 0;
	int m,n,o;
	if(d>0)
		{
		m=i+1;
		n=d+i;
		o=j;
		}
	else
		{
		m=d+i+1;
		n=i;
		o=e+j;
		}
	for(;m<n;m++)
	{
		if(d>0&&e>0||d<0&&e<0)
			o++;
		else
			o--;
		if(coin[m][o].i!=0)
			return 0;
	}
	return 1;
}

//Function to check valid move for rook
int rook(int i,int j,int d,int e)
{
	if(d!=0&&e!=0)
		return 0;
	int m,n;
	if(d==0)
	{
		if(e>0)
			{
			m=j+1;
			n=e+j-1;
			}
		else
			{
			m=e+j;
			n=j;
			}
		for(;m<n;m++)
			if(coin[i][m].i!=0)
				return 0;
	}
	else
	{
		if(d>0)
			{
			m=i+1;
			n=d+i;
			}
		else
			{
			m=d+i+1;
			n=i;
			}
		for(;m<n;m++)
			if(coin[m][j].i!=0)
				return 0;
	}
	return 1;
}

//Function to check valid move for pawn
int pawn(int d,int e,int i,int j)
{
	int n=0;
	if(coin[d][e].i!=0)
	{
		if(abs(d-i)==1&&abs(e-j)==1)
			n=1;
	}
	else if(abs(e-j)==0&&abs(d-i)==1)
	n=1;
return n;
}

//Function to check the position(x,y) clicked
void check_chess(int x,int y,int &i,int &j)
{
for(i=0;i<8;i++)
	for(j=0;j<8;j++)
		if(x>31+50*j&&x<31+50*(j+1)&&y>28+50*i&&y<28+50*(i+1))
			return;
}

//Function to initialise chess board
void initialise_chess()
{
ifstream f1("CHESS_BOARD.dat",ios::binary);
for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
		f1.read((char*)&coin[i][j],sizeof(board_chess));
f1.close();
}

//Function to check if any player has won
int check_chess()
{
	int i,j,n=0,row,col;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(strcmp(coin[i][j].type,"K ")==0)
			{
				n++;
				row=i;
				col=j;
			}
	if(n==1)
	{
	cout<<name[coin[row][col].i-1]<<" is the winner";
	getch();
	return coin[row][col].i;
	}
	return 0;
}

//Function to draw chess board
void board_chess()
{
int poly[8],i=0,j=7,l;
for(i=0;i<8;i++)
	for(j=0;j<8;j++)
		{
		if(i%2==j%2)
			l=0;
		else
			l=15;
		setcolor(l);
		rectangle(31+50*j,28+50*i,31+50*(j+1),28+50*(i+1));
		setfillstyle(1,l);
		floodfill(33+50*j,30+50*i,l);
		if(coin[i][j].i==1)
			setcolor(2);
		else if(coin[i][j].i==2)
			setcolor(4);
		outtextxy(50*(j+1),50*(i+1),coin[i][j].type);
		}
setcolor(1);
rectangle(31,28,31+50*j,28+50*i);

}

//Function to play Chess
int chess(char user[])
{
	clrscr();
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	initialise_chess();
	int i,j,k=1,d,e,x,y,choice=0;
	settextstyle(4,HORIZ_DIR,8);
	outtextxy(180,150,"CHESS");
	gotoxy(28,20);
	strcpy(name[0],user);
	gotoxy(28,22);
	cout<<"PLAYER 2:";
	gets(name[1]);
	gotoxy(28,24);
	cout<<"LOADING......";
	delay(3500);
	closegraph();
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	do
	{
		board_chess();
		gotoxy(58,3);
		cout<<"Player "<<k<<" : ";
		board_chess();
		detect_mouse();
		showmouse();
		detect(x,y);
		int n=0;
		check_chess(x,y,i,j);
		gotoxy(69,3);
		label:
		detect(x,y);
		check_chess(x,y,d,e);
		if(d==i&&e==j)
			goto label;
		if(coin[i][j].i!=k)
			continue;
		if(coin[d][e].i==k||i==8)
			{
			cout<<"INVALID MOVE";
			break;
			}
		else
		{
			switch(coin[i][j].type[0])
			{
			case 'B':n=bush(i,j,d-i,e-j);
				break;
			case 'R':n=rook(i,j,d-i,e-j);
				break;
			case 'Q':n=bush(i,j,d-i,e-j);
				if(n==0)
					n=rook(i,j,d-i,e-j);
				break;
			case 'K':int k=abs(d-i),l=abs(e-j);
				if(k==1&&l<2||l==1&&k<2)
					n=1;
				break;
			case 'H':k=abs(d-i),l=abs(e-j);
				 if(k==2&&l==1||k==1&&l==2)
				 n=1;
				 break;
			case 'P':
				 n=pawn(d,e,i,j);
				 break;
			}
			if(n==0)
			{
				cout<<"INVALID MOVE";
				continue;
			}
			if(coin[d][e].i==0)
			{
				c=coin[i][j];
				coin[i][j]=coin[d][e];
				coin[d][e]=c;
			}
			else
			{
				coin[d][e]=coin[i][j];
				coin[i][j]=r;
			}
		}
		k++;
		if(k==3)
			k=1;
		clrscr();
		cleardevice();
		choice=check_chess();
	}while(choice==0 &&!kbhit());
	if(choice==1)
		return 100;
	else
		return 0;
}


