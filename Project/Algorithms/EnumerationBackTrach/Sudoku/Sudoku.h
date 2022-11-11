#pragma once
#include <vector>
#include <iostream>
#include <CommandFramework/CommandReceiver.h>

class Sudoku{
public:
   Sudoku(CommandReceiver &receiver);
   bool isSolution(std::vector<std::vector<int>> const &solution);
   void solve(std::vector<std::vector<int>> &sample);
private:
   CommandReceiver &receiver;
   bool _solve(std::vector<std::vector<int>> &sample, size_t position);
   bool isRowCorrect(size_t row, std::vector<std::vector<int>> const &solution);
   bool isColumnCorrect(size_t column, std::vector<std::vector<int>> const &solution);
   bool isSquareCorrect(size_t square, std::vector<std::vector<int>> const &solution);
};

void showSample(std::vector<std::vector<int>> const &sample);