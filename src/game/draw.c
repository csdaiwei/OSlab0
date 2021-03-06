#include "game.h"
#include "string.h"
#include "device/video.h"



//绘制游戏过程屏幕
void
draw_gamescreen()
{	
	int i;
	int x,y;
	bomb_body nb;//now bomb
	plane_body np = get_plane();//now plane
	int num = get_bomb_num();

	assert( np.x != 0);

	prepare_buffer(); /* 准备缓冲区 */
	
	for( i = 0; i < num; i++ )
	{
		nb = get_bomb(i);
		
		assert( nb.x != 0);		

		x =(int) nb.x;
		y =(int) nb.y;
		draw_bomb(x,y);
	}

	x = (int) np.x;
	y = (int) np.y;
	draw_plane(x,y);

	//绘制FPS，clock
	draw_string(itoa(get_fps()), 0, 0, 14);
	draw_string("FPS", 0, strlen(itoa(get_fps())) * 8, 14);
	draw_string(itoa(get_clock()), 190, 0, 14);
	draw_string("S", 190, strlen(itoa(get_clock()))*8, 14);

	display_buffer(); /* 绘制缓冲区 */

}

//绘制开始屏幕
void 
draw_startscreen(void)
{
	
	char buf1[15] = "Welcome Game !";
	char buf2[34] = "Control your plane with 'i,j,k,l'";
	char buf3[32] = "Avoid the bomb and stay alive !";
	char buf4[29] = "Ready ? press 'A' to start !";
	
	buf1[14] = 0;
	buf2[33] = 0;
	buf3[31] = 0;
	buf4[28] = 0;
	
	prepare_buffer();
	
	draw_string( buf1, 40, 90, 14 );
	draw_string( buf2, 70, 25, 14 );
	draw_string( buf3, 100, 35, 14 );
	draw_string( buf4, 130, 45, 14 );

	display_buffer();
}

//绘制终止屏幕
void
draw_stopscreen(void)
{

	char buf1[17] = "BBOOOOOMMM!!!!!!";
	char buf2[39] = "Wow! you stayed alive for     seconds!";
	char buf3[23] = "Press 'A' to restart !";
	int clock = get_clock();

	buf1[16] = 0;
	buf2[38] = 0;
	buf3[22] = 0;

	prepare_buffer();

	draw_string( buf1, 50, 100, 14 );
	draw_string( buf2, 80, 10, 14 );
	draw_string( itoa(clock), 80, 225, 14 );
	draw_string( buf3, 110, 65, 14 );

	display_buffer();
}


