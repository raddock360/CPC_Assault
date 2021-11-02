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
                             11 	.globl _sys_render_init
                             12 	.globl _sys_render_one_entity
                             13 	.globl _man_entity_forall
                             14 	.globl _cpct_getScreenPtr
                             15 	.globl _cpct_setPALColour
                             16 	.globl _cpct_setVideoMode
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
   4161                      53 _sys_render_one_entity::
   4161 DD E5         [15]   54 	push	ix
   4163 DD 21 00 00   [14]   55 	ld	ix,#0
   4167 DD 39         [15]   56 	add	ix,sp
   4169 F5            [11]   57 	push	af
                             58 ;src/sys/render.c:15: if (e->prevptr != 0) *(e->prevptr) = 0;
   416A DD 4E 04      [19]   59 	ld	c,4 (ix)
   416D DD 46 05      [19]   60 	ld	b,5 (ix)
   4170 21 05 00      [10]   61 	ld	hl, #0x0005
   4173 09            [11]   62 	add	hl,bc
   4174 E3            [19]   63 	ex	(sp), hl
   4175 E1            [10]   64 	pop	hl
   4176 E5            [11]   65 	push	hl
   4177 5E            [ 7]   66 	ld	e, (hl)
   4178 23            [ 6]   67 	inc	hl
   4179 56            [ 7]   68 	ld	d, (hl)
   417A 7A            [ 4]   69 	ld	a, d
   417B B3            [ 4]   70 	or	a,e
   417C 28 02         [12]   71 	jr	Z,00102$
   417E AF            [ 4]   72 	xor	a, a
   417F 12            [ 7]   73 	ld	(de), a
   4180                      74 00102$:
                             75 ;src/sys/render.c:16: if (!(e->type & e_type_dead)) {
   4180 0A            [ 7]   76 	ld	a, (bc)
   4181 07            [ 4]   77 	rlca
   4182 38 1F         [12]   78 	jr	C,00105$
                             79 ;src/sys/render.c:17: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
   4184 69            [ 4]   80 	ld	l, c
   4185 60            [ 4]   81 	ld	h, b
   4186 23            [ 6]   82 	inc	hl
   4187 23            [ 6]   83 	inc	hl
   4188 56            [ 7]   84 	ld	d, (hl)
   4189 69            [ 4]   85 	ld	l, c
   418A 60            [ 4]   86 	ld	h, b
   418B 23            [ 6]   87 	inc	hl
   418C 7E            [ 7]   88 	ld	a, (hl)
   418D C5            [11]   89 	push	bc
   418E 5F            [ 4]   90 	ld	e, a
   418F D5            [11]   91 	push	de
   4190 21 00 C0      [10]   92 	ld	hl, #0xc000
   4193 E5            [11]   93 	push	hl
   4194 CD 91 42      [17]   94 	call	_cpct_getScreenPtr
   4197 EB            [ 4]   95 	ex	de,hl
   4198 FD E1         [14]   96 	pop	iy
   419A FD 7E 04      [19]   97 	ld	a, 4 (iy)
   419D 12            [ 7]   98 	ld	(de), a
                             99 ;src/sys/render.c:19: e->prevptr = pvmem;
   419E E1            [10]  100 	pop	hl
   419F E5            [11]  101 	push	hl
   41A0 73            [ 7]  102 	ld	(hl), e
   41A1 23            [ 6]  103 	inc	hl
   41A2 72            [ 7]  104 	ld	(hl), d
   41A3                     105 00105$:
   41A3 DD F9         [10]  106 	ld	sp, ix
   41A5 DD E1         [14]  107 	pop	ix
   41A7 C9            [10]  108 	ret
                            109 ;src/sys/render.c:33: void sys_render_init() {
                            110 ;	---------------------------------
                            111 ; Function sys_render_init
                            112 ; ---------------------------------
   41A8                     113 _sys_render_init::
                            114 ;src/sys/render.c:34: cpct_setVideoMode(0);
   41A8 2E 00         [ 7]  115 	ld	l, #0x00
   41AA CD 2F 42      [17]  116 	call	_cpct_setVideoMode
                            117 ;src/sys/render.c:35: cpct_setBorder(HW_BLACK);
   41AD 21 10 14      [10]  118 	ld	hl, #0x1410
   41B0 E5            [11]  119 	push	hl
   41B1 CD C5 41      [17]  120 	call	_cpct_setPALColour
                            121 ;src/sys/render.c:36: cpct_setPALColour(0, HW_BLACK);
   41B4 21 00 14      [10]  122 	ld	hl, #0x1400
   41B7 E5            [11]  123 	push	hl
   41B8 CD C5 41      [17]  124 	call	_cpct_setPALColour
   41BB C9            [10]  125 	ret
                            126 ;src/sys/render.c:44: void sys_render_update() {
                            127 ;	---------------------------------
                            128 ; Function sys_render_update
                            129 ; ---------------------------------
   41BC                     130 _sys_render_update::
                            131 ;src/sys/render.c:45: man_entity_forall (sys_render_one_entity);
   41BC 21 61 41      [10]  132 	ld	hl, #_sys_render_one_entity
   41BF E5            [11]  133 	push	hl
   41C0 CD 58 40      [17]  134 	call	_man_entity_forall
   41C3 F1            [10]  135 	pop	af
   41C4 C9            [10]  136 	ret
                            137 	.area _CODE
                            138 	.area _INITIALIZER
                            139 	.area _CABS (ABS)
