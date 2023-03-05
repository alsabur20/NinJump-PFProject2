#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void mainScreen();
void stage();
void printNinjaRight(int x, int y);
void printNinjaLeft(int x, int y);
void eraseNinja(int x, int y);
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
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
void collisionDetection();

// Maze
int mazeY = 37;

// Snake Left Wall
char sL1[2] = {'(', ' '};
char sL2[2] = {' ', ')'};
char sL3[2] = {'(', ' '};
char sL4[2] = {' ', '0'};

// Snake Right Wall
char sR1[3] = {' ', ')'};
char sR2[3] = {'(', ' '};
char sR3[3] = {' ', ')'};
char sR4[3] = {'0', ' '};

// Character Oriented Right
char r1[4] = {' ', ' ', ' ', '>'};
char r2[4] = {'O', ' ', '/', ' '};
char r3[4] = {' ', '\\', ' ', ' '};
char r4[4] = {' ', ' ', ' ', '>'};

// Character Oriented Left
char l1[4] = {'<', ' ', ' ', ' '};
char l2[4] = {' ', '\\', ' ', 'O'};
char l3[4] = {' ', ' ', '/', ' '};
char l4[4] = {'<', ' ', ' ', ' '};

// Canon Left Wall
char x = 177;
char cL1[3] = {'O', x, x};
char cL2[3] = {'O', x, x};
char cL3[3] = {' ', x, x};

// Canon Right Wall
char cR1[3] = {x, x, 'O'};
char cR2[3] = {x, x, 'O'};
char cR3[3] = {x, x, ' '};

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

// Coordinates
int cLX = 2;  // X-Coordinate of Left Canon
int cLY = 3;  // Y-Cordinate of Left Canon
int cRX = 49; // X-Coordinate of Right Canon
int cRY = 5;  // Y-Cordinate of Right Canon
int sLX = 2;  // X-Coordinate of Left Snake
int sLY = 5;  // Y-Cordinate of Left Snake
int sRX = 50; // X-Coordinate of Right Snake
int sRY = 3;  // Y-Cordinate of Right Snake
int nX = 2;   // X-Coordinate of Ninja
int nY = 25;  // Y-Cordinate of Ninja

int hit = 0;

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
bool isNinjaMoving = false;

main()
{
    system("cls");
    mainScreen();
    stage();

    // generateLeftSnake();
    // generateRightSnake();
    // printRightSnake();
    // printCanonLeft();
    // printCanonRight();
    while (lifeCount > 0)
    {
        if (nX < 27)
        {
            printNinjaLeft(nX, nY);
        }
        else
        {
            printNinjaRight(nX, nY);
        }
        if (hit == 5)
        {
            hit = 0;
            lifeCount--;
        }
        if (mainTick > 509 && mainTick < 1000)
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
        // if (GetAsyncKeyState(VK_SPACE))
        // {
        //     generateBulletFromRightCanon();
        // }
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
                printNinjaLeft(nX, nY);
            }
            else
            {
                printNinjaRight(nX, nY);
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
            if (nX > 27)
            {
                printNinjaRight(nX, nY);
            }
            else
            {
                printNinjaLeft(nX, nY);
            }
        }
        moveBulletFromLeftCanon();
        moveBulletFromRightCanon();
        moveLeftSnake();
        moveRightSnake();
        // collisionDetection();
        //  gotoxy(60, 5);
        //  cout << "Hits: " << hit;
        gotoxy(60, 6);
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
void collisionDetection()
{
    int startX = nX;
    int endX = nX + 3;
    int startY = nY;
    int endY = nY + 3;
    for (int col = startY; col <= endY; col++)
    {
        for (int row = startX; row <= endX; row++)
        {
            // for left canon bullets
            for (int i = 0; i < lCFireCount; i++)
            {
                if (row == lCFireX[i] && col == lCFireY[i])
                {
                    hit++;
                    eraseBulletOfCanon(lCFireX[i], lCFireY[i]);
                    for (int k = 0; k < lCFireCount - 1; k++)
                    {
                        lCFireX[k] = lCFireX[k + 1];
                        lCFireY[k] = lCFireY[k + 1];
                    }
                    lCFireCount--;
                    return;
                }
            }
            // for right canon bullets
            for (int i = 0; i < rCFireCount; i++)
            {
                if (row == rCFireX[i] && col == rCFireY[i])
                {
                    hit++;
                    eraseBulletOfCanon(rCFireX[i], rCFireY[i]);
                    for (int k = 0; k < rCFireCount - 1; k++)
                    {
                        rCFireX[k] = rCFireX[k + 1];
                        rCFireY[k] = rCFireY[k + 1];
                    }
                    rCFireCount--;
                    return;
                }
            }
            // for left snake
            for (int i = 0; i < lSCount; i++)
            {
                if (row == lSX[i] && col == lSY[i])
                {
                    hit++;
                    eraseSnake(lSX[i], lSY[i]);
                    for (int k = 0; k < lSCount - 1; k++)
                    {
                        lSX[k] = lSX[k + 1];
                        lSY[k] = lSY[k + 1];
                    }
                    lSCount--;
                    return;
                }
            }
            // for right snake
            for (int i = 0; i < rSCount; i++)
            {
                if (row == rSX[i] && col == rSY[i])
                {
                    hit++;
                    eraseSnake(rSX[i], rSY[i]);
                    for (int k = 0; k < rSCount - 1; k++)
                    {
                        rSX[k] = rSX[k + 1];
                        rSY[k] = rSY[k + 1];
                    }
                    rSCount--;
                    return;
                }
            }
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
            hit++;
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
            hit++;
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
    gotoxy(sLX, sLY - 3);
    for (int i = 0; i < 2; i++)
    {
        cout << sL1[i];
    }
    gotoxy(sLX, sLY - 2);
    for (int i = 0; i < 2; i++)
    {
        cout << sL2[i];
    }
    gotoxy(sLX, sLY - 1);
    for (int i = 0; i < 2; i++)
    {
        cout << sL3[i];
    }
    gotoxy(sLX, sLY);
    for (int i = 0; i < 2; i++)
    {
        cout << sL4[i];
    }
    lSCount++;
}
void generateRightSnake()
{
    rSX[rSCount] = sRX;
    rSY[rSCount] = sRY;
    gotoxy(sRX, sRY - 3);
    for (int i = 0; i < 2; i++)
    {
        cout << sR1[i];
    }
    gotoxy(sRX, sRY - 2);
    for (int i = 0; i < 2; i++)
    {
        cout << sR2[i];
    }
    gotoxy(sRX, sRY - 1);
    for (int i = 0; i < 2; i++)
    {
        cout << sR3[i];
    }
    gotoxy(sRX, sRY);
    for (int i = 0; i < 2; i++)
    {
        cout << sR4[i];
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
    gotoxy(x, y - 3);
    for (int i = 0; i < 2; i++)
    {
        cout << sR1[i];
    }
    gotoxy(x, y - 2);
    for (int i = 0; i < 2; i++)
    {
        cout << sR2[i];
    }
    gotoxy(x, y - 1);
    for (int i = 0; i < 2; i++)
    {
        cout << sR3[i];
    }
    gotoxy(x, y);
    for (int i = 0; i < 2; i++)
    {
        cout << sR4[i];
    }
}
void printLeftSnake(int x, int y)
{
    // 3X4
    gotoxy(x, y - 3);
    for (int i = 0; i < 2; i++)
    {
        cout << sL1[i];
    }
    gotoxy(x, y - 2);
    for (int i = 0; i < 2; i++)
    {
        cout << sL2[i];
    }
    gotoxy(x, y - 1);
    for (int i = 0; i < 2; i++)
    {
        cout << sL3[i];
    }
    gotoxy(x, y);
    for (int i = 0; i < 2; i++)
    {
        cout << sL4[i];
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
            hit++;
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
            hit++;
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
    gotoxy(cLX, cLY);
    for (int i = 0; i < 3; i++)
    {
        cout << cL1[i];
    }
    gotoxy(cLX, cLY + 1);
    for (int i = 0; i < 3; i++)
    {
        cout << cL2[i];
    }
    gotoxy(cLX, cLY + 2);
    for (int i = 0; i < 3; i++)
    {
        cout << cL3[i];
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
    gotoxy(cRX, cRY);
    for (int i = 0; i < 3; i++)
    {
        cout << cR1[i];
    }
    gotoxy(cRX, cRY + 1);
    for (int i = 0; i < 3; i++)
    {
        cout << cR2[i];
    }
    gotoxy(cRX, cRY + 2);
    for (int i = 0; i < 3; i++)
    {
        cout << cR3[i];
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
    gotoxy(x, y);
    for (int i = 0; i < 4; i++)
    {
        cout << r1[i];
    }
    gotoxy(x, y + 1);
    for (int i = 0; i < 4; i++)
    {
        cout << r2[i];
    }
    gotoxy(x, y + 2);
    for (int i = 0; i < 4; i++)
    {
        cout << r3[i];
    }
    gotoxy(x, y + 3);
    for (int i = 0; i < 4; i++)
    {
        cout << r4[i];
    }
}
void printNinjaLeft(int x, int y)
{
    gotoxy(x, y);
    for (int i = 0; i < 4; i++)
    {
        cout << l1[i];
    }
    gotoxy(x, y + 1);
    for (int i = 0; i < 4; i++)
    {
        cout << l2[i];
    }
    gotoxy(x, y + 2);
    for (int i = 0; i < 4; i++)
    {
        cout << l3[i];
    }
    gotoxy(x, y + 3);
    for (int i = 0; i < 4; i++)
    {
        cout << l4[i];
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
void mainScreen()
{

    cout << "                                                                                    " << endl;
    cout << "                                                                                    " << endl;
    cout << "                                                                                    " << endl;
    cout << "                                                 -:                                 " << endl;
    cout << "                                                  #%+                               " << endl;
    cout << "                                                   @%%-                             " << endl;
    cout << "                                                   @@%%=                            " << endl;
    cout << "                                 .           :--:. %@@@@+                           " << endl;
    cout << "                               :=--=.        .-*%%@@@@@@@@@@%#*+-                   " << endl;
    cout << "                               --:=%@+:::.      .#@@@@@%%%%%%%%%%%+                 " << endl;
    cout << "                                ..-%@@@%%%%+:    :@@@@%%%%%%%%%%%%#%:               " << endl;
    cout << "                                   =@@%%%%%%%#=  %@@@@@%%%%%%%%%%%%#%.              " << endl;
    cout << "                          .:.     .=@@@@@@@%%%%%#@@@@@@@@%%%%%%%%%%%#+              " << endl;
    cout << "                         =-:-####%@@%%%%%@@@@@@@@@@@@@*+*##%%%%%%%%%#*              " << endl;
    cout << "                         =::-#%@@%%%%%%%%%%%%%%%@@@@@@*-:::::-======+=              " << endl;
    cout << "                          .:.  :@%%%%%%%%%%%%%%%%@@@@@%=:::.+*-=:::=*               " << endl;
    cout << "                                .=%@@@@@@@@%%%%%%%%@@@@@#-:.-+--::+=                " << endl;
    cout << "              -*#%.             +%#####%%%%@@@%%%%#@@@@@@@#*+===+=.                 " << endl;
    cout << "           -#%@@%@%:          -%@@%#%@@@%%%%%%%%%##%%+:-=++++=-.                    " << endl;
    cout << "         =%@%=: +%@@* .=****%@@@@@@@%##%%%@@@@%%@#@%-                               " << endl;
    cout << "        .=--     =%%@@@@%%%%@@@@%%%%%%%#######@%%+-                                 " << endl;
    cout << "                  :#@@@@%%%%%@@@@%%%%%%%%%%%%%=.                                    " << endl;
    cout << "                    #@@%%%%%%%%%@@@%%%%%%%%%%%%%*=.                                 " << endl;
    cout << "                    .%@@%%%%%%%*-:*@@%%%%%%%%%%%%%%#:                               " << endl;
    cout << "                      :=+*+=-.     .*@@@@@@@%%@@%%%%%                               " << endl;
    cout << "                                     .*@@@@@@@@%%%%@*                               " << endl;
    cout << "                                       .*@@@@@@@@@@@*         .                     " << endl;
    cout << "                                          :=**####@@@%=    =%%=                     " << endl;
    cout << "                                                  .=#@%#=+%@#.                      " << endl;
    cout << "                                                     :%@@@%-                        " << endl;
    cout << "             ...:::::::--------------------------------##=::::::...                 " << endl;
    cout << "               .......:::::::::::::::::::::::::::::::::::.......                    " << endl;
    cout << "                                                                                    " << endl;
    cout << "                                                                                    " << endl;
    cout << "  _   _ _            _                         _____       _                " << endl;
    cout << " | \\ | (_)          | |                       |  __ \\     | |               " << endl;
    cout << " |  \\| |_ _ __      | |_   _ _ __ ___  _ __   | |  | | ___| |_   ___  _____ " << endl;
    cout << " | . ` | | '_ \\ _   | | | | | '_ ` _ \\| '_ \\  | |  | |/ _ \\ | | | \\ \\/ / _ \\" << endl;
    cout << " | |\\  | | | | | |__| | |_| | | | | | | |_) | | |__| |  __/ | |_| |>  <  __/" << endl;
    cout << " |_| \\_|_|_| |_|\\____/ \\__,_|_| |_| |_| .__/  |_____/ \\___|_|\\__,_/_/\\_\\___|" << endl;
    cout << "                                      | |                                   " << endl;
    cout << "                                      |_|                                   " << endl;
    getch();
}
void stage()
{
    // Grid Size = 54X39
    system("cls");
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|                                                  |_" << endl;
    cout << "_|__________________________________________________|_" << endl;
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