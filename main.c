// Moved to https://github.com/sokoloowski/tictactoe

#include <stdio.h>

#if defined __linux__
#define IS_LINUX 1
#elif defined _WIN32
#define IS_LINUX 0
#endif

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define DEFAULT "\033[0m"

#define PLAYER -1
#define BLANK 0
#define AI 1

int optimalX,
    optimalY;

int arr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void printBoard(int board[3][3])
{
    if (IS_LINUX)
        system("clear"); // for Unix
    else
        system("cls"); // for Windows
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" ");
            if (board[i][j] == AI && IS_LINUX)
            {
                printf(RED);
            }
            else if (board[i][j] == PLAYER && IS_LINUX)
            {
                printf(GREEN);
            }
            printf("%c ", board[i][j] == BLANK ? (3 * i) + j + 1 + '0' : (board[i][j] == PLAYER ? 'o' : 'x'));
            if (IS_LINUX)
                printf(DEFAULT);
            if (j != 2)
                printf("|");
        }
        if (i != 2)
            printf("\n---+---+---\n");
    }
    printf("\n");
}

int estimateBoard(int board[3][3])
{
    if (
        (board[0][0] == PLAYER && board[0][1] == PLAYER && board[0][2] == PLAYER) ||
        (board[1][0] == PLAYER && board[1][1] == PLAYER && board[1][2] == PLAYER) ||
        (board[2][0] == PLAYER && board[2][1] == PLAYER && board[2][2] == PLAYER) ||
        (board[0][0] == PLAYER && board[1][0] == PLAYER && board[2][0] == PLAYER) ||
        (board[0][1] == PLAYER && board[1][1] == PLAYER && board[2][1] == PLAYER) ||
        (board[0][2] == PLAYER && board[1][2] == PLAYER && board[2][2] == PLAYER) ||
        (board[0][0] == PLAYER && board[1][1] == PLAYER && board[2][2] == PLAYER) ||
        (board[0][2] == PLAYER && board[1][1] == PLAYER && board[2][0] == PLAYER))
        return PLAYER;
    else if (
        (board[0][0] == AI && board[0][1] == AI && board[0][2] == AI) ||
        (board[1][0] == AI && board[1][1] == AI && board[1][2] == AI) ||
        (board[2][0] == AI && board[2][1] == AI && board[2][2] == AI) ||
        (board[0][0] == AI && board[1][0] == AI && board[2][0] == AI) ||
        (board[0][1] == AI && board[1][1] == AI && board[2][1] == AI) ||
        (board[0][2] == AI && board[1][2] == AI && board[2][2] == AI) ||
        (board[0][0] == AI && board[1][1] == AI && board[2][2] == AI) ||
        (board[0][2] == AI && board[1][1] == AI && board[2][0] == AI))
        return AI;
    else
        return BLANK;
}

int minimax(int board[3][3], int player)
{
    if (estimateBoard(board) != BLANK)
    {
        return estimateBoard(board) * player; // -1 * -1 || 1 * 1
    }

    int localX = -1;
    int localY = -1;
    int score = -2;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[x][y] == BLANK)
            {
                board[x][y] = player;
                int scoreForTheMove = -minimax(board, player == PLAYER ? AI : PLAYER);
                if (scoreForTheMove > score)
                {
                    score = scoreForTheMove;
                    localX = x;
                    localY = y;
                }
                board[x][y] = BLANK;
            }
        }
    }
    optimalX = localX;
    optimalY = localY;
    if (optimalX == -1 && optimalY == -1)
    {
        return 0; // No move - it's a draw
    }
    return score;
}

void getMove(int board[3][3])
{
    int position = 0;
    printf("Enter the number of the field on the board: ");
    scanf("%d", &position);
    if (position >= 1 && position <= 9)
    {
        int x = (position - 1) / 3;
        int y = (position - 1) % 3;
        if (board[x][y] == BLANK)
        {
            board[x][y] = PLAYER;
        }
        else
        {
            printBoard(board);
            if (IS_LINUX)
                printf(RED);
            printf("This field is already taken!");
            if (IS_LINUX)
                printf(DEFAULT);
            printf("\n");
            getMove(board);
        }
    }
    else
    {
        printBoard(board);
        if (IS_LINUX)
            printf(RED);
        printf("Invalid value!");
        if (IS_LINUX)
            printf(DEFAULT);
        printf("\n");
        getMove(board);
    }
}

int main(void)
{
    int end = 0;
    printBoard(arr);
    while (!end)
    {
        getMove(arr);
        printBoard(arr);

        if (estimateBoard(arr) == PLAYER)
        {
            printf("You won!\n");
            return 0;
        }

        printf("Processing...\n");
        minimax(arr, AI);
        arr[optimalX][optimalY] = AI;
        printBoard(arr);

        if (estimateBoard(arr) == AI)
        {
            printf("You lost...\n");
            return 0;
        }

        end = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (arr[i][j] == BLANK)
                    end = 0;
    }
    printf("Draw.\n");
    return 0;
}