#include "tablica.h"
#include <cstdio>
#include <iostream>

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
