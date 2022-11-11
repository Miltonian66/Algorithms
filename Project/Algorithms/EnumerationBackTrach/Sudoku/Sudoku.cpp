#include "Sudoku.h"

struct Move{
   size_t row;
   size_t column;
   int value;
};

Sudoku::Sudoku(CommandReceiver &receiver) : receiver(receiver){}

bool Sudoku::isSolution(std::vector<std::vector<int>> const &solution){   
   for(size_t i = 0; i < 9; i++){
      for(size_t j = 0; j < 9; j++){
         if(solution[i][j] == -1)
            return false;
      }
      if(!isRowCorrect(i, solution) || !isColumnCorrect(i, solution) || !isSquareCorrect(i, solution))
         return false;
   }
   return true;
}

void Sudoku::solve(std::vector<std::vector<int>> &sample){
   for(size_t i = 0; i < 9; i++){
      for(size_t j = 0; j < 9; j++){
         if(sample[i][j] == -1){
            _solve(sample, i * 9 + j);
            return;
         }
      }
   }
}

bool Sudoku::_solve(std::vector<std::vector<int>> &sample, size_t position){
   if(position == 81)
      return true;
   size_t row = position / 9;
   size_t column = position % 9;
   size_t square = (row / 3) * 3 + column / 3;
   size_t nextPosition = 81;
   for(size_t i = position + 1; i < 81; i++){
      size_t cr = i / 9, cc = i % 9;
      if(sample[cr][cc] == -1){
         nextPosition = i;
         break;
      }
   }
   for(int i = 1; i < 10; i++){
      sample[row][column] = i;
      if(!isRowCorrect(row, sample) || !isColumnCorrect(column, sample) || !isSquareCorrect(square, sample))
         continue;
      if(_solve(sample, nextPosition))
         return true;
   }
   showSample(sample);
   sample[row][column] = -1;
   return false;
}

bool Sudoku::isRowCorrect(size_t row, std::vector<std::vector<int>> const &solution){
   bool presented[9] = {};
   for(size_t i = 0; i < 9; i++){
      int number = solution[row][i];
      if(number == -1)
         continue;
      bool &current = presented[number - 1];
      if(current)
         return false;
      current = true;
   }
   return true;
}

bool Sudoku::isColumnCorrect(size_t column, std::vector<std::vector<int>> const &solution){
   bool presented[9] = {};
   for(size_t i = 0; i < 9; i++){
      int number = solution[i][column];
      if(number == -1)
         continue;
      bool &current = presented[number - 1];
      if(current)
         return false;
      current = true;
   }
   return true;
}
bool Sudoku::isSquareCorrect(size_t square, std::vector<std::vector<int>> const &solution){
   bool presented[9] = {};
   for(size_t i = 0; i < 9; i++){
      int number = solution[square / 3 + i / 3][(square % 3) * 3 + i % 3];
      if(number == -1)
         continue;
      bool &current = presented[number - 1];
      if(current)
         return false;
      current = true;
   }
   return true;
}

void showSample(std::vector<std::vector<int>> const &sample){
   std::cout << "_________________________\n";
   for(size_t i = 0; i < 9; i++){
      std::cout << "|";
      for(size_t j = 0; j < 9; j++){
         std::cout << (sample[i][j] == -1 ? " " : std::to_string(sample[i][j])) << "|" << (j % 3 == 2 ? (j == 8 ? "" : " * |") : "");
      }
      std::cout << "\n";
      if(i % 3 == 2)
         std::cout << "\n";
   }
   std::cout << "_________________________\n";
}