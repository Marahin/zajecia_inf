#include "player.h"

Player::Player(string name)
{
  posX = 0;
  posY = 0;
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
