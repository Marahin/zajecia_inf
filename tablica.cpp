#include "tablica.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include <ncurses.h>
using namespace std;


Tablica2D::Tablica2D( int rows, int columns )
:tbl_(nullptr), columns_(columns), rows_(rows)
{
  tbl_ = new int* [rows_];
  for( unsigned int x=0; x< (unsigned int) rows_; x++){
    tbl_[x] = new int [columns_];
  }
}

Tablica2D::~Tablica2D(){
  for( unsigned int x=0; x<( unsigned int ) rows_; x++){
    delete tbl_[x];
  }
  delete[] tbl_;
  tbl_ = nullptr; columns_ = rows_ = 0;
}

unsigned int Tablica2D::height(){
  return rows_;
}

unsigned int Tablica2D::width(){
  return columns_;
}

void Tablica2D::set(unsigned int row, unsigned int column, unsigned int value){
  tbl_[ row ][ column ] = value;
}

unsigned int Tablica2D::get( unsigned int row, unsigned int column){
  unsigned int value = tbl_[row][column];
  return value;
}

void draw( Tablica2D * map ){
  cerr << "drawing map..." << endl;
  for( unsigned int rows = 0; rows < map->height(); rows++ ){
    for( unsigned int columns = 0; columns < map->width(); columns++){
      mvaddch(rows, columns, (char) map->get(rows, columns));
      refresh();
      usleep(3050);
    }
  }

  unsigned int x = 0; unsigned int y = 0;
  find_entrance(map, x, y);
  refresh();
}

bool isMapOk( Tablica2D *map, unsigned int rows, unsigned int columns){
  unsigned int tmp_el = 0;
  for( unsigned int column=0; column<columns; column++){
    for( unsigned int row=0; row<rows; row++){
      tmp_el = map->get(row, column);
      if( tmp_el != WALL && tmp_el != FLOOR && tmp_el != STAIRS_DOWN && tmp_el != STAIRS_UP && tmp_el != LOOT && tmp_el != MONSTER_RAT ){
        cerr << "Unknown element at: column " << column << ", row " << row << "(" << (char) tmp_el << ")" << endl;
        return false;
      }
    }
  }
  return true;
}

Tablica2D* load_map(string filepath){
  ifstream fin;
  fin.open( filepath );
  unsigned int columns, rows;
  fin >> rows >> columns;
  /* declaring new object of Tablica2D class */
  Tablica2D* map = new Tablica2D( rows, columns );

  /* temporary cell we get our input inside */
  char tmp_cell;

  /* debug */
  cout << "DBG: MAP rows AND columns: " << rows << ", " << columns << endl;

  /* filling the map */
  for( unsigned int row=0; row<rows; row++){
    for( unsigned int column=0; column<columns; column++){
      fin >> tmp_cell;
      cerr << "DBG: setting " << column << ", "<< row << " to " << tmp_cell << endl;
      map->set(row, column, tmp_cell);
    }
    cerr << "DBG: done did setting map";
  }

  fin.close();
  cerr << "DBG: checking if map is ok";
  if( isMapOk(map, rows, columns) ){
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
