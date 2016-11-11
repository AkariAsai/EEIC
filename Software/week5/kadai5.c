#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 50

void initBoard(int **board, int **temp){
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            board[i][j] = rand() % 2;
            temp[i][j] = 0;
        }
    }
}

int isDead(int sum, int current){
    switch (sum){
        case 2:
            return current? 1: 0;
        case 3:
            return 1;
        default:
            return 0;
    }
}

void updateTemp(int **board, int **temp){
    int i, j;
    int sum;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            sum = 0;
            sum = board[i+1>=N?1:i+1][j] + board[i-1<0?N-1:i-1][j] +board[i][j+1>=N?1:j+1] +board[i][j-1<0?N-1:j-1] +board[i+1>=N?1:i+1][j+1>=N?1:j+1] +board[i+1>=N?1:i+1][j-1<0?N-1:j-1] +board[i-1<0?N-1:i-1][j+1>=N?1:j+1] +board[i-1<0?N-1:i-1][j-1<0?N-1:j-1];
            temp[i][j] = isDead(sum, board[i][j]);
        }
    }
}

void updateBoard(int **board, int **temp){
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            board[i][j] = temp[i][j];
        }
    }
}

void printBoard(int **board){
    for(int i=1; i<N; i++){
        for(int j=1; j<N; j++){
            putchar(board[i][j]?'*':' ');
        }
        puts("");
    }
    puts("");
}

int main()
{
    int **board, **temp;
    int i, turn;
    
    board = (int**)malloc(sizeof(int*)*N+1);
    for (i = 0; i < N; i++){
        board[i] =  (int*)malloc(sizeof(int)*N+1);
    }
    
    temp = (int**)malloc(sizeof(int*)*N+1);
    for (i = 0; i < N; i++){
        temp[i] =  (int*)malloc(sizeof(int)*N+1);
    }
    
    initBoard(board, temp);
    for(turn=0;;turn++)
    {
        printf("TURN: %d\n", turn);
        printBoard(board);
        sleep(1);
        updateTemp(board, temp);
        updateBoard(board, temp);
        printBoard(board);
    }
    return 0;
}
