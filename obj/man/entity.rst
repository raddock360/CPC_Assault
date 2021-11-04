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
   4340                      31 _m_entities::
   4340                      32 	.ds 315
   447B                      33 _m_zero_type_at_the_end::
   447B                      34 	.ds 1
   447C                      35 _m_next_free_entity::
   447C                      36 	.ds 2
   447E                      37 _m_num_entities::
   447E                      38 	.ds 1
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
   402D                      67 _man_entity_init::
                             68 ;src/man/entity.c:14: cpct_memset (m_entities, 0, sizeof(m_entities));
   402D 21 3B 01      [10]   69 	ld	hl, #0x013b
   4030 E5            [11]   70 	push	hl
   4031 AF            [ 4]   71 	xor	a, a
   4032 F5            [11]   72 	push	af
   4033 33            [ 6]   73 	inc	sp
   4034 21 40 43      [10]   74 	ld	hl, #_m_entities
   4037 E5            [11]   75 	push	hl
   4038 CD BD 42      [17]   76 	call	_cpct_memset
                             77 ;src/man/entity.c:15: m_next_free_entity = m_entities;
   403B 21 40 43      [10]   78 	ld	hl, #_m_entities
   403E 22 7C 44      [16]   79 	ld	(_m_next_free_entity), hl
                             80 ;src/man/entity.c:16: m_num_entities = 0;
   4041 21 7E 44      [10]   81 	ld	hl,#_m_num_entities + 0
   4044 36 00         [10]   82 	ld	(hl), #0x00
                             83 ;src/man/entity.c:17: m_zero_type_at_the_end = e_type_invalid;
   4046 21 7B 44      [10]   84 	ld	hl,#_m_zero_type_at_the_end + 0
   4049 36 00         [10]   85 	ld	(hl), #0x00
   404B C9            [10]   86 	ret
                             87 ;src/man/entity.c:27: Entity_t* man_entity_create (void) {
                             88 ;	---------------------------------
                             89 ; Function man_entity_create
                             90 ; ---------------------------------
   404C                      91 _man_entity_create::
                             92 ;src/man/entity.c:28: Entity_t* e = m_next_free_entity;
   404C ED 4B 7C 44   [20]   93 	ld	bc, (_m_next_free_entity)
                             94 ;src/man/entity.c:29: m_next_free_entity = e + 1;
   4050 21 07 00      [10]   95 	ld	hl, #0x0007
   4053 09            [11]   96 	add	hl,bc
   4054 22 7C 44      [16]   97 	ld	(_m_next_free_entity), hl
                             98 ;src/man/entity.c:30: e->type = e_type_default;
   4057 3E 7F         [ 7]   99 	ld	a, #0x7f
   4059 02            [ 7]  100 	ld	(bc), a
                            101 ;src/man/entity.c:31: ++m_num_entities;
   405A 21 7E 44      [10]  102 	ld	hl, #_m_num_entities+0
   405D 34            [11]  103 	inc	(hl)
                            104 ;src/man/entity.c:32: return e;
   405E 69            [ 4]  105 	ld	l, c
   405F 60            [ 4]  106 	ld	h, b
   4060 C9            [10]  107 	ret
                            108 ;src/man/entity.c:46: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
                            109 ;	---------------------------------
                            110 ; Function man_entity_forall
                            111 ; ---------------------------------
   4061                     112 _man_entity_forall::
                            113 ;src/man/entity.c:47: Entity_t* e = m_entities;
   4061 01 40 43      [10]  114 	ld	bc, #_m_entities+0
                            115 ;src/man/entity.c:49: while (e->type != e_type_invalid) {
   4064                     116 00101$:
   4064 0A            [ 7]  117 	ld	a, (bc)
   4065 B7            [ 4]  118 	or	a, a
   4066 C8            [11]  119 	ret	Z
                            120 ;src/man/entity.c:50: ptrfunc(e);
   4067 C5            [11]  121 	push	bc
   4068 C5            [11]  122 	push	bc
   4069 21 06 00      [10]  123 	ld	hl, #6
   406C 39            [11]  124 	add	hl, sp
   406D 7E            [ 7]  125 	ld	a, (hl)
   406E 23            [ 6]  126 	inc	hl
   406F 66            [ 7]  127 	ld	h, (hl)
   4070 6F            [ 4]  128 	ld	l, a
   4071 CD 9E 42      [17]  129 	call	___sdcc_call_hl
   4074 F1            [10]  130 	pop	af
   4075 C1            [10]  131 	pop	bc
                            132 ;src/man/entity.c:51: ++e;
   4076 21 07 00      [10]  133 	ld	hl, #0x0007
   4079 09            [11]  134 	add	hl,bc
   407A 4D            [ 4]  135 	ld	c, l
   407B 44            [ 4]  136 	ld	b, h
   407C 18 E6         [12]  137 	jr	00101$
                            138 ;src/man/entity.c:64: void man_entity_destroy (Entity_t* dead_e) {
                            139 ;	---------------------------------
                            140 ; Function man_entity_destroy
                            141 ; ---------------------------------
   407E                     142 _man_entity_destroy::
   407E DD E5         [15]  143 	push	ix
   4080 DD 21 00 00   [14]  144 	ld	ix,#0
   4084 DD 39         [15]  145 	add	ix,sp
                            146 ;src/man/entity.c:65: Entity_t* de = dead_e;
   4086 DD 5E 04      [19]  147 	ld	e,4 (ix)
   4089 DD 56 05      [19]  148 	ld	d,5 (ix)
                            149 ;src/man/entity.c:66: Entity_t* last = m_next_free_entity;
   408C 2A 7C 44      [16]  150 	ld	hl, (_m_next_free_entity)
                            151 ;src/man/entity.c:67: --last;
   408F 01 F9 FF      [10]  152 	ld	bc, #0xfff9
   4092 09            [11]  153 	add	hl,bc
   4093 4D            [ 4]  154 	ld	c, l
   4094 44            [ 4]  155 	ld	b, h
                            156 ;src/man/entity.c:68: if (de != last) 
   4095 7B            [ 4]  157 	ld	a, e
   4096 91            [ 4]  158 	sub	a, c
   4097 20 04         [12]  159 	jr	NZ,00109$
   4099 7A            [ 4]  160 	ld	a, d
   409A 90            [ 4]  161 	sub	a, b
   409B 28 17         [12]  162 	jr	Z,00102$
   409D                     163 00109$:
                            164 ;src/man/entity.c:69: cpct_memcpy(dead_e, last, sizeof(Entity_t));
   409D 69            [ 4]  165 	ld	l, c
   409E 60            [ 4]  166 	ld	h, b
   409F DD 5E 04      [19]  167 	ld	e, 4 (ix)
   40A2 DD 56 05      [19]  168 	ld	d, 5 (ix)
   40A5 D5            [11]  169 	push	de
   40A6 FD E1         [14]  170 	pop	iy
   40A8 C5            [11]  171 	push	bc
   40A9 11 07 00      [10]  172 	ld	de, #0x0007
   40AC D5            [11]  173 	push	de
   40AD E5            [11]  174 	push	hl
   40AE FD E5         [15]  175 	push	iy
   40B0 CD B5 42      [17]  176 	call	_cpct_memcpy
   40B3 C1            [10]  177 	pop	bc
   40B4                     178 00102$:
                            179 ;src/man/entity.c:70: last->type = e_type_invalid;
   40B4 AF            [ 4]  180 	xor	a, a
   40B5 02            [ 7]  181 	ld	(bc), a
                            182 ;src/man/entity.c:71: m_next_free_entity = last;
   40B6 ED 43 7C 44   [20]  183 	ld	(_m_next_free_entity), bc
                            184 ;src/man/entity.c:72: --m_num_entities;
   40BA 21 7E 44      [10]  185 	ld	hl, #_m_num_entities+0
   40BD 35            [11]  186 	dec	(hl)
   40BE DD E1         [14]  187 	pop	ix
   40C0 C9            [10]  188 	ret
                            189 ;src/man/entity.c:83: void man_entity_set4destruction (Entity_t* dead_e) {
                            190 ;	---------------------------------
                            191 ; Function man_entity_set4destruction
                            192 ; ---------------------------------
   40C1                     193 _man_entity_set4destruction::
                            194 ;src/man/entity.c:84: dead_e->type |= e_type_dead;
   40C1 D1            [10]  195 	pop	de
   40C2 C1            [10]  196 	pop	bc
   40C3 C5            [11]  197 	push	bc
   40C4 D5            [11]  198 	push	de
   40C5 0A            [ 7]  199 	ld	a, (bc)
   40C6 CB FF         [ 8]  200 	set	7, a
   40C8 02            [ 7]  201 	ld	(bc), a
   40C9 C9            [10]  202 	ret
                            203 ;src/man/entity.c:91: void man_entity_update (void) {
                            204 ;	---------------------------------
                            205 ; Function man_entity_update
                            206 ; ---------------------------------
   40CA                     207 _man_entity_update::
                            208 ;src/man/entity.c:92: Entity_t* e = m_entities;
   40CA 21 40 43      [10]  209 	ld	hl, #_m_entities+0
                            210 ;src/man/entity.c:93: while(e->type != e_type_invalid) {
   40CD                     211 00104$:
   40CD 7E            [ 7]  212 	ld	a, (hl)
   40CE B7            [ 4]  213 	or	a, a
   40CF C8            [11]  214 	ret	Z
                            215 ;src/man/entity.c:94: if (e->type & e_type_dead) {
   40D0 07            [ 4]  216 	rlca
   40D1 30 09         [12]  217 	jr	NC,00102$
                            218 ;src/man/entity.c:95: man_entity_destroy(e);
   40D3 E5            [11]  219 	push	hl
   40D4 E5            [11]  220 	push	hl
   40D5 CD 7E 40      [17]  221 	call	_man_entity_destroy
   40D8 F1            [10]  222 	pop	af
   40D9 E1            [10]  223 	pop	hl
   40DA 18 F1         [12]  224 	jr	00104$
   40DC                     225 00102$:
                            226 ;src/man/entity.c:97: ++e;
   40DC 01 07 00      [10]  227 	ld	bc, #0x0007
   40DF 09            [11]  228 	add	hl, bc
   40E0 18 EB         [12]  229 	jr	00104$
                            230 ;src/man/entity.c:108: u8 man_entity_freeSpace() {
                            231 ;	---------------------------------
                            232 ; Function man_entity_freeSpace
                            233 ; ---------------------------------
   40E2                     234 _man_entity_freeSpace::
                            235 ;src/man/entity.c:109: return MAX_ENTITIES - m_num_entities;
   40E2 21 7E 44      [10]  236 	ld	hl, #_m_num_entities
   40E5 3E 2D         [ 7]  237 	ld	a, #0x2d
   40E7 96            [ 7]  238 	sub	a, (hl)
   40E8 6F            [ 4]  239 	ld	l, a
   40E9 C9            [10]  240 	ret
                            241 	.area _CODE
                            242 	.area _INITIALIZER
                            243 	.area _CABS (ABS)
