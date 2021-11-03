;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.8 #9946 (Linux)
;--------------------------------------------------------
	.module entity
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _cpct_memcpy
	.globl _cpct_memset
	.globl _m_num_entities
	.globl _m_next_free_entity
	.globl _m_zero_type_at_the_end
	.globl _m_entities
	.globl _man_entity_init
	.globl _man_entity_create
	.globl _man_entity_forall
	.globl _man_entity_destroy
	.globl _man_entity_set4destruction
	.globl _man_entity_update
	.globl _man_entity_freeSpace
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_m_entities::
	.ds 280
_m_zero_type_at_the_end::
	.ds 1
_m_next_free_entity::
	.ds 2
_m_num_entities::
	.ds 1
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;src/man/entity.c:13: void man_entity_init (void) {
;	---------------------------------
; Function man_entity_init
; ---------------------------------
_man_entity_init::
;src/man/entity.c:14: cpct_memset (m_entities, 0, sizeof(m_entities));
	ld	hl, #0x0118
	push	hl
	xor	a, a
	push	af
	inc	sp
	ld	hl, #_m_entities
	push	hl
	call	_cpct_memset
;src/man/entity.c:15: m_next_free_entity = m_entities;
	ld	hl, #_m_entities
	ld	(_m_next_free_entity), hl
;src/man/entity.c:16: m_num_entities = 0;
	ld	hl,#_m_num_entities + 0
	ld	(hl), #0x00
;src/man/entity.c:17: m_zero_type_at_the_end = e_type_invalid;
	ld	hl,#_m_zero_type_at_the_end + 0
	ld	(hl), #0x00
	ret
;src/man/entity.c:27: Entity_t* man_entity_create (void) {
;	---------------------------------
; Function man_entity_create
; ---------------------------------
_man_entity_create::
;src/man/entity.c:28: Entity_t* e = m_next_free_entity;
	ld	bc, (_m_next_free_entity)
;src/man/entity.c:29: m_next_free_entity = e + 1;
	ld	hl, #0x0007
	add	hl,bc
	ld	(_m_next_free_entity), hl
;src/man/entity.c:30: e->type = e_type_default;
	ld	a, #0x7f
	ld	(bc), a
;src/man/entity.c:31: ++m_num_entities;
	ld	hl, #_m_num_entities+0
	inc	(hl)
;src/man/entity.c:32: return e;
	ld	l, c
	ld	h, b
	ret
;src/man/entity.c:46: void man_entity_forall (void (*ptrfunc) (Entity_t*)) {
;	---------------------------------
; Function man_entity_forall
; ---------------------------------
_man_entity_forall::
;src/man/entity.c:47: Entity_t* e = m_entities;
	ld	bc, #_m_entities+0
;src/man/entity.c:49: while (e->type != e_type_invalid) {
00101$:
	ld	a, (bc)
	or	a, a
	ret	Z
;src/man/entity.c:50: ptrfunc(e);
	push	bc
	push	bc
	ld	hl, #6
	add	hl, sp
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
	ld	l, a
	call	___sdcc_call_hl
	pop	af
	pop	bc
;src/man/entity.c:51: ++e;
	ld	hl, #0x0007
	add	hl,bc
	ld	c, l
	ld	b, h
	jr	00101$
;src/man/entity.c:64: void man_entity_destroy (Entity_t* dead_e) {
;	---------------------------------
; Function man_entity_destroy
; ---------------------------------
_man_entity_destroy::
	push	ix
	ld	ix,#0
	add	ix,sp
;src/man/entity.c:65: Entity_t* de = dead_e;
	ld	e,4 (ix)
	ld	d,5 (ix)
;src/man/entity.c:66: Entity_t* last = m_next_free_entity;
	ld	hl, (_m_next_free_entity)
;src/man/entity.c:67: --last;
	ld	bc, #0xfff9
	add	hl,bc
	ld	c, l
	ld	b, h
;src/man/entity.c:68: if (de != last) 
	ld	a, e
	sub	a, c
	jr	NZ,00109$
	ld	a, d
	sub	a, b
	jr	Z,00102$
00109$:
;src/man/entity.c:69: cpct_memcpy(dead_e, last, sizeof(Entity_t));
	ld	l, c
	ld	h, b
	ld	e, 4 (ix)
	ld	d, 5 (ix)
	push	de
	pop	iy
	push	bc
	ld	de, #0x0007
	push	de
	push	hl
	push	iy
	call	_cpct_memcpy
	pop	bc
00102$:
;src/man/entity.c:70: last->type = e_type_invalid;
	xor	a, a
	ld	(bc), a
;src/man/entity.c:71: m_next_free_entity = last;
	ld	(_m_next_free_entity), bc
;src/man/entity.c:72: --m_num_entities;
	ld	hl, #_m_num_entities+0
	dec	(hl)
	pop	ix
	ret
;src/man/entity.c:83: void man_entity_set4destruction (Entity_t* dead_e) {
;	---------------------------------
; Function man_entity_set4destruction
; ---------------------------------
_man_entity_set4destruction::
;src/man/entity.c:84: dead_e->type |= e_type_dead;
	pop	de
	pop	bc
	push	bc
	push	de
	ld	a, (bc)
	set	7, a
	ld	(bc), a
	ret
;src/man/entity.c:91: void man_entity_update (void) {
;	---------------------------------
; Function man_entity_update
; ---------------------------------
_man_entity_update::
;src/man/entity.c:92: Entity_t* e = m_entities;
	ld	hl, #_m_entities+0
;src/man/entity.c:93: while(e->type != e_type_invalid) {
00104$:
	ld	a, (hl)
	or	a, a
	ret	Z
;src/man/entity.c:94: if (e->type & e_type_dead) {
	rlca
	jr	NC,00102$
;src/man/entity.c:95: man_entity_destroy(e);
	push	hl
	push	hl
	call	_man_entity_destroy
	pop	af
	pop	hl
	jr	00104$
00102$:
;src/man/entity.c:97: ++e;
	ld	bc, #0x0007
	add	hl, bc
	jr	00104$
;src/man/entity.c:108: u8 man_entity_freeSpace() {
;	---------------------------------
; Function man_entity_freeSpace
; ---------------------------------
_man_entity_freeSpace::
;src/man/entity.c:109: return MAX_ENTITIES - m_num_entities;
	ld	hl, #_m_num_entities
	ld	a, #0x28
	sub	a, (hl)
	ld	l, a
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
