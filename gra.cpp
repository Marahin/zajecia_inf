#include <cstdio>
#include <iostream>
#include <fstream>
#include <ncurses.h>

#include "tablica.h"

using namespace std;

void draw( Tablica2D* map_obj ){
  /* ... */
}

Tablica2D* load_map(string filepath){
  ifstream fin;
  fin.open( filepath );
  unsigned int width, height;
  fin >> width >> height;
  /* declaring new object of Tablica2D class */
  Tablica2D* map = new Tablica2D( width, height );

  /* temporary cell we get our input inside */
  char tmp_cell; 

  /* filling the map */
  for( unsigned int x=0; x<height; x++){
    for( unsigned int y=0; y<width; y++){
      tmp_cell = getch();
      map->set(x, y, tmp_cell);
    }
  }
  fin.close();
}


int main( int argc, char* argv[]){
  /* ncurses */
  initscr();
  timeout(-1);
  /* eo ncurses */

  Tablica2D *map = load_map("map.txt");
  draw( map );

  /* ncurses */
  endwin();
  /* eo ncurses */
  return 0;
}
