#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"
#include "assert.h"

#define NUM  50 //炸弹数组个数

static bomb_body bomb[NUM];//一维结构数组表示炸弹，结构体在game.h中定义
static plane_body plane;//飞机结构体（对象），结构体在game.h中定义

bomb_body
get_bomb(int i)
{
	return bomb[i];
}

int
get_bomb_num(void)
{
	return NUM;
}

plane_body
get_plane(void)
{
	return plane;
}

//plane初始化，在屏幕中心
void
plane_initial(void)
{
	plane.x = 100;
	plane.y = 160;
}


//bomb数组的初始化
void
bomb_initial(void)
{	
	int i;
	for( i = 0; i < NUM; i++ )
	{
		bomb[i].x = rand() % ( SCR_HEIGHT / 8 - 2) * 8 + 8;
		bomb[i].y = rand() % ( SCR_WIDTH  / 8 - 2) * 8 + 8;
		bomb[i].vx = (rand() % 140) / 100.0 - 0.7;//generate a float num -0.7 ~ 0.7 
		bomb[i].vy = (rand() % 140) / 100.0 - 0.7;
	}
	protect_center();
}

//保护屏幕中心一块区域没有炸弹
void
protect_center(void)
{
	int i;
	float x_diff;
	float y_diff;
	
	for( i = 0; i < NUM; i++ )
	{
		x_diff = fabs(bomb[i].x - 100);//fabs,绝对值函数，在math.c中定义
		y_diff = fabs(bomb[i].y - 160);

		if( x_diff < 30 && y_diff < 50)
		{
			bomb[i].x = (int)(bomb[i].x * 2) % ( SCR_HEIGHT / 8 - 2) * 8 + 8;
			bomb[i].y = (int)(bomb[i].y * 2) % ( SCR_WIDTH  / 8 - 2) * 8 + 8;
		}
	}
}

//逻辑时钟前进1单位,更新bomb的位置 
void
update_bomb_pos(void) 
{
	int i;
	for( i = 0; i < NUM; i++ )
	{
		bomb[i].x += bomb[i].vx; 
		bomb[i].y += bomb[i].vy;
	}
	protect_border();
}

//保护炸弹不飞出屏幕
void
protect_border()
{
	int i;
	for( i = 0; i < NUM; i++ )
	{
		if( bomb[i].x < 8 || bomb[i].x > 192 )
			bomb[i].vx = -bomb[i].vx;	//撞边时该方向速度反向
		if( bomb[i].y < 8 || bomb[i].y > 312 )
			bomb[i].vy = -bomb[i].vy;
	}

}

//检测是否发生碰撞
bool
check_crash(void)
{
	int i;
	float x_diff,y_diff;

	if(plane.x < 6 || plane.x > 194 || plane.y < 6 || plane.y > 314)
	{		
		return TRUE;//飞机撞边
	}	
	for( i = 0; i < NUM; i++ )
	{
		x_diff = fabs(plane.x - bomb[i].x);
		y_diff = fabs(plane.y - bomb[i].y);
		if(x_diff < 3 && y_diff < 2 )
		{
			return TRUE;//飞机撞炸弹
		}
	}
	return FALSE;
}



//更新按键控制飞机
bool 
keyboard_plane_control(void)
{

	disable_interrupt();

	if(query_key(9))		//J pressed （left）
	{	
		plane.y -= 4;
		release_key(9);
		return TRUE;
	}
	if(query_key(10))		//K pressed  (down)
	{
		plane.x += 4;
		release_key(10);
		return TRUE;
	}
	if(query_key(11))		//L pressed  (right)
	{
		plane.y += 4;
		release_key(11);
		return TRUE;
	}
	if(query_key(8))		//I pressed  (up)
	{
		plane.x -= 4;
		release_key(8);
		return TRUE;
	}

	enable_interrupt();
	
	return FALSE;
}

//更新按键控制游戏开始
bool
keyboard_game_start(void)
{
	disable_interrupt();
	
	if( query_key(0) )	//A pressed
	{
		release_key(0);
		return TRUE;
	}

	enable_interrupt();

	return FALSE;
}

