//function to initialise snake_board array for display
void init_snake(char num[][4])
{
	int i,j,k;
	for(i=0;i<100;i++)
		strcpy(num[i],"   ");
	strcpy(num[99],"100");
	for(i=99;i>=1;i--)
		{
		k=3;j=i;
		num[i-1][k--]='\0';
		do
		{
		num[i-1][k--]=j%10+48;
		j/=10;
		}while(j);
		}
}

//Function for display of opening page
void intro_snake(char name[][30],char *a)
{
	settextstyle(4,HORIZ_DIR,8);
	delay(600);
	setcolor(10);
	outtextxy(20,20,"SNAKE");
	setcolor(11);
	delay(600);
	outtextxy(196,100,"AND");
	delay(600);
	setcolor(5);
	outtextxy(275,180,"LADDER");
	strcpy(name[0],a);
	gotoxy(19,20);
	cout<<"Player 2: ";cin>>name[1];
	gotoxy(19,25);
	cout<<"LOADING....";
	delay(1000);
	cleardevice();
	settextstyle(4,HORIZ_DIR,7);
	outtextxy(50,20,"INSTRUCTIONS");
	gotoxy(1,10);
	cout<<"1.GREEN LINE REPRESENT SNAKES\n\n\n2.PINK LINE REPRESENT LADDER";
	cout<<"\n\n\n3.NUMBER ON WHICH PLAYER 1 STANDS IS IN GREEN";
	cout<<"\n\n\n4.NUMBER ON WHICH PLAYER 2 STANDS IS IN PINK";
	cout<<"\n\n\n5.IF BOTH PLAYERS STAND ON SAME NUMBER THE NUMBER IS IN YELLOW";
	cout<<"\n\n\n6.PRESS ESC TO QUIT THE GAME";
	getch();
	cleardevice();
}

//Function to draw snake and ladder board
void board_snake(char num[][4],char s[][4])
{
	int x,i,j,k;
	//smake and ladder no.s
	for(i=10,x=1;i>=1;i--,x++)
		{
		if(i%2==0)
			j=i*10;
		else j=(i-1)*10+1;
		for(int k=1;k<=10;k++)
			{
			setcolor(15);
			if(!strcmp(s[0],s[1])&&strcmp(s[0],"   "))
				setcolor(14);
			else
			{
			if(!strcmp(num[j-1],s[0]))
				setcolor(3);
			if(!strcmp(num[j-1],s[1]))
				setcolor(12);
			}
			outtextxy(40*k,40*x,num[j-1]);
			if(i%2==0)
				j--;
			else
				j++;
			}
		}

	// snake and ladder board grids
	setcolor(9);
	for(i=0;i<=10;i++)
	{
	line(30+40*i,20,i*40+30,420);
	line(30,40*i+20,430,40*i+20);
	}

	//snake lines
	setcolor(10);
	line(380,52,255,250);
	line(86,318,130,168);
	line(250,90,200,200);
	line(90,40,220,280);
	line(300,280,370,370);

	//ladder lines
	setcolor(5);
	line(260,400,140,330);
	line(370,280,290,170);
	line(380,120,330,50);
	line(130,120,50,240);
	line(170,280,250,200);
}

//function to update the score of each player
int update_snake(char name[][30],int k)
	{
	static int score[2]={0,0};
	int d=random(6000)%6+1;
	gotoxy(57,3);
	cout<<name[k]<<" ROLLED "<<d;
	score[k]+=d;
	if(score[k]==100)
		return 0;
	else if(score[k]>100)
		score[k]-=d;
	switch(score[k])
		{

		//ladder check
		case 37:score[k]=55;break;
		case 72:score[k]=93;break;
		case 32:score[k]=67;break;
		case 41:score[k]=78;break;
		case 6:score[k]=23;break;

		//snake check
		case 92:score[k]=46;break;
		case 63:score[k]=22;break;
		case 86:score[k]=56;break;
		case 99:score[k]=36;break;
		case 34:score[k]=12;break;
		}
	return score[k];
	}

//Function to play the game
int snake_ladder(char *b)
{
	int i,j,k=-1;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	char name[2][30], num[100][4],s[2][4]={"   ","   "};
	init_snake(num);
	intro_snake(name,b);
	strupr(name[0]);
	strupr(name[1]);
	clrscr();
	closegraph();
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	board_snake(num,s);
	char a=getche();
	do
	{

		if(a==27)
			return 0;
		k++;
		if(k==2)
			k=0;
		int l=2;
		j=update_snake(name,k);
		if(!j)
			break;
		do
		{
			s[k][l--]=j%10+48;
			j/=10;
		}
		while(j);
		board_snake(num,s);
		a=getche();
		cleardevice();
	}
	while(1);
	closegraph();
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	//winner anouncement
	settextstyle(7,HORIZ_DIR,7);
	outtextxy(150,150,name[k]);
	outtextxy(200,230,"WINS!!!");
	getch();
	if(k==0)
		return 100;
	return 0;
}