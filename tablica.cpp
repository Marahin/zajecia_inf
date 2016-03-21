#include "tablica.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include <ncurses.h>
using namespace std;


Tablica2D::Tablica2D( int w, int h )
:tbl_(nullptr), w_(w), h_(h)
{
  tbl_ = new int* [h_];
  for( unsigned int x=0; x< (unsigned int) h_; x++){
    tbl_[x] = new int [w_];
  }
}

Tablica2D::~Tablica2D(){
  for( unsigned int x=0; x<( unsigned int ) h_; x++){
    delete tbl_[x];
  }
  delete[] tbl_;
  tbl_ = nullptr; w_ = h_ = 0;
}

unsigned int Tablica2D::height(){
  return h_;
}

unsigned int Tablica2D::width(){
  return w_;
}

void Tablica2D::set(unsigned int height, unsigned int width, unsigned int value){
  tbl_[ height ][ width ] = value;
}

unsigned int Tablica2D::get( unsigned int height, unsigned int width){
  unsigned int value = tbl_[height][width];
  return value;
}

void draw( Tablica2D * map ){
  //mvaddch(1, 1, '.');
  for( unsigned int x=0; x<( map->width() ); x++){
    for( unsigned int y=0; y<( map->height() ); y++){
      //printw("%c", (char) map->get(x, y) );
      //mvaddch(x+1,y+1, (char) map->get(x, y));
      //printf("%c", map->get(x, y));
      mvaddch(x, y, (char) map->get(x, y));
      usleep(1500);
      refresh();
    }
    //printf("\n");
  }
  unsigned int x = 0; unsigned int y = 0;
  find_entrance( map, x, y );
  refresh();
}

bool isMapOk( Tablica2D *map, unsigned int width, unsigned int height){
  unsigned int tmp_el = 0;
  for( unsigned int y=0; y<width; y++){
    for( unsigned int x=0; x<height; x++){
      tmp_el = map->get(x, y);
      if( tmp_el != WALL && tmp_el != FLOOR && tmp_el != STAIRS_DOWN && tmp_el != STAIRS_UP && tmp_el != LOOT && tmp_el != MONSTER_RAT ){
        cerr << "ERR: the map has an unknown element at x: " << x << " and y: " << y << endl;
        return false;
      }
    }
  }
  return true;
}

Tablica2D* load_map(string filepath){
  ifstream fin;
  fin.open( filepath );
  unsigned int width, height;
  fin >> height >> width;
  /* declaring new object of Tablica2D class */
  Tablica2D* map = new Tablica2D( width, height );

  /* temporary cell we get our input inside */
  char tmp_cell;

  /* debug */
  cout << "DBG: MAP HEIGHT AND WIDTH: " << height << ", " << width << endl;

  /* filling the map */
  for( unsigned int x=0; x<height; x++){
    for( unsigned int y=0; y<width; y++){
      fin >> tmp_cell;
      cerr << "DBG: setting " << x << ", "<< y << " to " << tmp_cell << endl;
      map->set(x, y, tmp_cell);
    }
    cerr << "DBG: done did setting map";
  }

  fin.close();
  cerr << "DBG: checking if map is ok";
  if( isMapOk(map, width, height) ){
    return map;
  }
  else{
    cerr << "ERR: map is not OK, returning nullpointer" << endl;
    return nullptr;
  }
}


bool find_entrance(Tablica2D *map, unsigned int &tmp_pl_x, unsigned int &tmp_pl_y){
  unsigned int height = map->height();
  unsigned int width = map->width();
  unsigned int entrance_ = STAIRS_UP;
  for( unsigned int x=0; x<height-1; x++){
    for( unsigned int y=0; y<width-1; y++){
      if( map->get(x, y) == entrance_ ){
        // found entrance
        tmp_pl_x = x;
        tmp_pl_y = y;
        /*
        if( OPT_DBG_MODE ){ */
          cerr << endl << "found entrance at (" << x << ", " << y+2 << ")" << endl;
        //}
        return true;
      }
    }
  }
  return false;
}
