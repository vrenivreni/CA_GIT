void init_map()
{
    int ii;
 
    memcpy32(&tile8_mem[0][1], nums8Tiles, nums8TilesLen/4);
    memcpy32(pal_bg_mem, numsPal, numsPalLen/4);
 
    /* REG_BG2CNT wurde schon im Kapitel Affine Background 
	 Control Register
     behandelt
	 */
	 
    REG_BG2CNT= BG_CBB(0) | BG_SBB(8) |  BG_AFF_64x64;
    bgaff= bg_aff_default;
 
    // fill per 256 screen entries (=32x4 bands)
    u32 *pse= (u32*)se_mem[8];
    /*
   	 u32 ses= 0x01010101
   	 Default-Wert 0x 01 01 01 01 setzt vier Spalten auf den
   	 HEX Wert 1, was die Farbe rot dastellt.
    */
 
    // Setzen von einer Farbe (hier rot) von nur einer Spalte
    u32 ses= 0x00000001;
    for(ii=0; ii<16; ii++)
    {
   	 memset32(pse, ses, MAP_AFF_SIZE/4);
   	 pse += MAP_AFF_SIZE/4;
   	 /*
	    ses += 0x01010101;
   		 Default-Wert, addiert immer den Wert 1 auf die 
		 jewiligen Spalten 0 - 3
   		 Somit werden nacheinander die Farben geaendert
   	 */
   	 // Zum Teste, keine Addition, die Kacheln bleiben alle rot
   	 ses += 0x00000000;
    }
}