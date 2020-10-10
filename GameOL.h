//Ben Bartol
//Student ID: 2315721
//Student Email: bartol@chapman.edu
//CPSC 350
//Assignment 2 Game of Life

#include <iostream>
#include <fstream>

using namespace std;

class GameOL{

private:
  int genCount;
  string outputStyle;
  string outFileName;
  string outputString;

public:
  GameOL();
  ~GameOL();

  void makeRandBoard(int& boardLength, int& boardWidth);
  void makeFileBoard(string inputfile);

  void chooseSettings();
  void chooseMode(int& boardLength, int& boardWidth, char**& board);
  void printOptions(string outputStyle, int genCount, char**& board, int boardLength, int boardWidth);

  //Game Modes
  int classicMode(int boardLength, int boardWidth, char**& board);
  int mirrorMode(int boardLength, int boardWidth, char**& board);
  int donutMode(int boardLength, int boardWidth, char**& board);


};
