#ifndef PLAYER
#define PLAYER

#include <cstdio>
#include <iostream>
using namespace std;

class Player{
public:
  Player(string name);
  unsigned int positionX();
  unsigned int positionY();
  void setPosition(unsigned int x, unsigned int y);
private:
  Player(const Player&);
  Player& operator = ( const Player& );

  unsigned int posX;
  unsigned int posY;
};


#endif
