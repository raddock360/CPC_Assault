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
                             15 	.globl _cpct_setVideoMode
                             16 	.globl _sys_render_init
                             17 	.globl _sys_render_update
                             18 ;--------------------------------------------------------
                             19 ; special function registers
                             20 ;--------------------------------------------------------
                             21 ;--------------------------------------------------------
                             22 ; ram data
                             23 ;--------------------------------------------------------
                             24 	.area _DATA
                             25 ;--------------------------------------------------------
                             26 ; ram data
                             27 ;--------------------------------------------------------
                             28 	.area _INITIALIZED
                             29 ;--------------------------------------------------------
                             30 ; absolute external ram data
                             31 ;--------------------------------------------------------
                             32 	.area _DABS (ABS)
                             33 ;--------------------------------------------------------
                             34 ; global & static initialisations
                             35 ;--------------------------------------------------------
                             36 	.area _HOME
                             37 	.area _GSINIT
                             38 	.area _GSFINAL
                             39 	.area _GSINIT
                             40 ;--------------------------------------------------------
                             41 ; Home
                             42 ;--------------------------------------------------------
                             43 	.area _HOME
                             44 	.area _HOME
                             45 ;--------------------------------------------------------
                             46 ; code
                             47 ;--------------------------------------------------------
                             48 	.area _CODE
                             49 ;src/sys/render.c:14: void sys_render_one_entity (Entity_t* e) {
                             50 ;	---------------------------------
                             51 ; Function sys_render_one_entity
                             52 ; ---------------------------------
   40C4                      53 _sys_render_one_entity::
   40C4 DD E5         [15]   54 	push	ix
   40C6 DD 21 00 00   [14]   55 	ld	ix,#0
   40CA DD 39         [15]   56 	add	ix,sp
   40CC F5            [11]   57 	push	af
                             58 ;src/sys/render.c:15: if (e->prevptr != 0) *(e->prevptr) = 0;
   40CD DD 4E 04      [19]   59 	ld	c,4 (ix)
   40D0 DD 46 05      [19]   60 	ld	b,5 (ix)
   40D3 21 05 00      [10]   61 	ld	hl, #0x0005
   40D6 09            [11]   62 	add	hl,bc
   40D7 E3            [19]   63 	ex	(sp), hl
   40D8 E1            [10]   64 	pop	hl
   40D9 E5            [11]   65 	push	hl
   40DA 5E            [ 7]   66 	ld	e, (hl)
   40DB 23            [ 6]   67 	inc	hl
   40DC 56            [ 7]   68 	ld	d, (hl)
   40DD 7A            [ 4]   69 	ld	a, d
   40DE B3            [ 4]   70 	or	a,e
   40DF 28 02         [12]   71 	jr	Z,00102$
   40E1 AF            [ 4]   72 	xor	a, a
   40E2 12            [ 7]   73 	ld	(de), a
   40E3                      74 00102$:
                             75 ;src/sys/render.c:16: if (!(e->type & e_type_dead)) {
   40E3 0A            [ 7]   76 	ld	a, (bc)
   40E4 07            [ 4]   77 	rlca
   40E5 38 1F         [12]   78 	jr	C,00105$
                             79 ;src/sys/render.c:17: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
   40E7 69            [ 4]   80 	ld	l, c
   40E8 60            [ 4]   81 	ld	h, b
   40E9 23            [ 6]   82 	inc	hl
   40EA 23            [ 6]   83 	inc	hl
   40EB 56            [ 7]   84 	ld	d, (hl)
   40EC 69            [ 4]   85 	ld	l, c
   40ED 60            [ 4]   86 	ld	h, b
   40EE 23            [ 6]   87 	inc	hl
   40EF 7E            [ 7]   88 	ld	a, (hl)
   40F0 C5            [11]   89 	push	bc
   40F1 5F            [ 4]   90 	ld	e, a
   40F2 D5            [11]   91 	push	de
   40F3 21 00 C0      [10]   92 	ld	hl, #0xc000
   40F6 E5            [11]   93 	push	hl
   40F7 CD AC 42      [17]   94 	call	_cpct_getScreenPtr
   40FA EB            [ 4]   95 	ex	de,hl
   40FB FD E1         [14]   96 	pop	iy
   40FD FD 7E 04      [19]   97 	ld	a, 4 (iy)
   4100 12            [ 7]   98 	ld	(de), a
                             99 ;src/sys/render.c:19: e->prevptr = pvmem;
   4101 E1            [10]  100 	pop	hl
   4102 E5            [11]  101 	push	hl
   4103 73            [ 7]  102 	ld	(hl), e
   4104 23            [ 6]  103 	inc	hl
   4105 72            [ 7]  104 	ld	(hl), d
   4106                     105 00105$:
   4106 DD F9         [10]  106 	ld	sp, ix
   4108 DD E1         [14]  107 	pop	ix
   410A C9            [10]  108 	ret
                            109 ;src/sys/render.c:33: void sys_render_init() {
                            110 ;	---------------------------------
                            111 ; Function sys_render_init
                            112 ; ---------------------------------
   410B                     113 _sys_render_init::
                            114 ;src/sys/render.c:34: cpct_setVideoMode(0);
   410B 2E 00         [ 7]  115 	ld	l, #0x00
   410D CD 4A 42      [17]  116 	call	_cpct_setVideoMode
                            117 ;src/sys/render.c:35: cpct_setBorder(HW_BLACK);
   4110 21 10 14      [10]  118 	ld	hl, #0x1410
   4113 E5            [11]  119 	push	hl
   4114 CD E0 41      [17]  120 	call	_cpct_setPALColour
                            121 ;src/sys/render.c:36: cpct_setPALColour(0, HW_BLACK);
   4117 21 00 14      [10]  122 	ld	hl, #0x1400
   411A E5            [11]  123 	push	hl
   411B CD E0 41      [17]  124 	call	_cpct_setPALColour
   411E C9            [10]  125 	ret
                            126 ;src/sys/render.c:44: void sys_render_update() {
                            127 ;	---------------------------------
                            128 ; Function sys_render_update
                            129 ; ---------------------------------
   411F                     130 _sys_render_update::
                            131 ;src/sys/render.c:45: man_entity_forall (sys_render_one_entity);
   411F 21 C4 40      [10]  132 	ld	hl, #_sys_render_one_entity
   4122 E5            [11]  133 	push	hl
   4123 CD 57 41      [17]  134 	call	_man_entity_forall
   4126 F1            [10]  135 	pop	af
   4127 C9            [10]  136 	ret
                            137 	.area _CODE
                            138 	.area _INITIALIZER
                            139 	.area _CABS (ABS)
