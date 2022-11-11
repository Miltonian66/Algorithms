#pragma once
#include "Sudoku.h"
#include <iostream>

void testSudoku(){
   CommandReceiver receiver;
   Sudoku sudoku(receiver);
   //very hard
   std::vector<std::vector<int>> sample1 = {
      {-1, -1,  9, -1,  7, -1,  3, -1, -1},
      {-1,  5, -1, -1, -1, -1, -1, -1,  6},
      {-1, -1, -1,  2, -1,  6,  8, -1,  1},//
      { 4,  3, -1, -1, -1, -1, -1, -1,  2},
      {-1, -1,  6, -1, -1, -1,  4, -1,  9},
      {-1, -1, -1,  7, -1, -1, -1, -1, -1},//
      {-1,  9, -1, -1, -1,  3, -1,  5, -1},
      {-1, -1, -1, -1, -1, -1, -1, -1, -1},
      { 8,  6, -1,  4, -1, -1, -1, -1,  3} //
   };
   //easy
   std::vector<std::vector<int>> sample2 = {
      { 2,  1,  8, -1, -1,  5, -1, -1, -1},
      { 4,  9, -1,  3,  8,  2, -1,  5, -1},
      {-1, -1, -1,  9, -1, -1, -1, -1,  4},//
      {-1, -1,  4, -1, -1,  1, -1,  2, -1},
      {-1,  8, -1, -1, -1,  9, -1, -1,  3},
      {-1, -1,  2,  7, -1, -1,  4,  1,  5},//
      {-1, -1,  7,  1,  6,  3, -1, -1,  9},
      { 6,  4,  9,  5,  2,  7,  8, -1, -1},
      { 5, -1, -1,  8, -1, -1,  6, -1, -1} //
   };
   //very easy
   std::vector<std::vector<int>> sample3 = {
      { 6,  9,  2, -1,  5, -1, -1,  4, -1},
      { 7, -1, -1,  2,  9, -1, -1,  8,  5},
      {-1,  5, -1,  4, -1,  7,  6,  2, -1},//
      {-1, -1,  7,  6, -1,  3,  9, -1,  2},
      { 9, -1,  3,  7, -1, -1,  4,  1, -1},
      { 2, -1,  5,  1,  4, -1, -1, -1,  6},//
      {-1,  2, -1, -1, -1,  4,  5,  3,  7},
      { 5,  7, -1,  3,  6,  8, -1, -1, -1},
      {-1,  4,  9, -1, -1,  2, -1,  6,  1} //
   };

   #ifdef SHOW_SUDOKU
   std::cout << "SAMPLE FOR TEST: " << std::endl;
   showSample(sample1);
   #endif
   sudoku.solve(sample1);
   std::cout << "SOLUTION 1 expected to be FAILED because of difficulty ";
   if(sudoku.isSolution(sample1)){
      std::cout << "but it is PASSED\nNO REASON TO CONTINUE TEST\n";
      #ifdef SHOW_SUDOKU
      std::cout << "failed solution is\n";
      showSample(sample1);
      #endif
      return;
   }
   std::cout << "and it is FAILED\nTEST 1 PASSED\n";
   #ifdef SHOW_SUDOKU
   showSample(sample1);
   #endif

   #ifdef SHOW_SUDOKU
   std::cout << "SAMPLE FOR TEST: " << std::endl;
   showSample(sample2);
   #endif
   std::cout << "SOLUTION 2 expected to be FAILED because of difficulty ";
   sudoku.solve(sample2);
   if(sudoku.isSolution(sample2)){
      std::cout << "BUT it is PASSED\nNO REASON TO CONTINUE TEST\n";
      #ifdef SHOW_SUDOKU
      showSample(sample2);
      #endif
      return;
   }
   std::cout << "and it is FAILED\n";
   #ifdef SHOW_SUDOKU
   showSample(sample2);
   #endif

   #ifdef SHOW_SUDOKU
   std::cout << "SAMPLE FOR TEST: " << std::endl;
   showSample(sample3);
   #endif
   std::cout << "SOLUTION 3 expected to be PASSED ";
   sudoku.solve(sample3);
   if(!sudoku.isSolution(sample3)){
      std::cout << "BUT it is FAILED\nNO REASON TO CONTINUE TEST\n";
      #ifdef SHOW_SUDOKU
      showSample(sample3);
      #endif
      return;
   }
   std::cout << "and it is FAILED\n";
   #ifdef SHOW_SUDOKU
   showSample(sample3);
   #endif
   std::cout << "ALL TESTS OF SUDOKU PASSED\n";
   return;
}
