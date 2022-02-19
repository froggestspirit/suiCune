#include "../constants.h"
#include "region.h"

void IsInJohto(void){
    //  Return 0 if the player is in Johto, and 1 in Kanto.

    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);

    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto Johto;

    CP_A(LANDMARK_SPECIAL);
    IF_NZ goto CheckRegion;

    LD_A_addr(wBackupMapGroup);
    LD_B_A;
    LD_A_addr(wBackupMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);


CheckRegion:
        CP_A(KANTO_LANDMARK);
    IF_NC goto Kanto;


Johto:
        XOR_A_A;  // JOHTO_REGION
    RET;


Kanto:
        LD_A(KANTO_REGION);
    RET;

}

void SetXYCompareFlags(void){
    //  //  dummied out
    RET;

}
