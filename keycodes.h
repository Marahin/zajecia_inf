#include <vector>

#ifndef KEYCODES_H
#define KEYCODES_H


#define KC_ARROWKEY_UP 65
#define KC_ARROWKEY_DOWN 66
#define KC_ARROWKEY_LEFT 68
#define KC_ARROWKEY_RIGHT 67

#define KC_KEY_W 119
#define KC_KEY_A 97
#define KC_KEY_S 115
#define KC_KEY_D 100

#define KC_KEY_ESC NULL
#define KC_KEY_Q 113

static const std::vector<unsigned int> ARROWKEY_INITCODES = {27, 91};
bool codeInArrowKeyInitCodes(unsigned int keycode);

#endif
