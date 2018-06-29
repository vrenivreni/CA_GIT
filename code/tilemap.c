int main()
{
	// Palette laden
	memcpy(pal_bg_mem, brinPal, brinPalLen);
	// Bloecke in CBB 0 laden
	memcpy(&tile_mem[0][0], brinTiles, brinTilesLen);
	// Tilemap in SBB 30 laden
	memcpy(&se_mem[29][0], brinMap, brinMapLen);

	// BG0 fuer eine 4bpp 64x32t Karte initialisieren
	REG_BG0CNT= BG_CBB(0) | BG_SBB(29) | BG_4BPP | BG_REG_64x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;

	// Durch die Karte scrollen
	int x= 0, y= 0;
	while(1)
	{
		vid_vsync();
		key_poll();
		x += key_tri_horz();
		y += key_tri_vert();
		REG_BG0HOFS= x;
		REG_BG0VOFS= y;
	}
	return 0;
}
