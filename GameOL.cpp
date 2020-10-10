//Ben Bartol
//Student ID: 2315721
//Student Email: bartol@chapman.edu
//CPSC 350
//Assignment 2 Game of Life

#include "GameOL.h"
#include <fstream>
#include <string>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

//default constructor
GameOL::GameOL(){
  string outputStyle = "";
  int genCount;
  string outputString = "";
  string outFileName = "";
}

//destructor
GameOL::~GameOL(){
}

void GameOL::chooseSettings(){
  string boardSetting = "";
  bool choice1 = true;
  bool choice2 = false;

  while(choice1 == true){
    //first, selecting how they want the board printed
    //you can choose between printed in a file, with a pause, or by enter key
    cout << "How would you like your data printed? ('file', 'pause', 'enter')" << endl;
    cin >> outputStyle;

    if((outputStyle == "File")||(outputStyle == "file")){

      cout << "What is the name of the file you'd like to print to?" << endl;
      cin >> outFileName;

      choice1 = false;


    }else if((outputStyle == "Pause")||(outputStyle == "pause")){
      choice1 = false;

    }else if((outputStyle == "Enter")||(outputStyle == "enter")){
      choice1 = false;

    }else{
      cout << "Please try again\n" << endl;
      choice1 = true;
    }
  }

  while(choice2 == false){
    //secondly, choosing between a random board or submitting their own
    string outFileName = "";

    cout << "Would you like to use a random board or use your own file? ('random', 'file')" << endl;
    cin >> boardSetting;

    if((boardSetting == "Random")||(boardSetting == "random")){
      int boardLength = 0;
      int boardWidth = 0;

      makeRandBoard(boardLength, boardWidth);
      choice2 = false;

    }else if((boardSetting == "File")||(boardSetting == "file")){

      string fileName;

      cout << "What is the name of the file you'd like you use?" << endl;
      cin >> fileName;

      makeFileBoard(fileName);

      choice2 = true;

    }else{

      cout << "Please try again\n" << endl;
      choice2 = false;
    }
  }

}

void GameOL::makeFileBoard(string inputfile){

  ifstream inFS;

  inFS.open(inputfile.c_str());

  int boardLength = 0;
  int boardWidth = 0;
  int counter = 0;
  string line = "";

  while(!inFS.eof()){
    getline(inFS, line);

    if(counter == 0){
      boardLength = atoi(line.c_str());
    }else if(counter == 1){
      boardWidth = atoi(line.c_str());
    }else{
      break;
    }
    counter++;
  }

  counter = 0;

  char** transferBoard = new char*[boardLength];

  for(int i = 0; i < boardLength; ++i){
    transferBoard[i] = new char[boardWidth];
  }

  for(int i = 0; i < boardLength; ++i){
    for(int j = 0; j < boardWidth; ++j){
      transferBoard[i][j] = '-';
    }
  }
  inFS.seekg(0, inFS.beg);
  int row = 0;

  while(!inFS.eof()){
    getline(inFS, line);

    if(counter == 0){
    }else if(counter == 1){
    }else{
      for(int i = 0; i < boardWidth; i++){
        char element = line[i];
        transferBoard[row][i] = element;
      }
      row++;
    }
    counter++;
  }

  chooseMode(boardLength, boardWidth, transferBoard);

}

void GameOL::makeRandBoard(int& boardLength, int& boardWidth){

  double density = 0.0;
  bool validInput = false;
  int numCells = 0;
  int randLength = 0;
  int randWidth = 0;

  cout << "What do you want the length of the board to be?" << endl;
  cin >> boardLength;

  cout << "What do you want the width of the board to be?" << endl;
  cin >> boardWidth;

  while(validInput == false){
    cout << "Give me a number between 0 and 1 that will be the density value" << endl;
    cin >> density;

    if((density >= 0) && (density <= 1)){
      validInput = true;
    }else{
      validInput = false;
    }

  }
  char** transferBoard = new char*[boardLength];

  for(int i = 0; i < boardLength; ++i){
    transferBoard[i] = new char[boardWidth];
  }

  numCells = round((boardLength*boardWidth)*density);

  for(int i = 0; i < boardLength; i++){
    for(int j = 0; j < boardWidth; j++){
      transferBoard[i][j] = '-';
    }
  }

  srand(time(NULL));

  for(int k = 0; k < numCells; k++){
    randLength = rand() % (boardLength);
    randWidth = rand() % (boardWidth);

    int numOfCells = 1;
    while(numOfCells > 0){
      if(transferBoard[randLength][randWidth] == '-'){
        transferBoard[randLength][randWidth] = 'X';
        numOfCells--;
      }else{
        randLength = rand() % (boardLength);
        randWidth = rand() % (boardWidth);
      }
    }
  }
  chooseMode(boardLength, boardWidth, transferBoard);


}


void GameOL::chooseMode(int& boardLength, int& boardWidth, char**& board){
  string modeChoice;
  bool keepGoing = true;

  while(keepGoing == true){
    cout << "Choose your game mode: Classic, Mirror, or Donut" << endl;
    cin >> modeChoice;

    if((modeChoice == "Classic")||(modeChoice == "classic")){
      classicMode(boardLength, boardWidth, board);
      keepGoing = false;
    }else if((modeChoice == "Mirror")||(modeChoice == "mirror")){
      mirrorMode(boardLength, boardWidth, board);
      keepGoing = false;
    }else if((modeChoice == "Donut")||(modeChoice == "donut")){
      donutMode(boardLength, boardWidth, board);
      keepGoing = false;
    }else{
      keepGoing = true;
    }
  }
}


int GameOL::classicMode(int boardLength, int boardWidth, char**& board){

  int count = 0;
  genCount = 1;
  bool stable = false;

  char** nextGen = new char*[boardLength];

  for(int i = 0; i < boardLength; ++i){
    nextGen[i] = new char[boardWidth];
  }

  while(stable == false){
    for(int i = 0; i < boardLength; ++i){
      for(int j = 0; j < boardWidth; ++j){
        count = 0;

        //top left corner
        if(i == 0 && j == 0){
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i][j+1] == 'X'){
            count++;
          }


        //bottom left corner
        }else if(i == (boardLength - 1) && j == 0){
          if(board[i-1][j] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i][j+1] == 'X'){
            count++;
          }


          //top right corner
        }else if(i == 0 && j == (boardWidth - 1)){
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i+1][j-1] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count++;
          }


          //bottom right corner
        }else if(i == (boardLength - 1) && j == (boardWidth - 1)){
          if(board[i-1][j] == 'X'){
            count++;
          }
          if(board[i-1][j-1] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count++;
          }


          //top row
        }else if(i == 0){
          if(board[i][j+1] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count++;
          }
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i+1][j-1] == 'X'){
            count++;
          }


          //left side
        }else if(j == 0){
          if(board[i][j+1] == 'X'){
            count++;
          }
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j] == 'X'){
            count++;
          }


          //bottom row
        }else if(i == (boardLength - 1)){
          if(board[i][j+1] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j-1] == 'X'){
            count++;
          }
          if(board[i-1][j] == 'X'){
            count++;
          }

          //right side
        }else if(j == (boardWidth - 1)){
          if(board[i][j-1] == 'X'){
            count++;
          }
          if(board[i-1][j] == 'X'){
            count++;
          }
          if(board[i-1][j-1] == 'X'){
            count++;
          }
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count++;
          }

          //any middle cell
        }else{
          if(board[i][j+1] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count++;
          }
          if(board[i+1][j-1] == 'X'){
            count++;
          }
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j-1] == 'X'){
            count++;
          }
          if(board[i-1][j] == 'X'){
            count++;
          }
        }

        //if the cell has less than two neighbors, it will die
        if(count < 2){
          nextGen[i][j] = '-';


        //if the cell has exactly two neighbors, it will remain the same
        }else if(count == 2){
          nextGen[i][j] = board[i][j];


        //if the cell has exactly three neighbors, it remain be populated
        }else if(count == 3){
          nextGen[i][j] = 'X';

        //if the cell has four or more neighbors, it will die
        }else if(count > 3){
          nextGen[i][j] = '-';
        }

      }
    }


    int checker = 0;

    for(int i = 0; i < boardLength; ++i){
      for(int j = 0; j < boardWidth; ++j){
        if(nextGen[i][j] == board[i][j]){
          checker++;
        }else{
          stable = false;
        }
      }
    }



    if(checker == (boardLength*boardWidth)){
      stable = true;
      cout << "The world is stable" << endl;
      cout << "If you want, try another board!" << endl;
    }

    if(stable == false){
      std::stringstream sstr;
      sstr << "Generation: " << genCount << endl;
      outputString += sstr.str();

      if(genCount == 1){

        for(int i = 0; i < boardLength; ++i){
          for(int j = 0; j < boardWidth; ++j){

            std::stringstream sstr;
            sstr << board[i][j];
            outputString += sstr.str();
          }
          std::stringstream sstr;
          sstr << "\n";
          outputString += sstr.str();
        }


        printOptions(outputStyle, genCount, board, boardLength, boardWidth);


        for(int i = 0; i < boardLength; ++i){
          for(int j = 0; j < boardWidth; ++j){
            board[i][j] = nextGen[i][j];
          }
        }

      }else{

        for(int i = 0; i < boardLength; ++i){
          for(int j = 0; j < boardWidth; ++j){
            board[i][j] = nextGen[i][j];
            std::stringstream sstr;
            sstr << board[i][j];
            outputString += sstr.str();
          }

          std::stringstream sstr;
          sstr << "\n";
          outputString += sstr.str();

        }
        printOptions(outputStyle, genCount, board, boardLength, boardWidth);
      }

    }
    genCount++;
  }

  if(outFileName != ""){
    ofstream outFS;
    outFS.open(outFileName.c_str());
    outFS << outputString << '\n';
    outFS.close();
  }

  return 0;
}


void GameOL::printOptions(string outputStyle, int genCount, char**& board, int boardLength, int boardWidth){
  bool enter = false;

  if((outputStyle == "Pause")||(outputStyle == "pause")){

    sleep(1); //pauses
    cout << "Generation: " << genCount << endl;

    for(int i = 0; i < boardLength; ++i){
      for(int j = 0; j < boardWidth; ++j){
        cout << board[i][j];
      }
      cout << "\n";
    }
  }else if((outputStyle == "Enter")||(outputStyle == "enter")){

    cout << "Press the 'enter' key to continue" << endl;
    cin.get();

    if(cin.get()){
      enter = true;
    }

    if(enter = true){
      cout << "Generation: " << genCount << endl;

      for(int i = 0; i < boardLength; ++i){
        for(int j = 0; j < boardWidth; ++j){
          cout << board[i][j];
        }
        cout << "\n";
      }
    }
  }
}

int GameOL::mirrorMode(int boardLength, int boardWidth, char**& board){
  int count = 0;
  genCount = 1;
  bool stable = false;

  char** nextGen = new char*[boardLength];

  for(int i = 0; i < boardLength; ++i){
    nextGen[i] = new char[boardWidth];
  }

  while(stable == false){
    for(int i = 0; i < boardLength; ++i){
      for(int j = 0; j < boardWidth; ++j){
        count = 0;

        //If count is incremented by one, there was one neighbor with no reflection
        //If count is incremented by two, it is accounting for the neighbor and the reflection of the neighbor
        //if count is incremented by three, is is accounting for its own reflection in the corner

        if(i == 0 && j == 0){
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i+1][j] == 'X'){
            count+=2;
          }
          if(board[i][j+1] == 'X'){
            count+=2;
          }
          if(board[i][j] == 'X'){
            count+=3;
          }
        }else if(i == 0 && j == (boardWidth - 1)){
          if(board[i+1][j-1] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count+=2;
          }
          if(board[i+1][j] == 'X'){
            count+=2;
          }
          if(board[i][j] == 'X'){
            count+=3;
          }
        }else if(i == (boardLength - 1) && j == (boardWidth - 1)){
          if(board[i-1][j-1] == 'X'){
            count++;
          }
          if(board[i][j-1] == 'X'){
            count+=2;
          }
          if(board[i-1][j] == 'X'){
            count+=2;
          }
          if(board[i][j] == 'X'){
            count+=3;
          }
        }else if(i == (boardLength - 1) && j == 0){
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i][j+1] == 'X'){
            count+=2;
          }
          if(board[i-1][j] == 'X'){
            count+=2;
          }
          if(board[i][j] == 'X'){
            count+=3;
          }
        }else if(i == 0){
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i+1][j-1] == 'X'){
            count++;
          }
          if(board[i][j] == 'X'){
            count++;
          }
          if(board[i][j+1] == 'X'){
            count+=2;
          }
          if(board[i][j-1] == 'X'){
            count+=2;
          }
        }else if(j == 0){
          if(board[i][j+1] == 'X'){
            count++;
          }
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i][j] == 'X'){
            count++;
          }
          if(board[i+1][j] == 'X'){
            count+=2;
          }
          if(board[i-1][j] == 'X'){
            count+=2;
          }
        }else if(i == (boardLength - 1)){
          if(board[i-1][j] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j-1] == 'X'){
            count++;
          }
          if(board[i][j] == 'X'){
            count++;
          }
          if(board[i][j+1] == 'X'){
            count+=2;
          }
          if(board[i][j-1] == 'X'){
            count+=2;
          }
        }else if(j == (boardWidth - 1)){
          if(board[i][j-1] == 'X'){
            count++;
          }
          if(board[i+1][j-1] == 'X'){
            count++;
          }
          if(board[i-1][j-1] == 'X'){
            count++;
          }
          if(board[i][j] == 'X'){
            count++;
          }
          if(board[i-1][j] == 'X'){
            count+=2;
          }
          if(board[i+1][j] == 'X'){
            count++;
          }
        }else{
          if(board[i][j-1] == 'X'){
            count++;
          }
          if(board[i][j+1] == 'X'){
            count++;
          }
          if(board[i+1][j+1] == 'X'){
            count++;
          }
          if(board[i+1][j] == 'X'){
            count++;
          }
          if(board[i+1][j-1] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
          if(board[i-1][j] == 'X'){
            count++;
          }
          if(board[i-1][j+1] == 'X'){
            count++;
          }
        }

        if(count < 2){
          nextGen[i][j] = '-';
        }else if(count == 2){
          nextGen[i][j] = board[i][j];
        }else if(count == 3){
          nextGen[i][j] = 'X';
        }else if(count > 3){
          nextGen[i][j] = '-';
        }



      }
    }

    int checker = 0;

    for(int i = 0; i < boardLength; ++i){
      for(int j = 0; j < boardWidth; ++j){
        if(nextGen[i][j] == board[i][j]){
          checker++;
        }else{
          stable = false;
        }
      }
    }


    if(checker == (boardLength*boardWidth)){
      stable = true;
      cout << "The world is stable" << endl;
      cout << "If you want, try another board!" << endl;

    }

    if(stable == false){

      std::stringstream sstr;
      sstr << "Generation: " << genCount << endl;
      outputString += sstr.str();

      if(genCount == 1){
        for(int i = 0; i < boardLength; ++i){
          for(int j = 0; j < boardWidth; ++j){
            std::stringstream sstr;
            sstr << board[i][j];
            outputString += sstr.str();
          }
          std::stringstream sstr;
          sstr << "\n";
          outputString += sstr.str();
        }

          printOptions(outputStyle, genCount, board, boardLength, boardWidth);

          for(int i = 0; i < boardLength; ++i){
            for(int j = 0; j < boardWidth; ++j){
              board[i][j] = nextGen[i][j];
            }
          }
        }else{

          for(int i = 0; i < boardLength; ++i){
            for(int j = 0; j < boardWidth; ++j){
              board[i][j] = nextGen[i][j];
              std::stringstream sstr;
              sstr << board[i][j];
            }
            std::stringstream sstr;
            sstr << "\n";
            outputString += sstr.str();
          }

          printOptions(outputStyle, genCount, board, boardLength, boardWidth);
        }
      }

      genCount++;
    }

    if(outFileName != ""){
      ofstream outFS;
      outFS.open(outFileName.c_str());
      outFS << outputString << "\n";
      outFS.close();
    }

    return 0;
  }


int GameOL::donutMode(int boardLength, int boardWidth, char**& board){

    int count = 0;
    genCount = 1;
    bool stable = false;

    char** nextGen = new char*[boardLength];

    for(int i = 0; i < boardLength; ++i){
      nextGen[i] = new char[boardWidth];
    }

    while(stable == false){
      for(int i = 0; i < boardLength; ++i){
        for(int j = 0; j < boardWidth; ++j){
          count = 0;

          if(i == 0 && j == 0){
            if(board[i+1][j] == 'X'){
              count++;
            }
            if(board[i+1][j+1] == 'X'){
              count++;
            }
            if(board[i][j+1] == 'X'){
              count++;
            }
            if(board[boardLength - 1][j] == 'X'){
              count++;
            }
            if(board[boardLength - 1][j+1] == 'X'){
              count++;
            }
            if(board[boardLength - 1][boardWidth - 1] == 'X'){
              count++;
            }
            if(board[i][boardWidth - 1 == 'X']){
              count++;
            }
            if(board[i+1][boardWidth - 1 == 'X']){
              count++;
            }
          }else if(i == 0 && j == (boardWidth - 1)){
            if(board[i+1][j] == 'X'){
              count++;
            }
            if(board[i][j-1] == 'X'){
              count++;
            }
            if(board[i+1][j-1] == 'X'){
              count++;
            }
            if(board[boardLength - 1][j] == 'X'){
              count++;
            }
            if(board[boardLength - 1][j+1] == 'X'){
              count++;
            }
            if(board[boardLength - 1][boardWidth - 1] == 'X'){
              count++;
            }
            if(board[i][boardWidth - 1] == 'X'){
              count++;
            }
            if(board[i+1][boardWidth - 1] == 'X'){
              count++;
            }
          }else if(i == (boardLength - 1) && j == 0){
            if(board[i-1][j] == 'X'){
              count++;
            }
            if(board[i][j+1] == 'X'){
              count++;
            }
            if(board[i-1][j+1] == 'X'){
              count++;
            }
            if(board[0][j] == 'X'){
              count++;
            }
            if(board[0][j+1] == 'X'){
              count++;
            }
            if(board[0][boardWidth - 1] == 'X'){
              count++;
            }
            if(board[i-1][boardWidth - 1] == 'X'){
              count++;
            }
            if(board[i][boardWidth - 1] == 'X'){
              count++;
            }
          }else if(i == (boardLength - 1) && j == (boardWidth - 1)){
            if(board[i-1][j] == 'X'){
              count++;
            }
            if(board[i-1][j-1] == 'X'){
              count++;
            }
            if(board[i][j-1] == 'X'){
              count++;
            }
            if(board[0][j-1] == 'X'){
              count++;
            }
            if(board[0][j] == 'X'){
              count++;
            }
            if(board[0][0] == 'X'){
              count++;
            }
            if(board[i][0] == 'X'){
              count++;
            }
            if(board[i-1][0] == 'X'){
              count++;
            }
          }else if(i == 0){
            if(board[i][j+1] == 'X'){
              count++;
            }
            if(board[i][j-1] == 'X'){
              count++;
            }
            if(board[i+1][j-1] == 'X'){
              count++;
            }
            if(board[i+1][j+1] == 'X'){
              count++;
            }
            if(board[i+1][j] == 'X'){
              count++;
            }
            if(board[boardLength - 1][j-1] == 'X'){
              count++;
            }
            if(board[boardLength - 1][j] == 'X'){
              count++;
            }
            if(board[boardLength - 1][j+1] == 'X'){
              count++;
            }
          }else if(j == 0){
            if(board[i][j+1] == 'X'){
              count++;
            }
            if(board[i-1][j] == 'X'){
              count++;
            }
            if(board[i-1][j+1] == 'X'){
              count++;
            }
            if(board[i+1][j] == 'X'){
              count++;
            }
            if(board[i+1][j+1] == 'X'){
              count++;
            }
            if(board[i-1][boardWidth - 1] == 'X'){
              count++;
            }
            if(board[i][boardWidth - 1] == 'X'){
              count++;
            }
            if(board[i+1][boardWidth - 1] == 'X'){
              count++;
            }
          }else if(i == (boardLength - 1)){
            if(board[i][j+1] == 'X'){
              count++;
            }
            if(board[i][j-1] == 'X'){
              count++;
            }
            if(board[i-1][j] == 'X'){
              count++;
            }
            if(board[i-1][j-1] == 'X'){
              count++;
            }
            if(board[i-1][j+1] == 'X'){
              count++;
            }
            if(board[0][j+1] == 'X'){
              count++;
            }
            if(board[0][j] == 'X'){
              count++;
            }
            if(board[0][j-1] == 'X'){
              count++;
            }
          }else if(j == (boardWidth - 1)){
            if(board[i][j-1] == 'X'){
              count++;
            }
            if(board[i-1][j] == 'X'){
              count++;
            }
            if(board[i-1][j-1] == 'X'){
              count++;
            }
            if(board[i+1][j] == 'X'){
              count++;
            }
            if(board[i+1][j-1] == 'X'){
              count++;
            }
            if(board[i-1][0] == 'X'){
              count++;
            }
            if(board[i][0] == 'X'){
              count++;
            }
            if(board[i+1][0] == 'X'){
              count++;
            }
          }else{
            if(board[i][j+1] == 'X'){
              count++;
            }
            if(board[i][j-1] == 'X'){
              count++;
            }
            if(board[i-1][j-1] == 'X'){
              count++;
            }
            if(board[i-1][j] == 'X'){
              count++;
            }
            if(board[i-1][j+1] == 'X'){
              count++;
            }
            if(board[i+1][j] == 'X'){
              count++;
            }
            if(board[i+1][j-1] == 'X'){
              count++;
            }
            if(board[i+1][j+1] == 'X'){
              count++;
            }
          }

          if(count < 2){
            nextGen[i][j] = '-';
          }else if(count == 2){
            nextGen[i][j] = board[i][j];
          }else if(count == 3){
            nextGen[i][j] = 'X';
          }else if(count > 3){
            nextGen[i][j] = '-';
          }

        }

      }

      int checker = 0;


      for(int i = 0; i < boardLength; ++i){
        for(int j = 0; j < boardWidth; ++j){
          if(nextGen[i][j] == board[i][j]){
            checker++;
          }else{
            stable = false;
          }
        }
      }



      if(checker == (boardLength*boardWidth)){
        stable = true;

        cout << "The world is stable" << endl;
        cout << "If you want, try another board!" << endl;
      }

      if(stable == false){
        std::stringstream sstr;
        sstr << "Generation: " << genCount << endl;
        outputString += sstr.str();

        if(genCount == 1){
          for(int i = 0; i < boardLength; ++i){
            for(int j = 0; j < boardWidth; ++j){
              std::stringstream sstr;
              sstr << board[i][j];
              outputString += sstr.str();

          }
          std::stringstream sstr;
          sstr << "\n";
          outputString += sstr.str();
        }



        printOptions(outputStyle, genCount, board, boardLength, boardWidth);

        for(int i = 0; i < boardLength; ++i){
          for(int j = 0; j < boardWidth; ++j){
            board[i][j] = nextGen[i][j];
          }
        }
      }else{

        for(int i = 0; i < boardLength; ++i){
          for(int j = 0; j < boardWidth; ++j){
            board[i][j] = nextGen[i][j];
            sstr << board[i][j];
            outputString += sstr.str();
          }

          std::stringstream sstr;
          sstr << "\n";
          outputString += sstr.str();
        }

        printOptions(outputStyle, genCount, board, boardLength, boardWidth);
      }
    }

    genCount++;

  }

  if(outFileName != ""){
    ofstream outFS;
    outFS.open(outFileName.c_str());
    outFS << outputString << "\n";
    outFS.close();
  }

  return 0;
}
