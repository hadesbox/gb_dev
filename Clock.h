unsigned long bars;
unsigned long beats;
unsigned long clockCount;
void tick(){
	for (int i = 0; i < 7; ++i)
	{
		tracks[i].tick(bars, beats);
		if (clockCount%24)
		{
			bars++;
		}
	}
}
