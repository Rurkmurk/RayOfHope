u8 LoadLevel()
{
	u8 map[40][25];
	u8 x, y;
	u8 j=0;
	u16 i=0;
	u8 buf[3];
	u8 *p;
	
	p=(*map[25]);
	
	load_file("level001", 30, 1);
		
	for (y=0;y<25;y++)
		for (x=0;x<40;x++)
		{
			do
			{
				buf[j]=get_mem(30,32768+i)-48;
				j++;
				i++;
			}while (get_mem(30,32768+i)!=',');
			
			if (j==3) map[x][y]=100*buf[0]+10*buf[1]+buf[2];
			else if (j==2) map[x][y]=10*buf[0]+buf[1];
			else map[x][y]=buf[0];

			i++;
			j=0;
		}
	return *p;
}