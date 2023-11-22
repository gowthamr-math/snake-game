#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\keyboard.h>
#include<allegro5\events.h>
#include<allegro5\timer.h>
#include<time.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_image.h>
#include"objects.h"



int const width=600,height=300;
snake snake;
food food;
float FPS=60;
bool key=0;
bool foodcatched=false;
bool over=false;
ALLEGRO_SAMPLE *sample=NULL;
ALLEGRO_SAMPLE *boom=NULL;

int err=0;

void initsnake(void);
void initfood(void);
void updatesnake(int x, int y);
void drawsnake(void);
void drawfood(ALLEGRO_BITMAP *foodimage);
void updatefood(void);
void checkfoodcatch(void);
int checkcollision(void);

int main(void)
{	
	

	al_init();
	al_init_font_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();

	
	ALLEGRO_BITMAP *foodimage=NULL;
	ALLEGRO_BITMAP *icon=NULL;
	ALLEGRO_FONT *font=al_load_font("PTC75F.ttf",30,0);
	ALLEGRO_BITMAP *bg=NULL;
	ALLEGRO_EVENT_QUEUE *q;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMER *timer;

	boom=al_load_sample("boom.wav");
	sample=al_load_sample("beep.wav");
	display=al_create_display(width,height);
	q=al_create_event_queue();
	timer=al_create_timer(5/FPS);
	foodimage=al_load_bitmap("food.png");
	headimage=al_load_bitmap("head.png");
	bodyimage=al_load_bitmap("body.png");
	lbodyimage=al_load_bitmap("lbody.png");
	tailimage=al_load_bitmap("tail.png");
	bg=al_load_bitmap("bg.jpg");
	icon=al_load_bitmap("icon.png");

	al_reserve_samples(2);
	al_set_window_title(display,"SNAKE");
	al_set_display_icon(display,icon);
	srand(time(NULL));
	al_register_event_source(q,al_get_timer_event_source(timer));
	al_register_event_source(q,al_get_keyboard_event_source());
	al_register_event_source(q,al_get_display_event_source(display));

	initsnake();
	initfood();
	al_draw_bitmap(bg, 0,0,0);
	for(int i=1;i<4;i++)
	{
		snake.x+=snake.dirx*20;
		snake.y+=snake.diry*20;
		updatesnake(snake.x, snake.y);
		
		foodcatched=true;
	}
	drawsnake();
	initfood();
	foodcatched=false;
	al_flip_display();
	al_draw_bitmap(bg, 0,0,0);
	al_start_timer(timer);
	
	while(!over)
	{	
		al_wait_for_event(q,&ev);
		if(ev.type==ALLEGRO_EVENT_KEY_DOWN&&key==0)
		{
			
			switch(ev.keyboard.keycode)
			{
				
			case ALLEGRO_KEY_RIGHT:
				if(snake.dirx==0){
				snake.dirx=1;
				snake.diry=0;
				}break;
			case ALLEGRO_KEY_LEFT:
				if(snake.dirx==0){
				snake.dirx=-1;
				snake.diry=0;
				}break;
			case ALLEGRO_KEY_DOWN:
				if(snake.diry==0){
				snake.diry=1;
				snake.dirx=0;
				}break;
			case ALLEGRO_KEY_UP:
				if(snake.diry==0){
				snake.dirx=0;
				snake.diry=-1;
				}break;
			}
			key=1;
		}
		else if(ev.type==ALLEGRO_EVENT_TIMER)
		{
		snake.x+=snake.dirx*20;
		snake.y+=snake.diry*20;
		
		key=0;

		updatesnake(snake.x, snake.y);
		
		if(1==checkcollision())
		{
			
			break;
		}
		drawsnake();
		checkfoodcatch();
		
		if(foodcatched)
		{
		updatefood();
		
		}
		
		drawfood(foodimage);
		
		al_flip_display();
		al_draw_bitmap(bg, 0,0,0);
		}
		else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			over=true;
		}
	}
	
	if(over==!true)
	{
	al_stop_timer(timer);
	timer=al_create_timer(5.0);
	al_start_timer(timer);
	al_register_event_source(q,al_get_display_event_source(display));
	al_register_event_source(q,al_get_timer_event_source(timer));
	al_rest(1.0);
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_textf(font,al_map_rgb(255,0,0),300,135,ALLEGRO_ALIGN_CENTRE,"SCORE : %i ",snake.length-2);
	al_flip_display();
	ab:
	al_wait_for_event(q,&ev);
	if(ev.type!=ALLEGRO_EVENT_DISPLAY_CLOSE&&ev.type!=ALLEGRO_EVENT_TIMER)
		goto ab;
	}
	al_destroy_sample(sample);
	al_destroy_sample(boom);
	al_destroy_bitmap(headimage);
	al_destroy_bitmap(bodyimage);
	al_destroy_bitmap(lbodyimage);
	al_destroy_bitmap(tailimage);
	al_destroy_bitmap(foodimage);
	al_destroy_bitmap(bg);
	al_destroy_font(font);
	al_destroy_event_queue(q);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}
void initsnake(void)
{
snake.x=260;
snake.y=height/2+10;
snake.dirx=1;
snake.diry=0;
snake.length=0;
snake.arrx[0]=260;
snake.arry[0]=height/2+10;
snake.numarr[0]=true;
for(int i=1;i<=num;i++)
{	
	snake.arrx[i]=0;
	snake.arry[i]=0;
	snake.numarr[i]=false;
}
}
void initfood(void)
{
	start:
	food.x=(rand()%29)*20;
	food.y=(rand()%14)*20;
	for(int i=0;true==snake.numarr[i];i++)
	{
	if(snake.arrx[i]==food.x&&snake.arry[i]==food.y)  
	goto start;
	}	
}
void updatesnake(int x, int y)
{
	if(foodcatched==true)
	{
	snake.length++;
	snake.numarr[snake.length]=true;
	foodcatched=false;
	}
	
	for(int i=0;true==snake.numarr[i];i++)
	{
	snake.arrx[snake.length-i+1]=snake.arrx[snake.length-i];
	snake.arry[snake.length-i+1]=snake.arry[snake.length-i];
	}
	snake.arrx[0]=x;
	snake.arry[0]=y;
	
	
}
void drawsnake()
{	
	if(snake.dirx==1)
	drawhead(snake.arrx[0],snake.arry[0],RIGHT);
	if(snake.dirx==-1)
	drawhead(snake.arrx[0],snake.arry[0],LEFT);
	if(snake.diry==1)
	drawhead(snake.arrx[0],snake.arry[0],DOWN);
	if(snake.diry==-1)
	drawhead(snake.arrx[0],snake.arry[0],UP);
	for(int i=1;i<=snake.length-1;i++)
	{
	if(snake.arrx[i-1]==snake.arrx[i]+20&&snake.arrx[i+1]==snake.arrx[i]-20)
	drawbody(snake.arrx[i],snake.arry[i],LEFTTORIGHT);
	if(snake.arrx[i-1]==snake.arrx[i]-20&&snake.arry[i-1]==snake.arry[i]&&snake.arrx[i+1]==snake.arrx[i]+20&&snake.arry[i+1]==snake.arry[i])
	drawbody(snake.arrx[i],snake.arry[i],RIGHTTOLEFT);
	if(snake.arrx[i-1]==snake.arrx[i]&&snake.arry[i-1]==snake.arry[i]+20&&snake.arrx[i+1]==snake.arrx[i]&&snake.arry[i+1]==snake.arry[i]-20)
	drawbody(snake.arrx[i],snake.arry[i],UPTODOWN);
	if(snake.arrx[i-1]==snake.arrx[i]&&snake.arry[i-1]==snake.arry[i]-20&&snake.arrx[i+1]==snake.arrx[i]&&snake.arry[i+1]==snake.arry[i]+20)
	drawbody(snake.arrx[i],snake.arry[i],DOWNTOUP);
	if(snake.arrx[i-1]==snake.arrx[i]+20&&snake.arry[i+1]==snake.arry[i]-20)
	drawbody(snake.arrx[i],snake.arry[i],UPTORIGHT);
	if(snake.arrx[i-1]==snake.arrx[i]-20&&snake.arry[i+1]==snake.arry[i]-20)
	drawbody(snake.arrx[i],snake.arry[i],UPTOLEFT);
	if(snake.arrx[i-1]==snake.arrx[i]+20&&snake.arry[i+1]==snake.arry[i]+20)
	drawbody(snake.arrx[i],snake.arry[i],DOWNTORIGHT);
	if(snake.arrx[i-1]==snake.arrx[i]-20&&snake.arry[i+1]==snake.arry[i]+20)
	drawbody(snake.arrx[i],snake.arry[i],DOWNTOLEFT);
	if(snake.arry[i-1]==snake.arry[i]-20&&snake.arrx[i+1]==snake.arrx[i]-20)
	drawbody(snake.arrx[i],snake.arry[i],LEFTTOUP);
	if(snake.arry[i-1]==snake.arry[i]-20&&snake.arrx[i+1]==snake.arrx[i]+20)
	drawbody(snake.arrx[i],snake.arry[i],RIGHTTOUP);
	if(snake.arry[i-1]==snake.arry[i]+20&&snake.arrx[i+1]==snake.arrx[i]-20)
	drawbody(snake.arrx[i],snake.arry[i],LEFTTODOWN);
	if(snake.arry[i-1]==snake.arry[i]+20&&snake.arrx[i+1]==snake.arrx[i]+20)
	drawbody(snake.arrx[i],snake.arry[i],RIGHTTODOWN);
	}
	if(snake.arrx[snake.length-1]==snake.arrx[snake.length]+20)
	drawtail(snake.arrx[snake.length],snake.arry[snake.length],RIGHT);
	if(snake.arrx[snake.length-1]==snake.arrx[snake.length]-20)
	drawtail(snake.arrx[snake.length],snake.arry[snake.length],LEFT);
	if(snake.arry[snake.length-1]==snake.arry[snake.length]+20)
	drawtail(snake.arrx[snake.length],snake.arry[snake.length],DOWN);
	if(snake.arry[snake.length-1]==snake.arry[snake.length]-20)
	drawtail(snake.arrx[snake.length],snake.arry[snake.length],UP);
	
	
/*
	for(int i=0;i<=snake.length;i++)
	{
	drawrect(snake.arrx[i],snake.arry[i]);
	}
*/	
}
void updatefood(void)
{	
	start:
	food.x=(rand()%29)*20;
	food.y=(rand()%14)*20;
	for(int i=0;true==snake.numarr[i];i++)
	{
	if(snake.arrx[i]==food.x&&snake.arry[i]==food.y)  
	goto start;
	}	
}
void drawfood(ALLEGRO_BITMAP *foodimage)
{
drawfoodrect(food.x,food.y,foodimage);
}
void checkfoodcatch()
{
	if(food.x==snake.arrx[0]&&food.y==snake.arry[0])
	{
	foodcatched=true;
	al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
	
	}
}
int checkcollision()
{
if(snake.arrx[0]<0||snake.arrx[0]>580||snake.arry[0]<0||snake.arry[0]>280)
	{
		al_play_sample(boom, 2.0,0,3.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		return 1;
	}
for(int i=1;true==snake.numarr[i];i++)
{
if(snake.arrx[0]==snake.arrx[i])
{	
	if(snake.arry[0]==snake.arry[i])
	{
		al_play_sample(boom, 2.0,0,3.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		return 1;
	}
}
}
return 0;
}