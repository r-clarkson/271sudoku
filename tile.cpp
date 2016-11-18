#include <stdio.h>
#include <iostream>
using namespace std;

class tile{
private:
  int value;
public:
  tile (){
    value = 0;
  }
  int getValue();
  void setValue(int number);
  bool clearTile();
};

bool tile::clearTile(){
  value = 0;
  return true;
}

void tile::setValue(int number){
  value = number;
}

int tile::getValue(){
  return value;
}
