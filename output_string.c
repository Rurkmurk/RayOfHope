#ifndef _OUTPUT_STRING
#define _OUTPUT_STRING


void output_string(u8 output_x, u8 output_y, u8* str)
{
	static u8 n;
	static u8 save_output_x;
	save_output_x=output_x;
	select_image(IMG_FONT);
	color_key (15);
	while(1)
	{
		n=*str++;
		if(!n) break;
		if (n-32==62)
		{
			output_x=save_output_x;
			output_y++;
			n=*str++;
		}
		draw_tile_key(output_x,output_y,n-32);
		output_x++;
	}
}

void speed_meter()
{
	static u16 tic;
	static u32 time_tic;
	
	tic=0;
	time_tic=time();
	vsync();
	while (time_tic+2>time())
		tic++;

	if (tic<500)
	{
		model=ATM;
		stalact_speed=4;
	}
}

#endif