#ifndef PLAYER
#define PLAYER

#include <string>

class Player{
public:
  Player(std::string name);
  unsigned int positionX();
  unsigned int positionY();
  void setPosition(unsigned int x, unsigned int y);
private:
  Player(const Player&);
  Player& operator = ( const Player& );
  std::string name;
  unsigned int posX;
  unsigned int posY;
};

Player* createPlayer( std::string nickname );

#endif
