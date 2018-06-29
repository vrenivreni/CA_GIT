void sbb_aff()

{

	AFF_SRC_EX asx=

	{
		// Initialwerte der Koordinanten in X-Richtung (p0-Display)
		32<<8, 64<<8,			
		// Initialwerte der Koordinanten in Y-Richtung (q0-Display)
		120, 80,				
		// Initialwerte der Skalierung und Rotierung
		0x0100, 0x0100, 0	
	};
  /*

 		die Variable DX ist fuer die Geschwindigkeit der Verschiebung entlang der

		Koordinaten zustaendig

  */
	const int DX=256;
	/*

		ss ist der initiale Zoom beim Start der mGBA Anwendung

		wird hier der Wert auf 0x0300 gesetzt, ist das Zoomlevel

		deutlich groesser

	*/
	FIXED ss= 0x0100;

	while(1)
	{
		/* Wenn Funktion vid_vsync deaktiviert flimmert der Bildschirm

		*/
		vid_vsync();
		/* key_poll() ist unbedingt notwendig, sonst funktioniert die

			 Eingabe von der Tastatur nicht.

		*/
		key_poll();
		// dir + A : move map in screen coords
		if(key_is_down(KEY_A))
		{
			asx.scr_x += key_tri_horz();
			asx.scr_y += key_tri_vert();
		}
		else	// dir : move map in map coords
		{
			asx.tex_x -= DX*key_tri_horz();
			asx.tex_y -= DX*key_tri_vert();
		}
		/*

			Rotation: der binaere Wert, hier der Standardwert 128

			vor dem key_tri_shoulder() Funktion ist fuer die Geschwindigkeit der

			Rotation zustaendig.

		*/
		asx.alpha -= 128*key_tri_shoulder();
		// B: scale up ; B+Se : scale down
		if(key_is_down(KEY_B))
			/*
			ss ist fuer Zoom Einstellung
			*/
			ss += (key_is_down(KEY_SELECT) ? -1 : 1);
		// St+Se : reset
		// St : toggle wrapping flag.
		if(key_hit(KEY_START))
		{
			if(key_is_down(KEY_SELECT))
			{
				asx.tex_x= asx.tex_y= 0;
				asx.scr_x= asx.scr_y= 0;
				asx.alpha= 0;
				ss= 1<<8;
			}
			else
				REG_BG2CNT ^= BG_WRAP;
		}
		asx.sx= asx.sy= (1<<16)/ss;
		/*

			Funktion, welche die Eigentliche Rotierung veranlasst. bg_rotscale_ex fuehrt eine

			Reihe von mathematischen Operationen aus. Es fuehrt auch die Transformation um

			die Matrix P durch.

		*/
		bg_rotscale_ex(&bgaff, &asx);
		/*
			REG_BG_AFFINE[2]= bgaff veranlasst, dass das Bild rotiert sich
			verschiebt. Dies ist auch die Initialisierung der affinen Hintergruende
		*/
		REG_BG_AFFINE[2]= bgaff;
		// the cross indicates the rotation point
		// (== p in map-space; q in screen-space)
		obj_set_pos(obj_cross, asx.scr_x-3, (asx.scr_y-3));
		obj_set_pos(obj_disp, (bgaff.dx>>8)-3, (bgaff.dy>>8)-3);
		// Print Funktion fuer die Anzeige der Koordinaten im unteren linken Bildschirm
		tte_printf("#{es;P}p0\t: (%d, %d)\nq0\t: (%d, %d)\ndx\t: (%d, %d)",
			asx.tex_x>>8, asx.tex_y>>8, asx.scr_x, asx.scr_y,
			bgaff.dx>>8, bgaff.dy>>8);
	}

}

