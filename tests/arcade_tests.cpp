#include "../Project/main.h"
#include <cassert>

int main() {
    assert(gmail_validation("not-an-email") == -1);
    assert(gmail_validation("a@b.example") == 1);
    assert(gmail_validation("a@@b.example") == -1);
    assert(strong_pass_check("Short1!") == -1);
    assert(strong_pass_check("Valid_pw123") == 1);
    const string first = hash_password("Valid_pw123");
    assert(password_matches("Valid_pw123", first));
    assert(!password_matches("Invalid_pw123", first));
    assert(hash_password("Valid_pw123") != first);
    assert(!password_matches("anything", "pbkdf2-sha256$broken"));
    char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    istringstream moves("0\n99\nnot-a-number\n1\n");
    auto original = cin.rdbuf(moves.rdbuf());
    playerMove(board, 'X');
    cin.rdbuf(original);
    cin.clear();
    assert(board[0] == 'X');
    playerInfo player{"Test", 'X'};
    char four[9][10]{};
    four[1][1]='X'; four[1][2]='X'; four[1][3]='X';
    assert(CheckFour(four, player) == 0);
    four[1][4]='X'; assert(CheckFour(four, player) == 1);
    memset(four, 0, sizeof(four));
    for(int i=0;i<4;++i) four[6-i][7-i]='X';
    assert(CheckFour(four, player) == 1);
    const auto file = filesystem::temp_directory_path() / ("arcade-test-" + to_string(GetCurrentProcessId()) + ".txt");
    _putenv_s("ARCADE_DATA_FILE", file.string().c_str());
    user = 1;
    db[0] = {1, "Player With Spaces", "player@example.test", first, 3};
    assert(record_data_to_file());
    load_data_from_file();
    assert(user == 1 && db[0].name == "Player With Spaces" && db[0].score_point == 3);
    assert(password_matches("Valid_pw123", db[0].password));
    { ofstream corrupt(file, ios::app); corrupt << "malformed\n1 bad\n"; }
    load_data_from_file();
    assert(user == 1);
    filesystem::remove(file);
    _putenv_s("ARCADE_DATA_FILE", "");
    cout << "Arcade regression checks passed.\n";
}
