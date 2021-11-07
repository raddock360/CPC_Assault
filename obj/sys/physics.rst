                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module physics
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _sys_physics_update_one_entity
                             12 	.globl _man_entity_set4destruction
                             13 	.globl _man_entity_forall
                             14 	.globl _sys_physics_update
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
                             46 ;src/sys/physics.c:4: void sys_physics_update_one_entity (Entity_t* e) {
                             47 ;	---------------------------------
                             48 ; Function sys_physics_update_one_entity
                             49 ; ---------------------------------
   40A5                      50 _sys_physics_update_one_entity::
   40A5 DD E5         [15]   51 	push	ix
   40A7 DD 21 00 00   [14]   52 	ld	ix,#0
   40AB DD 39         [15]   53 	add	ix,sp
   40AD F5            [11]   54 	push	af
                             55 ;src/sys/physics.c:5: u8 newx = e->x + e->vx;
   40AE DD 5E 04      [19]   56 	ld	e,4 (ix)
   40B1 DD 56 05      [19]   57 	ld	d,5 (ix)
   40B4 4B            [ 4]   58 	ld	c, e
   40B5 42            [ 4]   59 	ld	b, d
   40B6 03            [ 6]   60 	inc	bc
   40B7 0A            [ 7]   61 	ld	a, (bc)
   40B8 DD 77 FF      [19]   62 	ld	-1 (ix), a
   40BB 6B            [ 4]   63 	ld	l, e
   40BC 62            [ 4]   64 	ld	h, d
   40BD 23            [ 6]   65 	inc	hl
   40BE 23            [ 6]   66 	inc	hl
   40BF 23            [ 6]   67 	inc	hl
   40C0 6E            [ 7]   68 	ld	l, (hl)
   40C1 DD 7E FF      [19]   69 	ld	a, -1 (ix)
   40C4 85            [ 4]   70 	add	a, l
   40C5 DD 77 FE      [19]   71 	ld	-2 (ix), a
                             72 ;src/sys/physics.c:6: if(newx > e->x) 
   40C8 DD 7E FF      [19]   73 	ld	a, -1 (ix)
   40CB DD 96 FE      [19]   74 	sub	a, -2 (ix)
   40CE 30 07         [12]   75 	jr	NC,00102$
                             76 ;src/sys/physics.c:7: man_entity_set4destruction(e);
   40D0 C5            [11]   77 	push	bc
   40D1 D5            [11]   78 	push	de
   40D2 CD 10 42      [17]   79 	call	_man_entity_set4destruction
   40D5 F1            [10]   80 	pop	af
   40D6 C1            [10]   81 	pop	bc
   40D7                      82 00102$:
                             83 ;src/sys/physics.c:8: e->x = newx;
   40D7 DD 7E FE      [19]   84 	ld	a, -2 (ix)
   40DA 02            [ 7]   85 	ld	(bc), a
   40DB DD F9         [10]   86 	ld	sp, ix
   40DD DD E1         [14]   87 	pop	ix
   40DF C9            [10]   88 	ret
                             89 ;src/sys/physics.c:11: void sys_physics_update() {
                             90 ;	---------------------------------
                             91 ; Function sys_physics_update
                             92 ; ---------------------------------
   40E0                      93 _sys_physics_update::
                             94 ;src/sys/physics.c:13: man_entity_forall (sys_physics_update_one_entity);
   40E0 21 A5 40      [10]   95 	ld	hl, #_sys_physics_update_one_entity
   40E3 E5            [11]   96 	push	hl
   40E4 CD B0 41      [17]   97 	call	_man_entity_forall
   40E7 F1            [10]   98 	pop	af
   40E8 C9            [10]   99 	ret
                            100 	.area _CODE
                            101 	.area _INITIALIZER
                            102 	.area _CABS (ABS)
