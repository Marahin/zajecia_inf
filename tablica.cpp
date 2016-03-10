#include "tablica.h"
#include <cstdio>
#include <iostream>
#include <fstream>
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
  initscr();
  noecho();
  cbreak();   /* Line buffering disabled. pass on everything */
  clear();
  //mvaddch(1, 1, '.');
  move(1,1);
  for( unsigned int x=0; x<( map->height() ); x++ ){
    for( unsigned int y=0; y<( map->width()); y++){
      //printw("%c", (char) map->get(x, y) );
      mvaddch(x,y,map->get(x, y));
      //printf("%c", map->get(x, y));
    }
    //printf("\n");
  }
  unsigned int x = 0; unsigned int y = 0;
  find_entrance( map, x, y );
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

bool find_entrance(Tablica2D *map, unsigned int &tmp_pl_x, unsigned int &tmp_pl_y){
  unsigned int height = map->height();
  unsigned int width = map->width();
  unsigned int entrance_ = STAIRS_UP;

  for( unsigned int x=0; x<height; x++){
    for( unsigned int y=0; y<width; y++){
      if( map->get(x, y) == entrance_ ){
        // found entrance
        tmp_pl_x = x;
        tmp_pl_y = y;
        /*
        if( OPT_DBG_MODE ){ */
          cerr << "found entrance at (" << x << ", " << y+2 << ")" << endl;
        //}
        return true;
      }
    }
  }
  return false;
}
