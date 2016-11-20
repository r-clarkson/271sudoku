#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
/**
* Meat & Bones of creating sudoku puzzle
* Some function concepts based on http://stackoverflow.com/questions/15690254/how-to-generate-a-complete-sudoku-board-algorithm-error
*/
class puzzleGenerator{
private:
  tile** puzzle;
public:
  puzzleGenerator(){
    srand (time(NULL));
    puzzle = new tile*[9];
    for (int i = 0; i < 9; ++i){
      puzzle[i] = new tile[9];
    }

    for (int i = 0; i < 9; ++i){
      for (int j = 0; j < 9; ++j){
        puzzle[i][j] = tile();
      }
    }
  }

  void clearPuzzle();
  void resetPuzzle();

  bool checkBox(int number,int row, int col);
  bool checkRow(int number, int row);
  bool checkColumn(int number, int col);
  bool checkPuzzle(int number, int col, int row);

  int nextRow(int row, int col);
  int nextCol(int row, int col);
  tile nextTile(int row, int col);
  int randomIndex();
  void generatePuzzle(int row, int col);
  void deletePuzzle();

  void printPuzzle();
  int getVal(int row, int col);
};

/**
* Returns value of certain tile in puzzle
*/
int puzzleGenerator::getVal(int row, int col){
  return puzzle[row][col].getValue();
}
/**
* Prints all puzzle values (used for testing)
*/
void puzzleGenerator::printPuzzle(){
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      cout << puzzle[i][j].getValue() << endl;
    }
  }
}
/**
* Clears all puzzle values
*/
void puzzleGenerator::clearPuzzle(){
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      puzzle[i][j].clearTile();
    }
  }
}
/**
* Resets all values and tried values for puzzle tiles
*/
void puzzleGenerator::resetPuzzle(){
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      puzzle[i][j].reset();
    }
  }
}
/**
* Checks whether a value will work based on surrounding box values
*/
bool puzzleGenerator::checkBox(int number,int row, int col){
  int r = row+1, c = col+1;
  if (r % 3 == 0) {
    r -= 3;
  } else {
    r = (r / 3) * 3;
  }
  if (c % 3 == 0) {
    c -= 3;
  } else {
    c = (c / 3) * 3;
  }
  for (int i = r; i < r + 3; ++i) {
    for (int j = c; j < c + 3; ++j) {
      if (puzzle[i][j].getFilled() && (puzzle[i][j].getValue() == number)) {
        return false;
      }
    }
  }
  return true;
}
/**
* Checks whether a value will work based on surrounding row tiles
*/
bool puzzleGenerator::checkRow(int number, int row){
  for (int i = 0; i < 9; ++i) {
    if (puzzle[row][i].getFilled() && puzzle[row][i].getValue() == number) {
      return false;
    }
  }
  return true;
}
/**
* Checks whether a value will work based on surrounding column tiles
*/
bool puzzleGenerator::checkColumn(int number, int col){
  for (int i = 0; i < 9; ++i) {
    if (puzzle[i][col].getFilled() && puzzle[i][col].getValue() == number) {
      return false;
    }
  }
  return true;
}
/**
* Combines checkbox, checkrow, and checkcolumn to make sure value will work in all three before setting it
*/
bool puzzleGenerator::checkPuzzle(int number, int row, int col){
  return (checkBox(number, row, col)
  && checkRow(number, row)
  && checkColumn(number, col));
}
/**
* Adds to row/column and returns the next tile to be filled
*/
tile puzzleGenerator::nextTile(int row, int col){
  int r = row, c = col;
  if (c < 8) {
    c++;
  } else {
    c = 0;
    r++;
  }
  return puzzle[r][c];
}
/**
* Returns the row of the next tile to be filled
*/
int puzzleGenerator::nextRow(int row, int col){
  int r = row, c = col;
  if (c < 8) {
    c++;
  } else {
    c = 0;
    r++;
  }
  return r;
}
/**
* Returns the column of the next tile to be filled
*/
int puzzleGenerator::nextCol(int row, int col){
  int r = row, c = col;
  if (c < 8) {
    c++;
  } else {
    c = 0;
    r++;
  }
  return c;
}
/**
* Returns a random number between 1-9 (rand is seeded in class constructor)
*/
int puzzleGenerator::randomIndex(){
  return ((rand() % 9) + 1);
}
/**
* Generates the puzzle recursively (tile-by-tile) using class functions... see further comments within
*/
void puzzleGenerator::generatePuzzle(int row, int column){
  //We begin with 1,1, so they must be set down to 0,0 of the array of tiles
  row = row-1;
  column = column-1;
  //will continue until last array tile is filled
  if (!puzzle[8][8].getFilled()){
    //when all numbers 1-9 have not been tried, generates a random number that hasn't been tried
    while (puzzle[row][column].amountTried() < 8){
      int candidate = 0;
      do {
        candidate = randomIndex();
      } while(puzzle[row][column].tried(candidate));
      //if value works for given tile (checked with check functions), sets the value and uses recursion to set the next tile
      if (checkPuzzle(candidate,row,column)){
        puzzle[row][column].setValue(candidate);
        //when the row and column are 8 (9x9=81), stops making tiles
        if (row == 8 && column == 8){
          return;
        }
        tile next = nextTile(row, column);
        if (nextRow(row, column) <= 8 && nextCol(row, column) <= 8) {
          generatePuzzle(nextRow(row, column)+1, nextCol(row, column)+1);
        }
      }
      else{
        //adds the value to the vector of tried values for tile and then continues without recursion
        puzzle[row][column].tryNumber(candidate);
      }
    }
    //if the value didn't work, recursion didn't happen: this backtracks by resetting the tile
    if (!puzzle[8][8].getFilled()){
      puzzle[row][column].reset();
    }
  }
}
/**
* Deletes the puzzle/frees memory
*/
void puzzleGenerator::deletePuzzle(){
  for (int i =0; i < 9; ++i){
    delete [] puzzle[i];
  }
  delete [] puzzle;
}
