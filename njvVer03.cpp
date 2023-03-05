#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void instructions();
void story();
void loadingScreen();
void printStage();
void header();
void printNinjaRight(int x, int y);
void printNinjaLeft(int x, int y);
void eraseNinja(int x, int y);
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
string setcolor(unsigned short color);
void moveNinjaUp();
void moveNinjaDown();
void moveNinjaLeft();
void moveNinjaRight();
void printCanonLeft();
void printCanonRight();
void eraseLeftCanon();
void eraseRightCanon();
void moveBulletFromLeftCanon();
void moveBulletFromRightCanon();
void eraseBulletOfCanon(int x, int y);
void generateBulletFromLeftCanon();
void generateBulletFromRightCanon();
void printFireOfLeftCanon(int x, int y);
void printLeftSnake(int x, int y);
void printRightSnake(int x, int y);
void eraseSnake(int x, int y);
void moveLeftSnake();
void moveRightSnake();
void generateLeftSnake();
void generateRightSnake();
void generateLeftCoin();
void generateRightCoin();
void printCoin(int x, int y);
void eraseCoin(int x, int y);
void moveLeftCoin();
void moveRightCoin();

char loadingPageCharacter[16][45] = {
    {"                         =.                 "},
    {"                         =%+                "},
    {"               ..     :=-+@@#::.            "},
    {"              .--*:.    *@@@%%%%%*:         "},
    {"                .@@%%#= :@@@%%%%%%%-        "},
    {"           .::::=%@@@@%%%@@%%%%%%%%#        "},
    {"           :-=*@%%%%%%%%@@@#-:-====+        "},
    {"      .        -%%@@@@%%%@@@#=:+-:=         "},
    {"   :+%@#     .=%%%%%%%%%%%%=+**=-.          "},
    {"  -+: .%@*%%%@@@%%%###%%#=                  "},
    {"       .#@@%%%@@%%%%%%%+:                   "},
    {"         *%%%*=:=%@%%%%%%%-                 "},
    {"                  +@@@@%%%=                 "},
    {"                    -+*#*@%-  -+            "},
    {"                          =%%%+             "},
    {"                 Loading...                 "}};
char stage[39][55] = {{"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|                                                  |_"},
                      {"_|__________________________________________________|_"}};
// Maze
int mazeY = 37;

// Snake Left Wall
char snakeLeft[4][3] = {{"( "},
                        {" )"},
                        {"( "},
                        {" 0"}};

// Snake Right Wall
char snakeRight[4][3] = {{" )"},
                         {"( "},
                         {" )"},
                         {"0 "}};

// Character Oriented Right
char ninjaRight[4][5] = {{"   >"},
                         {"O / "},
                         {" \\  "},
                         {"   >"}};
// Character Oriented Left
char ninjaLeft[4][5] = {{"<   "},
                        {" \\ O"},
                        {"  / "},
                        {"<   "}};

// Canon Left Wall
char x = 177;
char canonLeft[3][3] = {{'O', x, x},
                        {'O', x, x},
                        {' ', x, x}};

// Canon Right Wall
char canonRight[3][3] = {{x, x, 'O'},
                         {x, x, 'O'},
                         {x, x, ' '}};

// Snake Movement Coordinates
int lSX[100];
int lSY[100];
int lSCount = 0;
int rSX[100];
int rSY[100];
int rSCount = 0;

// Canon Fire Coordinates
int lCFireX[100];
int lCFireY[100];
int lCFireCount = 0;
int rCFireX[100];
int rCFireY[100];
int rCFireCount = 0;

// Left Coin Coordinates
int lcoinX[100];
int lcoinY[100];
int lcoinCount = 0;

// Right Coin Coordinates
int rcoinX[100];
int rcoinY[100];
int rcoinCount = 0;

// Coordinates
int cLX = 2;  // X-Coordinate of Left Canon
int cLY = 3;  // Y-Cordinate of Left Canon
int cRX = 49; // X-Coordinate of Right Canon
int cRY = 3;  // Y-Cordinate of Right Canon
int sLX = 2;  // X-Coordinate of Left Snake
int sLY = 3;  // Y-Cordinate of Left Snake
int sRX = 50; // X-Coordinate of Right Snake
int sRY = 3;  // Y-Cordinate of Right Snake
int nX = 2;   // X-Coordinate of Ninja
int nY = 25;  // Y-Cordinate of Ninja
int lcX = 3;
int lcY = 6;
int rcX = 49;
int rcY = 6;

int hit = 0;
int score = 0;

char moveStatus = 'S'; // Flag for checking Movement State  S=Static,R=Right,L=Left
int lifeCount = 5;
int tick1 = 0;
int tick2 = 0;
int tick3 = 0;
int tick4 = 0;
int mainTick = 0;
bool isLeftCanonPresent = false;
bool isRightCanonPresent = false;
bool isLeftSnakePresent = false;
bool isRightSnakePresent = false;
bool isBulletMoving = false;
bool isShieldActive = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
main()
{
    system("cls");
    // mainScreen();
    loadingScreen();
    int choice;
    while (1)
    {
        header();
        cout << "          1. Play Game                                                              " << endl;
        cout << "          2. Read Instructions                                                      " << endl;
        cout << "          3. Story Line                                                             " << endl;
        cout << "          4. Exit                                                                   " << endl;
        cout << "          Enter Chioce:";
        cin >> choice;
        if (choice == 1)
        {
            printStage();
            // generateLeftSnake();
            // generateRightSnake();
            // printRightSnake();
            // printCanonLeft();
            // printCanonRight();
            while (lifeCount > 0)
            {
                if (nX < 27)
                {
                    if (isShieldActive == true)
                    {
                        setcolor(12);
                        printNinjaLeft(nX, nY);
                        setcolor(15);
                    }
                    else
                    {
                        printNinjaLeft(nX, nY);
                    }
                }
                else
                {
                    if (isShieldActive == true)
                    {
                        setcolor(12);
                        printNinjaRight(nX, nY);
                        setcolor(15);
                    }
                    else
                    {
                        printNinjaRight(nX, nY);
                    }
                }
                if (hit == 5)
                {
                    hit = 0;
                    lifeCount--;
                }
                if (mainTick > 500 && mainTick < 1000)
                {
                    int x = rand() % 20;
                    if (x == 7)
                    {
                        generateBulletFromLeftCanon();
                    }
                }
                if (mainTick == 500)
                {
                    eraseRightCanon();
                    isRightCanonPresent = false;
                    if (isLeftSnakePresent == false && isLeftCanonPresent == false)
                    {
                        printCanonLeft();
                        generateBulletFromLeftCanon();
                        isLeftCanonPresent = true;
                    }
                }
                if (mainTick > 1000 && mainTick < 2000)
                {
                    int x = rand() % 20;
                    if (x == 7)
                    {
                        if (isRightCanonPresent == false)
                        {
                            generateRightSnake();
                        }
                    }
                }
                if (mainTick == 1000)
                {
                    eraseLeftCanon();
                    isLeftCanonPresent = false;
                    if (isRightSnakePresent == false && isRightCanonPresent == false)
                    {
                        generateRightSnake();
                        isRightSnakePresent = true;
                    }
                }
                if (mainTick > 2000 && mainTick < 3000)
                {
                    int x = rand() % 20;
                    if (x == 7)
                    {
                        if (isLeftCanonPresent == false)
                        {
                            generateLeftSnake();
                        }
                    }
                }
                if (mainTick == 2000)
                {
                    isRightSnakePresent = false;
                    if (isLeftCanonPresent == false && isLeftSnakePresent == false)
                    {
                        generateLeftSnake();
                        isLeftSnakePresent = true;
                    }
                }
                if (mainTick > 3000 && mainTick < 4000)
                {
                    int x = rand() % 15;
                    if (x == 7)
                    {
                        generateBulletFromRightCanon();
                    }
                }
                if (mainTick == 3000)
                {
                    isLeftSnakePresent = false;
                    if (isRightSnakePresent == false && isRightCanonPresent == false)
                    {
                        printCanonRight();
                        generateBulletFromRightCanon();
                        isRightCanonPresent = true;
                    }
                }
                if (mainTick == 4000)
                {
                    eraseLeftCanon();
                    eraseRightCanon();
                    isRightCanonPresent = false;
                    isLeftCanonPresent = false;
                    isRightSnakePresent = false;
                    isLeftSnakePresent = false;
                    mainTick = 0;
                }
                if (GetAsyncKeyState(VK_SPACE))
                {
                    generateRightCoin();
                }
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
                {
                    if (moveStatus == 'S')
                    {
                        moveStatus = 'R';
                    }
                }
                if (GetAsyncKeyState(VK_LEFT) & 0x8000)
                {
                    if (moveStatus == 'S')
                    {
                        moveStatus = 'L';
                    }
                }
                if (moveStatus == 'S')
                {
                    if (GetAsyncKeyState(VK_UP) & 0x8000)
                    {
                        if (nY > 8)
                        {
                            moveNinjaUp();
                        }
                    }
                    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
                    {
                        if (nY < 32)
                        {
                            moveNinjaDown();
                        }
                    }
                }
                if (moveStatus == 'R')
                {
                    char next = getCharAtxy(nX + 4, nY);
                    if (next == ' ')
                    {
                        eraseNinja(nX, nY);
                        nX++;
                    }
                    else
                    {
                        moveStatus = 'S';
                    }
                    if (nX < 27)
                    {
                        if (isShieldActive == true)
                        {
                            setcolor(12);
                            printNinjaLeft(nX, nY);
                            setcolor(15);
                        }
                        else
                        {
                            printNinjaLeft(nX, nY);
                        }
                    }
                    else
                    {
                        if (isShieldActive == true)
                        {
                            setcolor(12);
                            printNinjaRight(nX, nY);
                            setcolor(15);
                        }
                        else
                        {
                            printNinjaRight(nX, nY);
                        }
                    }
                }
                else if (moveStatus == 'L')
                {
                    char next = getCharAtxy(nX - 1, nY);
                    if (next == ' ' || next == 'O')
                    {
                        // if(next == 'O')
                        // {
                        //     hit++;
                        // }
                        eraseNinja(nX, nY);
                        nX--;
                    }
                    else
                    {
                        moveStatus = 'S';
                    }
                    if (nX < 27)
                    {
                        if (isShieldActive == true)
                        {
                            setcolor(12);
                            printNinjaLeft(nX, nY);
                            setcolor(15);
                        }
                        else
                        {
                            printNinjaLeft(nX, nY);
                        }
                    }
                    else
                    {
                        if (isShieldActive == true)
                        {
                            setcolor(12);
                            printNinjaRight(nX, nY);
                            setcolor(15);
                        }
                        else
                        {
                            printNinjaRight(nX, nY);
                        }
                    }
                }
                moveBulletFromLeftCanon();
                moveBulletFromRightCanon();
                moveLeftSnake();
                moveRightSnake();
                moveLeftCoin();
                moveRightCoin();
                // collisionDetection();
                //  gotoxy(60, 5);
                //  cout << "Hits: " << hit;
                gotoxy(60, 6);
                cout << "Score: " << score;
                gotoxy(60, 7);
                cout << "Life Count: " << lifeCount;
                mainTick++;
                tick1++;
                tick2++;
                tick3++;
                tick4++;
                Sleep(10);
            }
            system("cls");
            cout << "GameOver!!!!!";
        }

        else if (choice == 2)
        {
            header();
            instructions();
            getch();
        }
        else if (choice == 3)
        {
            header();
            story();
            getch();
        }
        else if (choice == 4)
        {
            break;
        }
        else if (choice > 4)
        {
            cout << "Invalid Choice!!" << endl;
            cout << "Enter Correct Choice!!" << endl;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void moveNinjaUp()
{
    char next = getCharAtxy(nX, nY - 1);
    if (next == ' ' || next == 'O')
    {
        // if(next == 'O')
        // {
        //     hit++;
        // }
        eraseNinja(nX, nY);
        nY--;
    }
    else
    {
        moveStatus = 'S';
    }
    if (nX < 27)
    {
        if (isShieldActive == true)
        {
            setcolor(12);
            printNinjaLeft(nX, nY);
            setcolor(15);
        }
        else
        {
            printNinjaLeft(nX, nY);
        }
    }
    else
    {
        if (isShieldActive == true)
        {
            setcolor(12);
            printNinjaRight(nX, nY);
            setcolor(15);
        }
        else
        {
            printNinjaRight(nX, nY);
        }
    }
}
void moveNinjaDown()
{
    char next = getCharAtxy(nX, nY + 4);
    if (next == ' ' || next == 'O')
    {
        // if(next == 'O')
        // {
        //     hit++;
        // }
        eraseNinja(nX, nY);
        nY++;
    }
    else
    {
        moveStatus = 'S';
    }
    if (nX < 27)
    {
        if (isShieldActive == true)
        {
            setcolor(12);
            printNinjaLeft(nX, nY);
            setcolor(15);
        }
        else
        {
            printNinjaLeft(nX, nY);
        }
    }
    else
    {
        if (isShieldActive == true)
        {
            setcolor(12);
            printNinjaRight(nX, nY);
            setcolor(15);
        }
        else
        {
            printNinjaRight(nX, nY);
        }
    }
}
void generateLeftCoin()
{
    lcoinY[lcoinCount] = lcY;
    lcoinX[lcoinCount] = lcX;
    gotoxy(lcX, lcY);
    cout << "@";
    lcoinCount++;
}
void generateRightCoin()
{
    rcoinX[rcoinCount] = rcX;
    rcoinY[rcoinCount] = rcY;
    gotoxy(rcX, rcY);
    cout << "@";
    rcoinCount++;
}
void printCoin(int x, int y)
{
    gotoxy(x, y);
    cout << "@";
}
void eraseCoin(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void moveLeftCoin()
{
    int i = 0;
    while (i < lcoinCount)
    {
        char next = getCharAtxy(lcoinX[i], lcoinY[i] + 1);
        char next1 = getCharAtxy(lcoinX[i] + 1, lcoinY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/')
        {
            score += 5;
            eraseCoin(lcoinX[i], lcoinY[i]);
            for (int j = i; j < lcoinCount - 1; j++)
            {
                lcoinX[j] = lcoinX[j + 1];
                lcoinY[j] = lcoinY[j + 1];
            }
            lcoinCount--;
        }
        else if (lcoinY[i] == mazeY)
        {
            eraseCoin(lcoinX[i], lcoinY[i]);
            for (int j = i; j < lcoinCount - 1; j++)
            {
                lcoinX[j] = lcoinX[j + 1];
                lcoinY[j] = lcoinY[j + 1];
            }
            lcoinCount--;
        }
        else
        {

            eraseCoin(lcoinX[i], lcoinY[i]);
            lcoinY[i] = lcoinY[i] + 1;
            printCoin(lcoinX[i], lcoinY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void moveRightCoin()
{
    int i = 0;
    while (i < rcoinCount)
    {
        char next = getCharAtxy(rcoinX[i], rcoinY[i] + 1);
        char next1 = getCharAtxy(rcoinX[i] + 1, rcoinY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/')
        {
            score += 5;
            eraseCoin(rcoinX[i], rcoinY[i]);
            for (int j = i; j < rcoinCount - 1; j++)
            {
                rcoinX[j] = rcoinX[j + 1];
                rcoinY[j] = rcoinY[j + 1];
            }
            rcoinCount--;
        }
        else if (rcoinY[i] == mazeY)
        {
            eraseCoin(rcoinX[i], rcoinY[i]);
            for (int j = i; j < rcoinCount - 1; j++)
            {
                rcoinX[j] = rcoinX[j + 1];
                rcoinY[j] = rcoinY[j + 1];
            }
            rcoinCount--;
        }
        else
        {

            eraseCoin(rcoinX[i], rcoinY[i]);
            rcoinY[i] = rcoinY[i] + 1;
            printCoin(rcoinX[i], rcoinY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void moveRightSnake()
{
    int i = 0;
    while (i < rSCount)
    {
        char next = getCharAtxy(rSX[i], rSY[i] + 1);
        char next1 = getCharAtxy(rSX[i] + 1, rSY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/')
        {
            if (isShieldActive == false)
            {
                hit++;
            }
            eraseSnake(rSX[i], rSY[i]);
            for (int j = i; j < rSCount - 1; j++)
            {
                rSX[j] = rSX[j + 1];
                rSY[j] = rSY[j + 1];
            }
            rSCount--;
        }
        else if (rSY[i] == mazeY)
        {
            eraseSnake(rSX[i], rSY[i]);
            for (int j = i; j < rSCount - 1; j++)
            {
                rSX[j] = rSX[j + 1];
                rSY[j] = rSY[j + 1];
            }
            rSCount--;
            // isRightSnakePresent = false;
        }
        else
        {

            eraseSnake(rSX[i], rSY[i]);
            rSY[i] = rSY[i] + 1;
            printRightSnake(rSX[i], rSY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void moveLeftSnake()
{
    int i = 0;
    while (i < lSCount)
    {
        char next = getCharAtxy(lSX[i], lSY[i] + 1);
        char next1 = getCharAtxy(lSX[i] + 1, lSY[i] + 1);
        if (next1 == '<' || next1 == '\\' || next == '<' || next == '\\')
        {
            if (isShieldActive == false)
            {
                hit++;
            }
            eraseSnake(lSX[i], lSY[i]);
            for (int j = i; j < lSCount - 1; j++)
            {
                lSX[j] = lSX[j + 1];
                lSY[j] = lSY[j + 1];
            }
            lSCount--;
        }
        else if (lSY[i] == mazeY)
        {
            eraseSnake(lSX[i], lSY[i]);
            for (int j = i; j < lSCount - 1; j++)
            {
                lSX[j] = lSX[j + 1];
                lSY[j] = lSY[j + 1];
            }
            lSCount--;
            // isLeftSnakePresent = false;
        }
        else
        {

            eraseSnake(lSX[i], lSY[i]);
            lSY[i] = lSY[i] + 1;
            printLeftSnake(lSX[i], lSY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void generateLeftSnake()
{
    lSX[lSCount] = sLX;
    lSY[lSCount] = sLY;
    int x = sLX;
    int y = sLY;
    for (int row = 3; row >= 0; row--)
    {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++)
        {
            cout << snakeLeft[row][col];
        }
        y--;
    }
    lSCount++;
}
void generateRightSnake()
{
    rSX[rSCount] = sRX;
    rSY[rSCount] = sRY;
    int x = sRX;
    int y = sRY;
    for (int row = 3; row >= 0; row--)
    {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++)
        {
            cout << snakeRight[row][col];
        }
        y--;
    }
    rSCount++;
}
void eraseSnake(int x, int y)
{
    // 3X4
    gotoxy(x, y - 3);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }
    gotoxy(x, y - 2);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }
    gotoxy(x, y - 1);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }
    gotoxy(x, y);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }
}
void printRightSnake(int x, int y)
{
    // 3X4
    for (int row = 3; row >= 0; row--)
    {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++)
        {
            cout << snakeRight[row][col];
        }
        y--;
    }
}
void printLeftSnake(int x, int y)
{
    // 3X4
    for (int row = 3; row >= 0; row--)
    {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++)
        {
            cout << snakeLeft[row][col];
        }
        y--;
    }
}
void moveBulletFromLeftCanon()
{
    int i = 0;
    while (i < lCFireCount)
    {
        char next = getCharAtxy(lCFireX[i], lCFireY[i] + 1);
        char next2 = getCharAtxy(lCFireX[i] + 1, lCFireY[i] + 1);
        if (next == '<' || next == '\\' || next2 == '<' || next2 == '\\')
        {
            if (isShieldActive == false)
            {
                hit++;
            }
            eraseBulletOfCanon(lCFireX[i], lCFireY[i]);
            for (int j = i; j < lCFireCount - 1; j++)
            {
                lCFireX[j] = lCFireX[j + 1];
                lCFireY[j] = lCFireY[j + 1];
            }
            lCFireCount--;
        }

        if (lCFireY[i] == mazeY)
        {
            eraseBulletOfCanon(lCFireX[i], lCFireY[i]);
            for (int j = i; j < lCFireCount - 1; j++)
            {
                lCFireX[j] = lCFireX[j + 1];
                lCFireY[j] = lCFireY[j + 1];
            }
            lCFireCount--;
            // eraseLeftCanon();
            // isLeftCanonPresent = false;
        }
        else
        {
            eraseBulletOfCanon(lCFireX[i], lCFireY[i]);
            lCFireY[i] = lCFireY[i] + 1;
            printFireOfLeftCanon(lCFireX[i], lCFireY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void moveBulletFromRightCanon()
{
    int i = 0;
    while (i < rCFireCount)
    {
        char next = getCharAtxy(rCFireX[i], rCFireY[i] + 1);
        char next2 = getCharAtxy(rCFireX[i] + 1, rCFireY[i] + 1);
        if (next == '>' || next == '/' || next2 == '>' || next2 == '/')
        {
            if (isShieldActive == false)
            {
                hit++;
            }
            eraseBulletOfCanon(rCFireX[i], rCFireY[i]);
            for (int j = i; j < rCFireCount - 1; j++)
            {
                rCFireX[j] = rCFireX[j + 1];
                rCFireY[j] = rCFireY[j + 1];
            }
            rCFireCount--;
        }
        else if (rCFireY[i] == mazeY)
        {
            eraseBulletOfCanon(rCFireX[i], rCFireY[i]);
            for (int j = i; j < rCFireCount - 1; j++)
            {
                rCFireX[j] = rCFireX[j + 1];
                rCFireY[j] = rCFireY[j + 1];
            }
            rCFireCount--;
        }

        else
        {

            eraseBulletOfCanon(rCFireX[i], rCFireY[i]);
            rCFireY[i] = rCFireY[i] + 1;
            printFireOfLeftCanon(rCFireX[i], rCFireY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void printFireOfLeftCanon(int x, int y)
{
    gotoxy(x, y);
    cout << "O";
}
void eraseBulletOfCanon(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void generateBulletFromRightCanon()
{
    rCFireX[rCFireCount] = cRX + 1;
    rCFireY[rCFireCount] = cRY + 3;
    gotoxy(rCFireX[rCFireCount], rCFireY[rCFireCount]);
    cout << "O";
    rCFireCount++;
}
void generateBulletFromLeftCanon()
{
    lCFireX[lCFireCount] = cLX + 1;
    lCFireY[lCFireCount] = cLY + 3;
    gotoxy(lCFireX[lCFireCount], lCFireY[lCFireCount]);
    cout << "O";
    lCFireCount++;
}
void eraseLeftCanon()
{
    gotoxy(cLX, cLY);
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
    }
    gotoxy(cLX, cLY + 1);
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
    }
    gotoxy(cLX, cLY + 2);
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
    }
}
void printCanonLeft()
{
    int x = cLX;
    int y = cLY;
    for (int row = 0; row < 3; row++)
    {
        gotoxy(x, y);
        for (int col = 0; col < 3; col++)
        {
            cout << canonLeft[row][col];
        }
        y++;
    }
}
void eraseRightCanon()
{
    gotoxy(cRX, cRY);
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
    }
    gotoxy(cRX, cRY + 1);
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
    }
    gotoxy(cRX, cRY + 2);
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
    }
}
void printCanonRight()
{
    int x = cRX;
    int y = cRY;
    for (int row = 0; row < 3; row++)
    {
        gotoxy(x, y);
        for (int col = 0; col < 3; col++)
        {
            cout << canonRight[row][col];
        }
        y++;
    }
}
void moveNinjaLeft()
{
    char next = getCharAtxy(nX - 1, nY);
    if (next == ' ')
    {

        for (int i = 0; i < 46; i++)
        {
            eraseNinja(nX, nY);
            nX--;
            if (i < 20)
            {
                printNinjaRight(nX, nY);
            }
            else
            {
                printNinjaLeft(nX, nY);
            }
            Sleep(10);
        }
    }
}
void moveNinjaRight()
{
    char next = getCharAtxy(nX + 4, nY);
    if (next == ' ')
    {
        for (int i = 0; i < 46; i++)
        {
            eraseNinja(nX, nY);
            nX++;
            if (i < 20)
            {
                printNinjaLeft(nX, nY);
            }
            else
            {
                printNinjaRight(nX, nY);
            }
            Sleep(10);
        }
    }
}
void printNinjaRight(int x, int y)
{
    for (int row = 0; row < 4; row++)
    {
        gotoxy(x, y);
        for (int col = 0; col < 4; col++)
        {
            cout << ninjaRight[row][col];
        }
        y++;
    }
}
void printNinjaLeft(int x, int y)
{
    for (int row = 0; row < 4; row++)
    {
        gotoxy(x, y);
        for (int col = 0; col < 4; col++)
        {
            cout << ninjaLeft[row][col];
        }
        y++;
    }
}
void eraseNinja(int x, int y)
{
    gotoxy(x, y);
    for (int i = 0; i < 4; i++)
    {
        cout << " ";
    }
    gotoxy(x, y + 1);
    for (int i = 0; i < 4; i++)
    {
        cout << " ";
    }
    gotoxy(x, y + 2);
    for (int i = 0; i < 4; i++)
    {
        cout << " ";
    }
    gotoxy(x, y + 3);
    for (int i = 0; i < 4; i++)
    {
        cout << " ";
    }
}
void loadingScreen()
{
    system("cls");
    int x = 5;
    int y = 2;
    for (int row = 0; row < 16; row++)
    {
        gotoxy(x, y);
        for (int col = 0; col < 45; col++)
        {
            cout << loadingPageCharacter[row][col];
        }
        y++;
    }
    gotoxy(x, y);
    char a = 219;
    for (int i = 0; i < 44; i++)
    {
        cout << a;
        Sleep(100);
    }
    gotoxy(0, 0);
}
void printStage()
{
    // Grid Size = 54X39
    system("cls");
    for (int row = 0; row < 39; row++)
    {
        for (int col = 0; col < 54; col++)
        {
            cout << stage[row][col];
        }
        Sleep(100);
        cout << endl;
    }
}
void header()
{
    system("cls");
    cout << "  _   _ _            _                         _____       _                       " << endl;
    cout << " | \\ | (_)          | |                       |  __ \\     | |                     " << endl;
    cout << " |  \\| |_ _ __      | |_   _ _ __ ___  _ __   | |  | | ___| |_   ___  _____        " << endl;
    cout << " | . ` | | '_ \\ _   | | | | | '_ ` _ \\| '_ \\  | |  | |/ _ \\ | | | \\ \\/ / _ \\ " << endl;
    cout << " | |\\  | | | | | |__| | |_| | | | | | | |_) | | |__| |  __/ | |_| |>  <  __/       " << endl;
    cout << " |_| \\_|_|_| |_|\\____/ \\__,_|_| |_| |_| .__/  |_____/ \\___|_|\\__,_/_/\\_\\___| " << endl;
    cout << "                                      | |                                           " << endl;
    cout << "                                      |_|                                           " << endl;
}
void instructions()
{
    cout << "Instructions!!" << endl;
    cout << "1. Press Up Arrow Key to Move Ninja Up" << endl;
    cout << "2. Press Down Arrow Key to Move Ninja Down" << endl;
    cout << "3. Press Right Arrow Key to make Ninja jump from left wall to right wall" << endl;
    cout << "4. Press Left Arrow Key to make Ninja jump from right wall to left wall" << endl;
    cout << "5. After every 5 hits ninja will lose 1 life" << endl;
    cout << "6. Collecting 1 coin will increase score by 5 points" << endl;
    cout << "7. If the player catches a shield he becomes invincible for a short period of time and cahnges color to red" << endl;
    cout << "Press any key to continue...";
}
void story()
{
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}