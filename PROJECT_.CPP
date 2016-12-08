#include<process.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip.h>
#include<dos.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<graphics.h>
#include<math.h>
#include"mouse.h"
#include"chess.h"
#include"pacman.h"
#include"hangman.h"
#include"snake_ladder.h"
#include"mine.h"

int no_of_users;

//for drawing borders
void border(int ul)
{
	setcolor(9);
	for(int i=0;i<=ul;i++)
		rectangle(10+i*25,10+i*25,620-i*25,460-i*25);
	setfillstyle(SOLID_FILL,9);
	floodfill(12,12,9);
}

//struct for dob
struct date_of_birth
{
	int dd,mm,yy;
};

//Personal details
class per_details
{
	protected:
	date_of_birth dob;
	char name[50],country[30];

	public:
	per_details()
	{
		dob.dd=0;
		dob.mm=0;
		dob.yy=0;
		strcpy(name,"\0");
		strcpy(country,"\0");
	}
};
//Security details
class security_details
{
	protected:
	char username[30],pass[30],ques[100],ans[30];

	public:
	security_details()
	{
	strcpy(username,"\0");
	strcpy(pass,"\0");
	strcpy(ques,"\0");
	strcpy(ans,"\0");
	}
};
//Scorecard
class scorecard
{
	protected:
	int chess,snake,hangman,minesweeper,pacman;
	public:
	scorecard()
	{
	chess=snake=minesweeper=hangman=pacman=0;
	}
};

class account:per_details,security_details,scorecard
{
	int accno;
	public:
	account()
	{
	accno=0;
	}
	void read();
	void display(char *);
	int chk_fields();
	void modify(int,int =0);
	void delete_acc();
	int ret_accno()
	{
		return accno;
	}
	char* ret_ques()
	{
		return ques;
	}
	char* ret_ans()
	{
		return ans;
	}
	char* ret_username()
	{
		return username;
	}
	char* ret_pass()
	{
		return pass;
	}
	void pts_update(char,int);
	void view_pts();
};

//display for view account
void account::display(char *comment)
{
	account b=*this;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	detect_mouse();
	showmouse();
	setcolor(9);
	border(1);
	setcolor(8);
	setfillstyle(SOLID_FILL,8);
	for(int i=0;i<7;i++)
	{
		gotoxy(38,5+3*i);
		cout<<":";
		if(i!=1)
			rectangle(310,61+i*48,550,83+i*48);
	}
	rectangle(310,109,360,131);
	rectangle(370,109,410,131);
	rectangle(420,109,490,131);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	rectangle(310,380,400,405);
	outtextxy(343,380,"OK");
	rectangle(410,380,510,405);
	outtextxy(430,380,"CANCEL");
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(230,61,"Name ");
	gotoxy(41,5);
	cout<<name;
	gotoxy(42,8);
	outtextxy(155,106,"Date Of Birth ");
	if(dob.dd)
		cout<<dob.dd;
	gotoxy(49,8);
	if(dob.mm)
		cout<<dob.mm;
	gotoxy(56,8);
	if(dob.yy)
		cout<<dob.yy;
	outtextxy(210,153,"Country ");
	gotoxy(41,11);
	cout<<country;
	outtextxy(200,201,"Username ");
	gotoxy(41,14);
	cout<<username;
	outtextxy(200,249,"Password ");
	gotoxy(41,17);
	cout<<pass;
	outtextxy(140,298,"Secret Question ");
	gotoxy(41,20);
	cout<<ques;
	outtextxy(220,347,"Answer ");
	gotoxy(41,23);
	cout<<ans;
	outtextxy(60,380,comment);
	do
	{
		int x,y,i=0;
		detect(x,y);
		if(y>380&&y<405)
		{
			if(x>310&&x<400)
				return;
			else if(x>410&&x<510)
			{
				*this=b;
				void sign(account &);
				cleardevice();
				sign(*this);
			}
		}
		else if(x>310 && x<550)
			for(i=0;i<7;i++)
				if(y>61+i*48 && y<83+i*48)
					modify(i+1,x);
	}while(1);
}

//Read account details
void account::read()
{
	accno=no_of_users+1;
	display("DATE FORMAT: dd-mm-yy");
	no_of_users++;
	hide_mouse();
	cleardevice();
}

//Modify Account
void account::modify(int i,int x)
{
	gotoxy(41,3*i+2);
	if(i!=2)
	for(int j=0;j<29;j++)
		cout<<" ";
	gotoxy(41,3*i+2);
	switch(i)
	{
		case 1: gets(name);
			break;
		case 2: if(x>=310 && x<=360)
				{
				gotoxy(42,8);
				cin>>dob.dd;
				}
			else if(x>=370 && x<=410)
				{
				gotoxy(49,8);
				cin>>dob.mm;
				}
			else if(x>=420 && x<=490)
				{
				gotoxy(56,8);
				cin>>dob.yy;
				}
			break;
		case 3: gets(country);
			break;
		case 4: gets(username);
			break;
		case 5: int i=0;
			char ch;
			do
			{
			ch=getche();
			pass[i++]=ch;
			if(ch==8 && i>0)
			{
				i--;
				cout<<" \b";
			}
			else if(ch==13)
				{
				pass[i]='\0';
				break;
				}
			else
				cout<<"\b*";
			}while(i<30);
			break;
		case 6: gets(ques);
			break;
		case 7:gets(ans);
			break;
	}
}

int size=sizeof(account);

//Update Points for each game for user account
void account::pts_update(char ch,int pts)
{
	switch(ch)
	{
	case 'S':snake+=pts;
		 break;
	case 'M':minesweeper+=pts;
		 break;
	case 'H':hangman+=pts;
		 break;
	case 'P':pacman+=pts;
		 break;
	case 'C':chess+=pts;
		 break;
	}
	fstream f("Account.dat",ios::binary|ios::in|ios::out);
	account a;
	while(f.read((char*)&a,size))
		if(strcmp(a.ret_username(),username)==0)
			{
			f.seekp(-size,ios::cur);
			f.write((char*)this,size);
			break;
			}
	f.close();
}

//Check if all fields are filled
int account::chk_fields()
{
account b;
if(strcmp(username,b.username)==0)
	return 0;
if(strcmp(pass,b.pass)==0)
	return 0;
if(strcmp(country,b.country)==0)
	return 0;
if(strcmp(name,b.name)==0)
	return 0;
if(strcmp(ques,b.ques)==0)
	return 0;
if(strcmp(ans,b.ans)==0)
	return 0;
if(dob.dd==0||dob.yy==0||dob.mm==0)
	return 0;
return 1;
}

//Assigning no.of users
void assign_no_of_users()
{
	ifstream f("Account.dat",ios::binary);
	account a;
	if(f.read((char*)&a,size)==0)
		no_of_users=0;
	else
		{
		f.seekg(-size,ios::end);
		f.read((char*)&a,size);
		no_of_users=a.ret_accno();
		}
	f.close();
}

//Function for Sign-up
void sign_up(account &a)
{
	cleardevice();
	ifstream f("Account.dat",ios::binary);
	account b;
	a.read();
	int n=a.chk_fields();
	gotoxy(10,27);
	if(n==0)
		a.display("ALL FIELDS SHOULD BE FILLED");
	while(f.read((char*)&b,size))
	{
		if(strcmp(a.ret_username(),b.ret_username())==0)
			{
			a.display("USERNAME ALREADY EXITS");
			f.seekg(0);
			}
	}
	ofstream f1("Account.dat",ios::binary|ios::app);
	f1.write((char*)&a,size);
	cleardevice();
	f1.close();
	f.close();

}

//Function to check secret answer
void chk_sec_ans(account &user)
{
	int gd,gm=DETECT;
	initgraph(&gm,&gd,"c:\\tc\\bgi");
	char ans[30]="\0",usrname[30];
	border(2);
	setcolor(11);
	rectangle(280,58+3*48,520,86+3*48);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	outtextxy(150,201,"Username: ");
	gotoxy(41,14);
	gets(usrname);
	cleardevice();
	border(2);
	setcolor(11);
	account a;
	ifstream f("Account.dat",ios::binary);
	while(f.read((char*)&a,size))
		if(strcmp(a.ret_username(),usrname)==0)
			{
			user=a;
			break;
			}
	void sign(account &);
	if(f.eof())
		{
		gotoxy(41,17);
		cout<<"Username doesn't exist";
		delay(1000);
		sign(user);
		}
	for(int i=2;i<4;i++)
		rectangle(280,58+i*48,520,86+i*48);
	outtextxy(115,153,"Secret Question :");
	gotoxy(41,11);
	cout<<user.ret_ques();
	outtextxy(150,201,"Answer :");
	gotoxy(41,14);
	gets(ans);
	if(strcmp(ans,user.ret_ans())!=0)
		sign(user);
}

//Function for Sign-in
void sign_in(account &user)
{
	closegraph();
	int gd,gm=DETECT;
	initgraph(&gm,&gd,"c:\\tc\\bgi");
	char usrname[30]="\0",pass[30]="\0";
	border(2);
	int x=0,y=0;
	setcolor(11);
	detect_mouse();
	showmouse();
	for(int i=2;i<6;i++)
		{
		if(i==4)
			continue;
		rectangle(280,58+i*48,520,86+i*48);
		}
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	gotoxy(41,20);
	cout<<"FORGOT YOUR PASSWORD?";
	outtextxy(150,153,"Username :");
	outtextxy(150,201,"Password :");
	rectangle(280,250,370,278);
	outtextxy(313,250,"OK");
	rectangle(380,250,490,278);
	outtextxy(402,250,"CANCEL");
	void sign(account &);
	do
	{
	detect(x,y);
	if(x>280 && x<520)
		if(y>58+2*48 && y<86+2*48)
			{
			gotoxy(38,11);
			for(int i=0;i<28;i++)
				cout<<" ";
			gotoxy(38,11);
			gets(usrname);
			}
		else if(y>58+3*48 && y<86+3*48)
			{
			gotoxy(38,14);
			for(int i=0;i<28;i++)
				cout<<" ";
			i=0;
			gotoxy(38,14);
			char ch;
			do
			{
			ch=getche();
			pass[i++]=ch;
			if(ch==8 && i>0)
			{
				i--;
				cout<<" \b";
				if(i==0)
					pass[0]='\0';
			}
			else if(ch==13)
				{
				pass[i]='\0';
				break;
				}
			else
				cout<<"\b*";
			}while(i<30);
			}
		else if(y>58+5*48 && y<86+5*48)
			chk_sec_ans(user);
	if(y>=250&&y<=278)
	{
		if(x>=280&&x<=370)
			break;
		else if(x>=380 && x<=490)
			{
			cleardevice();
			sign(user);
			}
	}
	}while(1);
	account a;
	ifstream f("Account.dat",ios::binary);
	while(f.read((char*)&a,size))
		if(strcmp(a.ret_username(),usrname)==0)
			if(strcmp(a.ret_pass(),pass)==0)
				{
				user=a;
				return;
				}
	gotoxy(41,23);
	cout<<"Wrong Username or Password";
	delay(500);
	cleardevice();
	sign(user);
}

//Function for Deletion of Account
void account::delete_acc()
{
	char password[30];
	cleardevice();
	account b;
	sign_in(b);
	if(strcmp(b.pass,pass)==0)
	{
	account b;
	ifstream f("Account.dat",ios::binary);
	ofstream f1("Temp.dat",ios::binary);
	while(f.read((char*)&b,size))
		if(strcmp(username,b.ret_username())!=0)
			f1.write((char*)&b,size);
	f.close();
	f1.close();
	f1.open("Account.dat",ios::binary);
	f.open("Temp.dat",ios::binary);
	while(f.read((char*)&b,size))
		f1.write((char*)&b,size);
	f.close();
	f1.close();
	remove("Temp.dat");
	}
	else
		{
		cout<<"Wrong Password";
		getch();
		return;
		}
}

//Function for Modifying an account
void modify(account &user)
{
	fstream f("Account.dat",ios::binary|ios::in|ios::out);
	account a;
	cleardevice();
	while(f.read((char*)&a,size))
		if(strcmp(a.ret_username(),user.ret_username())==0)
			{
			user.display("\0");
			f.seekp(-size,ios::cur);
			f.write((char*)&a,size);
			break;
			}
}

//Display for Sign-in and Sign-up page
void sign(account &user)
{
	cleardevice();
	border(2);
	setcolor(8);
	rectangle(80,190,282,270);
	rectangle(345,190,547,270);
	setfillstyle(SOLID_FILL,8);
	floodfill(90,200,8);
	floodfill(350,200,8);
	setcolor(7);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);
	outtextxy(180,220,"Sign In");
	outtextxy(450,220,"Sign Up");
	detect_mouse();
	showmouse();
	int x,y;
	detect(x,y);
	if(y>190&&y<270)
	{
		if(x>80&&x<282)
			sign_in(user);
		else if(x>345&&x<547)
			sign_up(user);
	}
}

//Display for open page
void open_page(account &user)
{
	int gdrive=DETECT,gmode;
	initgraph(&gdrive,&gmode,"c:\\tc\\bgi");
	border(2);
	setcolor(11);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 8);
	outtextxy(325, 105," Welcome to ");
	delay(500);
	settextstyle(GOTHIC_FONT,HORIZ_DIR,7);
	outtextxy(325,200,"GameArcade.com");
	delay(500);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(325,300,"PLAY PACMAN,MINESWEEPER,CHESS ONLINE");
	delay(500);
	outtextxy(325,330," AND LOTS MORE FOR FREE !!!! ");
	getch();
	delay(2500);
	cleardevice();
	sign(user);
}

//Function to choose game
char gamechoice()
{
	border(1);
	setcolor(11);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);
	rectangle(55,70,280,145);
	outtextxy(170,95,"Chess");
	rectangle(305,70,585,145);
	outtextxy(445,95,"Minesweeper");
	rectangle(305,320,585,395);
	outtextxy(452,345,"Hangman");
	rectangle(55,320,280,395);
	outtextxy(170,345,"Pacman");
	rectangle(110,200,525,275);
	outtextxy(320,225,"Snake & Ladder");
	detect_mouse();
	showmouse();
	int x,y;
	detect(x,y);
	char ch='\0';
	do
	{
	if(x>=110 && x<=525 && y>=200 && y<=275)
		ch='S';
	else if(x>=55 && x<=280)
		{
		if(y>=70 && y<=145)
			ch='C';
		else if(y>=320 && y<=395)
			ch='P';
		}
	else if(x>=305 && x<=585)
		{
		if(y>=70 && y<=145)
			ch='M';
		else if(y>=320 && y<=395)
			ch='H';
		}
	detect(x,y);
	}while(ch=='\0');
	cleardevice();
	return ch;
}

//Function to view the points of each game
void account::view_pts()
{
		int gd=DETECT,gm;
		initgraph(&gd,&gm,"c:\\tc\\bgi");
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,8);
		outtextxy(100,30,"VIEW SCORE");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(4);
		outtextxy(125,160,"Y");
		outtextxy(125,200,"H");
		outtextxy(125,240,"S");
		outtextxy(125,280,"C");
		outtextxy(125,320,"M");
		outtextxy(125,360,"P");
		setcolor(15);
		outtextxy(142,160,"OUR SCORE");
		outtextxy(142,200,"ANGMAN OVERALL HIGHSCORES");
		outtextxy(142,240,"NAKE AND LADDER HIGHSCORES");
		outtextxy(142,280,"HESS OVERALL HIGHSCORES");
		outtextxy(142,320,"INESWEEPER OVERALL HIGHSCORES");
		outtextxy(142,360,"ACMAN OVERALL HIGHSORES");
		char choice=getche();
		choice=toupper(choice);
		if(choice=='Y')
		{
		cleardevice();
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,8);
		outtextxy(100,30,"SCORECARD");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(15);
		outtextxy(142,150,"HANGMAN ");
		gotoxy(50,11);
		cout<<": "<<hangman;
		outtextxy(142,250,"SNAKE AND LADDER ");
		gotoxy(50,17);
		cout<<": "<<snake;
		outtextxy(142,200,"CHESS ");
		gotoxy(50,14);
		cout<<": "<<chess;
		outtextxy(142,300,"MINESWEEPER ");
		gotoxy(50,20);
		cout<<": "<<minesweeper;
		outtextxy(142,350,"PACMAN ");
		gotoxy(50,23);
		cout<<": "<<pacman;
		getch();
		return;
		}
		fstream f("account.dat",ios::binary|ios::in|ios::out);
		f.seekp(0,ios::end);
		int n=f.tellp()/size,i=0;
		account *users=new account [n],b;
		f.seekg(0,ios::beg);
		while(f.read((char*)&b,size))
			users[i++]=b;
		if(choice=='H')
		{
		for(i=0;i<n;i++)
			for(int j=0;j<n-i-1;j++)
				if(users[j].hangman<=users[j+1].hangman)
					{
					b=users[j];
					users[j]=users[j+1];
					users[j+1]=b;
					}
		cleardevice();
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,4);
		outtextxy(80,60,"HANGMAN OVERALL HIGHSCORES");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(15);
		for(i=0;i<5 && i<n;i++)
			{
			outtextxy(142,150+i*50,users[i].username);
			gotoxy(50,3*i+11);
			cout<<users[i].hangman<<" pts";
			}
		}
		else if(choice=='P')
		{
		for(i=0;i<n;i++)
			for(int j=0;j<n-i-1;j++)
				if(users[j].pacman<=users[j+1].pacman)
					{
					b=users[j];
					users[j]=users[j+1];
					users[j+1]=b;
					}
		cleardevice();
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,4);
		outtextxy(80,60,"PACMAN OVERALL HIGHSCORES");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(15);
		for(i=0;i<5 && i<n;i++)
			{
			outtextxy(142,150+i*50,users[i].username);
			gotoxy(50,3*i+11);
			cout<<users[i].pacman<<" pts";
			}
		}
		if(choice=='C')
		{
		for(i=0;i<n;i++)
			for(int j=0;j<n-i-1;j++)
				if(users[j].chess<=users[j+1].chess)
					{
					b=users[j];
					users[j]=users[j+1];
					users[j+1]=b;
					}
		cleardevice();
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,4);
		outtextxy(85,30,"CHESS OVERALL HIGHSCORES");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(15);
		for(i=0;i<5 && i<n;i++)
			{
			outtextxy(142,150+i*50,users[i].username);
			gotoxy(50,3*i+11);
			cout<<users[i].hangman<<" pts";
			}
		}
		if(choice=='M')
		{
		for(i=0;i<n;i++)
			for(int j=0;j<n-i-1;j++)
				if(users[j].minesweeper<=users[j+1].minesweeper)
					{
					b=users[j];
					users[j]=users[j+1];
					users[j+1]=b;
					}
		cleardevice();
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,4);
		outtextxy(50,30,"MINESWEEPER OVERALL HIGHSCORE");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(15);
		for(i=0;i<5 && i<n;i++)
			{
			outtextxy(142,150+i*50,users[i].username);
			gotoxy(50,3*i+11);
			cout<<users[i].minesweeper<<" pts";
			}
		}
		if(choice=='S')
		{
		for(i=0;i<n;i++)
			for(int j=0;j<n-i-1;j++)
				if(users[j].snake<=users[j+1].snake)
					{
					b=users[j];
					users[j]=users[j+1];
					users[j+1]=b;
					}
		cleardevice();
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,3);
		outtextxy(80,70,"SNAKE AND LADDER OVERALL HIGHSCORES");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(15);
		for(i=0;i<5 && i<n;i++)
			{
			outtextxy(142,150+i*50,users[i].username);
			gotoxy(50,3*i+11);
			cout<<users[i].snake<<" pts";
			}
		}
		f.close();
		delete []users;
		getch();
}

//Main() function
void main()
{
	clrscr();
	assign_no_of_users();
	account user;
	open_page(user);
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	char choice='\0',ch;
	while(choice!='E'&& user.ret_accno()!=0)
	{
		cleardevice();
		setcolor(15);
		border(1);
		settextstyle(1,HORIZ_DIR,8);
		outtextxy(100,30,"MAIN MENU");
		settextstyle(1,HORIZ_DIR,3);
		setcolor(4);
		outtextxy(125,160,"P");
		outtextxy(125,200,"V");
		outtextxy(125,240,"S");
		outtextxy(125,280,"D");
		outtextxy(125,320,"M");
		outtextxy(125,360,"E");
		setcolor(15);
		outtextxy(142,160,"LAY GAMES");
		outtextxy(142,360,"XIT");
		outtextxy(142,240,"IGN OUT");
		outtextxy(142,200,"IEW SCORECARD");
		outtextxy(142,280,"ELETE YOUR ACCOUNT");
		outtextxy(142,320,"ODIFY YOUR ACCOUNT");
		choice=getche();
		choice=toupper(choice);
		cleardevice();
		if(choice=='M')
			modify(user);
		else if(choice=='V')
			user.view_pts();
		else if(choice=='D')
		{
			user.delete_acc();
			user=account ();
			sign(user);
		}
		else if(choice=='S')
			sign(user);
		else if(choice=='P')
		{
			cleardevice();
				ch=gamechoice();
			char player[30];
			strcpy(player,user.ret_username());
			int pts=0;
			switch(ch)
			{
			case 'S':pts=snake_ladder(player);
				 break;
			case 'M':pts=mine();
				 break;
			case 'H':pts=hangman(player);
				 break;
			case 'P':pts=pacman(player);
				 break;
			case 'C':pts=chess(player);
				 break;
			}
		user.pts_update(ch,pts);
		}
	}
	closegraph();
}