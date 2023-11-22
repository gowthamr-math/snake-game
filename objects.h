#include<allegro5\allegro_primitives.h>
const int num=1000;
enum dir{RIGHT,LEFT,DOWN,UP,LEFTTORIGHT,RIGHTTOLEFT,UPTODOWN,DOWNTOUP,UPTORIGHT,UPTOLEFT,DOWNTORIGHT,DOWNTOLEFT,LEFTTOUP,LEFTTODOWN,RIGHTTOUP,RIGHTTODOWN};
extern ALLEGRO_BITMAP *headimage=NULL, *bodyimage=NULL, *tailimage=NULL,*lbodyimage=NULL;
ALLEGRO_DISPLAY *display;
struct snake
{
	int length;
	int x,y,dirx,diry;
	int speed;
	bool numarr[num];
	int arrx[num];
	int arry[num];
};
struct food
{
	int x,y;
};
struct rect
{
	int thikness;
};
/*void drawrect(int x, int y)
{
al_draw_filled_rectangle(x,y,x+19,y+19,al_map_rgb(255,255,255));
al_draw_filled_rectangle(x+2,y+2,x+17,y+17,al_map_rgb(230,0,0));
}*/
void drawfoodrect(int x,int y, ALLEGRO_BITMAP *foodimage)
{
al_draw_bitmap(foodimage,x,y,0);
}

void drawhead(int x,int y, dir z)
{
if(z==RIGHT)
al_draw_bitmap(headimage, x,y,ALLEGRO_FLIP_HORIZONTAL);
if(z==LEFT)
al_draw_bitmap(headimage, x,y,0);
if(z==UP)
al_draw_rotated_bitmap(headimage, 10,10,x+10,y+10,3.14*90/180,0);
if(z==DOWN)
al_draw_rotated_bitmap(headimage, 10,10,x+10,y+10,3.14*270/180,0);
}
void drawbody(int x,int y, dir z)
{
if(z==LEFTTORIGHT)
al_draw_bitmap(bodyimage, x,y,ALLEGRO_FLIP_HORIZONTAL);
if(z==RIGHTTOLEFT)
al_draw_bitmap(bodyimage, x,y,0);
if(z==DOWNTOUP)
al_draw_rotated_bitmap(bodyimage, 10,10,x+10,y+10,3.14*90/180,0);
if(z==UPTODOWN)
al_draw_rotated_bitmap(bodyimage, 10,10,x+10,y+10,3.14*270/180,0);
if(z==DOWNTOLEFT)
al_draw_bitmap(lbodyimage, x,y,ALLEGRO_FLIP_HORIZONTAL);
if(z==DOWNTORIGHT)
al_draw_bitmap(lbodyimage, x,y,0);
if(z==UPTORIGHT)
al_draw_bitmap(lbodyimage,x,y,ALLEGRO_FLIP_VERTICAL);
if(z==UPTOLEFT)
al_draw_rotated_bitmap(lbodyimage, 10,10,x+10,y+10,(3.14*90)/180,ALLEGRO_FLIP_HORIZONTAL);
if(z==LEFTTOUP)
al_draw_rotated_bitmap(lbodyimage, 10,10,x+10,y+10,(3.14*90)/180,ALLEGRO_FLIP_HORIZONTAL);
if(z==RIGHTTOUP)
al_draw_bitmap(lbodyimage,x,y,ALLEGRO_FLIP_VERTICAL);
if(z==LEFTTODOWN)
al_draw_bitmap(lbodyimage, x,y,ALLEGRO_FLIP_HORIZONTAL);
if(z==RIGHTTODOWN)
al_draw_bitmap(lbodyimage, x,y,0);
}
void drawtail(int x,int y, dir z)
{
if(z==RIGHT)
al_draw_bitmap(tailimage, x,y,ALLEGRO_FLIP_HORIZONTAL);
if(z==LEFT)
al_draw_bitmap(tailimage, x,y,0);
if(z==UP)
al_draw_rotated_bitmap(tailimage, 10,10,x+10,y+10,3.14*90/180,0);
if(z==DOWN)
al_draw_rotated_bitmap(tailimage, 10,10,x+10,y+10,3.14*270/180,0);
}