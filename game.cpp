#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <sstream>

#include "gamemap.h"
#include "common.h"
#include "keycodes.h"

using namespace std;


bool OPT_DBG_MODE = false;

void debug(){
  cerr << "CODES: " << endl;
  cerr << "\
  WALL " << WALL << endl << "\
  FLOOR " << FLOOR << endl << "\
  STAIRS_DOWN " << STAIRS_DOWN << endl << "\
  STAIRS_UP " << STAIRS_UP << endl << "\
  LOOT " << LOOT << endl << "\
  MONSTER_RAT " << MONSTER_RAT << endl;
}


int main( int argc, char* argv[]){
  OPT_DBG_MODE = false;
  /* getting the flags up */
  for(int x=0; x<argc; x++){
    if( string( argv[x] ) == "--debug" ){
      OPT_DBG_MODE = true;
    }
  }

  if( OPT_DBG_MODE ){
    debug();
  }
  /* end of flags, main program */

  initscr();
  noecho();
  cbreak();   /* Line buffering disabled. pass on everything */
  clear();

  GameMap* map = load_map("map.txt");

  /* exit code - 0 if ok, -1 if something went bad */
  unsigned int EXIT_CODE = 0;
  if( map != nullptr){
    cerr << "drawing map " << endl;
    draw( map );

    /* debug output stream */
    stringstream kc_dbg_string_;

    /* receiving the first touch! */
    unsigned int keycode_ = getch();

    /* main loop */

    while( true ){
      kc_dbg_string_ << "Received ";
      if( keycode_ == KC_KEY_ESC || keycode_ == KC_KEY_Q ){
        break;
      } else if( codeInArrowKeyInitCodes( keycode_ ) ){
          /* code received is not the real key code */
          /* so we have to access the next buffered value */
          /* in order to get the real mvp value */
          //keycode_ = getch();
          kc_dbg_string_ << "GATEWAY KEYCODE ";
      } else if( keycode_ == KC_KEY_W || keycode_ == KC_ARROWKEY_UP ){
        kc_dbg_string_ << "key (UP) ";
      } else if( keycode_ == KC_KEY_A || keycode_ == KC_ARROWKEY_LEFT){
        kc_dbg_string_ << "key (LEFT) ";
      } else if( keycode_ == KC_KEY_S || keycode_ == KC_ARROWKEY_DOWN){
        kc_dbg_string_ << "key (DOWN) ";
      } else if( keycode_ == KC_KEY_D || keycode_ == KC_ARROWKEY_RIGHT){
        kc_dbg_string_ << "key (RIGHT) ";
      } else{
        kc_dbg_string_ << "UNRECOGNIZED KEY ";
      }
      kc_dbg_string_ << "(code: " << keycode_ << ").\n";
      /* if the debug flag is passed - lets print that info out! */
      if( OPT_DBG_MODE ){ cerr << kc_dbg_string_.str(); }
      /* let's clear our info stream */
      kc_dbg_string_.str( string() );

      /* let's get our input back again! */
      keycode_ = getch();
    }
  }
  else{
    EXIT_CODE = -1;
  }
  refresh();
  endwin();
  return EXIT_CODE;
}
