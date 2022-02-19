DrawKrisPackGFX:
	ld hl, PackFGFXPointers
	add hl, de
	add hl, de
	ld a, [hli]
	ld e, a
	ld d, [hl]
	ld hl, vTiles2 + LEN_2BPP_TILE * $50
	lb bc, BANK(PackFGFX), 15
	call Request2bpp
	ret

PackFGFXPointers:
	dw PackFGFX + (15 * LEN_2BPP_TILE) * 1 ; ITEM_POCKET
	dw PackFGFX + (15 * LEN_2BPP_TILE) * 3 ; BALL_POCKET
	dw PackFGFX + (15 * LEN_2BPP_TILE) * 0 ; KEY_ITEM_POCKET
	dw PackFGFX + (15 * LEN_2BPP_TILE) * 2 ; TM_HM_POCKET

PackFGFX:
INCBIN "gfx/pack/pack_f.2bpp"
