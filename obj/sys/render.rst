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
   4106                      50 _sys_render_one_entity::
   4106 DD E5         [15]   51 	push	ix
   4108 DD 21 00 00   [14]   52 	ld	ix,#0
   410C DD 39         [15]   53 	add	ix,sp
                             54 ;src/sys/render.c:5: u8* pvmem = cpct_getScreenPtr (CPCT_VMEM_START, e->x, e->y);
   410E DD 5E 04      [19]   55 	ld	e,4 (ix)
   4111 DD 56 05      [19]   56 	ld	d,5 (ix)
   4114 6B            [ 4]   57 	ld	l, e
   4115 62            [ 4]   58 	ld	h, d
   4116 23            [ 6]   59 	inc	hl
   4117 23            [ 6]   60 	inc	hl
   4118 46            [ 7]   61 	ld	b, (hl)
   4119 6B            [ 4]   62 	ld	l, e
   411A 62            [ 4]   63 	ld	h, d
   411B 23            [ 6]   64 	inc	hl
   411C 7E            [ 7]   65 	ld	a, (hl)
   411D D5            [11]   66 	push	de
   411E C5            [11]   67 	push	bc
   411F 33            [ 6]   68 	inc	sp
   4120 F5            [11]   69 	push	af
   4121 33            [ 6]   70 	inc	sp
   4122 21 00 C0      [10]   71 	ld	hl, #0xc000
   4125 E5            [11]   72 	push	hl
   4126 CD 09 42      [17]   73 	call	_cpct_getScreenPtr
   4129 4D            [ 4]   74 	ld	c, l
   412A 44            [ 4]   75 	ld	b, h
   412B FD E1         [14]   76 	pop	iy
   412D FD 7E 04      [19]   77 	ld	a, 4 (iy)
   4130 02            [ 7]   78 	ld	(bc), a
   4131 DD E1         [14]   79 	pop	ix
   4133 C9            [10]   80 	ret
                             81 ;src/sys/render.c:9: void sys_render_update() {
                             82 ;	---------------------------------
                             83 ; Function sys_render_update
                             84 ; ---------------------------------
   4134                      85 _sys_render_update::
                             86 ;src/sys/render.c:10: man_entity_forall (sys_render_one_entity);
   4134 21 06 41      [10]   87 	ld	hl, #_sys_render_one_entity
   4137 E5            [11]   88 	push	hl
   4138 CD 9F 40      [17]   89 	call	_man_entity_forall
   413B F1            [10]   90 	pop	af
   413C C9            [10]   91 	ret
                             92 	.area _CODE
                             93 	.area _INITIALIZER
                             94 	.area _CABS (ABS)
