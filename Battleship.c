#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int boardSize = 10;
const int validCoordSize = 3;
const char top[boardSize] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const char side[boardSize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
char player1[boardSize][boardSize] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}};

char player2[boardSize][boardSize] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}};

char player1EBoard[boardSize][boardSize] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}};

char player2EBoard[boardSize][boardSize] =
    {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}
    };
int shipsLeft1 = 0;
int shipsLeft2 = 0;
int shipsSunk1 = 0;
int shipsSunk2 = 0;
int turn = 0;

void boardViewHelper(int j, char board[boardSize][boardSize])
{
    for (int k = 0; k < boardSize; k++)
    {
        if (k == 0)
        {
            printf("%*c", 3, ' ');
        }
        else
        {
            printf("%*c", 4, ' ');
        }
        printf("%c", board[j][k]);
    }
}

void gameBoard(char player[10][10])
{
    int i, j;
    for (i = 0; i < boardSize; i++)
    {
        printf("%*c", 4, ' ');
        printf("%c", top[i]);
        if (top[i] == '9')
        {
            printf("\n");
        }
    }
    for (j = 0; j < boardSize; j++)
    {
        printf("%c", side[j]); // change \n later
        boardViewHelper(j, player);
        printf("\n");
    }
    return;
}

void shipInput(char userCoords[], char board[boardSize][boardSize])
{
    int i;
    int row = -1;
    int col = -1;
    if (isalpha(userCoords[0]) > 0 && isdigit(userCoords[1]) > 0)
    {
        for (int i = 0; i < boardSize; i++)
        {
            if (side[i] == toupper(userCoords[0]))
            {
                row = i;
            }
            if (top[i] == userCoords[1])
            {
                col = i;
            }
            if (col > -1 && row > -1)
            {
                break;
            }
        }
        if (col > -1 && row > -1)
        {
            board[row][col] = 'O';
            shipsLeft1++;
            shipsLeft2++;
            gameBoard(board);
        }
        else
        {
        printf("Invalid Coords\n");
        }
    }
    else
    {
        printf("Invalid Coords\n");
    }
}

void placeShips(char board[boardSize][boardSize])
{
    char d;
    char userCoords[validCoordSize];
    char shipSpot = 'O';
    printf("Enter Ship Coordinates (i.e. G4) or 'x' if finished: \n");
    scanf("%s", userCoords);
    while((d = getchar()) != '\n' && d != EOF);
    if (userCoords[0] == 'x')
    {
        printf("End Turn\n");
        return;
    }
    shipInput(userCoords, board);
    placeShips(board);
}

void attackBoard(char board[boardSize][boardSize], char enemyBoard[boardSize][boardSize], char attackCoords[])
{
    int row = -1;
    int col = -1;
    if (isalpha(attackCoords[0]) > 0 && isdigit(attackCoords[1]) > 0)
    {
        for (int i = 0; i < boardSize; i++)
        {
            if (side[i] == toupper(attackCoords[0]))
            {
                row = i;
            }
            if (top[i] == attackCoords[1])
            {
                col = i;
            }
            if (col > -1 && row > -1)
            {
                break;
            }
        }
        if (col > -1 && row > -1)
        {
            if (board[row][col] == 'O') {
                printf("Hit!\n");
                enemyBoard[row][col] = 'X';
                if (turn % 2 != 0) {
                    shipsSunk1++;
                }
                else {
                    shipsSunk2++;
                }
            }
            else {
                enemyBoard[row][col] = '@';
            }
            gameBoard(enemyBoard);
        }
        else
        {
        printf("Invalid Coords\n");
        }
    }
    else
    {
        printf("Invalid Coords\n");
    }
}

void attack(char board[boardSize][boardSize], char enemyBoard[boardSize][boardSize])
{
    char attackCoords[validCoordSize];
    scanf("%s", attackCoords);
    printf("\n");
    attackBoard(board, enemyBoard, attackCoords);
    printf("\n");
}

void gameStart()
{
    turn++;
    printf("Ships Spots Left: P1 has %d, P2 has %d\n", shipsLeft1 / 2 - shipsSunk2, shipsLeft2 / 2 - shipsSunk1);
    if (shipsSunk1 == (shipsLeft2 / 2)) {
        printf("Game Over! Player 1 Won!\n");
        return;
    }
    else if (shipsSunk2 == (shipsLeft1 / 2)) {
        printf("Game Over! Player 2 Won!\n");
        return;
    }
    else if (turn % 2 != 0) {
        printf("Player 1 Attack! \n");
        gameBoard(player1EBoard);
        attack(player2, player1EBoard);
        gameStart(turn);
    }
    else {
        printf("Player 2 Attack! \n");
        gameBoard(player2EBoard);
        attack(player1, player2EBoard);
        gameStart(turn);
    }
}

int main()
{
    gameBoard(player1);
    printf("Player 1 Place Your Ships!\n");
    placeShips(player1);
    printf("\n\n\n\n\n\n\n\n");
    printf("Player 2 Place Your Ships!\n");
    gameBoard(player2);
    placeShips(player2);
    printf("\n\n\n\n\n\n\n\n");
    printf("Let the Games Begin!\n");
    gameStart();
    return 0;
}
