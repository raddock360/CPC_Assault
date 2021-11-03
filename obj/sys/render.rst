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
   417C                      55 _sys_render_one_entity::
   417C DD E5         [15]   56 	push	ix
   417E DD 21 00 00   [14]   57 	ld	ix,#0
   4182 DD 39         [15]   58 	add	ix,sp
   4184 F5            [11]   59 	push	af
                             60 ;src/sys/render.c:15: if (e->prevptr != 0) 
   4185 DD 4E 04      [19]   61 	ld	c,4 (ix)
   4188 DD 46 05      [19]   62 	ld	b,5 (ix)
   418B 21 05 00      [10]   63 	ld	hl, #0x0005
   418E 09            [11]   64 	add	hl,bc
   418F E3            [19]   65 	ex	(sp), hl
   4190 E1            [10]   66 	pop	hl
   4191 E5            [11]   67 	push	hl
   4192 5E            [ 7]   68 	ld	e, (hl)
   4193 23            [ 6]   69 	inc	hl
   4194 56            [ 7]   70 	ld	d, (hl)
   4195 7A            [ 4]   71 	ld	a, d
   4196 B3            [ 4]   72 	or	a,e
   4197 28 02         [12]   73 	jr	Z,00102$
                             74 ;src/sys/render.c:16: *(e->prevptr) = 0;
   4199 AF            [ 4]   75 	xor	a, a
   419A 12            [ 7]   76 	ld	(de), a
   419B                      77 00102$:
                             78 ;src/sys/render.c:18: if (!(e->type & e_type_dead)) {
   419B 0A            [ 7]   79 	ld	a, (bc)
   419C 07            [ 4]   80 	rlca
   419D 38 1F         [12]   81 	jr	C,00105$
                             82 ;src/sys/render.c:19: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
   419F 69            [ 4]   83 	ld	l, c
   41A0 60            [ 4]   84 	ld	h, b
   41A1 23            [ 6]   85 	inc	hl
   41A2 23            [ 6]   86 	inc	hl
   41A3 56            [ 7]   87 	ld	d, (hl)
   41A4 69            [ 4]   88 	ld	l, c
   41A5 60            [ 4]   89 	ld	h, b
   41A6 23            [ 6]   90 	inc	hl
   41A7 7E            [ 7]   91 	ld	a, (hl)
   41A8 C5            [11]   92 	push	bc
   41A9 5F            [ 4]   93 	ld	e, a
   41AA D5            [11]   94 	push	de
   41AB 21 00 C0      [10]   95 	ld	hl, #0xc000
   41AE E5            [11]   96 	push	hl
   41AF CD D7 42      [17]   97 	call	_cpct_getScreenPtr
   41B2 EB            [ 4]   98 	ex	de,hl
   41B3 FD E1         [14]   99 	pop	iy
   41B5 FD 7E 04      [19]  100 	ld	a, 4 (iy)
   41B8 12            [ 7]  101 	ld	(de), a
                            102 ;src/sys/render.c:21: e->prevptr = pvmem;
   41B9 E1            [10]  103 	pop	hl
   41BA E5            [11]  104 	push	hl
   41BB 73            [ 7]  105 	ld	(hl), e
   41BC 23            [ 6]  106 	inc	hl
   41BD 72            [ 7]  107 	ld	(hl), d
   41BE                     108 00105$:
   41BE DD F9         [10]  109 	ld	sp, ix
   41C0 DD E1         [14]  110 	pop	ix
   41C2 C9            [10]  111 	ret
                            112 ;src/sys/render.c:42: void sys_render_init() {
                            113 ;	---------------------------------
                            114 ; Function sys_render_init
                            115 ; ---------------------------------
   41C3                     116 _sys_render_init::
                            117 ;src/sys/render.c:43: cpct_setVideoMode(0);
   41C3 2E 00         [ 7]  118 	ld	l, #0x00
   41C5 CD 75 42      [17]  119 	call	_cpct_setVideoMode
                            120 ;src/sys/render.c:44: cpct_setBorder(HW_BLACK);
   41C8 21 10 14      [10]  121 	ld	hl, #0x1410
   41CB E5            [11]  122 	push	hl
   41CC CD 0B 42      [17]  123 	call	_cpct_setPALColour
                            124 ;src/sys/render.c:45: cpct_setPalette(palette, 16);
   41CF 21 10 00      [10]  125 	ld	hl, #0x0010
   41D2 E5            [11]  126 	push	hl
   41D3 21 DB 41      [10]  127 	ld	hl, #_palette
   41D6 E5            [11]  128 	push	hl
   41D7 CD F4 41      [17]  129 	call	_cpct_setPalette
   41DA C9            [10]  130 	ret
   41DB                     131 _palette:
   41DB 14                  132 	.db #0x14	; 20
   41DC 0B                  133 	.db #0x0b	; 11
   41DD 0B                  134 	.db #0x0b	; 11
   41DE 0B                  135 	.db #0x0b	; 11
   41DF 0B                  136 	.db #0x0b	; 11
   41E0 0B                  137 	.db #0x0b	; 11
   41E1 0B                  138 	.db #0x0b	; 11
   41E2 0B                  139 	.db #0x0b	; 11
   41E3 0B                  140 	.db #0x0b	; 11
   41E4 0B                  141 	.db #0x0b	; 11
   41E5 0B                  142 	.db #0x0b	; 11
   41E6 0B                  143 	.db #0x0b	; 11
   41E7 0B                  144 	.db #0x0b	; 11
   41E8 0B                  145 	.db #0x0b	; 11
   41E9 0B                  146 	.db #0x0b	; 11
   41EA 0B                  147 	.db #0x0b	; 11
                            148 ;src/sys/render.c:53: void sys_render_update() {
                            149 ;	---------------------------------
                            150 ; Function sys_render_update
                            151 ; ---------------------------------
   41EB                     152 _sys_render_update::
                            153 ;src/sys/render.c:54: man_entity_forall (sys_render_one_entity);
   41EB 21 7C 41      [10]  154 	ld	hl, #_sys_render_one_entity
   41EE E5            [11]  155 	push	hl
   41EF CD 61 40      [17]  156 	call	_man_entity_forall
   41F2 F1            [10]  157 	pop	af
   41F3 C9            [10]  158 	ret
                            159 	.area _CODE
                            160 	.area _INITIALIZER
                            161 	.area _CABS (ABS)
