#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bcrypt.h>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "SNAKE/main_for_snake.h"
#include "CONNECT_4/main_for_connect_4.h"
#include "Tic_Tac_Toe/main_for_tic_tac_toe.h"
#include "TETRIS/main_for_tetris.h"
#include "HANG_MAN/main_for_hangman.h"
using namespace std;

constexpr int SS = 50;
struct PlayerData {
    int id = 0;
    string name, email, password;
    int score_point = 0;
};
PlayerData db[SS];
int user = 0, user_index = -1;

string hex_bytes(const unsigned char* bytes, size_t size) {
    ostringstream result;
    for (size_t i = 0; i < size; ++i) result << hex << setw(2) << setfill('0') << unsigned(bytes[i]);
    return result.str();
}

string derive_password(const string& password, const vector<unsigned char>& salt) {
    BCRYPT_ALG_HANDLE algorithm = nullptr;
    if (BCryptOpenAlgorithmProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, nullptr, BCRYPT_ALG_HANDLE_HMAC_FLAG) < 0)
        throw runtime_error("Password hashing is unavailable.");
    unsigned char derived[32];
    const auto status = BCryptDeriveKeyPBKDF2(algorithm,
        reinterpret_cast<PUCHAR>(const_cast<char*>(password.data())), static_cast<ULONG>(password.size()),
        const_cast<PUCHAR>(salt.data()), static_cast<ULONG>(salt.size()), 600000, derived, sizeof(derived), 0);
    BCryptCloseAlgorithmProvider(algorithm, 0);
    if (status < 0) throw runtime_error("Password hashing failed.");
    return hex_bytes(derived, sizeof(derived));
}

string hash_password(const string& password) {
    vector<unsigned char> salt(16);
    if (BCryptGenRandom(nullptr, salt.data(), static_cast<ULONG>(salt.size()), BCRYPT_USE_SYSTEM_PREFERRED_RNG) < 0)
        throw runtime_error("Secure random generation failed.");
    return "pbkdf2-sha256$" + hex_bytes(salt.data(), salt.size()) + "$" + derive_password(password, salt);
}

bool password_matches(const string& supplied, const string& stored) {
    const string prefix = "pbkdf2-sha256$";
    if (stored.rfind(prefix, 0) != 0) return supplied == stored; // Migrated to a hash after successful legacy login.
    const auto separator = stored.find('$', prefix.size());
    if (separator != prefix.size() + 32 || stored.size() != separator + 65) return false;
    vector<unsigned char> salt;
    for (size_t i = prefix.size(); i < separator; i += 2) {
        const string pair = stored.substr(i, 2);
        if (!all_of(pair.begin(), pair.end(), [](unsigned char c) { return isxdigit(c); })) return false;
        salt.push_back(static_cast<unsigned char>(stoul(pair, nullptr, 16)));
    }
    const string actual = derive_password(supplied, salt), expected = stored.substr(separator + 1);
    volatile unsigned char difference = 0;
    for (size_t i = 0; i < actual.size(); ++i) difference = difference | (actual[i] ^ expected[i]);
    return difference == 0;
}

filesystem::path data_path() {
    const char* configured = getenv("ARCADE_DATA_FILE");
    return configured && *configured ? filesystem::path(configured) : filesystem::path("arcade-users.txt");
}

bool record_data_to_file() {
    const auto path = data_path();
    if (path.has_parent_path()) filesystem::create_directories(path.parent_path());
    ofstream file(path, ios::trunc);
    for (int i = 0; i < user; ++i)
        file << db[i].id << ' ' << quoted(db[i].name) << ' ' << quoted(db[i].email) << ' '
             << quoted(db[i].password) << ' ' << db[i].score_point << '\n';
    file.flush();
    if (!file) { cerr << "Could not save local profiles. Check the data file permissions.\n"; return false; }
    return true;
}

void load_data_from_file() {
    user = 0;
    ifstream file(data_path());
    string line;
    while (user < SS && getline(file, line)) {
        PlayerData entry;
        istringstream row(line);
        if (!(row >> entry.id >> quoted(entry.name) >> quoted(entry.email) >> quoted(entry.password) >> entry.score_point)
            || entry.email.find('@') == string::npos) {
            // Older records used an unquoted, possibly multi-word name.
            istringstream legacy(line);
            vector<string> fields;
            for (string field; legacy >> field;) fields.push_back(field);
            if (fields.size() < 5) continue;
            try {
                entry = PlayerData{};
                entry.id = stoi(fields.front());
                entry.score_point = stoi(fields.back());
                entry.email = fields[fields.size() - 3];
                entry.password = fields[fields.size() - 2];
                for (size_t i = 1; i + 3 < fields.size(); ++i) entry.name += (i == 1 ? "" : " ") + fields[i];
            } catch (const exception&) { continue; }
        }
        if (entry.id > 0 && !entry.name.empty() && entry.email.find('@') != string::npos && entry.score_point >= 0)
            db[user++] = entry;
    }
}

int gmail_validation(string email) {
    const auto at = email.find('@');
    return email.size() <= 254 && at != string::npos && at > 0 && email.find('@', at + 1) == string::npos
        && email.find('.', at + 2) != string::npos && email.back() != '.'
        && none_of(email.begin(), email.end(), [](unsigned char c) { return isspace(c); }) ? 1 : -1;
}

int strong_pass_check(string password) {
    bool lower = false, upper = false, digit = false, special = false;
    if (password.size() < 8 || password.size() > 128) return -1;
    for (unsigned char c : password) {
        lower |= bool(islower(c)); upper |= bool(isupper(c)); digit |= bool(isdigit(c)); special |= bool(ispunct(c));
    }
    return lower && upper && digit && special ? 1 : -1;
}

int read_option(int minimum, int maximum) {
    string line;
    while (getline(cin >> ws, line)) {
        istringstream input(line);
        int value; char extra;
        if ((input >> value) && !(input >> extra) && value >= minimum && value <= maximum) return value;
        cout << "Enter a number from " << minimum << " to " << maximum << ": ";
    }
    return -1;
}

void print_all_data() {
    for (int i = 0; i < user; ++i) cout << db[i].name << " — " << db[i].score_point << " points\n";
}

void user_sector() {
    while (true) {
        cout << "\nARCADE — " << db[user_index].name << "\n"
             << "1. Hangman\n2. Tic-Tac-Toe\n3. Tetris\n4. Snake\n5. Connect 4\n6. Scores\n0. Log out\nChoose: ";
        int option = read_option(0, 6);
        if (option < 0 || option == 0) return;
        switch (option) {
        case 1: mark_hang_man = 0; Main_hang_man(); db[user_index].score_point += mark_hang_man; break;
        case 2: mark_tic_tac_toe = 0; Main_Tic_Tac_Toe(); db[user_index].score_point += mark_tic_tac_toe; break;
        case 3: Main_tetris(); break;
        case 4: Main_Snake(); break;
        case 5: mark_connect_4 = 0; Main_Connect_4(); db[user_index].score_point += mark_connect_4; break;
        case 6: print_all_data(); break;
        }
        record_data_to_file();
        if (!cin) return;
    }
}

void registration() {
    if (user >= SS) { cout << "This local profile store is full.\n"; return; }
    string email, name, password;
    cout << "Email: "; if (!getline(cin >> ws, email)) return;
    if (gmail_validation(email) != 1) { cout << "Invalid email address.\n"; return; }
    for (int i = 0; i < user; ++i) if (db[i].email == email) { cout << "This email already has a profile.\n"; return; }
    cout << "Player name: "; if (!getline(cin, name)) return;
    if (name.empty() || name.size() > 80) { cout << "Use a name of 1 to 80 characters.\n"; return; }
    cout << "Password (8+ characters, upper/lower case, number and symbol): "; if (!getline(cin, password)) return;
    if (strong_pass_check(password) != 1) { cout << "Password does not meet the requirements.\n"; return; }
    int id = 1;
    for (int i = 0; i < user; ++i) id = max(id, db[i].id + 1);
    db[user++] = {id, name, email, hash_password(password), 0};
    if (record_data_to_file()) cout << "Registration saved. You can now log in.\n";
}

void log_in() {
    string name, email, password;
    cout << "Player name: "; if (!getline(cin >> ws, name)) return;
    cout << "Email: "; if (!getline(cin, email)) return;
    cout << "Password: "; if (!getline(cin, password)) return;
    for (int i = 0; i < user; ++i) {
        if (db[i].name == name && db[i].email == email && password_matches(password, db[i].password)) {
            user_index = i;
            if (db[i].password.rfind("pbkdf2-sha256$", 0) != 0) {
                db[i].password = hash_password(password); record_data_to_file();
            }
            cout << "Welcome " << db[i].name << "!\n";
            user_sector();
            return;
        }
    }
    cout << "Login failed. Check your player name, email and password.\n";
}

void welcome() {
    while (cin) {
        cout << "\nWelcome to the local arcade.\n1. Register\n2. Log in\n3. Exit\nChoose: ";
        int choice = read_option(1, 3);
        if (choice < 0 || choice == 3) return;
        try {
            if (choice == 1) registration(); else log_in();
        } catch (const exception& error) { cerr << error.what() << '\n'; }
    }
}
