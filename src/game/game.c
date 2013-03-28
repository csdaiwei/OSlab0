#include "x86/x86.h"
#include "game.h"
#include "string.h"
#include "device/timer.h"

#define FPS 30
#define UPDATE_PER_SECOND 100

volatile int tick = 0;

void
timer_event(void) {
	tick ++;
}


int get_clock(void)
{
	int s_clock = tick / 1000;	//仅保留到秒
	return s_clock;			//当游戏卡顿时，时钟记录会相应变慢 
}

static int real_fps;

void
set_fps(int value) {
	real_fps = value;
}
int
get_fps() {
	return real_fps;
}

bool startflag = FALSE;
int now , target;
int num_draw ;
bool redraw;


void
main_loop(void)
{
	
	draw_startscreen();

	while(TRUE)//外层循环，检测gamestart以控制游戏是否开始，永真
	{
		while( keyboard_game_start() )//等待键盘输入gamestart信号
			startflag = TRUE ;

		if( startflag )
			game_initial();//游戏循环初始化	

		while ( startflag )//内层循环。用于一次游戏中响应中断和屏幕刷新，开始后仅当发生撞机时终止循环
		{
			game_loop();
		}
	}
}

void game_initial(void)
{
	bomb_initial();
	plane_initial();
	tick = 0;
	now = 0;
	num_draw = 0;

}


void game_loop(void)
{
	wait_for_interrupt();
	disable_interrupt();
	if (now == tick)
	{
		enable_interrupt();
		//continue;
		return ;
	}
	assert(now < tick);
	target = tick; /* now总是小于tick，因此我们需要“追赶”当前的时间 */
	enable_interrupt();

	redraw = FALSE;

	while (keyboard_plane_control());

	
	while (now < target)
	{ 
		// 每隔一定时间更新屏幕上字符的位置并检测是否撞机 
		if (now % (HZ / UPDATE_PER_SECOND) == 0)
		{
			update_bomb_pos();

			if(check_crash())
			{
				//若撞机，则终止内循环并清除所有按键信息	
				release_all_key();
				startflag = FALSE;
				draw_stopscreen();
				break;
			}
		}
		// 每隔一定时间需要刷新屏幕
		if (now % (HZ / FPS) == 0)
		{
			redraw = TRUE;
		}
		/* 更新fps统计信息 */
		if (now % (HZ / 2) == 0)
		{
			int now_fps = num_draw * 2 + 1;
			if (now_fps > FPS) now_fps = FPS;
			set_fps(now_fps);
			num_draw = 0;
		}
		now ++;
	}

	if (redraw)
	{
		// 当需要重新绘图时重绘
		num_draw ++;
		draw_gamescreen();
	}


}
