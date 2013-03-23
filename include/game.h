#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"


//plane_body结构体定义
typedef struct plane_body
{
	float x;
	float y;

}plane_body;

//bomb_body结构体的定义
typedef struct bomb_body
{
	float x;
	float y;
	float vx;
	float vy;

}bomb_body;


// 中断时调用的函数
void timer_event(void);
void keyboard_event(int scan_code);


//屏幕刷新
void draw_gamescreen(void);
void draw_startscreen(void);
void draw_stopscreen(void);

/*
 * 游戏主逻辑相关函数
 */
//数组初始化
void bomb_initial(void);
void plane_initial(void);
//按时更新炸弹/飞机位置
void update_bomb_pos(void);
bool update_plane_pos(void);
//边界/中心保护
void protect_border(void);
void protect_center(void);
//获得炸弹/飞机位置
bomb_body get_bomb(int i);
plane_body get_plane(void);
int get_bomb_num(void);
//检测撞机
bool check_crash(void);
//检测游戏开始
bool check_gamestart(void);


/* 主循环 */
void main_loop(void);
void game_loop(void);
void game_initial(void);
int get_fps(void);
void set_fps(int fps);
int get_clock(void);


//按键相关
void press_key(int scan_code);
void release_key(int ch);
bool query_key(int ch);
int last_key_code(void);
void release_all_key(void);


//数学函数
float fabs(float x);
int rand(void);
void srand(int seed);


#endif
