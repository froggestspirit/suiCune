LoadMapGroupRoof::
	ld a, [wMapGroup]
	ld e, a
	ld d, 0
	ld hl, MapGroupRoofs
	add hl, de
	ld a, [hl]
	cp -1
	ret z
	ld hl, Roofs
	ld bc, ROOF_LENGTH * LEN_2BPP_TILE
	call AddNTimes
	ld de, vTiles2 + LEN_2BPP_TILE * $0a
	ld bc, ROOF_LENGTH * LEN_2BPP_TILE
	call CopyBytes
	ret

INCLUDE "data/maps/roofs.asm"
