//
// Created by zl_shit_h on 03/08/23.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

struct playerInfo
{
    string playerName;
    char playerID{};
};

int mark_connect_4 = 0;

int PlayerDrop( char board[][10], playerInfo activePlayer );
void CheckBellow ( char board[][10], playerInfo activePlayer, int dropChoice );
void DisplayBoard ( char board[][10] );
int CheckFour ( char board[][10], playerInfo activePlayer );
int FullBoard( char board[][10] );
void PlayerWin ( playerInfo activePlayer );
int restart ( char board[][10] );
int PlayerDropwithcom(char board[][10],playerInfo activePlayer);
int compdrop(char board[][10], playerInfo activePlayer);

//MAIN FUNCTION
int Main_Connect_4();


int PlayerDrop( char board[][10], playerInfo activePlayer )
{
    int dropChoice;
    do
    {
        cout << activePlayer.playerName << "'s Turn ";
        cout << "Please enter a number between 1 and 7: ";
        cin  >> dropChoice;

        while ( board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O' )
        {
            cout << "That row is full, please enter a new row: ";
            cin  >> dropChoice;
        }

    }while ( dropChoice < 1 || dropChoice > 7 );

    return dropChoice;
}

void CheckBellow ( char board[][10], playerInfo activePlayer, int dropChoice )
{
    int length, turn;
    length = 6;
    turn = 0;

    do
    {
        if ( board[length][dropChoice] != 'X' && board[length][dropChoice] != 'O' )
        {
            board[length][dropChoice] = activePlayer.playerID;
            turn = 1;
        }
        else
            --length;
    }while (  turn != 1 );


}

void DisplayBoard ( char board[][10] )
{
    int rows = 6, columns = 7, i, j;

    for(i = 1; i <= rows; i++)
    {
        cout << " |";
        for(j = 1; j <= columns; j++)
        {
            if(board[i][j] != 'X' && board[i][j] != 'O'){
                board[i][j] = '*';
            }

            cout << board[i][j];

        }

        cout << "|" << endl;
    }

}// board display end here


int CheckFour ( char board[][10], playerInfo activePlayer )
{
    char XO;
    int win;

    XO = activePlayer.playerID;
    win = 0;

    for( int i = 8; i >= 1; --i )
    {

        for( int ix = 9; ix >= 1; --ix )
        {

            if( board[i][ix] == XO     && //89  if i=4/ix=5  //upper left diagnol
                board[i-1][ix-1] == XO && //78     34
                board[i-2][ix-2] == XO &&  //67    23
                board[i-3][ix-3] == XO )    //56    12
            {
                win = 1;
            }
            /*
            r1|123456|
            r2|123456|
            r3|123456|
            r4|123456|
            r5|123456|
            r6|123456|
            */
            if( board[i][ix] == XO   &&  //89   45
                board[i][ix-1] == XO &&   //88   44  left
                board[i][ix-2] == XO &&  //87     43
                board[i][ix-3] == XO )    //86     42
            {
                win = 1;
            }

            if( board[i][ix] == XO   &&    //45
                board[i-1][ix] == XO &&   //35  //upper
                board[i-2][ix] == XO &&   //25
                board[i-3][ix] == XO )   //15
            {
                win = 1;
            }

            if( board[i][ix] == XO     &&  //45
                board[i-1][ix+1] == XO &&  //36 //upper right diagonal
                board[i-2][ix+2] == XO &&  //27
                board[i-3][ix+3] == XO )  //18
            {
                win = 1;
            }

            if ( board[i][ix] == XO   && //45
                 board[i][ix+1] == XO &&   //46 right
                 board[i][ix+2] == XO && //47
                 board[i][ix+3] == XO ) //48
            {
                win = 1;
            }
        }

    }

    return win;
}

int FullBoard( char board[][10] )
{
    int full;
    full = 0;
    for ( int i = 1; i <= 7; ++i )
    {
        if ( board[1][i] != '*' )
            ++full;
    }

    return full;
}

void PlayerWin ( playerInfo activePlayer )
{
    cout << endl << activePlayer.playerName << " Connected Four, " << activePlayer.playerName << " Win!" << endl;

}

int restart ( char board[][10] )
{
    int restart;

    cout << "Would you like to restart? Yes(1) No(2): ";
    cin  >> restart;
    if ( restart == 1 )
    {
        for(int i = 1; i <= 6; i++)
        {
            for(int ix = 1; ix <= 7; ix++)
            {
                board[i][ix] = '*';
            }
        }
    }
    else{
        cout << "Goodbye!" << endl;
    }
    return restart;
}
//computer
int PlayerDropwithcom(char board[][10],playerInfo activePlayer){
    int dropChoice;
    do
    {
        cout << activePlayer.playerName << "'s Turn ";
        cout << "Please enter a number between 1 and 7: ";
        cin  >> dropChoice;

        while ( board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O' )
        {
            cout << "That row is full, please enter a new row: ";
            cin  >> dropChoice;
        }

    }while ( dropChoice < 1 || dropChoice > 7 );

    return dropChoice;

}
int compdrop(char board[][10], playerInfo activePlayer){
    int dropChoice;
    do
    {
        cout << "Computer's move is " ;
        srand(time(0));
        dropChoice=rand()%7+1;
        cout << dropChoice << endl;
        while ( board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O' )
        {
            dropChoice=rand()%7+1;
        }

    }while ( dropChoice < 1 || dropChoice > 7 );

    return dropChoice;
}


int Main_Connect_4(){
    cout << "*************************************"<< endl;
    cout << "Let's Play Connect 4" << endl ;
    cout << "*************************************"<< endl <<endl;
    char board[9][10];
    DisplayBoard(board);
    cout << endl;

    int choice=0;
    do{
        cout << "Enter a mode " << endl;
        cout << "1.Play with Computer" << endl;
        cout << "2.Play with a Friend" << endl;
        cout << "3.To quit Connect-4" << endl;
        cin >> choice;
        if(choice == 1){
            playerInfo playerOne, com;
            int trueWidth = 7;
            int trueLength = 6;
            int dropChoice, win, full, again;

            cout << "Player please enter your name: ";
            cin  >> playerOne.playerName;
            playerOne.playerID = 'X';
            com.playerName="Computer";
            com.playerID = 'O';

            full = 0;
            win = 0;
            again = 0;
            DisplayBoard( board );
            do
            {
                dropChoice = PlayerDropwithcom(board, playerOne);
                CheckBellow( board, playerOne, dropChoice );
                DisplayBoard( board );
                win = CheckFour( board, playerOne );
                if ( win == 1 )
                {
                    PlayerWin(playerOne);
                    mark_connect_4 += 1;
                    again = restart(board);
                    if (again == 2)
                    {
                        break;
                    }
                }

                dropChoice = compdrop(board, com);
                CheckBellow( board, com, dropChoice );
                DisplayBoard( board );
                win = CheckFour( board, com );
                if ( win == 1 )
                {
                    PlayerWin(com);
                    again = restart(board);

                    if (again == 2)
                    {

                        break;
                    }
                }
                full = FullBoard( board );
                if ( full == 7 )
                {
                    cout << "The board is full, it is a draw!" << endl;
                    again = restart(board);
                }

            }while ( again != 2 );


        }
//choice 1 end here
        else if(choice == 2){
            playerInfo playerOne, playerTwo;
            char board[9][10];
            int trueWidth = 7;
            int trueLength = 6;
            int dropChoice, win, full, again;

            cout << "Let's Play Connect 4" << endl << endl;
            cout << "Player One please enter your name: ";
            cin  >> playerOne.playerName;
            playerOne.playerID = 'X';
            cout << "Player Two please enter your name: ";
            cin  >> playerTwo.playerName;
            playerTwo.playerID = 'O';

            full = 0;
            win = 0;
            again = 0;
            DisplayBoard( board );
            do
            {
                dropChoice = PlayerDrop( board, playerOne );
                CheckBellow( board, playerOne, dropChoice );
                DisplayBoard( board );
                win = CheckFour( board, playerOne );
                if ( win == 1 )
                {
                    PlayerWin(playerOne);
                    again = restart(board);
                    if (again == 2)
                    {
                        break;
                    }
                }

                dropChoice = PlayerDrop( board, playerTwo );
                CheckBellow( board, playerTwo, dropChoice );
                DisplayBoard( board );
                win = CheckFour( board, playerTwo );
                if ( win == 1 )
                {
                    PlayerWin(playerTwo);
                    again = restart(board);
                    if (again == 2)
                    {
                        break;
                    }
                }
                full = FullBoard( board );
                if ( full == 7 )
                {
                    cout << "The board is full, it is a draw!" << endl;
                    again = restart(board);
                }

            }while ( again != 2 );
        }else if ( choice == 3 ){
            return 0;
        } else {
            cout<<"Invalid Option!!\n"<<endl;
        }



    }while( choice !=1 && choice !=2);

    cout << "Thank you for playing!";
    return 0;
}
