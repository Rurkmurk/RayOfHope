#ifndef _UPDATE_SCREEN
#define _UPDATE_SCREEN

void update_sprite()
{
	u8 n;
	//player
	set_sprite(0,player.x,player.y,player.frame);

	//enemy

	for (n=1;n<=enemy_summ;n++)
		set_sprite(n,enemy[n].x,enemy[n].y,enemy[n].frame);
	
	//shot
	set_sprite(enemy_summ+1,shot.x,shot.y,shot.frame);
}


void update_terrain()
{
	u8 n,m;
	u8 tmp;

	//if (t_terrain+10<time())
	//{
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
			//	draw_tile(lava[n].x[m],lava[n].y[0],lava[n].tile[m]);
			//	draw_tile(lava[n].x[m],lava[n].y[1],lava[n].tile[m+4]);
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
			
			 for (m=0;m<4;m++)
			{
			//	draw_tile(water[n].x[m],water[n].y[0],water[n].tile[m]);
			//	draw_tile(water[n].x[m],water[n].y[1],water[n].tile[m+4]);
			} 
		}	
		n_frame=n_frame==0?1:0;
		//t_terrain=time();
	//}


}



#endif