# Windows Console Arcade

Five C++ console games with local player profiles: Hangman, Tic-Tac-Toe, Tetris, Snake and Connect 4. The original coursework uses Windows console APIs and requires Windows.

## Build and play

Install Visual Studio Build Tools with **Desktop development with C++** and CMake, then use a developer terminal:

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\arcade.exe
```

Alternatively, a Windows Zig toolchain can build directly:

```powershell
zig c++ Project/main.cpp -std=c++17 -lbcrypt -o arcade.exe
.\arcade.exe
```

Register a local profile, then log in with the same name, email and password. Choose a game from the menu; `0` logs out, and `3` exits the welcome menu. Profiles and points persist in `arcade-users.txt` in the working directory. Set `ARCADE_DATA_FILE` to use another path. This is local storage, with a maximum of 50 profiles. Passwords use Windows BCrypt PBKDF2-SHA256 with random salts; old plaintext records migrate on successful login.

## Controls

| Game | Controls |
| --- | --- |
| Hangman | Enter letters as prompted |
| Tic-Tac-Toe | Choose computer/two players; squares 1–9 |
| Tetris | A/D move, S down, Space rotates |
| Snake | W/A/S/D |
| Connect 4 | Choose computer/two players; columns 1–7 |

Points from Hangman, Tic-Tac-Toe and Connect 4 appear in Scores. Tetris displays its own round score. Use a real terminal for real-time Tetris/Snake input. Historical compiled coursework binaries are not the current build; compile from source using the instructions above.

## Check

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

The checks cover password storage, input bounds and profile save/reload. CI builds and checks on Windows. Real-time game presentation still requires an interactive Windows console.
