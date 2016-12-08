#include<graphics.h>
union REGS in,out;
void detect_mouse ()
{
  label:
  in.x.ax = 0;
  int86 (0X33,&in,&out);
  if (out.x.ax == 0)
	goto label;
}
void showmouse()
{
   in.x.ax = 1;
   int86 (0X33,&in,&out);
}
void hide_mouse ()
{
   in.x.ax = 2;
   int86 (0X33,&in,&out);
}
void detect(int &i,int&j)
{
int cl=0,x,y;
do
    {
     in.x.ax = 3;
     int86 (0X33,&in,&out);
     if (out.x.bx == 1)
	{
	 x = out.x.cx;
	 y = out.x.dx;
	 cl++;
	}
     delay (100); // Otherwise due to quick computer response 100s of words will get print
    }
    while(cl==0);
    i=x;
    j=y;
}