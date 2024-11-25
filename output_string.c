#ifndef _OUTPUT_STRING
#define _OUTPUT_STRING

//////////////////////////////////////////////////////////////
/* void itoa(i16 val, u8* buf)
{
    static u8 *p;                 
    static  u8 *firstdig;          
    static i8 temp;               
    static i8 digval;         
	static u8 a;
	for(a=0;a<16;a++)buf[a]=0;
	
    p = buf;
    firstdig = p;           
 
    do {
        digval = (unsigned) (val % 10);
        val /= 10;       
 
        
        if (digval > 9)*p++ = (char) (digval - 10 + 'a'); 
        else *p++ = (char) (digval + '0');       
 
    } 
	while (val > 0);
	 
    *p-- = '\0';            
 
    do 
	{
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;   
        --p;
        ++firstdig;         
    } while (firstdig < p); 
} */

////////////////////////////////////////////////////////////////////////////////////////
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

#endif