#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int mark_tic_tac_toe = 0;
void drawBoard(char *space);
void playerMove(char *space, char player);
void comMove(char *space, char com);
bool checkmate(char *space, char player, char com);
bool checktie(char *space);
void playerMovewithoppo(char *space, char player);
void oppoMove(char *space, char oppo);
bool checkmatewithOppo(char *space, char player,char oppo);

int Main_Tic_Tac_Toe();

void drawBoard(char *space){
    cout << endl;
    cout << "     |     |     \n";
    cout << "  "<< space[0] <<"  |  "<< space[1] <<"  |  "  << space[2] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  "<< space[3] <<"  |  "<< space[4] <<"  |  "  << space[5] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  "<< space[6] <<"  |  "<< space[7] <<"  |  "  << space[8] << "\n";
    cout << "     |     |     \n";
    cout << endl;
}

void playerMove(char *space, char player){
    int number;
    do{
        cout << "Enter a number (1-9) : ";
        cin  >> number;
        number--;
        if(space[number] == ' '){
            space[number] = player;
            break;
        }
    }while( !number > 0 || !number < 8);

}
// For Computer
void comMove(char *space, char com){
    int number;
    srand(time(0));
    while (true){
        number = rand()%9;
        if (space[number] == ' '){
            space[number] = com;
            break;
        };
    }
}

bool checkmate(char *space, char player, char oppo){
    if ((space[0] != ' ')&&(space[0]==space[1] && space[1]==space[2])){
        space[0] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n") : cout << "You Lose! \n";}
    else if ((space[3] != ' ')&&(space[3]==space[4] && space[4]==space[5])){
        space[3] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n")  : cout << "You Lose! \n";}
    else if ((space[6] != ' ')&&(space[6]==space[7] && space[7]==space[8])){
        space[6] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n")  : cout << "You Lose! \n";}
    else if ((space[0] != ' ')&&(space[0]==space[3] && space[3]==space[6])){
        space[0] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n")  : cout << "You Lose! \n";}
    else if ((space[1] != ' ')&&(space[1]==space[4] && space[4]==space[7])){
        space[1] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n")  : cout << "You Lose! \n";}
    else if ((space[2] != ' ')&&(space[2]==space[5] && space[5]==space[8])){
        space[2] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n")  : cout << "You Lose! \n";}
    else if ((space[0] != ' ')&&(space[0]==space[4] && space[4]==space[8])){
        space[0] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n")  : cout << "You Lose! \n";}
    else if ((space[2] != ' ')&&(space[2]==space[4] && space[4]==space[6])){
        space[1] == player ? ( mark_tic_tac_toe =1,cout << "You Win! \n")  : cout << "You Lose! \n";}
    else {
        return false;
    }
    return true;}

bool checktie(char *space){
    for (int i=0;i<9;i++){
        if(space[i]==' '){
            return false;
        }};
    cout << "It's a Tie! \n";
    return true;}

// For OPPO
void playerMovewithoppo(char *space, char player){
    int number;
    do{
        cout << "Enter a number (1-9) Player 1: ";
        cin  >> number;
        number--;
        if(space[number] == ' '){
            space[number] = player;
            break;
        }
    }while( !number > 0 || !number < 8);

}
void oppoMove(char *space, char oppo){
    int number;
    do{
        cout << "Enter a number (1-9) Player 2: ";
        cin  >> number;
        number--;
        if(space[number] == ' '){
            space[number] = oppo;
            break;
        }
    }while( !number > 0 || !number < 8);

};


bool checkmatewithOppo(char *space, char player, char com) {
    if ((space[0] != ' ') && (space[0] == space[1] && space[1] == space[2])) {
        space[0] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else if ((space[3] != ' ') && (space[3] == space[4] && space[4] == space[5])) {
        space[3] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else if ((space[6] != ' ') && (space[6] == space[7] && space[7] == space[8])) {
        space[6] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else if ((space[0] != ' ') && (space[0] == space[3] && space[3] == space[6])) {
        space[0] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else if ((space[1] != ' ') && (space[1] == space[4] && space[4] == space[7])) {
        space[1] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else if ((space[2] != ' ') && (space[2] == space[5] && space[5] == space[9])) {
        space[2] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else if ((space[0] != ' ') && (space[0] == space[4] && space[4] == space[8])) {
        space[0] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else if ((space[2] != ' ') && (space[2] == space[4] && space[4] == space[6])) {
        space[1] == player ? cout << " Player 1 Win! \n Player 2 Lose! \n" : cout
                << " Player 1 Lose! \n Player 2 Win! \n";
    } else {
        return false;
    }
    return true;


}



int Main_Tic_Tac_Toe(){
    int modeChoice;
    cout << "*******************************************" << endl;
    cout << "****************TIC-TAC-TOE!***************" << endl;
    cout << "*******************************************" << endl;
    char space[9]={' ',' ',' ',' ',' ',' ',' ',' ',' ',};
    drawBoard(space);

    do{
        cout << "\nChoose a mode! " << endl;
        cout << "1.Play with a  Friend"<<endl;
        cout << "2.Play with Computer" << endl;
        cout << "3.To quit Tic-Tac-Toe!" << endl;
        cin >> modeChoice;


        if (modeChoice == 1){

            char space[9]={' ',' ',' ',' ',' ',' ',' ',' ',' ',};
            char player='X';
            char oppo = 'O';
            bool running = true;

            drawBoard(space);
            while (running){
                playerMovewithoppo(space, player);
                drawBoard(space);
                if (checkmatewithOppo(space, player, oppo)){
                    running = false;
                    break;
                }
                else if (checktie(space)){
                    running=false;
                    break;
                }

                oppoMove(space, oppo);
                drawBoard(space);

                if (checkmatewithOppo(space, player, oppo)){
                    running = false;
                    break;
                }
                else if(checktie(space)) {
                    running=false;
                    break;
                }
            }; // mode 1 while end

        }// mode 1 if
        else if(modeChoice ==2){

            char space[9]={' ',' ',' ',' ',' ',' ',' ',' ',' ',};
            char player='X';
            char com = 'O';
            bool running = true;

            drawBoard(space);

            while (running){
                playerMove(space, player);
                drawBoard(space);
                if (checkmate(space, player, com)){
                    running = false;
                    break;
                }
                else if (checktie(space)){
                    running=false;
                    break;
                }

                comMove(space, com);
                drawBoard(space);

                if (checkmate(space, player, com)){
                    running = false;
                    break;
                }
                else if(checktie(space)) {
                    running=false;
                    break;
                }
            };// mode 2 while end
        }// mode 2 else if
        else if( modeChoice == 3){

            return 0;

        } else {
            cout << "\nInvalid Choice!" << endl;
        }
    }while ( modeChoice >= 1 || modeChoice <= 3) ;

    //cout << "Thanks for playing. \n";

    return 0;
}
