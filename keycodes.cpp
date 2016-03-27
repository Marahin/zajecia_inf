#include "keycodes.h"
#include <algorithm>

bool codeInArrowKeyInitCodes( unsigned int keycode){
    if(
    std::find(
      ARROWKEY_INITCODES.begin(),
      ARROWKEY_INITCODES.end(), 
      keycode) != ARROWKEY_INITCODES.end()
    ){
      return true;
    }
    return false;
}
