#ifndef TABLICA_H
#define TABLICA_H

class Tablica2D{
public:
  Tablica2D(int w, int h);
  ~Tablica2D();
  unsigned int height();
  unsigned int width();
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

#endif //TABLICA_H
