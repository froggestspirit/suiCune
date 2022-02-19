INCLUDE "gfx/font.asm"

EnableHDMAForGraphics:
	db FALSE

Get1bppOptionalHDMA: ; unreferenced
	ld a, [EnableHDMAForGraphics]
	and a
	jp nz, Get1bppViaHDMA
	jp Get1bpp

Get2bppOptionalHDMA: ; unreferenced
	ld a, [EnableHDMAForGraphics]
	and a
	jp nz, Get2bppViaHDMA
	jp Get2bpp

_LoadStandardFont::
	ld de, Font
	ld hl, vTiles1
	lb bc, BANK(Font), 128 ; "A" to "9"
	ldh a, [rLCDC]
	bit rLCDC_ENABLE, a
	jp z, Copy1bpp

	ld de, Font
	ld hl, vTiles1
	lb bc, BANK(Font), 32 ; "A" to "]"
	call Get1bppViaHDMA
	ld de, Font + 32 * LEN_1BPP_TILE
	ld hl, vTiles1 + LEN_2BPP_TILE * $20
	lb bc, BANK(Font), 32 ; "a" to $bf
	call Get1bppViaHDMA
	ld de, Font + 64 * LEN_1BPP_TILE
	ld hl, vTiles1 + LEN_2BPP_TILE * $40
	lb bc, BANK(Font), 32 ; "Ä" to "←"
	call Get1bppViaHDMA
	ld de, Font + 96 * LEN_1BPP_TILE
	ld hl, vTiles1 + LEN_2BPP_TILE * $60
	lb bc, BANK(Font), 32 ; "'" to "9"
	call Get1bppViaHDMA
	ret

_LoadFontsExtra1::
	ld de, FontsExtra_SolidBlackGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * "■" ; $60
	lb bc, BANK(FontsExtra_SolidBlackGFX), 1
	call Get1bppViaHDMA
	ld de, PokegearPhoneIconGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * "☎" ; $62
	lb bc, BANK(PokegearPhoneIconGFX), 1
	call Get2bppViaHDMA
	ld de, FontExtra + 3 * LEN_2BPP_TILE ; "<BOLD_D>"
	ld hl, vTiles2 + LEN_2BPP_TILE * "<BOLD_D>"
	lb bc, BANK(FontExtra), 22 ; "<BOLD_D>" to "ぉ"
	call Get2bppViaHDMA
	jr LoadFrame

_LoadFontsExtra2::
	ld de, FontsExtra2_UpArrowGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * "▲" ; $61
	ld b, BANK(FontsExtra2_UpArrowGFX)
	ld c, 1
	call Get2bppViaHDMA
	ret

_LoadFontsBattleExtra::
	ld de, FontBattleExtra
	ld hl, vTiles2 + LEN_2BPP_TILE * $60
	lb bc, BANK(FontBattleExtra), 25
	call Get2bppViaHDMA
	jr LoadFrame

LoadFrame:
	ld a, [wTextboxFrame]
	maskbits NUM_FRAMES
	ld bc, TEXTBOX_FRAME_TILES * LEN_1BPP_TILE
	ld hl, Frames
	call AddNTimes
	ld d, h
	ld e, l
	ld hl, vTiles2 + LEN_2BPP_TILE * "┌" ; $79
	lb bc, BANK(Frames), TEXTBOX_FRAME_TILES ; "┌" to "┘"
	call Get1bppViaHDMA
	ld hl, vTiles2 + LEN_2BPP_TILE * " " ; $7f
	ld de, TextboxSpaceGFX
	lb bc, BANK(TextboxSpaceGFX), 1
	call Get1bppViaHDMA
	ret

LoadBattleFontsHPBar:
	ld de, FontBattleExtra
	ld hl, vTiles2 + LEN_2BPP_TILE * $60
	lb bc, BANK(FontBattleExtra), 12
	call Get2bppViaHDMA
	ld hl, vTiles2 + LEN_2BPP_TILE * $70
	ld de, FontBattleExtra + 16 * LEN_2BPP_TILE ; "<DO>"
	lb bc, BANK(FontBattleExtra), 3 ; "<DO>" to "『"
	call Get2bppViaHDMA
	call LoadFrame

LoadHPBar:
	ld de, EnemyHPBarBorderGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * $6c
	lb bc, BANK(EnemyHPBarBorderGFX), 4
	call Get1bppViaHDMA
	ld de, HPExpBarBorderGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * $73
	lb bc, BANK(HPExpBarBorderGFX), 6
	call Get1bppViaHDMA
	ld de, ExpBarGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * $55
	lb bc, BANK(ExpBarGFX), 9
	call Get2bppViaHDMA
	ld de, MobilePhoneTilesGFX + 7 * LEN_2BPP_TILE ; mobile phone icon
	ld hl, vTiles2 + LEN_2BPP_TILE * $5e
	lb bc, BANK(MobilePhoneTilesGFX), 2
	call Get2bppViaHDMA
	ret

StatsScreen_LoadFont:
	call _LoadFontsBattleExtra
	ld de, EnemyHPBarBorderGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * $6c
	lb bc, BANK(EnemyHPBarBorderGFX), 4
	call Get1bppViaHDMA
	ld de, HPExpBarBorderGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * $78
	lb bc, BANK(HPExpBarBorderGFX), 1
	call Get1bppViaHDMA
	ld de, HPExpBarBorderGFX + 3 * LEN_1BPP_TILE
	ld hl, vTiles2 + LEN_2BPP_TILE * $76
	lb bc, BANK(HPExpBarBorderGFX), 2
	call Get1bppViaHDMA
	ld de, ExpBarGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * $55
	lb bc, BANK(ExpBarGFX), 8
	call Get2bppViaHDMA
LoadStatsScreenPageTilesGFX:
	ld de, StatsScreenPageTilesGFX
	ld hl, vTiles2 + LEN_2BPP_TILE * $31
	lb bc, BANK(StatsScreenPageTilesGFX), 17
	call Get2bppViaHDMA
	ret
