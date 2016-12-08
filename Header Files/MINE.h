//MOUSE CONTROL
//union REGS in,out;

int callmouse()
{
 in.x.ax=1;
 int86(51,&in,&out);
 return 1;
}
void mouseposi(int &xpos,int &ypos,int &click)
{
 in.x.ax=3;
 int86(51,&in,&out);
 click=out.x.bx;
 xpos=out.x.cx;
 ypos=out.x.dx;
}
int mousehide()
{
 in.x.ax=2;
 int86(51,&in,&out);
 return 1;
}
void setposi(int xpos,int ypos)
{
 in.x.ax=4;
 in.x.cx=xpos;
 in.x.dx=ypos;
 int86(51,&in,&out);
}

//**MINESWEEPER**

int mine()
{int score=0;
 clrscr();
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\tc\\bgi");
 cleardevice();

 void search(char [][15],int,int,char[][15]);

 char m[15][15],n[15][15],w;
 int i,j,x,y,r,q,c,cf=0,a,b,cl,l,d,e,g,h,k=0;
 char I[5];

  for(i=0;i<15;i++)
  for(j=0;j<15;j++)
   if(i==0||j==0||i==14||j==14)
   m[i][j]='1';

 for(i=1;i<=13;i++)
  for(j=1;j<=13;j++)
   m[i][j]='-';

 //SETTING MINES
 randomize();
 for(i=1;i<=15;i++)
 m[1+random(13)][1+random(13)]='*';

 for(i=1;i<=13;i++)
  for(j=1;j<=13;j++)
  {
   x=0;
   if(m[i][j]!='*')
    for(d=i-1;d<=i+1;d++)
     for(e=j-1;e<=j+1;e++)
      if(d==i&&e==j)
       continue;
      else
      if(m[d][e]=='*')
       x++;
    if(x)
    m[i][j]=x+48;
  }

 for(i=1;i<=13;i++)
  for(j=1;j<=13;j++)
   if(m[i][j]=='*')
    cf++;

 for(i=0;i<15;i++)
  for(j=0;j<15;j++)
   n[i][j]='.';

 setcolor(7);
 rectangle(4,15,212,222);
 setfillstyle(SOLID_FILL,7);
 floodfill(20,20,7);
 setcolor(8);
 for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
 {
  line(j,15,j,222);
  line(4,r,212,r);
 }

 settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
 setcolor(0);
 for(i=1,r=21;i<=13;i++,r+=16)
  for(j=1,q=10;j<=13;j++,q+=16)
  {I[0]=n[i][j];I[1]='\0';
   setcolor(7);
   outtextxy(q,r,I);}

 setcolor(0);
 for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
 {line(j,15,j,222);
  line(4,r,212,r);}
 setcolor(15);
 rectangle(4,15,212,222);

 do
 {
  fflush(stdin);
  callmouse();
  cout<<'\n';
  gotoxy(2,17);
  cout<<"No.of flags left="<<cf;
  here:
  setposi(320,150);
  cl=0;
  do
  {
    mouseposi(a,b,cl);
  }while(!cl);
  if(cl==1)
  w='d';
  else if(cl==2)
  w='f';
  cl=0;
  for(j=15,d=1;j<210;j+=16,d++)
   {for(i=4,e=1;i<200;i+=16,e++)
    if(a>=i&&a<=i+16&&b>=j&&b<=j+16)
    {x=d;y=e;cl=1;break;}
    if(cl)break;}
    if(!cl)
    goto here;
  fflush(stdin);
  k=0;
  clrscr();cleardevice();
  setposi(320,150);

  if(w=='d')
  {if(m[x][y]=='*')
   {k=1;break;}
   else if(m[x][y]=='-')
   {if(n[x][y]=='f')
     {n[x][y]='.';cf++;}
    search(m,x,y,n);
    n[x][y]=m[x][y];

   }
   else
   n[x][y]=m[x][y];
  }
  else if(w=='f')
  if(n[x][y]!='f')
  {cf--;
   n[x][y]='f';}

  setcolor(7);
  rectangle(4,15,212,222);
  setfillstyle(SOLID_FILL,7);
  floodfill(20,20,7);
  setcolor(8);
  for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
  {line(j,15,j,222);
   line(4,r,212,r);}

  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  setcolor(0);
  for(i=1,r=21;i<=13;i++,r+=16)
   for(j=1,q=10;j<=13;j++,q+=16)
    {I[0]=n[i][j];I[1]='\0';
     if(n[i][j]>='1'&&n[i][j]<='8')
     {setcolor(8);
      setfillstyle(SOLID_FILL,8);
      floodfill(q,r,8);
     }
     if(n[i][j]=='1')
     setcolor(1);
     else if(n[i][j]=='2')
     setcolor(2);
     else if(n[i][j]=='3')
     setcolor(5);
     else if(n[i][j]=='4')
     setcolor(3);
     else if(n[i][j]>='5'&&n[i][j]<='8')
     setcolor(6);
     else if(n[i][j]=='f')
     setcolor(14);
     else if(n[i][j]=='.')
     setcolor(7);
     else if(n[i][j]=='-')
     {
      setcolor(8);
      setfillstyle(SOLID_FILL,8);
      floodfill(q,r,8);
     }
     outtextxy(q,r,I);
    }

  setcolor(0);
  for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
  {line(j,15,j,222);
   line(4,r,212,r);}
  setcolor(15);
  rectangle(4,15,212,222);
  for(i=1;i<=13;i++)
   for(j=1;j<=13;j++)
    if(m[i][j]!='*')
     if(n[i][j]!=m[i][j])
      k=1;
 }while(k);

 if(!k)
 {clrscr();
  cleardevice();

  setcolor(7);
  rectangle(4,15,212,222);
  setfillstyle(SOLID_FILL,7);
  floodfill(20,20,7);

  setcolor(8);
  for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
  {line(j,15,j,222);
   line(4,r,212,r);}

  gotoxy(2,17);
  cout<<"\n\nYOU WIN!!!";
  score+=100;

  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  setcolor(0);

  for(i=1,r=21;i<=13;i++,r+=16)
   for(j=1,q=10;j<=13;j++,q+=16)
   {if(m[i][j]=='*')
    n[i][j]='f';
    I[0]=n[i][j];I[1]='\0';
    if(n[i][j]>='1'&&n[i][j]<='8')
    {setcolor(8);
     setfillstyle(SOLID_FILL,8);
     floodfill(q,r,8);
    }
    if(n[i][j]=='1')
    setcolor(1);
    else if(n[i][j]=='2')
    setcolor(2);
    else if(n[i][j]=='3')
    setcolor(5);
    else if(n[i][j]=='4')
    setcolor(3);
    else if(n[i][j]>='5'&&n[i][j]<='8')
    setcolor(6);
    else if(n[i][j]=='f')
    setcolor(14);
    else if(n[i][j]=='.')
    setcolor(7);
    else if(n[i][j]=='-')
    {setcolor(8);
     setfillstyle(SOLID_FILL,8);
     floodfill(q,r,8);
    }
    outtextxy(q,r,I);
   }

  setcolor(0);
  for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
  {line(j,15,j,222);
   line(4,r,212,r);}
  setcolor(15);
  rectangle(4,15,212,222);

 }

 else
 {
  setcolor(8);
  rectangle(4,15,212,222);
  setfillstyle(SOLID_FILL,8);
  floodfill(20,20,8);
  setcolor(8);
  for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
  {line(j,15,j,222);
   line(4,r,212,r);}

  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  setcolor(0);
  for(i=1,r=21;i<=13;i++,r+=16)
   for(j=1,q=10;j<=13;j++,q+=16)
   {I[0]=m[i][j];I[1]='\0';
    if(m[i][j]=='1')
    setcolor(1);
    else if(m[i][j]=='2')
    setcolor(2);
    else if(m[i][j]=='3')
    setcolor(5);
    else if(m[i][j]=='4')
    setcolor(3);
    else if(m[i][j]>='5'&&m[i][j]<='8')
    setcolor(6);
    else if(m[i][j]=='*')
    setcolor(4);
    else if(m[i][j]=='.')
    setcolor(7);
    else if(m[i][j]=='-')
    setcolor(8);
    outtextxy(q,r,I);
   }

  setcolor(0);
  for(i=1,j=4,r=15;i<=14;i++,j+=16,r+=16)
  {line(j,15,j,222);
   line(4,r,212,r);}
  setcolor(15);
  rectangle(4,15,212,222);
  gotoxy(2,17);
  cout<<"\n\nGAME OVER!!!";

 }

 getch();
 return score;
}

void search(char a[15][15],int x,int y,char c[15][15])
{
 static int b[15][15]={0};int d,e;b[x][y]=1;
 for(d=x-1;d<=x+1;d++)
  for(e=y-1;e<=y+1;e++)
  {if(!b[d][e])
   {
    c[d][e]=a[d][e];
    b[d][e]=1;
    if(a[d][e]=='-')
    search(a,d,e,c);
   }
  }
}