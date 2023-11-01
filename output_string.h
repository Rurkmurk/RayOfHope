#ifndef __OUTPUT_STRING
#define __OUTPUT_STRING

void output_string(u8 output_x, u8 output_y, u8* str)
{
	u8 n;
	u8 save_output_x=output_x;
	select_image(IMG_FONT);
	color_key (15);
	while(1)
	{
		n=*str++;
		if(!n) break;
		draw_tile_key(output_x,output_y,n-32);
		output_x++;
		if (output_x>=40)
		{
			output_x=save_output_x;
			output_y++;
		}
	}
}

#endif