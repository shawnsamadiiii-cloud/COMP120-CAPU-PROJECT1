#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


const char player = 'O';
const char computer = 'X';
const char empty = ' ';


void init_board (char board[]) {
    int i;
    for (i = 0; i < 9; i++) {
        board[i] = empty;
    }
    
}


void display_board (char board[]) {
    int i;
    char c[9];

    for (i = 0; i < 9; i++) {
        c[i] = board[i];
        if (board [i] == empty) {
            c[i] = '0' + i;
        }
    }

    printf("\n");
    printf(" %c | %c | %c \n", c[0], c[1], c[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", c[3], c[4], c[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", c[6], c[7], c[8]);
    printf("\n");
}


char other_player (char player) {

    if (player == 'O') {
        return 'X';
    }
    else {
        return 'O';
    }
}


bool is_winner (char board[], char player) {

    if (board[0] == player && board[1] == player && board[2] == player) {
        return true;
    }
    if (board[3] == player && board[4] == player && board[5] == player) {
        return true;
    }
    if (board[6] == player && board[7] == player && board[8] == player) {
        return true;
    }
    if (board[0] == player && board[4] == player && board[8] == player) {
        return true;
    }
    if (board[2] == player && board[4] == player && board[6] == player) {
        return true;
    }
    if (board[0] == player && board[3] == player && board[6] == player) {
        return true;
    }
    if (board[1] == player && board[4] == player && board[7] == player) {
        return true;
    }
    if (board[2] == player && board[5] == player && board[8] == player) {
        return true;
    }
    else {
        return false;
    }
}


int get_player_move (char board[]) {

    int move;
    bool valid_move = false;

    while (!valid_move) {
        printf("It's your turn (O). Enter a box number from 0-8: ");
        scanf("%d", &move);
        if (move < 0 || move > 8) {
            printf("Invalid box number. Enter a box number from 0 to 8.\n");
        }
        else if (board[move] != empty) {
            printf("The box you chose is already taken. Please choose another box.\n");
        }
        else {
            valid_move = true;
        }
    }
    return move;
}


int get_computer_move (char board[]) {

    int move;

    printf("Computer is thinking...\n");

    do {
        move = rand() % 9;
    }
    while (board[move] != empty);
    printf("Computer (X) chose %d box. Your turn now.\n", move);
    return move;
}


void take_turn (char board[], char player) {
    
    int move;

    if (player == 'O') {
        move = get_player_move(board);
    }
    else {
        move = get_computer_move(board);
    }
    
    board[move] = player;

}


void play_game () {
    char board[9];
    char current_player = player;
    int turn;

    init_board (board);
    display_board (board);

    for (turn = 0; turn < 9; turn++) {
        take_turn (board, current_player);
        display_board (board);

        if (is_winner (board, current_player)) {
            printf("Player %c is the winner!\n", current_player);
            return;
        }
        else {
            current_player = other_player (current_player);
        }
    }
    printf("The game is a draw!\n");
}


bool play_again () {

    char player_response;

    do {
        printf("To play again, enter 'y' for yes or 'q' to quit: ");
        scanf(" %c", &player_response);

        if (player_response != 'y' && player_response != 'q') {
            printf("Invalid response. Please enter 'y' to play again or 'q' to exit the game: \n");
            scanf(" %c", &player_response);
        }

    }
    while (player_response != 'y' && player_response != 'q');
    
    if (player_response == 'y') {
        return true;
    }
    else {
        return false;
    }
}



int main (void) {

    bool again;

    srand (time (NULL));

    printf("=====================================\n");
    printf("    TIC-TACT-TOE vs COMPUTER\n");
    printf("=====================================\n");
    printf("You are (O) and you go first. The computer is (X). \n");
    printf("When it's your turn, choose an empty box: \n");

    do {
        play_game();
        again = play_again();
    }
    while (again);
        printf("Thanks for playing!\n");

    return 0;
}
