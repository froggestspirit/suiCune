#include "../constants.h"
#include "time_palettes.h"

void UpdateTimeAndPals(void){
    //  update time and time-sensitive palettes

//  rtc enabled?
    LD_A_addr(wSpriteUpdatesEnabled);
    CP_A(0);
    RET_Z ;

    CALL(aUpdateTime);

//  obj update on?
    LD_A_addr(wVramState);
    BIT_A(0);  // obj update
    RET_Z ;

    return TimeOfDayPals();
}

void TimeOfDayPals(void){
        CALLFAR(av_TimeOfDayPals);
    RET;

}

void UpdateTimePals(void){
        CALLFAR(av_UpdateTimePals);
    RET;

}
