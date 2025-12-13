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

void initBoard()
{
    char angka = '1';
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = angka++;
        }
    }
}

void drawBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(i == cursorY && j == cursorX)
                attron(A_REVERSE);

            mvprintw(4 + i, 4 + j * 4, " %c ", board[i][j]);

            if(i == cursorY && j == cursorX)
                attroff(A_REVERSE);
        }
    }
}

bool makeMove()
{
    int ch = getch();

    switch(ch)
    {
        case KEY_UP:
            if(cursorY > 0) cursorY--;
            break;
        case KEY_DOWN:
            if(cursorY < 2) cursorY++;
            break;
        case KEY_LEFT:
            if(cursorX > 0) cursorX--;
            break;
        case KEY_RIGHT:
            if(cursorX < 2) cursorX++;
            break;
        case 10:  
            if(board[cursorY][cursorX] != 'X' && board[cursorY][cursorX] != 'O')
            {
                board[cursorY][cursorX] = (turn == 1) ? 'X' : 'O';
                turn = (turn == 1 ? 2 : 1);
            }
            break;
        case 'q':
        case 'Q':
            return false;
    }
    return true;
}

int checkWinner()
{
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return (board[i][0] == 'X') ? 1 : 2;

        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return (board[0][i] == 'X') ? 1 : 2;
    }


    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return (board[0][0] == 'X') ? 1 : 2;

    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return (board[0][2] == 'X') ? 1 : 2;

   
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return 0;

    return 3;  
}

void saveScore(int winner)
{
    ofstream file("score.txt", ios::app);
    if(!file) return;

    if(winner == 1) file << "Pemenang : X" << endl;
    else if(winner == 2) file << "Pemenang : O" << endl;
    else file << "Hasil : Seri" << endl;

    file.close();
}
