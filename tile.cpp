#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class tile{
private:
  int value;
  vector<int> triedValues;
  bool tileFilled;

public:
  tile (){
    value = 0;
    tileFilled = false;
  }
  int getValue();
  void setValue(int number);
  void clearTile();
  bool tried(int number);
  void tryNumber(int number);
  int amountTried();
  void reset();
  void show();
  void hide();
  bool getFilled();
};

void tile::tryNumber(int number){
  triedValues.push_back(number);
}
void tile::clearTile(){
  value = 0;
  tileFilled = false;
}

void tile::setValue(int number){
  value = number;
  tileFilled = true;
  triedValues.push_back(number);
}

int tile::getValue(){
  return value;
}

bool tile::tried(int number){
  std::vector<int>::iterator n = find(triedValues.begin(),triedValues.end(),number);
  if (n == triedValues.end()){
    return false;
  }
  return true;
}

int tile::amountTried(){
  return triedValues.size();
}

void tile::reset(){
  clearTile();
  triedValues.erase(triedValues.begin(),triedValues.end());
}

void tile::show(){
  tileFilled = true;
}
void tile::hide(){
  tileFilled = false;
}
bool tile::getFilled(){
  return tileFilled;
}
