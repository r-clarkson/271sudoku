#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

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

int puzzleGenerator::getVal(int row, int col){
  return puzzle[row][col].getValue();
}

void puzzleGenerator::printPuzzle(){
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      cout << puzzle[i][j].getValue() << endl;
    }
  }
}
void puzzleGenerator::clearPuzzle(){
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      puzzle[i][j].clearTile();
    }
  }
}


void puzzleGenerator::resetPuzzle(){
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      puzzle[i][j].reset();
    }
  }
}

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

bool puzzleGenerator::checkRow(int number, int row){
  for (int i = 0; i < 9; ++i) {
    if (puzzle[row][i].getFilled() && puzzle[row][i].getValue() == number) {
      return false;
    }
  }
  return true;
}

bool puzzleGenerator::checkColumn(int number, int col){
  for (int i = 0; i < 9; ++i) {
    if (puzzle[i][col].getFilled() && puzzle[i][col].getValue() == number) {
      return false;
    }
  }
  return true;
}

bool puzzleGenerator::checkPuzzle(int number, int row, int col){
  return (checkBox(number, row, col)
  && checkRow(number, row)
  && checkColumn(number, col));
}

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

int puzzleGenerator::randomIndex(){
  return ((rand() % 9) + 1);
}

void puzzleGenerator::generatePuzzle(int row, int column){
  row = row-1;

  column = column-1;

  if (!puzzle[8][8].getFilled()){
    while (puzzle[row][column].amountTried() < 8){
      int candidate = 0;
      do {
        candidate = randomIndex();
      } while(puzzle[row][column].tried(candidate));
      if (checkPuzzle(candidate,row,column)){
        puzzle[row][column].setValue(candidate);
        if (row == 8 && column == 8){
          return;
        }
        tile next = nextTile(row, column);
        if (nextRow(row, column) <= 8 && nextCol(row, column) <= 8) {
          generatePuzzle(nextRow(row, column)+1, nextCol(row, column)+1);
        }
      }
      else{
        puzzle[row][column].tryNumber(candidate);
      }
    }
    if (!puzzle[8][8].getFilled()){
      puzzle[row][column].reset();
    }
  }
}

void puzzleGenerator::deletePuzzle(){
  for (int i =0; i < 9; ++i){
    delete [] puzzle[i];
  }
  delete [] puzzle;
}
