#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void initializeBoard(char **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 'X') {
                setColor(12); // Red for 'X'
                printf(" X ");
            } else if (board[i][j] == 'O') {
                setColor(9); // Blue for 'O'
                printf(" O ");
            } else {
                setColor(14); // Yellow for empty cells
                printf("   ");
            }
            setColor(7); // Reset to white for borders
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                printf("---");
                if (j < size - 1) printf("+");
            }
            printf("\n");
        }
    }
}

int checkWin(char **board, int size, char player) {
    int win;
    for (int i = 0; i < size; i++) {
        win = 1;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }
    for (int j = 0; j < size; j++) {
        win = 1;
        for (int i = 0; i < size; i++) {
            if (board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }
    win = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != player) {
            win = 0;
            break;
        }
    }
    if (win) return 1;
    win = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][size - i - 1] != player) {
            win = 0;
            break;
        }
    }
    if (win) return 1;
    return 0;
}

void playTicTacToe(int size) {
    char **board = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        board[i] = (char *)malloc(size * sizeof(char));
    }
    initializeBoard(board, size);
    char currentPlayer = 'X';
    int moves = 0, row, col;

    setColor(11); // Cyan for welcome message
    printf("Welcome to Dynamic Tic Tac Toe!\n");
    setColor(7);  // Reset to white

    while (moves < size * size) {
        setColor(13); // Magenta for board display
        printf("\nCurrent Board:\n");
        setColor(7);  // Reset to white
        printBoard(board, size);

        setColor(10); // Green for player prompt
        printf("\nPlayer %c, enter your move (row and column): ", currentPlayer);
        setColor(7);  // Reset to white
        scanf("%d %d", &row, &col);

        if (row < 1 || row > size || col < 1 || col > size || board[row - 1][col - 1] != ' ') {
            setColor(12); // Red for invalid move message
            printf("Invalid move! Try again.\n");
            setColor(7);  // Reset to white
            continue;
        }

        board[row - 1][col - 1] = currentPlayer;
        moves++;

        if (checkWin(board, size, currentPlayer)) {
            setColor(13); // Magenta for final board display
            printf("\nFinal Board:\n");
            setColor(7);  // Reset to white
            printBoard(board, size);

            setColor(10); // Green for winning message
            printf("Player %c wins!\n", currentPlayer);
            setColor(7);  // Reset to white
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    if (moves == size * size) {
        setColor(13); // Magenta for final board display
        printf("\nFinal Board:\n");
        setColor(7);  // Reset to white
        printBoard(board, size);

        setColor(14); // Yellow for draw message
        printf("It's a draw!\n");
        setColor(7);  // Reset to white
    }

    for (int i = 0; i < size; i++) {
        free(board[i]);
    }
    free(board);
}

int main() {
    int size;
    setColor(11); // Cyan for welcome message
     printf("########\\ ##\\            ########\\                   ########\\                        \n");
    printf("\\__##  __|\\__|           \\__##  __|                  \\__##  __|                       \n");
    printf("   ## |   ##\\  #######\\     ## | ######\\   #######\\     ## | ######\\   ######\\        \n");
    printf("   ## |   ## |##  _____|    ## | \\____##\\ ##  _____|    ## |##  __##\\ ##  __##\\       \n");
    printf("   ## |   ## |## /          ## | ####### |## /          ## |## /  ## |######## |      \n");
    printf("   ## |   ## |## |          ## |##  __## |## |          ## |## |  ## |##   ____|      \n");
    printf("   ## |   ## |\\#######\\     ## |\\####### |\\#######\\     ## |\\######  |\\#######\\       \n");
    printf("   \\__|   \\__| \\_______|     \\__| \\_______| \\______|    \\__| \\______/  \\_______|      \n");
    printf("\n");
    printf("Welcome to Dynamic Tic Tac Toe!\n");
    setColor(14); // Yellow for prompt
    printf("Enter the grid size (e.g., 3 for 3x3, 4 for 4x4, etc.): ");
    setColor(7);  // Reset to white
    scanf("%d", &size);

    if (size < 3) {
        setColor(12); // Red for error message
        printf("Grid size must be at least 3! Exiting.\n");
        setColor(7);  // Reset to white
        return 1;
    }

    playTicTacToe(size);
    return 0;
}
