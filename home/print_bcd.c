#include "../constants.h"
#include "print_bcd.h"

void PrintBCDNumber(void){
    //  function to print a BCD (Binary-coded decimal) number
//  de = address of BCD number
//  hl = destination address
//  c = flags and length
//  bit 7: if set, do not print leading zeroes
//         if unset, print leading zeroes
//  bit 6: if set, left-align the string (do not pad empty digits with spaces)
//         if unset, right-align the string
//  bit 5: if set, print currency symbol at the beginning of the string
//         if unset, do not print the currency symbol
//  bits 0-4: length of BCD number in bytes
//  Note that bits 5 and 7 are modified during execution. The above reflects
//  their meaning at the beginning of the functions's execution.
    LD_B_C;  // save flags in b
    RES_C(PRINTNUM_LEADINGZEROS_F);
    RES_C(PRINTNUM_LEFTALIGN_F);
    RES_C(PRINTNUM_MONEY_F);  // c now holds the length
    BIT_B(PRINTNUM_MONEY_F);
    IF_Z goto loop;
    BIT_B(PRINTNUM_LEADINGZEROS_F);
    IF_NZ goto loop;  // skip currency symbol
    LD_hl(0xf0);
    INC_HL;

loop:
        LD_A_de;
    SWAP_A;
    CALL(aPrintBCDDigit);  // print upper digit
    LD_A_de;
    CALL(aPrintBCDDigit);  // print lower digit
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    BIT_B(PRINTNUM_LEADINGZEROS_F);
    IF_Z goto done;  // if so, we are done
//  every digit of the BCD number is zero
    BIT_B(PRINTNUM_LEFTALIGN_F);
    IF_NZ goto skipLeftAlignmentAdjustment;
//  the string is left-aligned
    DEC_HL;

skipLeftAlignmentAdjustment:
        BIT_B(PRINTNUM_MONEY_F);
    IF_Z goto skipCurrencySymbol;
    LD_hl(0xf0);  // currency symbol
    INC_HL;

skipCurrencySymbol:
        LD_hl(0xf6);
    CALL(aPrintLetterDelay);
    INC_HL;

done:
        RET;

}

void PrintBCDDigit(void){
        AND_A(0b00001111);
    AND_A_A;
    IF_Z goto zeroDigit;
//  nonzero digit
    BIT_B(PRINTNUM_LEADINGZEROS_F);  // have any non-space characters been printed?
    IF_Z goto outputDigit;
//  if bit 7 is set, then no numbers have been printed yet
    BIT_B(PRINTNUM_MONEY_F);
    IF_Z goto skipCurrencySymbol;
    LD_hl(0xf0);
    INC_HL;
    RES_B(PRINTNUM_MONEY_F);

skipCurrencySymbol:
        RES_B(PRINTNUM_LEADINGZEROS_F);  // unset 7 to indicate that a nonzero digit has been reached

outputDigit:
        ADD_A(0xf6);
    LD_hli_A;
    JP(mPrintLetterDelay);


zeroDigit:
        BIT_B(PRINTNUM_LEADINGZEROS_F);  // either printing leading zeroes or already reached a nonzero digit?
    IF_Z goto outputDigit;  // if so, print a zero digit
    BIT_B(PRINTNUM_LEFTALIGN_F);
    RET_NZ ;
    LD_A(0x7f);
    LD_hli_A;  // if right-aligned, "print" a space by advancing the pointer
    RET;

}
