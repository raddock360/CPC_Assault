                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.6.8 #9946 (Linux)
                              4 ;--------------------------------------------------------
                              5 	.module entity
                              6 	.optsdcc -mz80
                              7 	
                              8 ;--------------------------------------------------------
                              9 ; Public variables in this module
                             10 ;--------------------------------------------------------
                             11 	.globl _cpct_memset
                             12 	.globl _m_next_free_entity
                             13 	.globl _m_entities
                             14 	.globl _man_entity_init
                             15 	.globl _man_entity_create
                             16 	.globl _man_entity_forall
                             17 	.globl _man_entity_destroy
                             18 ;--------------------------------------------------------
                             19 ; special function registers
                             20 ;--------------------------------------------------------
                             21 ;--------------------------------------------------------
                             22 ; ram data
                             23 ;--------------------------------------------------------
                             24 	.area _DATA
   4248                      25 _m_entities::
   4248                      26 	.ds 50
   427A                      27 _m_next_free_entity::
   427A                      28 	.ds 2
                             29 ;--------------------------------------------------------
                             30 ; ram data
                             31 ;--------------------------------------------------------
                             32 	.area _INITIALIZED
                             33 ;--------------------------------------------------------
                             34 ; absolute external ram data
                             35 ;--------------------------------------------------------
                             36 	.area _DABS (ABS)
                             37 ;--------------------------------------------------------
                             38 ; global & static initialisations
                             39 ;--------------------------------------------------------
                             40 	.area _HOME
                             41 	.area _GSINIT
                             42 	.area _GSFINAL
                             43 	.area _GSINIT
                             44 ;--------------------------------------------------------
                             45 ; Home
                             46 ;--------------------------------------------------------
                             47 	.area _HOME
                             48 	.area _HOME
                             49 ;--------------------------------------------------------
                             50 ; code
                             51 ;--------------------------------------------------------
                             52 	.area _CODE
                             53 ;src/man/entity.c:11: void man_entity_init (void) {
                             54 ;	---------------------------------
                             55 ; Function man_entity_init
                             56 ; ---------------------------------
   4079                      57 _man_entity_init::
                             58 ;src/man/entity.c:12: cpct_memset (m_entities, 0, sizeof(m_entities));
   4079 21 32 00      [10]   59 	ld	hl, #0x0032
   407C E5            [11]   60 	push	hl
   407D AF            [ 4]   61 	xor	a, a
   407E F5            [11]   62 	push	af
   407F 33            [ 6]   63 	inc	sp
   4080 21 48 42      [10]   64 	ld	hl, #_m_entities
   4083 E5            [11]   65 	push	hl
   4084 CD BD 41      [17]   66 	call	_cpct_memset
                             67 ;src/man/entity.c:13: m_next_free_entity = m_entities;
   4087 21 48 42      [10]   68 	ld	hl, #_m_entities
   408A 22 7A 42      [16]   69 	ld	(_m_next_free_entity), hl
   408D C9            [10]   70 	ret
                             71 ;src/man/entity.c:22: Entity_t* man_entity_create (void) {
                             72 ;	---------------------------------
                             73 ; Function man_entity_create
                             74 ; ---------------------------------
   408E                      75 _man_entity_create::
                             76 ;src/man/entity.c:23: Entity_t* e = m_next_free_entity;
   408E ED 4B 7A 42   [20]   77 	ld	bc, (_m_next_free_entity)
                             78 ;src/man/entity.c:24: m_next_free_entity = e + 1;
   4092 21 05 00      [10]   79 	ld	hl, #0x0005
   4095 09            [11]   80 	add	hl,bc
   4096 22 7A 42      [16]   81 	ld	(_m_next_free_entity), hl
                             82 ;src/man/entity.c:25: e->type = e_type_default;
   4099 3E 7F         [ 7]   83 	ld	a, #0x7f
   409B 02            [ 7]   84 	ld	(bc), a
                             85 ;src/man/entity.c:26: return e;
   409C 69            [ 4]   86 	ld	l, c
   409D 60            [ 4]   87 	ld	h, b
   409E C9            [10]   88 	ret
                             89 ;src/man/entity.c:35: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
                             90 ;	---------------------------------
                             91 ; Function man_entity_forall
                             92 ; ---------------------------------
   409F                      93 _man_entity_forall::
                             94 ;src/man/entity.c:36: Entity_t* e = m_entities;
   409F 01 48 42      [10]   95 	ld	bc, #_m_entities+0
                             96 ;src/man/entity.c:37: while (e->type != e_type_invalid) {
   40A2                      97 00101$:
   40A2 0A            [ 7]   98 	ld	a, (bc)
   40A3 B7            [ 4]   99 	or	a, a
   40A4 C8            [11]  100 	ret	Z
                            101 ;src/man/entity.c:38: ptrfunc(e);
   40A5 C5            [11]  102 	push	bc
   40A6 C5            [11]  103 	push	bc
   40A7 21 06 00      [10]  104 	ld	hl, #6
   40AA 39            [11]  105 	add	hl, sp
   40AB 7E            [ 7]  106 	ld	a, (hl)
   40AC 23            [ 6]  107 	inc	hl
   40AD 66            [ 7]  108 	ld	h, (hl)
   40AE 6F            [ 4]  109 	ld	l, a
   40AF CD A6 41      [17]  110 	call	___sdcc_call_hl
   40B2 F1            [10]  111 	pop	af
   40B3 C1            [10]  112 	pop	bc
                            113 ;src/man/entity.c:39: ++e;
   40B4 03            [ 6]  114 	inc	bc
   40B5 03            [ 6]  115 	inc	bc
   40B6 03            [ 6]  116 	inc	bc
   40B7 03            [ 6]  117 	inc	bc
   40B8 03            [ 6]  118 	inc	bc
   40B9 18 E7         [12]  119 	jr	00101$
                            120 ;src/man/entity.c:46: void man_entity_destroy (Entity_t* dead_e) {
                            121 ;	---------------------------------
                            122 ; Function man_entity_destroy
                            123 ; ---------------------------------
   40BB                     124 _man_entity_destroy::
                            125 ;src/man/entity.c:47: dead_e->type = e_type_invalid;
   40BB D1            [10]  126 	pop	de
   40BC C1            [10]  127 	pop	bc
   40BD C5            [11]  128 	push	bc
   40BE D5            [11]  129 	push	de
   40BF AF            [ 4]  130 	xor	a, a
   40C0 02            [ 7]  131 	ld	(bc), a
   40C1 C9            [10]  132 	ret
                            133 	.area _CODE
                            134 	.area _INITIALIZER
                            135 	.area _CABS (ABS)
