#define SS 50
#include <iostream>
#include "string"
#include "cstring"
#include "fstream"
#include "sstream"
#include "vector"
#include "SNAKE/main_for_snake.h"
#include "CONNECT_4/main_for_connect_4.h"
#include "Tic_Tac_Toe/main_for_tic_tac_toe.h"
#include "TETRIS/main_for_tetris.h"
#include "HANG_MAN/main_for_hangman.h"
using namespace std;


struct data{
    int id;
    string name;
    string email;
    string password;
    int score_point = 0;
};

struct data db[SS];

//Function Declaration
void welcome();
void registration();
int gmail_validation(string to_Valid);
int strong_pass_check(string pass);
void log_in();
void user_sector();
void record_data_to_file();
void load_data_from_file();
void print_all_data();
//Global Variables
int user = 0;
int user_index;

void welcome(){
    int option;
    cout<<"Welcome to our program!!\n";
    cout<<"Press 1 to Register:\nPress 2 to Log in:\nPress 3 to Exit:";
    cin>>option;

    if (option == 1 ){
        registration();
    } else if (option == 2 ){
        log_in();
    } else if(option == 3 ){
        ::exit(1);
    } else {
        cout<<"Enter only in the given range!";
        welcome();
    }
}


void registration(){
//    char r_email[50];
    string r_email;
    string r_name;
    string r_pw;
    int email_exit = -1;
    int strong_pass = -1;

    cout<<"Enter your email :";
//    cin.getline(r_email,50);
//    cin>>r_email;
//    cin.ignore();
    getline(cin>>ws,r_email);

    email_exit = gmail_validation(r_email);
    if (email_exit != -1){
        cout<<"Email registration succeed.\n";
        cout<<"Enter your user_name :";
//        cin.ignore();
        getline(cin>>ws,r_name);
//            cin>>r_name;
        cout<<"Enter your password : (Password must contain at least 8 letter, one capital, one small, one special character and one number!!)";
//        cin.ignore();
        getline(cin>>ws,r_pw);
//            cin>>r_pw;
        strong_pass = strong_pass_check(r_pw);
        if (strong_pass != -1){
            cout<<"Registration Succeed!";
            db[user].id = user+1;
            db[user].name = r_name;
            db[user].password = r_pw;
            db[user].email = r_email;
            user++;
            record_data_to_file();
            welcome();
        } else {
            cout<<"Password is too weak!!! Try again:\n";
            registration();
        }
    } else {
        cout<<"Email format invalid. Try again!!!\n";
        registration();
    }


}

void log_in(){
    user_index = 0;
    string l_name;
    string l_email;
    string l_pw;

    cout<<"This is login sector."<<endl;
    cout<<"Enter your user name :";
    cin.ignore();
    getline(cin,l_name);
    cout<<"Enter your email:";
//    cin.ignore();
    getline(cin,l_email);
    cout<<"Enter your password :";
//    cin.ignore();
    getline(cin,l_pw);
     for (int i=0; i<user; i++){
         if ( l_name == db[i].name && l_email == db[i].email && l_pw == db[i].password){
             user_index = i;
             cout<<"\nLog in succeed!";
             cout<<"Welcome "<<l_name<<" !!!\n";
             user_sector();
         }
     }
     cout<<"Log in failed!!!! Please try again!!\n\n\n"<<endl;
     welcome();
   //user_sector();
}

void user_sector(){
    int option;

    cout << "\n**********************" << endl;
    cout << "**********************" << endl;
    cout << "*****ARCADE GAME******" << endl;
    cout << "**********************" << endl;
    cout << "**********************" << endl <<endl;

    cout << "***************" << endl;
    cout << "Welcome Gamers!" << endl;
    cout << "Here in the \"ARCADE GAME\" we have plenty of games to play" << endl <<endl;

    do {
        cout << "***************" << endl;
        cout << "Available Games:" <<endl << endl;
        cout << "1.Hangman Game"<<endl;
        cout << "2.Tic-Tac-Toe"<<endl;
        cout << "3.Tetris Game"<<endl;
        cout << "4.Snake Game"<<endl;
        cout << "5.Connect-4 Game"<<endl <<endl;
        cout << "***************" << endl;

        cout << "Choose a game(1-5): ";
        cin>>option;
        if (option ==1 ){
            system("cls");
            Main_hang_man();
            db[user_index].score_point += mark_hang_man;
            record_data_to_file();
            user_sector();
        } else if (option ==2){
            system("cls");
            Main_Tic_Tac_Toe();
            db[user_index].score_point += mark_tic_tac_toe;
            record_data_to_file();
            user_sector();
        } else if (option == 3){
            system("cls");
            Main_tetris();
            user_sector();
        } else if (option == 4){
            system("cls");
            cout<<"fffff"<<endl;
            Main_Snake();
            user_sector();
        } else if (option == 5){
            system("cls");
            Main_Connect_4();
            db[user_index].score_point+=mark_connect_4;
            record_data_to_file();
            user_sector();
        } else {
            cout<<"\n\n*******Invalid option!*******!!"<<endl;
            cout<<"**********Please choose within the given options*******\n"<<endl;
        }

        cout << endl << endl;

    } while (true);



}


int gmail_validation(string to_Valid){
    int flag;
    string to_check;
    string Available[3] = {"@gmail.com","@yahoo.com","@email.com"};
    for (int i=0; i<to_Valid.length(); i++){
        if (to_Valid[i] == ' '){
            return -1;
        }

        if ( to_Valid[i] == '@'){
            flag = i;
            break;
        }

    }

    for (int i = flag; i<to_Valid.length(); i++){
        to_check+=to_Valid[i];
    }

    for (int i=0 ;i<3; i++){
        if (to_check == Available[i]){
            return 1;
        }
    }
    return -1;
}

int strong_pass_check(string pass){

    int i=0;
    int specialChar = 0;
    int smallChar = 0;
    int capChar = 0;
    int numChar = 0;
    if (pass.length() < 8){
        return -1;
    }

    while (true){

        if ( i == pass.length()){
            break;
        }
        if ( pass[i] >=33 && pass[i] <=42){

            specialChar++;
        } else if ( pass[i] >= 48 && pass[i] <= 57){

            numChar++;
        } else if ( pass[i] >= 64 && pass[i] <= 90){

            capChar++;
        } else if (pass[i] >= 97 && pass[i] <= 122) {

            smallChar++;
        }


        i++;


    }
    if (specialChar >0 && numChar >0 && capChar > 0 && smallChar > 0){
        return 1;
    } else{
        return -1;
    }

}

void record_data_to_file(){
    string file_Path ="D:\Project\Projectdb.txt";

    ofstream file(file_Path);
    for (int i=0; i<user; i++){
        file << db[i].id << " " << db[i].name << " " << db[i].email <<" " << db[i].password << " " << db[i].score_point << endl;
    }

    file.close();
}

void load_data_from_file(){
    string file_Path = "D:\Project\Projectdb.txt";
    string temp;
    string  name, email, password;
    int id;
    ifstream file(file_Path);
    if (file.is_open()){
        while (!file.eof()){
            getline(file,temp);
            if (temp.empty()){
                break;
            }
            istringstream iss(temp);
            vector <string> array_for_pass_and_email;
            for (string s;iss>>s;){
                array_for_pass_and_email.push_back(s);
            }
            for (int i=1; i<array_for_pass_and_email.size()-3;i++){
                if ( i!= array_for_pass_and_email.size()-4){
                    db[user].name+=array_for_pass_and_email[i] + " ";
                } else{
                    db[user].name += array_for_pass_and_email[i];
                }


            }

            db[user].id = stoi(array_for_pass_and_email[0]);
            db[user].email = array_for_pass_and_email[array_for_pass_and_email.size()-3];
            db[user].password = array_for_pass_and_email[array_for_pass_and_email.size()-2];
            db[user].score_point = stoi(array_for_pass_and_email[array_for_pass_and_email.size()-1]);
//        file >>db[user].id >> db[user].name >> db[user].email >> db[user].password ;
//      cout<<db[user].name<< "\n" << db[user].email<<"\n"<< db[user].password<<endl;
            user++;
        }

        user;

        file.close();
    } else{
        cout<<"Error Opening File!!";
    };


}


void print_all_data() {

    for (int i = 0; i < user; i++) {
        cout << db[i].id << " " << db[i].name<< " " << db[i].email << " " << db[i].password << " " << db[i].score_point << endl;
    }
}
