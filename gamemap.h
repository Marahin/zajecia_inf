#ifndef GAMEMAP_H
#define GAMEMAP_H

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



class GameMap{
public:
  GameMap(int columns, int rows);
  ~GameMap();
  unsigned int height();
  unsigned int width();
  /* first parameter: height, second parameter: width */
  void set( unsigned int row, unsigned int column, unsigned int value );
  unsigned int get( unsigned int row, unsigned int column );
private:
  /* do not copy objects that are not allowed to be copied */
  GameMap(const GameMap&);
  GameMap& operator = ( const GameMap& );
  /* .. */
  int ** tbl_;
  unsigned int columns_;
  unsigned int rows_;
};



/* functions */

bool find_entrance( GameMap* map, unsigned int &x, unsigned int &y );
GameMap* load_map( string filepath );
void draw( GameMap* map );


#endif //TABLICA_H
