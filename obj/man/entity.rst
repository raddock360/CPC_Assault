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
                             13 	.globl _m_num_entities
                             14 	.globl _m_next_free_entity
                             15 	.globl _m_zero_type_at_the_end
                             16 	.globl _m_entities
                             17 	.globl _man_entity_init
                             18 	.globl _man_entity_create
                             19 	.globl _man_entity_forall
                             20 	.globl _man_entity_destroy
                             21 	.globl _man_entity_set4destruction
                             22 	.globl _man_entity_update
                             23 	.globl _man_entity_freeSpace
                             24 ;--------------------------------------------------------
                             25 ; special function registers
                             26 ;--------------------------------------------------------
                             27 ;--------------------------------------------------------
                             28 ; ram data
                             29 ;--------------------------------------------------------
                             30 	.area _DATA
   435B                      31 _m_entities::
   435B                      32 	.ds 315
   4496                      33 _m_zero_type_at_the_end::
   4496                      34 	.ds 1
   4497                      35 _m_next_free_entity::
   4497                      36 	.ds 2
   4499                      37 _m_num_entities::
   4499                      38 	.ds 1
                             39 ;--------------------------------------------------------
                             40 ; ram data
                             41 ;--------------------------------------------------------
                             42 	.area _INITIALIZED
                             43 ;--------------------------------------------------------
                             44 ; absolute external ram data
                             45 ;--------------------------------------------------------
                             46 	.area _DABS (ABS)
                             47 ;--------------------------------------------------------
                             48 ; global & static initialisations
                             49 ;--------------------------------------------------------
                             50 	.area _HOME
                             51 	.area _GSINIT
                             52 	.area _GSFINAL
                             53 	.area _GSINIT
                             54 ;--------------------------------------------------------
                             55 ; Home
                             56 ;--------------------------------------------------------
                             57 	.area _HOME
                             58 	.area _HOME
                             59 ;--------------------------------------------------------
                             60 ; code
                             61 ;--------------------------------------------------------
                             62 	.area _CODE
                             63 ;src/man/entity.c:13: void man_entity_init (void) {
                             64 ;	---------------------------------
                             65 ; Function man_entity_init
                             66 ; ---------------------------------
   417C                      67 _man_entity_init::
                             68 ;src/man/entity.c:14: cpct_memset (m_entities, 0, sizeof(m_entities));
   417C 21 3B 01      [10]   69 	ld	hl, #0x013b
   417F E5            [11]   70 	push	hl
   4180 AF            [ 4]   71 	xor	a, a
   4181 F5            [11]   72 	push	af
   4182 33            [ 6]   73 	inc	sp
   4183 21 5B 43      [10]   74 	ld	hl, #_m_entities
   4186 E5            [11]   75 	push	hl
   4187 CD D0 42      [17]   76 	call	_cpct_memset
                             77 ;src/man/entity.c:15: m_next_free_entity = m_entities;
   418A 21 5B 43      [10]   78 	ld	hl, #_m_entities
   418D 22 97 44      [16]   79 	ld	(_m_next_free_entity), hl
                             80 ;src/man/entity.c:16: m_num_entities = 0;
   4190 21 99 44      [10]   81 	ld	hl,#_m_num_entities + 0
   4193 36 00         [10]   82 	ld	(hl), #0x00
                             83 ;src/man/entity.c:17: m_zero_type_at_the_end = e_type_invalid;
   4195 21 96 44      [10]   84 	ld	hl,#_m_zero_type_at_the_end + 0
   4198 36 00         [10]   85 	ld	(hl), #0x00
   419A C9            [10]   86 	ret
                             87 ;src/man/entity.c:27: Entity_t* man_entity_create (void) {
                             88 ;	---------------------------------
                             89 ; Function man_entity_create
                             90 ; ---------------------------------
   419B                      91 _man_entity_create::
                             92 ;src/man/entity.c:28: Entity_t* e = m_next_free_entity;
   419B ED 4B 97 44   [20]   93 	ld	bc, (_m_next_free_entity)
                             94 ;src/man/entity.c:29: m_next_free_entity = e + 1;
   419F 21 07 00      [10]   95 	ld	hl, #0x0007
   41A2 09            [11]   96 	add	hl,bc
   41A3 22 97 44      [16]   97 	ld	(_m_next_free_entity), hl
                             98 ;src/man/entity.c:30: e->type = e_type_default;
   41A6 3E 7F         [ 7]   99 	ld	a, #0x7f
   41A8 02            [ 7]  100 	ld	(bc), a
                            101 ;src/man/entity.c:31: ++m_num_entities;
   41A9 21 99 44      [10]  102 	ld	hl, #_m_num_entities+0
   41AC 34            [11]  103 	inc	(hl)
                            104 ;src/man/entity.c:32: return e;
   41AD 69            [ 4]  105 	ld	l, c
   41AE 60            [ 4]  106 	ld	h, b
   41AF C9            [10]  107 	ret
                            108 ;src/man/entity.c:46: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
                            109 ;	---------------------------------
                            110 ; Function man_entity_forall
                            111 ; ---------------------------------
   41B0                     112 _man_entity_forall::
                            113 ;src/man/entity.c:47: Entity_t* e = m_entities;
   41B0 01 5B 43      [10]  114 	ld	bc, #_m_entities+0
                            115 ;src/man/entity.c:49: while (e->type != e_type_invalid) {
   41B3                     116 00101$:
   41B3 0A            [ 7]  117 	ld	a, (bc)
   41B4 B7            [ 4]  118 	or	a, a
   41B5 C8            [11]  119 	ret	Z
                            120 ;src/man/entity.c:50: ptrfunc(e);
   41B6 C5            [11]  121 	push	bc
   41B7 C5            [11]  122 	push	bc
   41B8 21 06 00      [10]  123 	ld	hl, #6
   41BB 39            [11]  124 	add	hl, sp
   41BC 7E            [ 7]  125 	ld	a, (hl)
   41BD 23            [ 6]  126 	inc	hl
   41BE 66            [ 7]  127 	ld	h, (hl)
   41BF 6F            [ 4]  128 	ld	l, a
   41C0 CD B9 42      [17]  129 	call	___sdcc_call_hl
   41C3 F1            [10]  130 	pop	af
   41C4 C1            [10]  131 	pop	bc
                            132 ;src/man/entity.c:51: ++e;
   41C5 21 07 00      [10]  133 	ld	hl, #0x0007
   41C8 09            [11]  134 	add	hl,bc
   41C9 4D            [ 4]  135 	ld	c, l
   41CA 44            [ 4]  136 	ld	b, h
   41CB 18 E6         [12]  137 	jr	00101$
                            138 ;src/man/entity.c:64: void man_entity_destroy (Entity_t* dead_e) {
                            139 ;	---------------------------------
                            140 ; Function man_entity_destroy
                            141 ; ---------------------------------
   41CD                     142 _man_entity_destroy::
   41CD DD E5         [15]  143 	push	ix
   41CF DD 21 00 00   [14]  144 	ld	ix,#0
   41D3 DD 39         [15]  145 	add	ix,sp
                            146 ;src/man/entity.c:65: Entity_t* de = dead_e;
   41D5 DD 5E 04      [19]  147 	ld	e,4 (ix)
   41D8 DD 56 05      [19]  148 	ld	d,5 (ix)
                            149 ;src/man/entity.c:66: Entity_t* last = m_next_free_entity;
   41DB 2A 97 44      [16]  150 	ld	hl, (_m_next_free_entity)
                            151 ;src/man/entity.c:67: --last;
   41DE 01 F9 FF      [10]  152 	ld	bc, #0xfff9
   41E1 09            [11]  153 	add	hl,bc
   41E2 4D            [ 4]  154 	ld	c, l
   41E3 44            [ 4]  155 	ld	b, h
                            156 ;src/man/entity.c:68: if (de != last) 
   41E4 7B            [ 4]  157 	ld	a, e
   41E5 91            [ 4]  158 	sub	a, c
   41E6 20 04         [12]  159 	jr	NZ,00109$
   41E8 7A            [ 4]  160 	ld	a, d
   41E9 90            [ 4]  161 	sub	a, b
   41EA 28 17         [12]  162 	jr	Z,00102$
   41EC                     163 00109$:
                            164 ;src/man/entity.c:69: cpct_memcpy(dead_e, last, sizeof(Entity_t));
   41EC 69            [ 4]  165 	ld	l, c
   41ED 60            [ 4]  166 	ld	h, b
   41EE DD 5E 04      [19]  167 	ld	e, 4 (ix)
   41F1 DD 56 05      [19]  168 	ld	d, 5 (ix)
   41F4 D5            [11]  169 	push	de
   41F5 FD E1         [14]  170 	pop	iy
   41F7 C5            [11]  171 	push	bc
   41F8 11 07 00      [10]  172 	ld	de, #0x0007
   41FB D5            [11]  173 	push	de
   41FC E5            [11]  174 	push	hl
   41FD FD E5         [15]  175 	push	iy
   41FF CD DE 42      [17]  176 	call	_cpct_memcpy
   4202 C1            [10]  177 	pop	bc
   4203                     178 00102$:
                            179 ;src/man/entity.c:70: last->type = e_type_invalid;
   4203 AF            [ 4]  180 	xor	a, a
   4204 02            [ 7]  181 	ld	(bc), a
                            182 ;src/man/entity.c:71: m_next_free_entity = last;
   4205 ED 43 97 44   [20]  183 	ld	(_m_next_free_entity), bc
                            184 ;src/man/entity.c:72: --m_num_entities;
   4209 21 99 44      [10]  185 	ld	hl, #_m_num_entities+0
   420C 35            [11]  186 	dec	(hl)
   420D DD E1         [14]  187 	pop	ix
   420F C9            [10]  188 	ret
                            189 ;src/man/entity.c:83: void man_entity_set4destruction (Entity_t* dead_e) {
                            190 ;	---------------------------------
                            191 ; Function man_entity_set4destruction
                            192 ; ---------------------------------
   4210                     193 _man_entity_set4destruction::
                            194 ;src/man/entity.c:84: dead_e->type |= e_type_dead;
   4210 D1            [10]  195 	pop	de
   4211 C1            [10]  196 	pop	bc
   4212 C5            [11]  197 	push	bc
   4213 D5            [11]  198 	push	de
   4214 0A            [ 7]  199 	ld	a, (bc)
   4215 CB FF         [ 8]  200 	set	7, a
   4217 02            [ 7]  201 	ld	(bc), a
   4218 C9            [10]  202 	ret
                            203 ;src/man/entity.c:91: void man_entity_update (void) {
                            204 ;	---------------------------------
                            205 ; Function man_entity_update
                            206 ; ---------------------------------
   4219                     207 _man_entity_update::
                            208 ;src/man/entity.c:92: Entity_t* e = m_entities;
   4219 21 5B 43      [10]  209 	ld	hl, #_m_entities+0
                            210 ;src/man/entity.c:93: while(e->type != e_type_invalid) {
   421C                     211 00104$:
   421C 7E            [ 7]  212 	ld	a, (hl)
   421D B7            [ 4]  213 	or	a, a
   421E C8            [11]  214 	ret	Z
                            215 ;src/man/entity.c:94: if (e->type & e_type_dead) {
   421F 07            [ 4]  216 	rlca
   4220 30 09         [12]  217 	jr	NC,00102$
                            218 ;src/man/entity.c:95: man_entity_destroy(e);
   4222 E5            [11]  219 	push	hl
   4223 E5            [11]  220 	push	hl
   4224 CD CD 41      [17]  221 	call	_man_entity_destroy
   4227 F1            [10]  222 	pop	af
   4228 E1            [10]  223 	pop	hl
   4229 18 F1         [12]  224 	jr	00104$
   422B                     225 00102$:
                            226 ;src/man/entity.c:97: ++e;
   422B 01 07 00      [10]  227 	ld	bc, #0x0007
   422E 09            [11]  228 	add	hl, bc
   422F 18 EB         [12]  229 	jr	00104$
                            230 ;src/man/entity.c:108: u8 man_entity_freeSpace() {
                            231 ;	---------------------------------
                            232 ; Function man_entity_freeSpace
                            233 ; ---------------------------------
   4231                     234 _man_entity_freeSpace::
                            235 ;src/man/entity.c:109: return MAX_ENTITIES - m_num_entities;
   4231 21 99 44      [10]  236 	ld	hl, #_m_num_entities
   4234 3E 2D         [ 7]  237 	ld	a, #0x2d
   4236 96            [ 7]  238 	sub	a, (hl)
   4237 6F            [ 4]  239 	ld	l, a
   4238 C9            [10]  240 	ret
                            241 	.area _CODE
                            242 	.area _INITIALIZER
                            243 	.area _CABS (ABS)
