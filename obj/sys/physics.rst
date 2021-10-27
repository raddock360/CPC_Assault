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
                             12 	.globl _man_entity_forall
                             13 	.globl _man_entity_destroy
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
   40C2                      50 _sys_physics_update_one_entity::
   40C2 DD E5         [15]   51 	push	ix
   40C4 DD 21 00 00   [14]   52 	ld	ix,#0
   40C8 DD 39         [15]   53 	add	ix,sp
   40CA F5            [11]   54 	push	af
                             55 ;src/sys/physics.c:5: u8 newx = e->x + e->vx;
   40CB DD 4E 04      [19]   56 	ld	c,4 (ix)
   40CE DD 46 05      [19]   57 	ld	b,5 (ix)
   40D1 59            [ 4]   58 	ld	e, c
   40D2 50            [ 4]   59 	ld	d, b
   40D3 13            [ 6]   60 	inc	de
   40D4 1A            [ 7]   61 	ld	a, (de)
   40D5 DD 77 FF      [19]   62 	ld	-1 (ix), a
   40D8 69            [ 4]   63 	ld	l, c
   40D9 60            [ 4]   64 	ld	h, b
   40DA 23            [ 6]   65 	inc	hl
   40DB 23            [ 6]   66 	inc	hl
   40DC 23            [ 6]   67 	inc	hl
   40DD 6E            [ 7]   68 	ld	l, (hl)
   40DE DD 7E FF      [19]   69 	ld	a, -1 (ix)
   40E1 85            [ 4]   70 	add	a, l
   40E2 DD 77 FE      [19]   71 	ld	-2 (ix), a
                             72 ;src/sys/physics.c:6: if(newx > e->x) 
   40E5 DD 7E FF      [19]   73 	ld	a, -1 (ix)
   40E8 DD 96 FE      [19]   74 	sub	a, -2 (ix)
   40EB 30 07         [12]   75 	jr	NC,00102$
                             76 ;src/sys/physics.c:7: man_entity_destroy(e);
   40ED C5            [11]   77 	push	bc
   40EE CD BB 40      [17]   78 	call	_man_entity_destroy
   40F1 F1            [10]   79 	pop	af
   40F2 18 04         [12]   80 	jr	00104$
   40F4                      81 00102$:
                             82 ;src/sys/physics.c:10: e->x = newx;
   40F4 DD 7E FE      [19]   83 	ld	a, -2 (ix)
   40F7 12            [ 7]   84 	ld	(de), a
   40F8                      85 00104$:
   40F8 DD F9         [10]   86 	ld	sp, ix
   40FA DD E1         [14]   87 	pop	ix
   40FC C9            [10]   88 	ret
                             89 ;src/sys/physics.c:13: void sys_physics_update() {
                             90 ;	---------------------------------
                             91 ; Function sys_physics_update
                             92 ; ---------------------------------
   40FD                      93 _sys_physics_update::
                             94 ;src/sys/physics.c:15: man_entity_forall (sys_physics_update_one_entity);
   40FD 21 C2 40      [10]   95 	ld	hl, #_sys_physics_update_one_entity
   4100 E5            [11]   96 	push	hl
   4101 CD 9F 40      [17]   97 	call	_man_entity_forall
   4104 F1            [10]   98 	pop	af
   4105 C9            [10]   99 	ret
                            100 	.area _CODE
                            101 	.area _INITIALIZER
                            102 	.area _CABS (ABS)
