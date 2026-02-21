#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <vector>

using namespace std;

#define WIDTH 50
#define HEIGHT 25

int Main_Snake();



class Snake {
public:
    Snake(COORD pos, int vel);
    void change_dir(char dir);
    void move_snake();
    COORD get_snake_pos();
    bool eaten(COORD food_pos);
    void snake_grow();
    bool collide();
    vector<COORD> get_snake_body_pos();
    int direction_X = 1;
    int direction_Y = 0;

private:
    COORD pos;
    int len;
    int vel;
    char direction;
    vector<COORD> body;
};

Snake::Snake(COORD pos, int vel) {
    this->pos = pos;
    this->vel = vel;
    len = 1;
    direction = 'd';
    body.push_back(pos);
}

void Snake::change_dir(char dir) {
    direction = dir;
}

void Snake::move_snake() {
    switch (direction) {
        case 'w':
            if (pos.Y >= 0) {
                direction_X = 0;
                direction_Y = -1;
            }
            break;
        case 'a':
            if (pos.X >= 0) {
                direction_X = -1;
                direction_Y = 0;
            }
            break;
        case 's':
            if (pos.Y <= HEIGHT - 1) {
                direction_X = 0;
                direction_Y = 1;
            }
            break;
        case 'd':
            if (pos.X <= WIDTH - 1) {
                direction_Y = 0;
                direction_X = 1;
            }
            break;
    }
    pos.X += direction_X;
    pos.Y += direction_Y;
    body.push_back(pos);
    if (body.size() > len) {
        body.erase(body.begin());
    }
}

COORD Snake::get_snake_pos() {
    return pos;
}

bool Snake::eaten(COORD food_pos) {
    if (food_pos.X == pos.X && food_pos.Y == pos.Y) {
        return true;
    } else {
        return false;
    }
}

void Snake::snake_grow() {
    len++;
}

bool Snake::collide() {
    for (int count = 1; count < body.size() - 1; count++) {
        if (pos.X == body[count - 1].X && pos.Y == body[count - 1].Y) {
            return false;
        }
    }
    if (pos.X == 0 || pos.X == WIDTH - 1 || pos.Y == 0 || pos.Y == HEIGHT - 1) {
        return false;
    } else {
        return true;
    }
}

vector<COORD> Snake::get_snake_body_pos() {
    return body;
}

class Food {
private:
    COORD pos{};

public:
    COORD get_food_pos();
    COORD current_food_pos();
};

COORD Food::get_food_pos() {
    srand(static_cast<unsigned>(time(0)));
    pos.X = (rand() % (WIDTH - 2) + 1);
    pos.Y = (rand() % (HEIGHT - 2) + 1);
    return pos;
}

COORD Food::current_food_pos() {
    return pos;
}

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int Main_Snake(){
 HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    DWORD written;

    position.X = 0;
    position.Y = 0;

    SetConsoleCursorPosition(console, position);
    SetConsoleTitle("Snake Game");

    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(console, &cursor_info);

    int Snake_Speed = 100;
    bool flag_for_food = true;
    COORD snake_pos;
    COORD food_pos;
    vector<COORD> body_pos;

    char screen[WIDTH][HEIGHT];

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                screen[x][y] = '#';
            } else {
                screen[x][y] = ' ';
            }
        }
    }

    // Initialize game objects and variables here
    Snake snake({WIDTH / 2, HEIGHT / 2}, 1);
    Food food;

    while (snake.collide()) {
        if (flag_for_food) {
            food_pos = food.get_food_pos();
            flag_for_food = false;
        }

        if (_kbhit()) {
            char ch = _getch();
            snake.change_dir(ch);
        }

        snake.move_snake();
        if (snake.eaten(food.current_food_pos())) {
            flag_for_food = true;
            Snake_Speed -= 10;
            food_pos = food.get_food_pos();
            snake.snake_grow();
        }

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                    screen[x][y] = '#';
                } else {
                    screen[x][y] = ' ';
                }
            }
        }

        snake_pos = snake.get_snake_pos();
        body_pos = snake.get_snake_body_pos();

        for (int count = 0; count < body_pos.size(); count++) {
            screen[body_pos[count].X][body_pos[count].Y] = '_';
        }

        screen[food_pos.X][food_pos.Y] = 'f';
        screen[snake_pos.X][snake_pos.Y] = 'o';

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                position.X = x;
                position.Y = y;
                SetConsoleCursorPosition(console, position);
                WriteConsoleA(console, &screen[x][y], 1, &written, NULL);
            }
        }

        Sleep(Snake_Speed);
    }

    return 0;
}
