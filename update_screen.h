#ifndef _UPDATE_SCREEN
#define _UPDATE_SCREEN

void update_player()
{
	set_sprite(0,p.x,p.y,p.frame);
}



void update_terrain()
{
	u8 n,m;
	u8 tmp;

	//if (t_terrain+10<time())
	{
		//lava anim
		select_image(IMG_TILE);
		for (n=0;n<lava_summ;n++)
		{
			tmp=lava[n].tile[0];
			lava[n].tile[0]=lava[n].tile[1];
			lava[n].tile[1]=lava[n].tile[2];
			lava[n].tile[2]=lava[n].tile[3];
			lava[n].tile[3]=tmp;
			
			tmp=lava[n].tile[4];
			lava[n].tile[4]=lava[n].tile[5];
			lava[n].tile[5]=lava[n].tile[6];
			lava[n].tile[6]=lava[n].tile[7];
			lava[n].tile[7]=tmp;
			
			
			for (m=0;m<4;m++)
			{
				//draw_tile(lava[n].x[m],lava[n].y[0],lava[n].tile[m]);
				//draw_tile(lava[n].x[m],lava[n].y[1],lava[n].tile[m+4]);
			}
		}
		
		// water anim
		for (n=0;n<water_summ;n++)
		{
			tmp=water[n].tile[0];
			water[n].tile[0]=water[n].tile[1];
			water[n].tile[1]=water[n].tile[2];
			water[n].tile[2]=water[n].tile[3];
			water[n].tile[3]=tmp;
			
			switch (n_frame)
			{
				case 0:
				water[n].tile[4]+=4;
				water[n].tile[5]+=4;
				water[n].tile[6]+=4;
				water[n].tile[7]+=4;
				break;
				case 1:
				water[n].tile[4]-=4;
				water[n].tile[5]-=4;
				water[n].tile[6]-=4;
				water[n].tile[7]-=4;
				break;
			}
			
			/* for (m=0;m<4;m++)
			{
				draw_tile(water[n].x[m],water[n].y[0],water[n].tile[m]);
				draw_tile(water[n].x[m],water[n].y[1],water[n].tile[m+4]);
			} */
		}	
		
		if (n_frame==0) n_frame=1;
		else n_frame=0;
		//t_terrain=time();
	}


}



#endif