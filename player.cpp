#include "player.h"

#include <cstdio>
#include <string>
#include <iostream>

Player::Player(std::string name_)
:name(name_), posX(0), posY(0)
{
}

unsigned int Player::positionX(){
  return posX;
}

unsigned int Player::positionY(){
  return posY;
}

void Player::setPosition( unsigned int x, unsigned int y ){
  posX = x;
  posY = y;
}

Player* createPlayer( std::string nickname ){
  /* TODO: insert nickname validation here */
  return (Player*) new Player(nickname);
}
