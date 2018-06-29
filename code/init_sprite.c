void init_sprite()
{
	u32 tid= 0, pb= 0;	// Tile-Index, Palette

	OBJ_ATTR *metr= &obj_buffer[0];
	obj_set_attr(metr, 
        ATTR0_SQUARE,   // Rechteck, regulaeres Sprite (nicht affin)
		ATTR1_SIZE_64,	// 64x64p,
		ATTR2_PALBANK(pb) | tid);
}
