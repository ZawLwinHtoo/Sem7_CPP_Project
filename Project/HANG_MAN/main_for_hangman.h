#include <iostream>
#include <ctype.h>
#include <cstring>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;


int mark_hang_man = 0;
//FUNCTIONS DECLARATION
string chooseWord(const vector<string>& topicWords);
string initializeGuessedWord(const string& word);
void displayHangman(int attemptsLeft);
void displayHiddenWord(const string& hiddenWord);
void updateGuessedWord(string& guessedWord, const string& word, char guess);
int Main_hang_man();


string chooseWord(const vector<string>& topicWords)
{
    int index = rand() % topicWords.size();
    return topicWords[index];
}

string initializeGuessedWord(const string& word) {
    string guessedWord(word.length(), '_');
    return guessedWord;
}

void displayHangman(int attemptsLeft) {
    // ... (your existing displayHangman code)
    cout << "Attempts left: " << attemptsLeft << "\n";
    if (attemptsLeft == 6) {
        cout << " _________\n"
             << " |/     |   \n"
             << " |\n"
             << " |\n"
             << " |\n"
             << " |\n"
             << " |\n"
             << "==========\n";
    } else if (attemptsLeft == 5) {
        cout << " _________\n"
             << " |/   |   \n"
             << " |    O   \n"
             << " |\n"
             << " |\n"
             << " |\n"
             << " |\n"
             << " |\n"
             << "==========\n";
    } else if (attemptsLeft == 4) {
        cout << " _________\n"
             << " |/   |   \n"
             << " |    O   \n"
             << " |    |   \n"
             << " |    |   \n"
             << " |\n"
             << " |\n"
             << " |\n"
             << " |\n"
             << "==========\n";
    } else if (attemptsLeft == 3) {
        cout << " _________\n"
             << " |/   |   \n"
             << " |    O   \n"
             << " |   /|   \n"
             << " |    |   \n"
             << " |\n"
             << " |\n"
             << "==========\n";
    } else if (attemptsLeft == 2) {
        cout << " _________\n"
             << " |/   |   \n"
             << " |    O   \n"
             << " |   /|\\ \n"
             << " |    |   \n"
             << " |\n"
             << " |\n"
             << "==========\n";
    } else if (attemptsLeft == 1) {
        cout << " _________\n"
             << " |/   |   \n"
             << " |    O   \n"
             << " |   /|\\ \n"
             << " |    |   \n"
             << " |   /   \n"
             << " |\n"
             << "==========\n";
    }
}



void displayHiddenWord(const string& hiddenWord)
{
    cout << "Current word: " << hiddenWord << "\n";
}

void updateGuessedWord(string& guessedWord, const string& word, char guess) {
    for (size_t i = 0; i < word.length(); ++i)
    {
        if (word[i] == guess)
            guessedWord[i] = guess;
    }
}


int Main_hang_man(){

    srand(time(0));
    const int MAX=50;
    int i,j,k;
    int counter=0, pos;

    vector <string> topicWords[] = {
            {"apple", "orange", "banana", "grapes", "kiwi", "strawberry", "watermelon", "mango", "mangosteen", "avocado"},
            {"cat", "dog", "elephant", "dinosaur", "kangaroo", "rhinoceros", "panda", "monkey", "giraffe", "zebra"},
            {"white", "blue", "black", "green", "purple", "magenta", "indigo", "pink", "yellow", "brown"},
            {"burger", "pizza", "toast", "steak", "oat", "yogurt", "cheese", "chocolate", "pasta", "curry"},
            {"anger", "fear", "love", "happiness", "anxiety", "embarrassment", "sadness", "loneliness", "jealousy", "pride"}
    };

    int choose;
    cout<<"THIS IS HANGMAN GAME\n\n";
    cout << "\n\nChoose the topic (1-5) ";
    cout << "\n1. Fruit \n2. Animal \n3. Colour \n4. Food \n5. Emotion \n6.To quit Hang-Man\n";
    cout << "Your choice: ";
    cin >> choose;
    cout << endl;

    vector <string> chosenTopic;
    if (choose >= 1 && choose <= 5)
        chosenTopic = topicWords[choose - 1];
    else if( choose == 6){
//        exit(0);
        return 0;
    }else{
        cout << "Invalid topic choice!\n";
        return 1; // Exit the program
    }

    string chosenWord = chooseWord(chosenTopic);
    string guessedWord = initializeGuessedWord(chosenWord);
    int attemptsLeft = 6;
    char guess;


    while (attemptsLeft > 0 && guessedWord != chosenWord)
    {
        displayHangman(attemptsLeft);


        cout << "Current word: " << guessedWord << endl;
        cout << "Attempts left: " << attemptsLeft << endl;
        cout << "Guess a letter: ";
        cin >> guess;

        if (guessedWord.find(guess) != string::npos)
        {
            cout << "You've already guessed that letter.\n";
            continue;
        }

        if(chosenWord.find(guess) != string::npos)
        {
            updateGuessedWord(guessedWord, chosenWord, guess);
        }
        else
        {
            cout << "Incorrect guess!\n";
            --attemptsLeft;
        }
    }


    if (guessedWord == chosenWord) {
        cout << "Congratulations! You guessed the word: " << chosenWord << endl;
        mark_hang_man = 1;
    } else {
        cout << " _________\n"
             << " |/   |   \n"
             << " |    O   \n"
             << " |   /|\\ \n"
             << " |    |   \n"
             << " |   / \\  \n"
             << " |\n"
             << "==========\n";
        cout << "Sorry, you've run out of attempts. The word was: " << chosenWord << endl;
    }

    return 0;
}
