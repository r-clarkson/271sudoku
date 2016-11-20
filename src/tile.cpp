#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
/**
* This class represents an individual value/tile of the puzzle
*/
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
  bool getFilled();
};
/**
* Adds a number to the tile's tried values
*/
void tile::tryNumber(int number){
  triedValues.push_back(number);
}
/**
* Clears tile's value and marks it as unfilled
*/
void tile::clearTile(){
  value = 0;
  tileFilled = false;
}
/**
* Sets tile's value
*/
void tile::setValue(int number){
  value = number;
  tileFilled = true;
  triedValues.push_back(number);
}
/**
* Returns tile's value
*/
int tile::getValue(){
  return value;
}
/**
* Checks to see if a number is in tile's tried values vector
* Returns false if it has not been tried, true if it has been tried
*/
bool tile::tried(int number){
  std::vector<int>::iterator n = find(triedValues.begin(),triedValues.end(),number);
  if (n == triedValues.end()){
    return false;
  }
  return true;
}
/**
* Returns number of values in tried values vector
*/
int tile::amountTried(){
  return triedValues.size();
}
/**
* Resets tile by clearing it and then erasing tried values vector
*/
void tile::reset(){
  clearTile();
  triedValues.erase(triedValues.begin(),triedValues.end());
}
/**
* Returns true if tile is filled, false if it is unfilled
*/
bool tile::getFilled(){
  return tileFilled;
}
