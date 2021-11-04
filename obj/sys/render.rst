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
                             60 ;src/sys/render.c:18: if (e->prevptr != 0) 	
   41AF DD 4E 04      [19]   61 	ld	c,4 (ix)
   41B2 DD 46 05      [19]   62 	ld	b,5 (ix)
   41B5 21 05 00      [10]   63 	ld	hl, #0x0005
   41B8 09            [11]   64 	add	hl,bc
   41B9 E3            [19]   65 	ex	(sp), hl
   41BA E1            [10]   66 	pop	hl
   41BB E5            [11]   67 	push	hl
   41BC 5E            [ 7]   68 	ld	e, (hl)
   41BD 23            [ 6]   69 	inc	hl
   41BE 56            [ 7]   70 	ld	d, (hl)
   41BF 7A            [ 4]   71 	ld	a, d
   41C0 B3            [ 4]   72 	or	a,e
   41C1 28 02         [12]   73 	jr	Z,00102$
                             74 ;src/sys/render.c:19: *(e->prevptr) = 0;
   41C3 AF            [ 4]   75 	xor	a, a
   41C4 12            [ 7]   76 	ld	(de), a
   41C5                      77 00102$:
                             78 ;src/sys/render.c:23: if (!(e->type & e_type_dead)) {
   41C5 0A            [ 7]   79 	ld	a, (bc)
   41C6 07            [ 4]   80 	rlca
   41C7 38 1F         [12]   81 	jr	C,00105$
                             82 ;src/sys/render.c:24: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
   41C9 69            [ 4]   83 	ld	l, c
   41CA 60            [ 4]   84 	ld	h, b
   41CB 23            [ 6]   85 	inc	hl
   41CC 23            [ 6]   86 	inc	hl
   41CD 56            [ 7]   87 	ld	d, (hl)
   41CE 69            [ 4]   88 	ld	l, c
   41CF 60            [ 4]   89 	ld	h, b
   41D0 23            [ 6]   90 	inc	hl
   41D1 7E            [ 7]   91 	ld	a, (hl)
   41D2 C5            [11]   92 	push	bc
   41D3 5F            [ 4]   93 	ld	e, a
   41D4 D5            [11]   94 	push	de
   41D5 21 00 C0      [10]   95 	ld	hl, #0xc000
   41D8 E5            [11]   96 	push	hl
   41D9 CD 01 43      [17]   97 	call	_cpct_getScreenPtr
   41DC EB            [ 4]   98 	ex	de,hl
   41DD FD E1         [14]   99 	pop	iy
   41DF FD 7E 04      [19]  100 	ld	a, 4 (iy)
   41E2 12            [ 7]  101 	ld	(de), a
                            102 ;src/sys/render.c:26: e->prevptr = pvmem;
   41E3 E1            [10]  103 	pop	hl
   41E4 E5            [11]  104 	push	hl
   41E5 73            [ 7]  105 	ld	(hl), e
   41E6 23            [ 6]  106 	inc	hl
   41E7 72            [ 7]  107 	ld	(hl), d
   41E8                     108 00105$:
   41E8 DD F9         [10]  109 	ld	sp, ix
   41EA DD E1         [14]  110 	pop	ix
   41EC C9            [10]  111 	ret
                            112 ;src/sys/render.c:47: void sys_render_init() {
                            113 ;	---------------------------------
                            114 ; Function sys_render_init
                            115 ; ---------------------------------
   41ED                     116 _sys_render_init::
                            117 ;src/sys/render.c:48: cpct_setVideoMode(0);
   41ED 2E 00         [ 7]  118 	ld	l, #0x00
   41EF CD 9F 42      [17]  119 	call	_cpct_setVideoMode
                            120 ;src/sys/render.c:49: cpct_setBorder(HW_BLACK);
   41F2 21 10 14      [10]  121 	ld	hl, #0x1410
   41F5 E5            [11]  122 	push	hl
   41F6 CD 35 42      [17]  123 	call	_cpct_setPALColour
                            124 ;src/sys/render.c:50: cpct_setPalette(palette, 16);
   41F9 21 10 00      [10]  125 	ld	hl, #0x0010
   41FC E5            [11]  126 	push	hl
   41FD 21 05 42      [10]  127 	ld	hl, #_palette
   4200 E5            [11]  128 	push	hl
   4201 CD 1E 42      [17]  129 	call	_cpct_setPalette
   4204 C9            [10]  130 	ret
   4205                     131 _palette:
   4205 14                  132 	.db #0x14	; 20
   4206 0B                  133 	.db #0x0b	; 11
   4207 0A                  134 	.db #0x0a	; 10
   4208 1E                  135 	.db #0x1e	; 30
   4209 0B                  136 	.db #0x0b	; 11
   420A 0B                  137 	.db #0x0b	; 11
   420B 0B                  138 	.db #0x0b	; 11
   420C 0B                  139 	.db #0x0b	; 11
   420D 0B                  140 	.db #0x0b	; 11
   420E 0B                  141 	.db #0x0b	; 11
   420F 0B                  142 	.db #0x0b	; 11
   4210 0B                  143 	.db #0x0b	; 11
   4211 0B                  144 	.db #0x0b	; 11
   4212 0B                  145 	.db #0x0b	; 11
   4213 0B                  146 	.db #0x0b	; 11
   4214 0B                  147 	.db #0x0b	; 11
                            148 ;src/sys/render.c:59: void sys_render_update() {
                            149 ;	---------------------------------
                            150 ; Function sys_render_update
                            151 ; ---------------------------------
   4215                     152 _sys_render_update::
                            153 ;src/sys/render.c:60: man_entity_forall (sys_render_one_entity);
   4215 21 A6 41      [10]  154 	ld	hl, #_sys_render_one_entity
   4218 E5            [11]  155 	push	hl
   4219 CD 61 40      [17]  156 	call	_man_entity_forall
   421C F1            [10]  157 	pop	af
   421D C9            [10]  158 	ret
                            159 	.area _CODE
                            160 	.area _INITIALIZER
                            161 	.area _CABS (ABS)
