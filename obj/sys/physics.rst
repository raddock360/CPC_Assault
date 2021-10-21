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
                             46 ;src/sys/physics.c:4: void sys_physics_update_one_entity( Entity_t* e ) {
                             47 ;	---------------------------------
                             48 ; Function sys_physics_update_one_entity
                             49 ; ---------------------------------
   4074                      50 _sys_physics_update_one_entity::
   4074 DD E5         [15]   51 	push	ix
   4076 DD 21 00 00   [14]   52 	ld	ix,#0
   407A DD 39         [15]   53 	add	ix,sp
   407C F5            [11]   54 	push	af
                             55 ;src/sys/physics.c:5: u8 newx = e->x + e->vx;
   407D DD 4E 04      [19]   56 	ld	c,4 (ix)
   4080 DD 46 05      [19]   57 	ld	b,5 (ix)
   4083 59            [ 4]   58 	ld	e, c
   4084 50            [ 4]   59 	ld	d, b
   4085 13            [ 6]   60 	inc	de
   4086 1A            [ 7]   61 	ld	a, (de)
   4087 DD 77 FF      [19]   62 	ld	-1 (ix), a
   408A 69            [ 4]   63 	ld	l, c
   408B 60            [ 4]   64 	ld	h, b
   408C 23            [ 6]   65 	inc	hl
   408D 23            [ 6]   66 	inc	hl
   408E 23            [ 6]   67 	inc	hl
   408F 6E            [ 7]   68 	ld	l, (hl)
   4090 DD 7E FF      [19]   69 	ld	a, -1 (ix)
   4093 85            [ 4]   70 	add	a, l
   4094 DD 77 FE      [19]   71 	ld	-2 (ix), a
                             72 ;src/sys/physics.c:6: if(newx > e->x) 
   4097 DD 7E FF      [19]   73 	ld	a, -1 (ix)
   409A DD 96 FE      [19]   74 	sub	a, -2 (ix)
   409D 30 07         [12]   75 	jr	NC,00102$
                             76 ;src/sys/physics.c:7: man_entity_destroy( e );
   409F C5            [11]   77 	push	bc
   40A0 CD 6D 40      [17]   78 	call	_man_entity_destroy
   40A3 F1            [10]   79 	pop	af
   40A4 18 04         [12]   80 	jr	00104$
   40A6                      81 00102$:
                             82 ;src/sys/physics.c:10: e->x = newx;
   40A6 DD 7E FE      [19]   83 	ld	a, -2 (ix)
   40A9 12            [ 7]   84 	ld	(de), a
   40AA                      85 00104$:
   40AA DD F9         [10]   86 	ld	sp, ix
   40AC DD E1         [14]   87 	pop	ix
   40AE C9            [10]   88 	ret
                             89 ;src/sys/physics.c:13: void sys_physics_update() {
                             90 ;	---------------------------------
                             91 ; Function sys_physics_update
                             92 ; ---------------------------------
   40AF                      93 _sys_physics_update::
                             94 ;src/sys/physics.c:15: man_entity_forall( sys_physics_update_one_entity );
   40AF 21 74 40      [10]   95 	ld	hl, #_sys_physics_update_one_entity
   40B2 E5            [11]   96 	push	hl
   40B3 CD 51 40      [17]   97 	call	_man_entity_forall
   40B6 F1            [10]   98 	pop	af
   40B7 C9            [10]   99 	ret
                            100 	.area _CODE
                            101 	.area _INITIALIZER
                            102 	.area _CABS (ABS)
