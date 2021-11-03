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
   4186                      53 _sys_render_one_entity::
   4186 DD E5         [15]   54 	push	ix
   4188 DD 21 00 00   [14]   55 	ld	ix,#0
   418C DD 39         [15]   56 	add	ix,sp
   418E F5            [11]   57 	push	af
                             58 ;src/sys/render.c:15: if (e->prevptr != 0) 
   418F DD 4E 04      [19]   59 	ld	c,4 (ix)
   4192 DD 46 05      [19]   60 	ld	b,5 (ix)
   4195 21 05 00      [10]   61 	ld	hl, #0x0005
   4198 09            [11]   62 	add	hl,bc
   4199 E3            [19]   63 	ex	(sp), hl
   419A E1            [10]   64 	pop	hl
   419B E5            [11]   65 	push	hl
   419C 5E            [ 7]   66 	ld	e, (hl)
   419D 23            [ 6]   67 	inc	hl
   419E 56            [ 7]   68 	ld	d, (hl)
   419F 7A            [ 4]   69 	ld	a, d
   41A0 B3            [ 4]   70 	or	a,e
   41A1 28 02         [12]   71 	jr	Z,00102$
                             72 ;src/sys/render.c:16: *(e->prevptr) = 0;
   41A3 AF            [ 4]   73 	xor	a, a
   41A4 12            [ 7]   74 	ld	(de), a
   41A5                      75 00102$:
                             76 ;src/sys/render.c:18: if (!(e->type & e_type_dead)) {
   41A5 0A            [ 7]   77 	ld	a, (bc)
   41A6 07            [ 4]   78 	rlca
   41A7 38 1F         [12]   79 	jr	C,00105$
                             80 ;src/sys/render.c:19: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
   41A9 69            [ 4]   81 	ld	l, c
   41AA 60            [ 4]   82 	ld	h, b
   41AB 23            [ 6]   83 	inc	hl
   41AC 23            [ 6]   84 	inc	hl
   41AD 56            [ 7]   85 	ld	d, (hl)
   41AE 69            [ 4]   86 	ld	l, c
   41AF 60            [ 4]   87 	ld	h, b
   41B0 23            [ 6]   88 	inc	hl
   41B1 7E            [ 7]   89 	ld	a, (hl)
   41B2 C5            [11]   90 	push	bc
   41B3 5F            [ 4]   91 	ld	e, a
   41B4 D5            [11]   92 	push	de
   41B5 21 00 C0      [10]   93 	ld	hl, #0xc000
   41B8 E5            [11]   94 	push	hl
   41B9 CD B6 42      [17]   95 	call	_cpct_getScreenPtr
   41BC EB            [ 4]   96 	ex	de,hl
   41BD FD E1         [14]   97 	pop	iy
   41BF FD 7E 04      [19]   98 	ld	a, 4 (iy)
   41C2 12            [ 7]   99 	ld	(de), a
                            100 ;src/sys/render.c:21: e->prevptr = pvmem;
   41C3 E1            [10]  101 	pop	hl
   41C4 E5            [11]  102 	push	hl
   41C5 73            [ 7]  103 	ld	(hl), e
   41C6 23            [ 6]  104 	inc	hl
   41C7 72            [ 7]  105 	ld	(hl), d
   41C8                     106 00105$:
   41C8 DD F9         [10]  107 	ld	sp, ix
   41CA DD E1         [14]  108 	pop	ix
   41CC C9            [10]  109 	ret
                            110 ;src/sys/render.c:35: void sys_render_init() {
                            111 ;	---------------------------------
                            112 ; Function sys_render_init
                            113 ; ---------------------------------
   41CD                     114 _sys_render_init::
                            115 ;src/sys/render.c:36: cpct_setVideoMode(0);
   41CD 2E 00         [ 7]  116 	ld	l, #0x00
   41CF CD 54 42      [17]  117 	call	_cpct_setVideoMode
                            118 ;src/sys/render.c:37: cpct_setBorder(HW_BLACK);
   41D2 21 10 14      [10]  119 	ld	hl, #0x1410
   41D5 E5            [11]  120 	push	hl
   41D6 CD EA 41      [17]  121 	call	_cpct_setPALColour
                            122 ;src/sys/render.c:38: cpct_setPALColour(0, HW_BLACK);
   41D9 21 00 14      [10]  123 	ld	hl, #0x1400
   41DC E5            [11]  124 	push	hl
   41DD CD EA 41      [17]  125 	call	_cpct_setPALColour
   41E0 C9            [10]  126 	ret
                            127 ;src/sys/render.c:46: void sys_render_update() {
                            128 ;	---------------------------------
                            129 ; Function sys_render_update
                            130 ; ---------------------------------
   41E1                     131 _sys_render_update::
                            132 ;src/sys/render.c:47: man_entity_forall (sys_render_one_entity);
   41E1 21 86 41      [10]  133 	ld	hl, #_sys_render_one_entity
   41E4 E5            [11]  134 	push	hl
   41E5 CD 61 40      [17]  135 	call	_man_entity_forall
   41E8 F1            [10]  136 	pop	af
   41E9 C9            [10]  137 	ret
                            138 	.area _CODE
                            139 	.area _INITIALIZER
                            140 	.area _CABS (ABS)
