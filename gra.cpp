#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "tablica.h"

using namespace std;


bool OPT_DBG_MODE;

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

  Tablica2D* map = load_map("map.txt");

  /* exit code - 0 if ok, -1 if something went bad */
  unsigned int EXIT_CODE = 0;
  if( map != nullptr){
    cerr << "drawing map " << endl;
    draw( map );
    while( getch() != 'q' ){

    }
  }
  else{
    EXIT_CODE = -1;
  }
  refresh();
  endwin();
  return EXIT_CODE;
}
