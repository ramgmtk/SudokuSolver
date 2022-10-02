Program: Soduko Solver <br />
Language: C++ <br />
<br />
Description: <br />
This program looks at a given sudoku board and attempts to solve the board if a solution exists. <br />
I utilize a stack to keep track of the sudoku's board state as the solver cycles through every possible <br />
number in every open space. The program is inefficient currently in how it evalutes each cell in the board, <br />
however the code is to showcase the use of a stack to keep track of the boards state and be able to revert the board <br />
if we attempts to find solutions down the wrong branch.<br />
<br />
Note: <br />
The work solver functions implementation was done using a similar method to what I used when solving the <br />
nqueens problem in the past. This prompt was inspired by leetcode question 36 'valid sudoku'.