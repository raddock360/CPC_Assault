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
                             14 	.globl _sys_render_update
                             15 ;--------------------------------------------------------
                             16 ; special function registers
                             17 ;--------------------------------------------------------
                             18 ;--------------------------------------------------------
                             19 ; ram data
                             20 ;--------------------------------------------------------
                             21 	.area _DATA
                             22 ;--------------------------------------------------------
                             23 ; ram data
                             24 ;--------------------------------------------------------
                             25 	.area _INITIALIZED
                             26 ;--------------------------------------------------------
                             27 ; absolute external ram data
                             28 ;--------------------------------------------------------
                             29 	.area _DABS (ABS)
                             30 ;--------------------------------------------------------
                             31 ; global & static initialisations
                             32 ;--------------------------------------------------------
                             33 	.area _HOME
                             34 	.area _GSINIT
                             35 	.area _GSFINAL
                             36 	.area _GSINIT
                             37 ;--------------------------------------------------------
                             38 ; Home
                             39 ;--------------------------------------------------------
                             40 	.area _HOME
                             41 	.area _HOME
                             42 ;--------------------------------------------------------
                             43 ; code
                             44 ;--------------------------------------------------------
                             45 	.area _CODE
                             46 ;src/sys/render.c:4: void sys_render_one_entity (Entity_t* e) {
                             47 ;	---------------------------------
                             48 ; Function sys_render_one_entity
                             49 ; ---------------------------------
   40D1                      50 _sys_render_one_entity::
   40D1 DD E5         [15]   51 	push	ix
   40D3 DD 21 00 00   [14]   52 	ld	ix,#0
   40D7 DD 39         [15]   53 	add	ix,sp
   40D9 F5            [11]   54 	push	af
   40DA F5            [11]   55 	push	af
                             56 ;src/sys/render.c:5: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x - e->vx, e->y);
   40DB DD 5E 04      [19]   57 	ld	e,4 (ix)
   40DE DD 56 05      [19]   58 	ld	d,5 (ix)
   40E1 21 02 00      [10]   59 	ld	hl, #0x0002
   40E4 19            [11]   60 	add	hl,de
   40E5 DD 75 FE      [19]   61 	ld	-2 (ix), l
   40E8 DD 74 FF      [19]   62 	ld	-1 (ix), h
   40EB 46            [ 7]   63 	ld	b, (hl)
   40EC 21 01 00      [10]   64 	ld	hl, #0x0001
   40EF 19            [11]   65 	add	hl,de
   40F0 E3            [19]   66 	ex	(sp), hl
   40F1 E1            [10]   67 	pop	hl
   40F2 E5            [11]   68 	push	hl
   40F3 4E            [ 7]   69 	ld	c, (hl)
   40F4 6B            [ 4]   70 	ld	l, e
   40F5 62            [ 4]   71 	ld	h, d
   40F6 23            [ 6]   72 	inc	hl
   40F7 23            [ 6]   73 	inc	hl
   40F8 23            [ 6]   74 	inc	hl
   40F9 6E            [ 7]   75 	ld	l, (hl)
   40FA 79            [ 4]   76 	ld	a, c
   40FB 95            [ 4]   77 	sub	a, l
   40FC D5            [11]   78 	push	de
   40FD C5            [11]   79 	push	bc
   40FE 33            [ 6]   80 	inc	sp
   40FF F5            [11]   81 	push	af
   4100 33            [ 6]   82 	inc	sp
   4101 21 00 C0      [10]   83 	ld	hl, #0xc000
   4104 E5            [11]   84 	push	hl
   4105 CD 84 42      [17]   85 	call	_cpct_getScreenPtr
   4108 D1            [10]   86 	pop	de
                             87 ;src/sys/render.c:6: *pvmem = 0;
   4109 36 00         [10]   88 	ld	(hl), #0x00
                             89 ;src/sys/render.c:7: pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
   410B DD 6E FE      [19]   90 	ld	l,-2 (ix)
   410E DD 66 FF      [19]   91 	ld	h,-1 (ix)
   4111 7E            [ 7]   92 	ld	a, (hl)
   4112 E1            [10]   93 	pop	hl
   4113 E5            [11]   94 	push	hl
   4114 46            [ 7]   95 	ld	b, (hl)
   4115 D5            [11]   96 	push	de
   4116 F5            [11]   97 	push	af
   4117 33            [ 6]   98 	inc	sp
   4118 C5            [11]   99 	push	bc
   4119 33            [ 6]  100 	inc	sp
   411A 21 00 C0      [10]  101 	ld	hl, #0xc000
   411D E5            [11]  102 	push	hl
   411E CD 84 42      [17]  103 	call	_cpct_getScreenPtr
   4121 4D            [ 4]  104 	ld	c, l
   4122 44            [ 4]  105 	ld	b, h
   4123 FD E1         [14]  106 	pop	iy
   4125 FD 7E 04      [19]  107 	ld	a, 4 (iy)
   4128 02            [ 7]  108 	ld	(bc), a
   4129 DD F9         [10]  109 	ld	sp, ix
   412B DD E1         [14]  110 	pop	ix
   412D C9            [10]  111 	ret
                            112 ;src/sys/render.c:11: void sys_render_update() {
                            113 ;	---------------------------------
                            114 ; Function sys_render_update
                            115 ; ---------------------------------
   412E                     116 _sys_render_update::
                            117 ;src/sys/render.c:12: man_entity_forall (sys_render_one_entity);
   412E 21 D1 40      [10]  118 	ld	hl, #_sys_render_one_entity
   4131 E5            [11]  119 	push	hl
   4132 CD 5D 41      [17]  120 	call	_man_entity_forall
   4135 F1            [10]  121 	pop	af
   4136 C9            [10]  122 	ret
                            123 	.area _CODE
                            124 	.area _INITIALIZER
                            125 	.area _CABS (ABS)
