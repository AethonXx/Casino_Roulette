#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

#pragma region Print

enum ConsoleColor
{
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    magenta = 5,
    brown = 6,
    lightGray = 7,
    darkGray = 8,
    lightBlue = 9,
    lightGreen = 10,
    lightCyan = 11,
    lightRed = 12,
    lightMagenta = 13,
    yellow = 14,
    white = 15
};

void print(string text = " ", int x = 0, int y = 0, ConsoleColor text_color = white, ConsoleColor background = black)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
    SetConsoleTextAttribute(handle, (WORD)((background << 4) | text_color));
    cout << text;
    SetConsoleTextAttribute(handle, (WORD)((black << 4) | white));
}void print(int x = 0, int y = 0, ConsoleColor background = black)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
    SetConsoleTextAttribute(handle, (WORD)((background << 4) | white));
    cout << " ";
    SetConsoleTextAttribute(handle, (WORD)((black << 4) | white));
}
#pragma endregion Print

#pragma region Field
string numbers[] = {
"01r", "02b", "03r", "04b", "05r", "06b", "07r", "08b", "09r", "10b", "11b", "12r",
"13b", "14r", "15b", "16r", "17b", "18r", "19r", "20b", "21r", "22b", "23r", "24b",
"25r", "26b", "27r", "28b", "29b", "30r", "31b", "32r", "33b", "34r", "35b", "36r" };

void field()
{
    for (int i = 0; i < 70; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            print(i, j, green);
        }
    }
    int circlex[] = { 9,10,11,6,7,8,12,13,14,3,4,5,15,16,17,2,18,1,19,1,19,1,19,2,18,15,16,17,3,4,5,12,13,14,6,7,8,9,10,11 };
    int circley[] = { 1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,4,4,5,5,6,6,7,7,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9 };

    for (size_t i = 22; i < 39; i++)
    {
        for (size_t j = 3; j < 9; j++)
        {
            print(i, j, darkGray);
        }
    }
    for (size_t i = 0; i < size(circlex); i++)
    {
        print(circlex[i] + 20, circley[i], yellow);
        print(circlex[i] + 20, circley[i] + 1, lightRed);
    }

    for (size_t i = 4; i < 57; i++)
    {
        print(i, 13, yellow);
        print(i, 23, yellow);
        print(i, 24, lightRed);
    }
    for (size_t i = 13; i < 24; i++)
    {
        print(4, i, yellow);
        print(56, i, yellow);
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            print(5 + j, i + 14, green);
        }
    }
    print("0", 6, 18, white, lightGreen);
    for (int k = 0; k < size(numbers); k++)
    {
        for (int i = 3; i >= 0; i--)
        {
            for (int j = 0; j < 3; j++)
            {
                string num = to_string(stoi(numbers[k].substr(0, 2)));
                print(i * j == 1 ? num : j == 2 && i < 3 && k % 3>0 ? "_" : i == 3 ? "|" : " ",
                    8 + i + ((k / 3) * 4), j + 20 - ((k * 3) % 9),
                    i * j == 1 ? white : darkGray,
                    numbers[k][2] == 'r' ? red : black);

            }
        }
    }
    print(66, 30, green);
}
#pragma endregion Field

int roulette() {
    int rnd;
    for (size_t k = 0; k < 20; k++) {


        rnd = rand() % (size(numbers) + 1) - 1;
        if (rnd == -1) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    print(28 + i, 5 + j, lightGreen);
                }
            }
            print("0", 29, 6, white, green);
        }
        else {
            char color;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    color = numbers[rnd][2];
                    print(28 + i, 5 + j, color == 'r' ? red : black);
                }
            }
            string num = to_string(rnd + 1);
            print(num, 29, 6, white, color == 'r' ? red : black);
        }
        Sleep(100);
    }
    return (rnd + 1);
}
using namespace std;
int main()
{
    setlocale(0, "");
    srand(time(NULL));
    field();
    int money = 1000;


    while (true) {
        print("Color:   red  | black                  x02", 4, 27);
        print("Parity: even  | odd                    x02", 4, 28);
        print("Half:  1to18  | 19to36                 x02", 4, 29);
        print("Dozen: dozen1 | dozen2  | dozen3       x03", 4, 30);
        print("Row:   line1  | line2   | line3        x03", 4, 31);
        print("Number:      0|36                      x36", 4, 32);
        print("Choice:      ", 4, 4);
        print("Bet:         ", 4, 6);
        print("Money:" + to_string(money) + " \t", 42, 2);
        string choice;
        print(11, 4);
        cin >> choice;
        int bet;
        print(" ", 8, 6);
        cin >> bet;
        int num = roulette();
        if (bet <= money and bet > 0)
            money -= bet;
        else
            continue;
        try {
            int x = stoi(choice);
            if (x == num) {
                money += bet * 2;
                print("Win!", 42, 5);
            }
            else
            {
                print("Lose!", 42, 5);
                money -= bet;
            }
        }
        catch (const std::exception&) {
            if (choice == "red") {
                if (numbers[num - 1][2] == 'r' and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else
                {
                    print("Lose!", 42, 5);
                }
            }
            if (choice == "black") {
                if (numbers[num - 1][2] == 'b' and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else
                {
                    print("Lose!", 42, 5);
                }
            }
            if (choice == "even") {
                if (num % 2 == 0 and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }

            }
            if (choice == "odd") {
                if (num % 2 == 1 and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }
            }
            if (choice == "dozen1") {
                if (num <= 12 and num != 0) {
                    money += bet * 3;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }
            }
            if (choice == "dozen2") {
                if (num >= 13 and num <= 24 and num != 0) {
                    money += bet * 3;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }
            }
            if (choice == "dozen3") {
                if (num >= 25 and num <= 36 and num != 0) {
                    money += bet * 3;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }
            }
            if (choice == "line1") {
                if (num >= 13 and num <= 24 and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }
            }
            if (choice == "line1") {
                if (num % 3 == 1 and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }

            }
            if (choice == "line2") {
                if (num % 3 == 2 and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }

            }
            if (choice == "line3") {
                if (num % 3 == 0 and num != 0) {
                    money += bet * 2;
                    print("Win!", 42, 5);
                }
                else {
                    print("Lose!", 42, 5);
                }

            }

        }
    }


    int pause; cin >> pause;
}

