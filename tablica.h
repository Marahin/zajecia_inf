#ifndef TABLICA_H
#define TABLICA_H

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

/* map elements */

#define WALL 35
#define FLOOR 46
#define STAIRS_DOWN 62
#define STAIRS_UP 60

/* items */
#define LOOT 42

/* monster */
#define MONSTER_RAT 114

/* eo map elements */



class Tablica2D{
public:
  Tablica2D(int w, int h);
  ~Tablica2D();
  unsigned int height();
  unsigned int width();
  /* first parameter: height, second parameter: width */
  void set( unsigned int h, unsigned int w, unsigned int value );
  unsigned int get( unsigned int h, unsigned int w );
private:
  /* do not copy objects that are not allowed to be copied */
  Tablica2D(const Tablica2D&);
  Tablica2D& operator = ( const Tablica2D& );
  /* .. */
  int ** tbl_;
  unsigned int w_;
  unsigned int h_;
};



/* functions */

bool find_entrance( Tablica2D* map, unsigned int &x, unsigned int &y );
Tablica2D* load_map( string filepath );
void draw( Tablica2D* map );


#endif //TABLICA_H
