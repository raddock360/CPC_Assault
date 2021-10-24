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
   4162                      25 _m_entities::
   4162                      26 	.ds 50
   4194                      27 _m_next_free_entity::
   4194                      28 	.ds 2
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
                             53 ;src/man/entity.c:9: void man_entity_init(void) {
                             54 ;	---------------------------------
                             55 ; Function man_entity_init
                             56 ; ---------------------------------
   4044                      57 _man_entity_init::
                             58 ;src/man/entity.c:10: cpct_memset(m_entities, 0, sizeof(m_entities));
   4044 21 32 00      [10]   59 	ld	hl, #0x0032
   4047 E5            [11]   60 	push	hl
   4048 AF            [ 4]   61 	xor	a, a
   4049 F5            [11]   62 	push	af
   404A 33            [ 6]   63 	inc	sp
   404B 21 62 41      [10]   64 	ld	hl, #_m_entities
   404E E5            [11]   65 	push	hl
   404F CD 23 41      [17]   66 	call	_cpct_memset
                             67 ;src/man/entity.c:11: m_next_free_entity = m_entities;
   4052 21 62 41      [10]   68 	ld	hl, #_m_entities
   4055 22 94 41      [16]   69 	ld	(_m_next_free_entity), hl
   4058 C9            [10]   70 	ret
                             71 ;src/man/entity.c:19: Entity_t* man_entity_create(void) {
                             72 ;	---------------------------------
                             73 ; Function man_entity_create
                             74 ; ---------------------------------
   4059                      75 _man_entity_create::
                             76 ;src/man/entity.c:20: Entity_t* e = m_next_free_entity;
   4059 ED 4B 94 41   [20]   77 	ld	bc, (_m_next_free_entity)
                             78 ;src/man/entity.c:21: m_next_free_entity = e + 1;
   405D 21 05 00      [10]   79 	ld	hl, #0x0005
   4060 09            [11]   80 	add	hl,bc
   4061 22 94 41      [16]   81 	ld	(_m_next_free_entity), hl
                             82 ;src/man/entity.c:22: e->type = e_type_default;
   4064 3E 7F         [ 7]   83 	ld	a, #0x7f
   4066 02            [ 7]   84 	ld	(bc), a
                             85 ;src/man/entity.c:23: return e;
   4067 69            [ 4]   86 	ld	l, c
   4068 60            [ 4]   87 	ld	h, b
   4069 C9            [10]   88 	ret
                             89 ;src/man/entity.c:30: void man_entity_forall( void (*ptrfunc) (Entity_t*) ) {
                             90 ;	---------------------------------
                             91 ; Function man_entity_forall
                             92 ; ---------------------------------
   406A                      93 _man_entity_forall::
                             94 ;src/man/entity.c:31: Entity_t * e = m_entities;
   406A 01 62 41      [10]   95 	ld	bc, #_m_entities+0
                             96 ;src/man/entity.c:32: while( e->type != e_type_invalid ) {
   406D                      97 00101$:
   406D 0A            [ 7]   98 	ld	a, (bc)
   406E B7            [ 4]   99 	or	a, a
   406F C8            [11]  100 	ret	Z
                            101 ;src/man/entity.c:33: ptrfunc( e );
   4070 C5            [11]  102 	push	bc
   4071 C5            [11]  103 	push	bc
   4072 21 06 00      [10]  104 	ld	hl, #6
   4075 39            [11]  105 	add	hl, sp
   4076 7E            [ 7]  106 	ld	a, (hl)
   4077 23            [ 6]  107 	inc	hl
   4078 66            [ 7]  108 	ld	h, (hl)
   4079 6F            [ 4]  109 	ld	l, a
   407A CD 14 41      [17]  110 	call	___sdcc_call_hl
   407D F1            [10]  111 	pop	af
   407E C1            [10]  112 	pop	bc
                            113 ;src/man/entity.c:34: ++e;
   407F 03            [ 6]  114 	inc	bc
   4080 03            [ 6]  115 	inc	bc
   4081 03            [ 6]  116 	inc	bc
   4082 03            [ 6]  117 	inc	bc
   4083 03            [ 6]  118 	inc	bc
   4084 18 E7         [12]  119 	jr	00101$
                            120 ;src/man/entity.c:41: void man_entity_destroy(Entity_t* dead_e) {
                            121 ;	---------------------------------
                            122 ; Function man_entity_destroy
                            123 ; ---------------------------------
   4086                     124 _man_entity_destroy::
                            125 ;src/man/entity.c:42: dead_e->type = e_type_invalid;
   4086 D1            [10]  126 	pop	de
   4087 C1            [10]  127 	pop	bc
   4088 C5            [11]  128 	push	bc
   4089 D5            [11]  129 	push	de
   408A AF            [ 4]  130 	xor	a, a
   408B 02            [ 7]  131 	ld	(bc), a
   408C C9            [10]  132 	ret
                            133 	.area _CODE
                            134 	.area _INITIALIZER
                            135 	.area _CABS (ABS)
