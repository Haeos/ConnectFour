/**
 * Connect Four stand alone game
 * @author Josh Downs
 * This version is assumes valid inputs from the user.
 * The following code is 
*/


#include <string>
#include <iostream>
#include <sstream>

using namespace std;

const int ROW = 6, COL = 7;

/**
 * Wipes the board for a fresh start
 * Will allow multiple session to be played once that feature is implemented
 * @param board[][] the current board being used
*/
void boardReset(char board[ROW][COL]);

/**
 * Prints the current board to the screen for the user
 * @param board[][] current board being used, will not be changed
 * @return string containing printed out board (converted from ostringstream)
*/
string printBoard(const char board[ROW][COL]);

/**
 * Verifies the space is available and inputs the correct players selection
 * @param board[][] current board being used
 * @param x column the player wishes to place their move
 * @param playerTurn the current players turn
 * @return returns true for valid and false for an invalid selection
*/
bool validEntry(char board[ROW][COL], int x, int playerTurn);

/**
 * Checks to see if a win condition has been met
 * @param board[][] curernt board being used
 * @param column the column selected by the current player, eliminates checking every possible win condition
 * @return returns true if a win condition is met and false if it has not been met
*/
bool winCondition(const char board[ROW][COL], int column);

int main()
{
    char board[ROW][COL];
    boardReset(board);
    
    cout << "//////////////////////////////////////////////////" << endl;
    cout << "//           Welcome to Connect Four!           //" << endl;
    cout << "//                                              //" << endl;
    cout << "//   The first player to connect four wins!     //" << endl;
    cout << "//            Player 1 will be \"x\"              //" << endl;
    cout << "//            Player 2 will be \"o\"              //" << endl;
    cout << "//////////////////////////////////////////////////" << endl;
    cout << endl;
    cout << "The starting board is:" << endl;
    cout << printBoard(board) << endl;
    
    // Will keep track of the players turn through modding by 2 and adding 1 so it alternates between the two players
    int playerTurn = 1;
    
    bool endOfGame = false;
    
    while (!endOfGame)
    {
        cout << "Player " << playerTurn << " select your column: ";
        int col;
        cin >> col;
        if (validEntry(board, col, playerTurn))
            playerTurn = playerTurn % 2 + 1;
        
        cout << printBoard(board) << endl;
        
        // Checking for win condition
        endOfGame = winCondition(board, col);
    }
    
    playerTurn = playerTurn % 2 + 1;
    cout << "Congratulations Player " << playerTurn << " you are the winner!" << endl;
    return 0;
}

string printBoard(const char board[ROW][COL])
{
    ostringstream out;
    
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            out << board[i][j] << " ";
        out << endl;
    }
    for (int i = 0; i < COL; i++)
    {
        out << i+1 << " ";
    }
    out << endl;
    return out.str();
}

void boardReset(char board[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            board[i][j] = '.';
    }
}

bool validEntry(char board[ROW][COL], int x, int playerTurn)
{
    char playerNum = '.';
    if (playerTurn == 1)
        playerNum = 'x';
    else
        playerNum = 'o';
    
    for (int i = ROW; i > 0; i--)
    {
        if (board[i-1][x-1] == '.')
        {
            board[i-1][x-1] = playerNum;
            return true;
        }
    }
    return false;
}

bool winCondition(const char board[ROW][COL], int column)
{
    int counter = 0;
    column--;
    
    // Checking for vertical victory
    for (int j = 1; j < ROW; j++)
    {
        if (board[j-1][column] == board[j][column] && board[j][column] != '.')
            counter++;
        else
            counter = 0;
        if (counter == 3)
            return true;
    }
    
    // Checking for horizontal victory
    counter = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 1; j < COL; j++)
        {
            if (board[i][j-1] == board[i][j] && board[i][j] != '.')
                counter++;
            else
                counter = 0;
            if (counter == 3)
                return true;
        }
    }
    
    // Figuring out the y position of the last move
    int y = ROW;
    for (int i = ROW-1; i >= 0; i--)
    {
        if (board[i][column] != '.')
            y--;
    }
    
    // Checking for diagonal victory
    // CheckRow and checkCol are -4 because they immediately get incremented/decremented inside the loop
    // Have to check 3 spaces on either side of the latest pieces position for win condition
    
    // Checking top right to bottom left
    counter = 0;
    int checkRow = y - 4;
    int checkCol = column - 4;
    
    for (int i = 0; i < COL; i++)
    {
        checkRow++;
        checkCol++;
        // Makes sure the correct points are being checked and that it resides within the bounds of the array
        if (checkRow < 0 || checkRow > ROW-1 || checkCol < 0 || checkCol > COL-1)
            continue;
        if (board[checkRow][checkCol] == board[checkRow-1][checkCol-1] && board[checkRow][checkCol] != '.')
            counter++;
        else
            counter = 0;
        if (counter == 3)
            return true;
    }
    
    // Checking top left to bottom right
    counter = 0;
    checkRow = y - 4;
    checkCol = column + 4;
    
    for (int i = 0; i < COL; i++)
    {
        checkRow++;
        checkCol--;
        if (checkRow < 0 || checkRow > ROW-1 || checkCol < 0 || checkCol > COL-1)
            continue;
        if (board[checkRow][checkCol] == board[checkRow-1][checkCol+1] && board[checkRow][checkCol] != '.')
            counter++;
        else
            counter = 0;
        if (counter == 3)
            return true;
    }
    
    return false;
}
