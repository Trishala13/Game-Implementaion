int a[26];

//function to initialise the word to be guessed
char* init_word(char *a)
{
	int i,count=0;
	ifstream f(a);
	char word[60],ch;
	while(f.getline(word,60))
		{
		count++;
		if(f.eof())
			break;
		}
	f.close();
	f.open(a);
	i=random(count);
	for(int j=0;j<=i;f.getline(word,60),j++);
	strupr(word);
	f.close();
	return word;
}

//Function to get topic and display it
void getword_hangman(char word[])
{
	randomize();
	//get topic
	int d=random(6000)%5;

	//introduce topic
	settextstyle(4,HORIZ_DIR,6);
	outtextxy(30,80,"YOUR TOPIC IS....");
	settextstyle(4,HORIZ_DIR,7);
	setcolor(10);
	delay(600);
	switch(d)
		{
		case 0: outtextxy(110,180,"SCIENTISTS");
			strcpy(word,init_word("scientist.txt"));
			break;
		case 1: outtextxy(110,180,"SINGERS");
			strcpy(word,init_word("singer.txt"));
			break;
		case 2: outtextxy(110,180,"ACTORS");
			strcpy(word,init_word("actors.txt"));
			break;
		case 3: outtextxy(110,180,"COMPUTER");
			strcpy(word,init_word("computer.txt"));
			break;
		case 4: outtextxy(110,180,"BIOLOGY");
			strcpy(word,init_word("Biology.txt"));
			break;
		}
	delay(500);
	cleardevice();
	settextstyle(4,HORIZ_DIR,7);
	outtextxy(50,20,"INSTRUCTIONS");
	gotoxy(1,10);
	cout<<"1.HANGMAN IS A TIMED GAME.\n\n\n";
	cout<<"2.SEVEN LIVES ARE GIVEN TO GUESS THE WORD.\n\n\n";
	cout<<"3.YOU LOSE A LIFE WHEN THE LETTER ENTERED IS NOT ";
	cout<<"PRESENT IN THE WORD.";
	cout<<"\n\n\n4.POINTS SCORED IS DETERMINED BY ";
	cout<<"THE ACCURACY OF GUESSING THE WORD";
	cout<<"\n\n\n5.PRESS ESC TO QUIT THE GAME.";
	getch();
}

//function to change a guessed char from lowercase to uppercase
char toup(char letter)
{
	//convert case of letter to upper case
	if(letter>='a'&&letter<='z')
		return letter-32;
	if(letter>='A'&&letter<='Z')
		return  letter;
	return '\0';
}

//function to draw hangman
void draw_hangman(int k)
{
	//draw box for hangman
	setcolor(10);
	line(1,1,300,1);
	line(1,1,1,300);
	line(1,300,300,300);
	line(300,300,300,1);

	//drawing stick figure for hangman
	setcolor(5);
	switch(k)
	{
	case 7: line(120,220,90,270);
	case 6:	line(120,220,150,270);
	case 5: line(120,105,90,155);
	case 4:	line(120,105,150,155);
	case 3: line(120,105,120,220);
	case 2: circle(120,70,35);
	case 1:	line(10,20,250,20);
		line(10,20,10,280);
		line(10,280,250,280);
		break;

	}
}

//Function to draw the board
void board_hangman(int k,char wrd[],char word[])
{
	//output screen for playing
	draw_hangman(k);
	int i,l;
	gotoxy(3,21);
	if(k<7&&strcmp(wrd,word))
	{
	cout<<"ENTER ALPHABET : ";
	gotoxy(3,23);
	for(i=0;word[i];i++)
		if(word[i]==' ')
			cout<<'\t';
		else if(wrd[i]==' ')
			cout<<"_ ";
		else
			cout<<wrd[i]<<" ";
	gotoxy(50,2);
	line(370,10,370,180);
	line(550,10,550,180);
	line(370,10,550,10);
	line(370,180,550,180);
	cout<<"LETTERS GUESSED : ";
	for(i=0,k=1,l=4;i<26;i++)
		if(a[i]==1)
			{
			if(k==1)
				gotoxy(51,l);
			else if(k==5)
				{
				l++;
				k=0;
				}
			cout<<char(i+65)<<"  ";
			k++;
			}
	}
}

//Function to check if letter is present in word
void check_hangman(char word[],char wrd[],char a,int &num)
{

	int i,n=0;
	for(i=0;word[i];i++)
		if(a==word[i])
			{
			wrd[i]=a;
			n=1;
			}
	if(!n) num++;
}

//function to check if letter is already guessed and
//update it to guessed if not guessed
int check1_hangman(char letter)
{
	gotoxy(3,25);
	if(a[letter-65]==1)
		{
		cout<<"ALREADY ENTERED";
		return 0;
		}
	a[letter-65]=1;
	return 1;

}

//function for timer
void timer(int n)
{
	int sec,millisec;
	sec=n/100;
	millisec=n%100;
	gotoxy(56,15);
	cout<<"TIMER";
	gotoxy(56,17);
	cout<<sec<<'.'<<millisec;
}
struct time T1,T2,T;

//function to play hangman
int hangman(char *name)
{
	char word[40],wrd[40],letter,player[20];
	int i=0,k=0,j,gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	long int sum=0;
	setcolor(12);
	settextstyle(4,HORIZ_DIR,8);
	outtextxy(120,170,"HANGMAN");
	gotoxy(20,20);
	delay(1000);
	clrscr();
	cleardevice();
	getword_hangman(word);
	strcpy(player,name);
	delay(2000);
	clrscr();
	closegraph();
	initgraph(&gd,&gm,"c:\\tc\\bgi");

	for(i=0;word[i];i++)
		wrd[i]=' ';
	wrd[i]='\0';
	gettime(&T);

	do
		{
		gettime(&T1);
		board_hangman(k,wrd,word);
		line(370,200,550,200);
		line(370,280,550,280);
		line(370,200,370,280);
		line(550,200,550,280);
		do
		{
		gettime(&T2);
		int n=100*(60*(T2.ti_min-T1.ti_min)+T2.ti_sec-T1.ti_sec)+(T2.ti_hund-T1.ti_hund);
		timer(n);
		}while(!kbhit());
		letter=getche();
		gettime(&T2);
		clrscr();
		cleardevice();

		if(letter==27)
			return 0;
		letter=toup(letter);
		gotoxy(3,25);
		if(letter)
			{
			if(check1_hangman(letter))
				check_hangman(word,wrd,letter,k);
			}
		else
			{
			cout<<"ENTER ALPHABETS ONLY";
			k++;
			}
		}
	while(k<7&&strcmp(word,wrd));
	gettime(&T2);
	sum=100*(60*(T2.ti_min-T.ti_min)+(T2.ti_sec-T.ti_sec))+(T2.ti_hund-T.ti_hund);
	clrscr();
	cleardevice();
	board_hangman(k,wrd,word);
	gotoxy(3,23);
	if(k<7) cout<<"CONGRATS!!!";
	else cout<<"OOPS!!...ALL THE BEST NEXT TIME...";
	cout<<"THE WORD IS "<<word;
	getch();
	clrscr();
	closegraph();
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	settextstyle(4,HORIZ_DIR,8);
	outtextxy(100,35,player);
	if(k<7)
		outtextxy(240,175,"WINS");
	else
		outtextxy(240,175,"LOSES");
	for(i=0,j=0;i<26;i++)
	if(a[i]==1) j++;
	gotoxy(20,19);
	cout<<"NUMBER OF LETTERS GUESSED: ";
	cout<<j;
	gotoxy(20,21);
	cout<<"NUMBER OF LETTERS CORRECTLY GUESSED: ";
	for(i=0,k=0;wrd[i];i++)
		if(wrd[i]>='A'&&wrd[i]<='Z')
			k++;
	cout<<k;
	gotoxy(20,23);
	cout<<"TIME ELAPSED: "<<sum/100<<'.'<<sum%100<<"sec";
	gotoxy(20,25);
	int accuracy=k*100.0/j;
	if(accuracy>100)
		accuracy=100;
	cout<<"ACCURACY = "<<setprecision(3)<<accuracy<<'%';
	getch();
	cleardevice();
	return accuracy;
}
