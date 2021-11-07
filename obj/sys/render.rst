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
   40E9                      55 _sys_render_one_entity::
   40E9 DD E5         [15]   56 	push	ix
   40EB DD 21 00 00   [14]   57 	ld	ix,#0
   40EF DD 39         [15]   58 	add	ix,sp
   40F1 F5            [11]   59 	push	af
   40F2 3B            [ 6]   60 	dec	sp
                             61 ;src/sys/render.c:21: if (e->prevptr != 0) 	
   40F3 DD 4E 04      [19]   62 	ld	c,4 (ix)
   40F6 DD 46 05      [19]   63 	ld	b,5 (ix)
   40F9 21 05 00      [10]   64 	ld	hl, #0x0005
   40FC 09            [11]   65 	add	hl,bc
   40FD E3            [19]   66 	ex	(sp), hl
   40FE E1            [10]   67 	pop	hl
   40FF E5            [11]   68 	push	hl
   4100 5E            [ 7]   69 	ld	e, (hl)
   4101 23            [ 6]   70 	inc	hl
   4102 56            [ 7]   71 	ld	d, (hl)
   4103 7A            [ 4]   72 	ld	a, d
   4104 B3            [ 4]   73 	or	a,e
   4105 28 02         [12]   74 	jr	Z,00102$
                             75 ;src/sys/render.c:22: *(e->prevptr) = 0;
   4107 AF            [ 4]   76 	xor	a, a
   4108 12            [ 7]   77 	ld	(de), a
   4109                      78 00102$:
                             79 ;src/sys/render.c:26: if (!(e->type & e_type_dead)) {
   4109 0A            [ 7]   80 	ld	a, (bc)
   410A 07            [ 4]   81 	rlca
   410B 38 39         [12]   82 	jr	C,00108$
                             83 ;src/sys/render.c:27: xPixelCoord = e->x;
   410D 69            [ 4]   84 	ld	l, c
   410E 60            [ 4]   85 	ld	h, b
   410F 23            [ 6]   86 	inc	hl
   4110 56            [ 7]   87 	ld	d, (hl)
                             88 ;src/sys/render.c:28: xByteCoord = (xPixelCoord / 2) + (xPixelCoord % 2);
   4111 5A            [ 4]   89 	ld	e, d
   4112 CB 3B         [ 8]   90 	srl	e
   4114 7A            [ 4]   91 	ld	a, d
   4115 E6 01         [ 7]   92 	and	a, #0x01
   4117 DD 77 FF      [19]   93 	ld	-1 (ix), a
   411A 7B            [ 4]   94 	ld	a, e
   411B DD 86 FF      [19]   95 	add	a, -1 (ix)
                             96 ;src/sys/render.c:29: pvmem = cpct_getScreenPtr (CPCT_VMEM_START, xByteCoord, e->y);
   411E 69            [ 4]   97 	ld	l, c
   411F 60            [ 4]   98 	ld	h, b
   4120 23            [ 6]   99 	inc	hl
   4121 23            [ 6]  100 	inc	hl
   4122 56            [ 7]  101 	ld	d, (hl)
   4123 C5            [11]  102 	push	bc
   4124 5F            [ 4]  103 	ld	e, a
   4125 D5            [11]  104 	push	de
   4126 21 00 C0      [10]  105 	ld	hl, #0xc000
   4129 E5            [11]  106 	push	hl
   412A CD 1C 43      [17]  107 	call	_cpct_getScreenPtr
   412D EB            [ 4]  108 	ex	de,hl
   412E FD E1         [14]  109 	pop	iy
   4130 FD 4E 04      [19]  110 	ld	c, 4 (iy)
                            111 ;src/sys/render.c:30: if( ( xPixelCoord % 2) == 0 ) {
   4133 DD 7E FF      [19]  112 	ld	a, -1 (ix)
   4136 B7            [ 4]  113 	or	a, a
   4137 20 06         [12]  114 	jr	NZ,00104$
                            115 ;src/sys/render.c:31: *pvmem = e->color >> 1;	
   4139 79            [ 4]  116 	ld	a,c
   413A CB 3F         [ 8]  117 	srl	a
   413C 12            [ 7]  118 	ld	(de), a
   413D 18 02         [12]  119 	jr	00105$
   413F                     120 00104$:
                            121 ;src/sys/render.c:33: *pvmem = e->color;
   413F 79            [ 4]  122 	ld	a, c
   4140 12            [ 7]  123 	ld	(de), a
   4141                     124 00105$:
                            125 ;src/sys/render.c:35: e->prevptr = pvmem;
   4141 E1            [10]  126 	pop	hl
   4142 E5            [11]  127 	push	hl
   4143 73            [ 7]  128 	ld	(hl), e
   4144 23            [ 6]  129 	inc	hl
   4145 72            [ 7]  130 	ld	(hl), d
   4146                     131 00108$:
   4146 DD F9         [10]  132 	ld	sp, ix
   4148 DD E1         [14]  133 	pop	ix
   414A C9            [10]  134 	ret
                            135 ;src/sys/render.c:56: void sys_render_init() {
                            136 ;	---------------------------------
                            137 ; Function sys_render_init
                            138 ; ---------------------------------
   414B                     139 _sys_render_init::
                            140 ;src/sys/render.c:57: cpct_setVideoMode(0);
   414B 2E 00         [ 7]  141 	ld	l, #0x00
   414D CD BA 42      [17]  142 	call	_cpct_setVideoMode
                            143 ;src/sys/render.c:58: cpct_setBorder(HW_BLACK);
   4150 21 10 14      [10]  144 	ld	hl, #0x1410
   4153 E5            [11]  145 	push	hl
   4154 CD 50 42      [17]  146 	call	_cpct_setPALColour
                            147 ;src/sys/render.c:59: cpct_setPalette(palette, 16);
   4157 21 10 00      [10]  148 	ld	hl, #0x0010
   415A E5            [11]  149 	push	hl
   415B 21 63 41      [10]  150 	ld	hl, #_palette
   415E E5            [11]  151 	push	hl
   415F CD 39 42      [17]  152 	call	_cpct_setPalette
   4162 C9            [10]  153 	ret
   4163                     154 _palette:
   4163 14                  155 	.db #0x14	; 20
   4164 0B                  156 	.db #0x0b	; 11
   4165 0A                  157 	.db #0x0a	; 10
   4166 1E                  158 	.db #0x1e	; 30
   4167 0B                  159 	.db #0x0b	; 11
   4168 0B                  160 	.db #0x0b	; 11
   4169 0B                  161 	.db #0x0b	; 11
   416A 0B                  162 	.db #0x0b	; 11
   416B 0B                  163 	.db #0x0b	; 11
   416C 0B                  164 	.db #0x0b	; 11
   416D 0B                  165 	.db #0x0b	; 11
   416E 0B                  166 	.db #0x0b	; 11
   416F 0B                  167 	.db #0x0b	; 11
   4170 0B                  168 	.db #0x0b	; 11
   4171 0B                  169 	.db #0x0b	; 11
   4172 0B                  170 	.db #0x0b	; 11
                            171 ;src/sys/render.c:68: void sys_render_update() {
                            172 ;	---------------------------------
                            173 ; Function sys_render_update
                            174 ; ---------------------------------
   4173                     175 _sys_render_update::
                            176 ;src/sys/render.c:69: man_entity_forall (sys_render_one_entity);
   4173 21 E9 40      [10]  177 	ld	hl, #_sys_render_one_entity
   4176 E5            [11]  178 	push	hl
   4177 CD B0 41      [17]  179 	call	_man_entity_forall
   417A F1            [10]  180 	pop	af
   417B C9            [10]  181 	ret
                            182 	.area _CODE
                            183 	.area _INITIALIZER
                            184 	.area _CABS (ABS)
