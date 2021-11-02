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
                             19 	.globl _man_entity_set4destruction
                             20 	.globl _man_entity_update
                             21 ;--------------------------------------------------------
                             22 ; special function registers
                             23 ;--------------------------------------------------------
                             24 ;--------------------------------------------------------
                             25 ; ram data
                             26 ;--------------------------------------------------------
                             27 	.area _DATA
   42D0                      28 _m_entities::
   42D0                      29 	.ds 70
   4316                      30 _m_next_free_entity::
   4316                      31 	.ds 2
                             32 ;--------------------------------------------------------
                             33 ; ram data
                             34 ;--------------------------------------------------------
                             35 	.area _INITIALIZED
                             36 ;--------------------------------------------------------
                             37 ; absolute external ram data
                             38 ;--------------------------------------------------------
                             39 	.area _DABS (ABS)
                             40 ;--------------------------------------------------------
                             41 ; global & static initialisations
                             42 ;--------------------------------------------------------
                             43 	.area _HOME
                             44 	.area _GSINIT
                             45 	.area _GSFINAL
                             46 	.area _GSINIT
                             47 ;--------------------------------------------------------
                             48 ; Home
                             49 ;--------------------------------------------------------
                             50 	.area _HOME
                             51 	.area _HOME
                             52 ;--------------------------------------------------------
                             53 ; code
                             54 ;--------------------------------------------------------
                             55 	.area _CODE
                             56 ;src/man/entity.c:11: void man_entity_init (void) {
                             57 ;	---------------------------------
                             58 ; Function man_entity_init
                             59 ; ---------------------------------
   4032                      60 _man_entity_init::
                             61 ;src/man/entity.c:12: cpct_memset (m_entities, 0, sizeof(m_entities));
   4032 21 46 00      [10]   62 	ld	hl, #0x0046
   4035 E5            [11]   63 	push	hl
   4036 AF            [ 4]   64 	xor	a, a
   4037 F5            [11]   65 	push	af
   4038 33            [ 6]   66 	inc	sp
   4039 21 D0 42      [10]   67 	ld	hl, #_m_entities
   403C E5            [11]   68 	push	hl
   403D CD 4D 42      [17]   69 	call	_cpct_memset
                             70 ;src/man/entity.c:13: m_next_free_entity = m_entities;
   4040 21 D0 42      [10]   71 	ld	hl, #_m_entities
   4043 22 16 43      [16]   72 	ld	(_m_next_free_entity), hl
   4046 C9            [10]   73 	ret
                             74 ;src/man/entity.c:22: Entity_t* man_entity_create (void) {
                             75 ;	---------------------------------
                             76 ; Function man_entity_create
                             77 ; ---------------------------------
   4047                      78 _man_entity_create::
                             79 ;src/man/entity.c:23: Entity_t* e = m_next_free_entity;
   4047 ED 4B 16 43   [20]   80 	ld	bc, (_m_next_free_entity)
                             81 ;src/man/entity.c:24: m_next_free_entity = e + 1;
   404B 21 07 00      [10]   82 	ld	hl, #0x0007
   404E 09            [11]   83 	add	hl,bc
   404F 22 16 43      [16]   84 	ld	(_m_next_free_entity), hl
                             85 ;src/man/entity.c:25: e->type = e_type_default;
   4052 3E 7F         [ 7]   86 	ld	a, #0x7f
   4054 02            [ 7]   87 	ld	(bc), a
                             88 ;src/man/entity.c:26: return e;
   4055 69            [ 4]   89 	ld	l, c
   4056 60            [ 4]   90 	ld	h, b
   4057 C9            [10]   91 	ret
                             92 ;src/man/entity.c:35: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
                             93 ;	---------------------------------
                             94 ; Function man_entity_forall
                             95 ; ---------------------------------
   4058                      96 _man_entity_forall::
                             97 ;src/man/entity.c:36: Entity_t* e = m_entities;
   4058 01 D0 42      [10]   98 	ld	bc, #_m_entities+0
                             99 ;src/man/entity.c:37: while (e->type != e_type_invalid) {
   405B                     100 00101$:
   405B 0A            [ 7]  101 	ld	a, (bc)
   405C B7            [ 4]  102 	or	a, a
   405D C8            [11]  103 	ret	Z
                            104 ;src/man/entity.c:38: ptrfunc(e);
   405E C5            [11]  105 	push	bc
   405F C5            [11]  106 	push	bc
   4060 21 06 00      [10]  107 	ld	hl, #6
   4063 39            [11]  108 	add	hl, sp
   4064 7E            [ 7]  109 	ld	a, (hl)
   4065 23            [ 6]  110 	inc	hl
   4066 66            [ 7]  111 	ld	h, (hl)
   4067 6F            [ 4]  112 	ld	l, a
   4068 CD 2E 42      [17]  113 	call	___sdcc_call_hl
   406B F1            [10]  114 	pop	af
   406C C1            [10]  115 	pop	bc
                            116 ;src/man/entity.c:39: ++e;
   406D 21 07 00      [10]  117 	ld	hl, #0x0007
   4070 09            [11]  118 	add	hl,bc
   4071 4D            [ 4]  119 	ld	c, l
   4072 44            [ 4]  120 	ld	b, h
   4073 18 E6         [12]  121 	jr	00101$
                            122 ;src/man/entity.c:52: void man_entity_destroy (Entity_t* dead_e) {
                            123 ;	---------------------------------
                            124 ; Function man_entity_destroy
                            125 ; ---------------------------------
   4075                     126 _man_entity_destroy::
   4075 DD E5         [15]  127 	push	ix
   4077 DD 21 00 00   [14]  128 	ld	ix,#0
   407B DD 39         [15]  129 	add	ix,sp
                            130 ;src/man/entity.c:53: Entity_t* de = dead_e;
   407D DD 5E 04      [19]  131 	ld	e,4 (ix)
   4080 DD 56 05      [19]  132 	ld	d,5 (ix)
                            133 ;src/man/entity.c:54: Entity_t* last = m_next_free_entity;
   4083 2A 16 43      [16]  134 	ld	hl, (_m_next_free_entity)
                            135 ;src/man/entity.c:55: --last;
   4086 01 F9 FF      [10]  136 	ld	bc, #0xfff9
   4089 09            [11]  137 	add	hl,bc
   408A 4D            [ 4]  138 	ld	c, l
   408B 44            [ 4]  139 	ld	b, h
                            140 ;src/man/entity.c:56: if (de != last) 
   408C 7B            [ 4]  141 	ld	a, e
   408D 91            [ 4]  142 	sub	a, c
   408E 20 04         [12]  143 	jr	NZ,00109$
   4090 7A            [ 4]  144 	ld	a, d
   4091 90            [ 4]  145 	sub	a, b
   4092 28 17         [12]  146 	jr	Z,00102$
   4094                     147 00109$:
                            148 ;src/man/entity.c:57: cpct_memcpy(dead_e, last, sizeof(Entity_t));
   4094 69            [ 4]  149 	ld	l, c
   4095 60            [ 4]  150 	ld	h, b
   4096 DD 5E 04      [19]  151 	ld	e, 4 (ix)
   4099 DD 56 05      [19]  152 	ld	d, 5 (ix)
   409C D5            [11]  153 	push	de
   409D FD E1         [14]  154 	pop	iy
   409F C5            [11]  155 	push	bc
   40A0 11 07 00      [10]  156 	ld	de, #0x0007
   40A3 D5            [11]  157 	push	de
   40A4 E5            [11]  158 	push	hl
   40A5 FD E5         [15]  159 	push	iy
   40A7 CD 45 42      [17]  160 	call	_cpct_memcpy
   40AA C1            [10]  161 	pop	bc
   40AB                     162 00102$:
                            163 ;src/man/entity.c:58: last->type = e_type_invalid;
   40AB AF            [ 4]  164 	xor	a, a
   40AC 02            [ 7]  165 	ld	(bc), a
                            166 ;src/man/entity.c:59: m_next_free_entity = last;
   40AD ED 43 16 43   [20]  167 	ld	(_m_next_free_entity), bc
   40B1 DD E1         [14]  168 	pop	ix
   40B3 C9            [10]  169 	ret
                            170 ;src/man/entity.c:70: void man_entity_set4destruction (Entity_t* dead_e) {
                            171 ;	---------------------------------
                            172 ; Function man_entity_set4destruction
                            173 ; ---------------------------------
   40B4                     174 _man_entity_set4destruction::
                            175 ;src/man/entity.c:71: dead_e->type |= e_type_dead;
   40B4 D1            [10]  176 	pop	de
   40B5 C1            [10]  177 	pop	bc
   40B6 C5            [11]  178 	push	bc
   40B7 D5            [11]  179 	push	de
   40B8 0A            [ 7]  180 	ld	a, (bc)
   40B9 CB FF         [ 8]  181 	set	7, a
   40BB 02            [ 7]  182 	ld	(bc), a
   40BC C9            [10]  183 	ret
                            184 ;src/man/entity.c:78: void man_entity_update (void) {
                            185 ;	---------------------------------
                            186 ; Function man_entity_update
                            187 ; ---------------------------------
   40BD                     188 _man_entity_update::
                            189 ;src/man/entity.c:79: Entity_t* e = m_entities;
   40BD 21 D0 42      [10]  190 	ld	hl, #_m_entities+0
                            191 ;src/man/entity.c:80: while(e->type != e_type_invalid) {
   40C0                     192 00104$:
   40C0 7E            [ 7]  193 	ld	a, (hl)
   40C1 B7            [ 4]  194 	or	a, a
   40C2 C8            [11]  195 	ret	Z
                            196 ;src/man/entity.c:81: if (e->type & e_type_dead) {
   40C3 07            [ 4]  197 	rlca
   40C4 30 09         [12]  198 	jr	NC,00102$
                            199 ;src/man/entity.c:82: man_entity_destroy(e);
   40C6 E5            [11]  200 	push	hl
   40C7 E5            [11]  201 	push	hl
   40C8 CD 75 40      [17]  202 	call	_man_entity_destroy
   40CB F1            [10]  203 	pop	af
   40CC E1            [10]  204 	pop	hl
   40CD 18 F1         [12]  205 	jr	00104$
   40CF                     206 00102$:
                            207 ;src/man/entity.c:84: ++e;
   40CF 01 07 00      [10]  208 	ld	bc, #0x0007
   40D2 09            [11]  209 	add	hl, bc
   40D3 18 EB         [12]  210 	jr	00104$
                            211 	.area _CODE
                            212 	.area _INITIALIZER
                            213 	.area _CABS (ABS)
