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
                             11 	.globl _cpct_memcpy
                             12 	.globl _cpct_memset
                             13 	.globl _m_next_free_entity
                             14 	.globl _m_entities
                             15 	.globl _man_entity_init
                             16 	.globl _man_entity_create
                             17 	.globl _man_entity_forall
                             18 	.globl _man_entity_destroy
                             19 ;--------------------------------------------------------
                             20 ; special function registers
                             21 ;--------------------------------------------------------
                             22 ;--------------------------------------------------------
                             23 ; ram data
                             24 ;--------------------------------------------------------
                             25 	.area _DATA
   42C3                      26 _m_entities::
   42C3                      27 	.ds 50
   42F5                      28 _m_next_free_entity::
   42F5                      29 	.ds 2
                             30 ;--------------------------------------------------------
                             31 ; ram data
                             32 ;--------------------------------------------------------
                             33 	.area _INITIALIZED
                             34 ;--------------------------------------------------------
                             35 ; absolute external ram data
                             36 ;--------------------------------------------------------
                             37 	.area _DABS (ABS)
                             38 ;--------------------------------------------------------
                             39 ; global & static initialisations
                             40 ;--------------------------------------------------------
                             41 	.area _HOME
                             42 	.area _GSINIT
                             43 	.area _GSFINAL
                             44 	.area _GSINIT
                             45 ;--------------------------------------------------------
                             46 ; Home
                             47 ;--------------------------------------------------------
                             48 	.area _HOME
                             49 	.area _HOME
                             50 ;--------------------------------------------------------
                             51 ; code
                             52 ;--------------------------------------------------------
                             53 	.area _CODE
                             54 ;src/man/entity.c:11: void man_entity_init (void) {
                             55 ;	---------------------------------
                             56 ; Function man_entity_init
                             57 ; ---------------------------------
   4137                      58 _man_entity_init::
                             59 ;src/man/entity.c:12: cpct_memset (m_entities, 0, sizeof(m_entities));
   4137 21 32 00      [10]   60 	ld	hl, #0x0032
   413A E5            [11]   61 	push	hl
   413B AF            [ 4]   62 	xor	a, a
   413C F5            [11]   63 	push	af
   413D 33            [ 6]   64 	inc	sp
   413E 21 C3 42      [10]   65 	ld	hl, #_m_entities
   4141 E5            [11]   66 	push	hl
   4142 CD 38 42      [17]   67 	call	_cpct_memset
                             68 ;src/man/entity.c:13: m_next_free_entity = m_entities;
   4145 21 C3 42      [10]   69 	ld	hl, #_m_entities
   4148 22 F5 42      [16]   70 	ld	(_m_next_free_entity), hl
   414B C9            [10]   71 	ret
                             72 ;src/man/entity.c:22: Entity_t* man_entity_create (void) {
                             73 ;	---------------------------------
                             74 ; Function man_entity_create
                             75 ; ---------------------------------
   414C                      76 _man_entity_create::
                             77 ;src/man/entity.c:23: Entity_t* e = m_next_free_entity;
   414C ED 4B F5 42   [20]   78 	ld	bc, (_m_next_free_entity)
                             79 ;src/man/entity.c:24: m_next_free_entity = e + 1;
   4150 21 05 00      [10]   80 	ld	hl, #0x0005
   4153 09            [11]   81 	add	hl,bc
   4154 22 F5 42      [16]   82 	ld	(_m_next_free_entity), hl
                             83 ;src/man/entity.c:25: e->type = e_type_default;
   4157 3E 7F         [ 7]   84 	ld	a, #0x7f
   4159 02            [ 7]   85 	ld	(bc), a
                             86 ;src/man/entity.c:26: return e;
   415A 69            [ 4]   87 	ld	l, c
   415B 60            [ 4]   88 	ld	h, b
   415C C9            [10]   89 	ret
                             90 ;src/man/entity.c:35: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
                             91 ;	---------------------------------
                             92 ; Function man_entity_forall
                             93 ; ---------------------------------
   415D                      94 _man_entity_forall::
                             95 ;src/man/entity.c:36: Entity_t* e = m_entities;
   415D 01 C3 42      [10]   96 	ld	bc, #_m_entities+0
                             97 ;src/man/entity.c:37: while (e->type != e_type_invalid) {
   4160                      98 00101$:
   4160 0A            [ 7]   99 	ld	a, (bc)
   4161 B7            [ 4]  100 	or	a, a
   4162 C8            [11]  101 	ret	Z
                            102 ;src/man/entity.c:38: ptrfunc(e);
   4163 C5            [11]  103 	push	bc
   4164 C5            [11]  104 	push	bc
   4165 21 06 00      [10]  105 	ld	hl, #6
   4168 39            [11]  106 	add	hl, sp
   4169 7E            [ 7]  107 	ld	a, (hl)
   416A 23            [ 6]  108 	inc	hl
   416B 66            [ 7]  109 	ld	h, (hl)
   416C 6F            [ 4]  110 	ld	l, a
   416D CD 21 42      [17]  111 	call	___sdcc_call_hl
   4170 F1            [10]  112 	pop	af
   4171 C1            [10]  113 	pop	bc
                            114 ;src/man/entity.c:39: ++e;
   4172 03            [ 6]  115 	inc	bc
   4173 03            [ 6]  116 	inc	bc
   4174 03            [ 6]  117 	inc	bc
   4175 03            [ 6]  118 	inc	bc
   4176 03            [ 6]  119 	inc	bc
   4177 18 E7         [12]  120 	jr	00101$
                            121 ;src/man/entity.c:52: void man_entity_destroy (Entity_t* dead_e) {
                            122 ;	---------------------------------
                            123 ; Function man_entity_destroy
                            124 ; ---------------------------------
   4179                     125 _man_entity_destroy::
   4179 DD E5         [15]  126 	push	ix
   417B DD 21 00 00   [14]  127 	ld	ix,#0
   417F DD 39         [15]  128 	add	ix,sp
                            129 ;src/man/entity.c:53: Entity_t* de = dead_e;
   4181 DD 5E 04      [19]  130 	ld	e,4 (ix)
   4184 DD 56 05      [19]  131 	ld	d,5 (ix)
                            132 ;src/man/entity.c:54: Entity_t* last = m_next_free_entity;
   4187 2A F5 42      [16]  133 	ld	hl, (_m_next_free_entity)
                            134 ;src/man/entity.c:55: --last;
   418A 01 FB FF      [10]  135 	ld	bc, #0xfffb
   418D 09            [11]  136 	add	hl,bc
   418E 4D            [ 4]  137 	ld	c, l
   418F 44            [ 4]  138 	ld	b, h
                            139 ;src/man/entity.c:56: if (de != last) 
   4190 7B            [ 4]  140 	ld	a, e
   4191 91            [ 4]  141 	sub	a, c
   4192 20 04         [12]  142 	jr	NZ,00109$
   4194 7A            [ 4]  143 	ld	a, d
   4195 90            [ 4]  144 	sub	a, b
   4196 28 17         [12]  145 	jr	Z,00102$
   4198                     146 00109$:
                            147 ;src/man/entity.c:57: cpct_memcpy(dead_e, last, sizeof(Entity_t));
   4198 69            [ 4]  148 	ld	l, c
   4199 60            [ 4]  149 	ld	h, b
   419A DD 5E 04      [19]  150 	ld	e, 4 (ix)
   419D DD 56 05      [19]  151 	ld	d, 5 (ix)
   41A0 D5            [11]  152 	push	de
   41A1 FD E1         [14]  153 	pop	iy
   41A3 C5            [11]  154 	push	bc
   41A4 11 05 00      [10]  155 	ld	de, #0x0005
   41A7 D5            [11]  156 	push	de
   41A8 E5            [11]  157 	push	hl
   41A9 FD E5         [15]  158 	push	iy
   41AB CD 46 42      [17]  159 	call	_cpct_memcpy
   41AE C1            [10]  160 	pop	bc
   41AF                     161 00102$:
                            162 ;src/man/entity.c:58: last->type = e_type_invalid;
   41AF AF            [ 4]  163 	xor	a, a
   41B0 02            [ 7]  164 	ld	(bc), a
                            165 ;src/man/entity.c:59: m_next_free_entity = last;
   41B1 ED 43 F5 42   [20]  166 	ld	(_m_next_free_entity), bc
   41B5 DD E1         [14]  167 	pop	ix
   41B7 C9            [10]  168 	ret
                            169 	.area _CODE
                            170 	.area _INITIALIZER
                            171 	.area _CABS (ABS)
