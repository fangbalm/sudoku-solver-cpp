#include <iostream>
#include <unistd.h>

using namespace std;

// display sudoku board
void showBoard(int board[9][9]){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// figure out the most recently available spot, return false if board is finished
bool checkSpot(int board[9][9], int &row, int &col){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (board[i][j] == 0){
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

// returns true if a number is fine at its current position
bool isCorrect(int board[9][9], int row, int col, int num){
    // validates if number is already in the row
    for (int i = 0; i < 9; i++){
        if (board[row][i] == num){
            return false;
        }
    }
    // validates if number is already in the column
    for (int j = 0; j < 9; j++){
        if (board[j][col] == num){
            return false;
        }
    }
    // find which sub box the num is in
    int boxRow = row/3;
    int boxColumn = col/3;
    // check if the num to try is in the sub 3x3 box
    for (int k = boxRow*3; k < (boxRow*3) + 3; k++){
        for (int l = boxColumn*3; l < (boxColumn*3) + 3; l++){
            if (board[k][l] == num){
                return false;
            }
        }
    }
    return true;
}

// backtracing algorithm
bool algorithm(int grid[9][9]){

    int row, col;
    // if there are no spots available, then the puzzle is solved, otherwise
    // assign to an open space if one was found
    if (!checkSpot(grid, row, col)){
        return true;
    }

    // loops through the dimensions of the grid (1-9) and tests unassigned spots
    for (int i = 1; i < 10; i++){
        if (isCorrect(grid, row, col, i)){
            grid[row][col] = i;
            // if this attempt solves the puzzle, return true
            if(algorithm(grid)){
                return true;
            }
            grid[row][col] = 0;
        }
    }
    // backtracing to find result
    return false;
}

int main(){
    
    cout << "Welcome to Sudoku Solver! I will try to solve your puzzle." << endl << endl;
    cout <<
    R"(
         .---.
        } n n {
         \_-_/
    .'c ."|_|". n`.
    '--'  /_\  `--'
         /| |\
        [_] [_]     )" << endl << endl;
    
    cout << "Loading";
    
    for (int i = 0; i < 3; i++) {
        sleep(1);
        cout << " . ";
    }
    
  
  

    int firstBoard[9][9] = {
        {0,2,0,0,0,0,0,0,0},
        {0,0,0,6,0,0,0,0,3},
        {0,7,4,0,8,0,0,0,0},
        {0,0,0,0,0,3,0,0,2},
        {0,8,0,0,4,0,0,1,0},
        {6,0,0,5,0,0,0,0,0},
        {0,0,0,0,1,0,7,8,0},
        {5,0,0,0,0,9,0,0,0},
        {0,0,0,0,0,0,0,4,0}
        
    };
    
    int secondBoard[9][9] = {
        {8,0,0,0,0,0,0,0,0},
        {0,0,3,6,0,0,0,0,0},
        {0,7,0,0,9,0,2,0,0},
        {0,5,0,0,0,7,0,0,0},
        {0,0,0,0,4,5,7,0,0},
        {0,0,0,1,0,0,0,3,0},
        {0,0,1,0,0,0,0,6,8},
        {0,0,8,5,0,0,0,1,0},
        {0,9,0,0,0,0,4,0,0}
    };
    

    if(algorithm(firstBoard)){
        cout << endl << endl << "Successfully solved first board!";
        cout << endl << endl;
        cout << "==================" << endl << endl;
        showBoard(firstBoard);
        cout << endl;
        cout << "==================" << endl;
    }
     if (algorithm(secondBoard)){
            cout << endl << endl << "Successfully solved second board!";
            cout << endl << endl;
            cout << "==================" << endl << endl;
            showBoard(secondBoard);
            cout << endl;
            cout << "==================" << endl << endl;
    }
    else{
        cout << "Uh oh, can't solve it!! D:" << endl;
    }
    return 0;
}
