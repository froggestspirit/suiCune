#include "../constants.h"
#include "hm_moves.h"

//  HM moves can't be forgotten

void IsHM(void){
        CP_A(HM01);
    IF_C goto NotHM;
    SCF;
    RET;

NotHM:
        AND_A_A;
    RET;

}

void IsHMMove(void){
        LD_HL(mIsHMMove_HMMoves);
    LD_DE(1);
    JP(mIsInArray);


HMMoves:
        //db ['CUT'];
    //db ['FLY'];
    //db ['SURF'];
    //db ['STRENGTH'];
    //db ['FLASH'];
    //db ['WATERFALL'];
    //db ['WHIRLPOOL'];
    //db ['-1'];  // end

}
