#include "../constants.h"
#include "sine.h"

void Cosine(void){
    //  //  unreferenced
//  a = d * cos(a * pi/32)
    ADD_A(0b010000);  // cos(x) = sin(x + pi/2)
// fallthrough
    return Sine();
}

void Sine(void){
    //  a = d * sin(a * pi/32)
    LD_E_A;
    HOMECALL(av_Sine);
    RET;

}
