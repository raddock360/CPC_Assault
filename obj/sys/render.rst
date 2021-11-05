                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module render
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _sys_render_one_entity
                             12 	.globl _man_entity_forall
                             13 	.globl _cpct_getScreenPtr
                             14 	.globl _cpct_setPALColour
                             15 	.globl _cpct_setPalette
                             16 	.globl _cpct_setVideoMode
                             17 	.globl _palette
                             18 	.globl _sys_render_init
                             19 	.globl _sys_render_update
                             20 ;--------------------------------------------------------
                             21 ; special function registers
                             22 ;--------------------------------------------------------
                             23 ;--------------------------------------------------------
                             24 ; ram data
                             25 ;--------------------------------------------------------
                             26 	.area _DATA
                             27 ;--------------------------------------------------------
                             28 ; ram data
                             29 ;--------------------------------------------------------
                             30 	.area _INITIALIZED
                             31 ;--------------------------------------------------------
                             32 ; absolute external ram data
                             33 ;--------------------------------------------------------
                             34 	.area _DABS (ABS)
                             35 ;--------------------------------------------------------
                             36 ; global & static initialisations
                             37 ;--------------------------------------------------------
                             38 	.area _HOME
                             39 	.area _GSINIT
                             40 	.area _GSFINAL
                             41 	.area _GSINIT
                             42 ;--------------------------------------------------------
                             43 ; Home
                             44 ;--------------------------------------------------------
                             45 	.area _HOME
                             46 	.area _HOME
                             47 ;--------------------------------------------------------
                             48 ; code
                             49 ;--------------------------------------------------------
                             50 	.area _CODE
                             51 ;src/sys/render.c:14: void sys_render_one_entity (Entity_t* e) {
                             52 ;	---------------------------------
                             53 ; Function sys_render_one_entity
                             54 ; ---------------------------------
   41A6                      55 _sys_render_one_entity::
   41A6 DD E5         [15]   56 	push	ix
   41A8 DD 21 00 00   [14]   57 	ld	ix,#0
   41AC DD 39         [15]   58 	add	ix,sp
   41AE F5            [11]   59 	push	af
   41AF 3B            [ 6]   60 	dec	sp
                             61 ;src/sys/render.c:21: if (e->prevptr != 0) 	
   41B0 DD 4E 04      [19]   62 	ld	c,4 (ix)
   41B3 DD 46 05      [19]   63 	ld	b,5 (ix)
   41B6 21 05 00      [10]   64 	ld	hl, #0x0005
   41B9 09            [11]   65 	add	hl,bc
   41BA DD 75 FE      [19]   66 	ld	-2 (ix), l
   41BD DD 74 FF      [19]   67 	ld	-1 (ix), h
   41C0 5E            [ 7]   68 	ld	e, (hl)
   41C1 23            [ 6]   69 	inc	hl
   41C2 56            [ 7]   70 	ld	d, (hl)
   41C3 7A            [ 4]   71 	ld	a, d
   41C4 B3            [ 4]   72 	or	a,e
   41C5 28 02         [12]   73 	jr	Z,00102$
                             74 ;src/sys/render.c:22: *(e->prevptr) = 0;
   41C7 AF            [ 4]   75 	xor	a, a
   41C8 12            [ 7]   76 	ld	(de), a
   41C9                      77 00102$:
                             78 ;src/sys/render.c:26: if (!(e->type & e_type_dead)) {
   41C9 0A            [ 7]   79 	ld	a, (bc)
   41CA 07            [ 4]   80 	rlca
   41CB 38 3D         [12]   81 	jr	C,00108$
                             82 ;src/sys/render.c:27: xPixelCoord = e->x;
   41CD 69            [ 4]   83 	ld	l, c
   41CE 60            [ 4]   84 	ld	h, b
   41CF 23            [ 6]   85 	inc	hl
   41D0 56            [ 7]   86 	ld	d, (hl)
                             87 ;src/sys/render.c:28: xByteCoord = (xPixelCoord / 2) + (xPixelCoord % 2);
   41D1 5A            [ 4]   88 	ld	e, d
   41D2 CB 3B         [ 8]   89 	srl	e
   41D4 7A            [ 4]   90 	ld	a, d
   41D5 E6 01         [ 7]   91 	and	a, #0x01
   41D7 DD 77 FD      [19]   92 	ld	-3 (ix), a
   41DA 7B            [ 4]   93 	ld	a, e
   41DB DD 86 FD      [19]   94 	add	a, -3 (ix)
                             95 ;src/sys/render.c:29: pvmem = cpct_getScreenPtr (CPCT_VMEM_START, xByteCoord, e->y);
   41DE 69            [ 4]   96 	ld	l, c
   41DF 60            [ 4]   97 	ld	h, b
   41E0 23            [ 6]   98 	inc	hl
   41E1 23            [ 6]   99 	inc	hl
   41E2 56            [ 7]  100 	ld	d, (hl)
   41E3 C5            [11]  101 	push	bc
   41E4 5F            [ 4]  102 	ld	e, a
   41E5 D5            [11]  103 	push	de
   41E6 21 00 C0      [10]  104 	ld	hl, #0xc000
   41E9 E5            [11]  105 	push	hl
   41EA CD 23 43      [17]  106 	call	_cpct_getScreenPtr
   41ED EB            [ 4]  107 	ex	de,hl
   41EE FD E1         [14]  108 	pop	iy
   41F0 FD 4E 04      [19]  109 	ld	c, 4 (iy)
                            110 ;src/sys/render.c:30: if( ( xPixelCoord % 2) == 0 ) {
   41F3 DD 7E FD      [19]  111 	ld	a, -3 (ix)
   41F6 B7            [ 4]  112 	or	a, a
   41F7 20 06         [12]  113 	jr	NZ,00104$
                            114 ;src/sys/render.c:31: *pvmem = e->color >> 1;	
   41F9 79            [ 4]  115 	ld	a,c
   41FA CB 3F         [ 8]  116 	srl	a
   41FC 12            [ 7]  117 	ld	(de), a
   41FD 18 02         [12]  118 	jr	00105$
   41FF                     119 00104$:
                            120 ;src/sys/render.c:33: *pvmem = e->color;
   41FF 79            [ 4]  121 	ld	a, c
   4200 12            [ 7]  122 	ld	(de), a
   4201                     123 00105$:
                            124 ;src/sys/render.c:35: e->prevptr = pvmem;
   4201 DD 6E FE      [19]  125 	ld	l,-2 (ix)
   4204 DD 66 FF      [19]  126 	ld	h,-1 (ix)
   4207 73            [ 7]  127 	ld	(hl), e
   4208 23            [ 6]  128 	inc	hl
   4209 72            [ 7]  129 	ld	(hl), d
   420A                     130 00108$:
   420A DD F9         [10]  131 	ld	sp, ix
   420C DD E1         [14]  132 	pop	ix
   420E C9            [10]  133 	ret
                            134 ;src/sys/render.c:56: void sys_render_init() {
                            135 ;	---------------------------------
                            136 ; Function sys_render_init
                            137 ; ---------------------------------
   420F                     138 _sys_render_init::
                            139 ;src/sys/render.c:57: cpct_setVideoMode(0);
   420F 2E 00         [ 7]  140 	ld	l, #0x00
   4211 CD C1 42      [17]  141 	call	_cpct_setVideoMode
                            142 ;src/sys/render.c:58: cpct_setBorder(HW_BLACK);
   4214 21 10 14      [10]  143 	ld	hl, #0x1410
   4217 E5            [11]  144 	push	hl
   4218 CD 57 42      [17]  145 	call	_cpct_setPALColour
                            146 ;src/sys/render.c:59: cpct_setPalette(palette, 16);
   421B 21 10 00      [10]  147 	ld	hl, #0x0010
   421E E5            [11]  148 	push	hl
   421F 21 27 42      [10]  149 	ld	hl, #_palette
   4222 E5            [11]  150 	push	hl
   4223 CD 40 42      [17]  151 	call	_cpct_setPalette
   4226 C9            [10]  152 	ret
   4227                     153 _palette:
   4227 14                  154 	.db #0x14	; 20
   4228 0B                  155 	.db #0x0b	; 11
   4229 0A                  156 	.db #0x0a	; 10
   422A 1E                  157 	.db #0x1e	; 30
   422B 0B                  158 	.db #0x0b	; 11
   422C 0B                  159 	.db #0x0b	; 11
   422D 0B                  160 	.db #0x0b	; 11
   422E 0B                  161 	.db #0x0b	; 11
   422F 0B                  162 	.db #0x0b	; 11
   4230 0B                  163 	.db #0x0b	; 11
   4231 0B                  164 	.db #0x0b	; 11
   4232 0B                  165 	.db #0x0b	; 11
   4233 0B                  166 	.db #0x0b	; 11
   4234 0B                  167 	.db #0x0b	; 11
   4235 0B                  168 	.db #0x0b	; 11
   4236 0B                  169 	.db #0x0b	; 11
                            170 ;src/sys/render.c:68: void sys_render_update() {
                            171 ;	---------------------------------
                            172 ; Function sys_render_update
                            173 ; ---------------------------------
   4237                     174 _sys_render_update::
                            175 ;src/sys/render.c:69: man_entity_forall (sys_render_one_entity);
   4237 21 A6 41      [10]  176 	ld	hl, #_sys_render_one_entity
   423A E5            [11]  177 	push	hl
   423B CD 61 40      [17]  178 	call	_man_entity_forall
   423E F1            [10]  179 	pop	af
   423F C9            [10]  180 	ret
                            181 	.area _CODE
                            182 	.area _INITIALIZER
                            183 	.area _CABS (ABS)
