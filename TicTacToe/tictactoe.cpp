#include <iostream>
#include <fstream>
#include <string>
#include <ncurses/curses.h>
using namespace std;

char board[3][3];
int cursorY = 0, cursorX = 0;
int turn = 1;

void initBoard();
void drawBoard();
bool makeMove();
int checkWinner();
void saveScore(int winner);

int main(){
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    bool playAgain = true;

    while(playAgain){
        turn = 1;
        cursorY = cursorX = 0;
        initBoard();

        while(true){
            clear();
            mvprintw(0, 0, "TIC TAC TOE");
            mvprintw(1, 0, "Gunakan panah untuk pilih kotak dan enter untuk taruh X/O");
            mvprintw(2, 0, "Giliran : %s", (turn == 1 ? "X" : "O"));

            drawBoard();

            int winner = checkWinner();
            if(winner != 0){
                clear();
                drawBoard();

                if(winner == 1) mvprintw(10, 0, "Pemenang : X");
                else if(winner == 2) mvprintw(10, 0, "Pemenang : O");
                else mvprintw(10, 0, "Hasil : Seri");

                saveScore(winner);

                mvprintw(12, 0, "Main lagi? (y/n) : ");
                int u = getch();
                if(u == 'y' || u == 'Y') {
                    playAgain = true;
                } else {
                    playAgain = false;
                }
                break;
            }

            if(!makeMove()) { 
                playAgain = false; 
                break; 
            }
        }
    }

    endwin();
    return 0;
}

