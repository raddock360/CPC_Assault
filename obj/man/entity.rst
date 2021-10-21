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
   40CF                      25 _m_entities::
   40CF                      26 	.ds 50
   4101                      27 _m_next_free_entity::
   4101                      28 	.ds 2
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
                             53 ;src/man/entity.c:6: void man_entity_init(void) {
                             54 ;	---------------------------------
                             55 ; Function man_entity_init
                             56 ; ---------------------------------
   402B                      57 _man_entity_init::
                             58 ;src/man/entity.c:7: cpct_memset(m_entities, 0, sizeof(m_entities));
   402B 21 32 00      [10]   59 	ld	hl, #0x0032
   402E E5            [11]   60 	push	hl
   402F AF            [ 4]   61 	xor	a, a
   4030 F5            [11]   62 	push	af
   4031 33            [ 6]   63 	inc	sp
   4032 21 CF 40      [10]   64 	ld	hl, #_m_entities
   4035 E5            [11]   65 	push	hl
   4036 CD B9 40      [17]   66 	call	_cpct_memset
                             67 ;src/man/entity.c:8: m_next_free_entity = m_entities;
   4039 21 CF 40      [10]   68 	ld	hl, #_m_entities
   403C 22 01 41      [16]   69 	ld	(_m_next_free_entity), hl
   403F C9            [10]   70 	ret
                             71 ;src/man/entity.c:11: Entity_t* man_entity_create(void) {
                             72 ;	---------------------------------
                             73 ; Function man_entity_create
                             74 ; ---------------------------------
   4040                      75 _man_entity_create::
                             76 ;src/man/entity.c:12: Entity_t* e = m_next_free_entity;
   4040 ED 4B 01 41   [20]   77 	ld	bc, (_m_next_free_entity)
                             78 ;src/man/entity.c:13: m_next_free_entity = e + 1;
   4044 21 05 00      [10]   79 	ld	hl, #0x0005
   4047 09            [11]   80 	add	hl,bc
   4048 22 01 41      [16]   81 	ld	(_m_next_free_entity), hl
                             82 ;src/man/entity.c:14: e->type = e_type_default;
   404B 3E 7F         [ 7]   83 	ld	a, #0x7f
   404D 02            [ 7]   84 	ld	(bc), a
                             85 ;src/man/entity.c:15: return e;
   404E 69            [ 4]   86 	ld	l, c
   404F 60            [ 4]   87 	ld	h, b
   4050 C9            [10]   88 	ret
                             89 ;src/man/entity.c:18: void man_entity_forall( void (*ptrfunc) (Entity_t*) ) {
                             90 ;	---------------------------------
                             91 ; Function man_entity_forall
                             92 ; ---------------------------------
   4051                      93 _man_entity_forall::
                             94 ;src/man/entity.c:19: Entity_t * e = m_entities;
   4051 01 CF 40      [10]   95 	ld	bc, #_m_entities+0
                             96 ;src/man/entity.c:20: while( e->type != e_type_invalid ) {
   4054                      97 00101$:
   4054 0A            [ 7]   98 	ld	a, (bc)
   4055 B7            [ 4]   99 	or	a, a
   4056 C8            [11]  100 	ret	Z
                            101 ;src/man/entity.c:21: ptrfunc( e );
   4057 C5            [11]  102 	push	bc
   4058 C5            [11]  103 	push	bc
   4059 21 06 00      [10]  104 	ld	hl, #6
   405C 39            [11]  105 	add	hl, sp
   405D 7E            [ 7]  106 	ld	a, (hl)
   405E 23            [ 6]  107 	inc	hl
   405F 66            [ 7]  108 	ld	h, (hl)
   4060 6F            [ 4]  109 	ld	l, a
   4061 CD B8 40      [17]  110 	call	___sdcc_call_hl
   4064 F1            [10]  111 	pop	af
   4065 C1            [10]  112 	pop	bc
                            113 ;src/man/entity.c:22: ++e;
   4066 03            [ 6]  114 	inc	bc
   4067 03            [ 6]  115 	inc	bc
   4068 03            [ 6]  116 	inc	bc
   4069 03            [ 6]  117 	inc	bc
   406A 03            [ 6]  118 	inc	bc
   406B 18 E7         [12]  119 	jr	00101$
                            120 ;src/man/entity.c:26: void man_entity_destroy(Entity_t* dead_e) {
                            121 ;	---------------------------------
                            122 ; Function man_entity_destroy
                            123 ; ---------------------------------
   406D                     124 _man_entity_destroy::
                            125 ;src/man/entity.c:27: dead_e->type = e_type_invalid;
   406D D1            [10]  126 	pop	de
   406E C1            [10]  127 	pop	bc
   406F C5            [11]  128 	push	bc
   4070 D5            [11]  129 	push	de
   4071 AF            [ 4]  130 	xor	a, a
   4072 02            [ 7]  131 	ld	(bc), a
   4073 C9            [10]  132 	ret
                            133 	.area _CODE
                            134 	.area _INITIALIZER
                            135 	.area _CABS (ABS)
