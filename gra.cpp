#include <cstdio>
#include <iostream>
#include <fstream>
#include <ncurses.h>

#include "tablica.h"

using namespace std;

void draw( Tablica2D * map ){
  //cerr << "trying to draw" << endl;
  clear();
  move( 1, 1);
  for( unsigned int x=0; x<( map->height() ); x++ ){
    for( unsigned int y=0; y<( map->width()); y++){
      //cerr << "trying to get data at (" << x << ", " << y << ")" << endl;
      addch( map->get(x, y) );
    }
  }
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
      fin >> tmp_cell;
      map->set(x, y, tmp_cell);
    }
  }

  fin.close();
  return map;
}

int main( int argc, char* argv[]){
  initscr();

  
  Tablica2D* map = load_map("map.txt");
  draw( map );

  endwin();
  return 0;
}
