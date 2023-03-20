#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Shield Function Prototypes
void generateRandomShield(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int lShieldX, int lShieldY, int rightShieldX[], int rightShieldY[], int &rightShieldCount, int rShieldX, int rShieldY, int &mainTick);
void generateRandomCoins(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int lCoinX, int lCoinY, int rightCoinX[], int rightCoinY[], int &rightCoinCount, int rCoinX, int rCoinY, int &mainTick);
void generateLeftShield(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int lShieldX, int lShieldY);
void generateRightShield(int rightShieldX[], int rightShieldY[], int &rightShieldCount, int rShieldX, int rShieldY);
void deleteLeftShieldFromArray(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int index);
void deleteRightShieldFromArray(int rightShieldX[], int rightShieldY[], int &rightShieldCount, int index);
void moveRightShield(int rightShieldX[], int rightShieldY[], int &rightShieldCount, int mazeYMax, int &score, bool &isShieldActive);
void moveLeftShield(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int mazeYMax, int &score, bool &isShieldActive);


//Coin Function Prototypes
void generateLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int lCoinX, int lCoinY);
void generateRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int rCoinX, int rCoinY);
void deleteLeftCoinFromArray(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int index);
void deleteRightCoinFromArray(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int index);
void moveLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int mazeYMax, int &score);
void moveRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int mazeYMax, int &score);

//Snake Function Prototypes
void printRightSnake(char snakeRight[4][3], int x, int y);
void printLeftSnake(char snakeLeft[4][3], int x, int y);
void eraseSnake(int x, int y);
void generateLeftSnake(char snakeLeft[4][3], int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, int lSnakeX, int lSnakeY);
void generateRightSnake(char snakeRight[4][3], int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, int rSnakeX, int rSnakeY);
void moveRightSnake(char snakeRight[4][3], int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, bool &isShieldActive, int &hit, int mazeYMax);
void moveLeftSnake(char snakeLeft[4][3], int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, bool &isShieldActive, int &hit, int mazeYMax);
void deleteLeftSnakeFromArray(int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, int index);
void deleteRightSnakeFromArray(int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, int index);

//Canon Function Prototypes
void printCanonLeft(char canonLeft[3][3], int leftCanonX, int leftCanonY);
void printCanonRight(char canonRight[3][3], int rightCanonX, int rightCanonY);
void eraseLeftCanon(int leftCanonX, int leftCanonY);
void eraseRightCanon(int rightCanonX, int rightCanonY);
void printFireOfCanon(int x, int y);
void eraseBulletOfCanon(int x, int y);
void generateBulletFromRightCanon(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int rightCanonX, int rightCanonY);
void generateBulletFromLeftCanon(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int leftCanonX, int leftCanonY);
void moveBulletFromLeftCanon(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int mazeYMax, bool &isShieldActive, int &hit);
void moveBulletFromRightCanon(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int mazeYMax, bool &isShieldActive, int &hit);
void eraseLeftBulletFromArray(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int index);
void eraseRightBulletFromArray(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int index);

//Smart Canon Function Prototypes
void generateBulletFromSmartCanon(int smartCanonBulletX[], int smartCanonBulletY[], int ratioX[], int ratioY[], int &smartCanonBulletcount, char smartBulletDirection[], int &ninjaX, int &ninjaY);
void moveBulletFromSmartCanon(int smartCanonBulletX[], int smartCanonBulletY[], int ratioX[], int ratioY[], int &smartCanonBulletcount, char smartBulletDirection[], int ninjaX, int ninjaY, int &hit);
void deleteSmartBulletDataFromArray(int smartCanonBulletX[], int smartCanonBulletY[], int ratioX[], int ratioY[], int &smartCanonBulletcount, char smartBulletDirection[], int index);
void smartBulletCollisionDetection(int ninjaX, int ninjaY, int smartCanonBulletX[], int smartCanonBulletY[], int &smartCanonBulletcount, char smartBulletDirection[], int ratioX[], int ratioY[], int &hit);
int calculateGCD(int nOne, int nTwo);

//Ninja Function Prototypes
void printNinjaRight(char ninjaRight[4][5], int x, int y, bool isShieldActive);
void printNinjaLeft(char ninjaLeft[4][5], int x, int y, bool isShieldActive);
void eraseNinja(int x, int y);
void moveNinjaDown(char ninjaLeft[4][5], char ninjaRight[4][5], int &ninjaX, int &ninjaY, char &moveStatus, bool isShieldActive);
void moveNinjaUp(char ninjaLeft[4][5], char ninjaRight[4][5], int &ninjaX, int &ninjaY, char &moveStatus, bool isShieldActive);

//Loading and Cover Page Function Prototypes
void loadingScreen(char loadingPageCharacter[16][45]);
void header();
void printStage(char stage[39][55]);
void instructions();
void story();
void loadLoadingPageCharacter(char loadingPageCharacter[16][45]);
void loadStage(char stage[39][55]);

//Other Prototypes
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
string setcolor(unsigned short color);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
main() {
    char loadingPageCharacter[16][45];
    char stage[39][55];
    // Maze
    int mazeYMax = 37;

    // Snake Left Wall
    char snakeLeft[4][3] = { {"( "},
                             {" )"},
                             {"( "},
                             {" 0"} };

    // Snake Right Wall
    char snakeRight[4][3] = { {" )"},
                              {"( "},
                              {" )"},
                              {"0 "} };

    // Character Oriented Right
    char ninjaRight[4][5] = { {"   >"},
                              {"O / "},
                              {" \\  "},
                              {"   >"} };
    // Character Oriented Left
    char ninjaLeft[4][5] = { {"<   "},
                             {" \\ O"},
                             {"  / "},
                             {"<   "} };

    // Canon Left Wall
    char x = 177;
    char canonLeft[3][3] = { {'O', x, x},
                             {'O', x, x},
                             {' ', x, x} };

    // Canon Right Wall
    char canonRight[3][3] = { {x, x, 'O'},
                              {x, x, 'O'},
                              {x, x, ' '} };

    // Snake Movement Coordinates
    int leftSnakeX[100];
    int leftSnakeY[100];
    int leftSnakeCount = 0;
    int rightSnakeX[100];
    int rightSnakeY[100];
    int rightSnakeCount = 0;

    // Canon Fire Coordinates
    int leftCanonBulletX[100];
    int leftCanonBulletY[100];

    int leftCanonBulletCount = 0;
    int rightCanonBulletX[100];
    int rightCanonBulletY[100];
    int rightCanonBulletCount = 0;

    // Left Coin Coordinates
    int leftCoinX[100];
    int leftCoinY[100];
    int leftCoinCount = 0;

    // Right Coin Coordinates
    int rightCoinX[100];
    int rightCoinY[100];
    int rightCoinCount = 0;

    // Left Shield Coordinates
    int leftShieldX[100];
    int leftShieldY[100];
    int leftShieldCount = 0;

    // Right Shield Coordinates
    int rightShieldX[100];
    int rightShieldY[100];
    int rightShieldCount = 0;


    // Smart Canon Coordinates
    int smartCanonBulletX[100];
    int smartCanonBulletY[100];
    int ratioX[100];
    int ratioY[100];
    int smartCanonBulletcount = 0;
    char smartBulletDirection[100];

    // Coordinates
    int leftCanonX = 2;  // X-Coordinate of Left Canon
    int leftCanonY = 3;  // Y-Cordinate of Left Canon
    int rightCanonX = 49; // X-Coordinate of Right Canon
    int rightCanonY = 3;  // Y-Cordinate of Right Canon
    int lSnakeX = 2;  // X-Coordinate of Left Snake
    int lSnakeY = 3;  // Y-Cordinate of Left Snake
    int rSnakeX = 50; // X-Coordinate of Right Snake
    int rSnakeY = 3;  // Y-Cordinate of Right Snake
    int ninjaX = 2;   // X-Coordinate of Ninja
    int ninjaY = 25;  // Y-Cordinate of Ninja
    int lCoinX = 3;
    int lCoinY = 6;
    int rCoinX = 49;
    int rCoinY = 6;
    int lShieldX = 3;
    int lShieldY = 6;
    int rShieldX = 49;
    int rShieldY = 6;

    int hit = 0;
    int score = 0;

    char moveStatus = 'S'; // Flag for checking Movement State  S=Static,R=Right,L=Left
    int lifeCount = 5;
    int mainTick = 0;
    bool isLeftCanonPresent = false;
    bool isRightCanonPresent = false;
    bool isLeftSnakePresent = false;
    bool isRightSnakePresent = false;
    bool isBulletMoving = false;
    bool isShieldActive = 0;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    loadLoadingPageCharacter(loadingPageCharacter);
    loadStage(stage);

    system("cls");
    // loadingScreen(loadingPageCharacter);
    string name;
    int choice;
    while (1) {
        header();
        cout << "          1. Play Game                                                              " << endl;
        cout << "          2. Read Instructions                                                      " << endl;
        cout << "          3. Story Line                                                             " << endl;
        cout << "          4. Exit                                                                   " << endl;
        cout << "          Enter Chioce:";
        cin >> choice;
        if (choice == 1) {
            system("cls");
            header();
            cout << "Enter your Name: ";
            cin.clear();
            cin.sync();
            getline(cin, name);
            printStage(stage);
            // generateLeftSnake();
            // generateRightSnake();
            // printRightSnake();
            // printCanonLeft();
            // printCanonRight();
            while (lifeCount > 0) {
                if (ninjaX < 27) {
                    printNinjaLeft(ninjaLeft, ninjaX, ninjaY, isShieldActive);
                }
                else {
                    printNinjaRight(ninjaRight, ninjaX, ninjaY, isShieldActive);
                }
                if (hit == 5) {
                    hit = 0;
                    lifeCount--;
                }
                if (mainTick > 500 && mainTick < 1000) {
                    int x = rand() % 20;
                    if (x == 7) {
                        generateBulletFromLeftCanon(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, leftCanonX, leftCanonY);
                    }
                }
                if (mainTick == 500) {
                    eraseRightCanon(rightCanonX, rightCanonY);
                    isRightCanonPresent = false;
                    if (isLeftSnakePresent == false && isLeftCanonPresent == false) {
                        printCanonLeft(canonLeft, leftCanonX, leftCanonY);
                        generateBulletFromLeftCanon(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, leftCanonX, leftCanonY);
                        isLeftCanonPresent = true;
                    }
                }
                if (mainTick > 1000 && mainTick < 2000) {
                    int x = rand() % 20;
                    if (x == 7) {
                        if (isRightCanonPresent == false) {
                            generateRightSnake(snakeRight, rightSnakeX, rightSnakeY, rightSnakeCount, rSnakeX, rSnakeY);
                        }
                    }
                }
                if (mainTick == 1000) {
                    eraseLeftCanon(leftCanonX, leftCanonY);
                    isLeftCanonPresent = false;
                    if (isRightSnakePresent == false && isRightCanonPresent == false) {
                        generateRightSnake(snakeRight, rightSnakeX, rightSnakeY, rightSnakeCount, rSnakeX, rSnakeY);
                        isRightSnakePresent = true;
                    }
                }
                if (mainTick > 2000 && mainTick < 3000) {
                    int x = rand() % 20;
                    if (x == 7) {
                        if (isLeftCanonPresent == false) {
                            generateLeftSnake(snakeLeft, leftSnakeX, leftSnakeY, leftSnakeCount, lSnakeX, lSnakeY);
                        }
                    }
                }
                if (mainTick == 2000) {
                    isRightSnakePresent = false;
                    if (isLeftCanonPresent == false && isLeftSnakePresent == false) {
                        generateLeftSnake(snakeLeft, leftSnakeX, leftSnakeY, leftSnakeCount, lSnakeX, lSnakeY);
                        isLeftSnakePresent = true;
                    }
                }
                if (mainTick > 3000 && mainTick < 4000) {
                    int x = rand() % 15;
                    if (x == 7) {
                        generateBulletFromRightCanon(rightCanonBulletX, rightCanonBulletY, rightCanonBulletCount, rightCanonX, rightCanonY);
                    }
                }
                if (mainTick == 3000) {
                    isLeftSnakePresent = false;
                    if (isRightSnakePresent == false && isRightCanonPresent == false) {
                        printCanonRight(canonRight, rightCanonX, rightCanonY);
                        generateBulletFromRightCanon(rightCanonBulletX, rightCanonBulletY, rightCanonBulletCount, rightCanonX, rightCanonY);
                        isRightCanonPresent = true;
                    }
                }
                if (mainTick == 4000) {
                    eraseLeftCanon(leftCanonX, leftCanonY);
                    eraseRightCanon(rightCanonX, rightCanonY);
                    isRightCanonPresent = false;
                    isLeftCanonPresent = false;
                    isRightSnakePresent = false;
                    isLeftSnakePresent = false;
                    mainTick = 0;
                }
                if (GetAsyncKeyState(VK_SPACE)) {
                    // generateRightCoin(rightCoinX, rightCoinY, rightCoinCount, rCoinX, rCoinY);
                    // generateLeftCoin(leftCoinX, leftCoinY, leftCoinCount, lCoinX, lCoinY);
                    // generateLeftSnake(snakeLeft, leftSnakeX, leftSnakeY, leftSnakeCount, lSnakeX, lSnakeY);
                    // generateBulletFromLeftCanon(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, leftCanonX, leftCanonY);
                    // generateLeftShield(leftShieldX, leftShieldY, leftShieldCount, lShieldX, lShieldY);
                    // score = 1000;
                    generateBulletFromSmartCanon(smartCanonBulletX, smartCanonBulletY, ratioX, ratioY, smartCanonBulletcount, smartBulletDirection, ninjaX, ninjaY);
                }
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    if (moveStatus == 'S') {
                        moveStatus = 'R';
                    }
                }
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                    if (moveStatus == 'S') {
                        moveStatus = 'L';
                    }
                }
                if (moveStatus == 'S') {
                    if (GetAsyncKeyState(VK_UP) & 0x8000) {
                        if (ninjaY > 8) {
                            moveNinjaUp(ninjaLeft, ninjaRight, ninjaX, ninjaY, moveStatus, isShieldActive);
                        }
                    }
                    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                        if (ninjaY < 32) {
                            moveNinjaDown(ninjaLeft, ninjaRight, ninjaX, ninjaY, moveStatus, isShieldActive);
                        }
                    }
                }
                if (moveStatus == 'R') {
                    char next = getCharAtxy(ninjaX + 4, ninjaY);
                    if (next == ' ') {
                        eraseNinja(ninjaX, ninjaY);
                        ninjaX++;
                    }
                    else {
                        moveStatus = 'S';
                    }
                    if (ninjaX < 27) {
                        printNinjaLeft(ninjaLeft, ninjaX, ninjaY, isShieldActive);
                    }
                    else {
                        printNinjaRight(ninjaRight, ninjaX, ninjaY, isShieldActive);
                    }
                }

                else if (moveStatus == 'L') {
                    char next = getCharAtxy(ninjaX - 1, ninjaY);
                    if (next == ' ' || next == 'O') {
                        // if(next == 'O')
                        // {
                        //     hit++;
                        // }
                        eraseNinja(ninjaX, ninjaY);
                        ninjaX--;
                    }
                    else {
                        moveStatus = 'S';
                    }
                    if (ninjaX < 27) {
                        printNinjaLeft(ninjaLeft, ninjaX, ninjaY, isShieldActive);
                    }
                    else {
                        printNinjaRight(ninjaRight, ninjaX, ninjaY, isShieldActive);
                    }
                }
                if ((mainTick == 600 || mainTick == 2000 || mainTick == 3500 || mainTick == 4000) && isShieldActive == 1) {
                    isShieldActive = 0;
                }
                char d = 254;
                if (score >= 1000) {
                    gotoxy(2, 8);
                    cout << d;
                    gotoxy(3, 8);
                    cout << d;
                    gotoxy(4, 8);
                    cout << d;
                    gotoxy(5, 8);
                    cout << d;
                    gotoxy(6, 8);
                    cout << d;
                }
                moveLeftShield(leftShieldX, leftShieldY, leftShieldCount, mazeYMax, score, isShieldActive);
                moveRightShield(rightShieldX, rightShieldY, rightShieldCount, mazeYMax, score, isShieldActive);
                generateRandomCoins(leftCoinX, leftCoinY, leftCoinCount, lCoinX, lCoinY, rightCoinX, rightCoinY, rightCoinCount, rCoinX, rCoinY, mainTick);
                generateRandomShield(leftShieldX, leftShieldY, leftShieldCount, lShieldX, lShieldY, rightShieldX, rightShieldY, rightShieldCount, rShieldX, rShieldY, mainTick);
                moveBulletFromLeftCanon(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, mazeYMax, isShieldActive, hit);
                moveBulletFromRightCanon(rightCanonBulletX, rightCanonBulletY, rightCanonBulletCount, mazeYMax, isShieldActive, hit);
                moveBulletFromSmartCanon(smartCanonBulletX, smartCanonBulletY, ratioX, ratioY, smartCanonBulletcount, smartBulletDirection, ninjaX, ninjaY, hit);
                moveLeftSnake(snakeLeft, leftSnakeX, leftSnakeY, leftSnakeCount, isShieldActive, hit, mazeYMax);
                moveRightSnake(snakeRight, rightSnakeX, rightSnakeY, rightSnakeCount, isShieldActive, hit, mazeYMax);
                moveLeftCoin(leftCoinX, leftCoinY, leftCoinCount, mazeYMax, score);
                moveRightCoin(rightCoinX, rightCoinY, rightCoinCount, mazeYMax, score);
                smartBulletCollisionDetection(ninjaX, ninjaY, smartCanonBulletX, smartCanonBulletY, smartCanonBulletcount, smartBulletDirection, ratioX, ratioY, hit);
                // if (mainTick == 4000) {
                //     mainTick = 0;
                // }
                gotoxy(60, 4);
                cout << "Name: " << name;
                gotoxy(60, 5);
                cout << "Hits: " << hit;
                gotoxy(60, 6);
                cout << "Score: " << score;
                gotoxy(60, 7);
                cout << "Life Count: " << lifeCount;
                if (isShieldActive == 1) {
                    gotoxy(60, 8);
                    cout << "Shield Status: Active";
                }
                else if (isShieldActive == 0) {
                    gotoxy(60, 8);
                    cout << "Shield Status: False";
                }
                gotoxy(60, 9);
                cout << "Main Tick: " << mainTick;
                mainTick++;
                Sleep(10);
            }
            if (lifeCount == 0) {
                system("cls");
                cout << "GameOver!!!!!";
                getch();
                lifeCount = 5;
                mainTick = 0;
                score = 0;
                hit = 0;
                isShieldActive = 0;
            }
        }

        else if (choice == 2) {
            header();
            instructions();
            getch();
        }
        else if (choice == 3) {
            header();
            story();
            getch();
        }
        else if (choice == 4) {
            break;
        }
        else if (choice > 4) {
            cout << "Invalid Choice!!" << endl;
            cout << "Enter Correct Choice!!" << endl;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void smartBulletCollisionDetection(int ninjaX, int ninjaY, int smartCanonBulletX[], int smartCanonBulletY[], int &smartCanonBulletcount, char smartBulletDirection[], int ratioX[], int ratioY[], int &hit) {
    int startX = ninjaX;
    int endX = ninjaX + 3;
    int startY = ninjaY;
    int endY = ninjaY + 3;
    for (int col = startY; col <= endY; col++) {
        for (int row = startX; row <= endX; row++) {
            // For Smart Canon Bullets
            for (int i = 0; i < smartCanonBulletcount; i++) {
                if (row == smartCanonBulletX[i] && col == smartCanonBulletY[i]) {
                    hit++;
                    eraseBulletOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                    for (int j = i; j < smartCanonBulletcount - 1; j++) {
                        smartCanonBulletX[j] = smartCanonBulletX[j + 1];
                        smartCanonBulletY[j] = smartCanonBulletY[j + 1];
                        ratioX[j] = ratioX[j + 1];
                        ratioY[j] = ratioY[j + 1];
                        smartBulletDirection[j] = smartBulletDirection[j + 1];
                    }
                    smartCanonBulletcount--;
                }
            }
        }
    }
}
void moveBulletFromSmartCanon(int smartCanonBulletX[], int smartCanonBulletY[], int ratioX[], int ratioY[], int &smartCanonBulletcount, char smartBulletDirection[], int ninjaX, int ninjaY, int &hit) {
    int i = 0;
    while (i < smartCanonBulletcount) {
        if (smartBulletDirection[i] == 'r') {
            char next = getCharAtxy(smartCanonBulletX[i] - 1, smartCanonBulletY[i] - 1);
            if (next != ' ' || next == '|') {
                eraseBulletOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                deleteSmartBulletDataFromArray(smartCanonBulletX, smartCanonBulletY, ratioX, ratioY, smartCanonBulletcount, smartBulletDirection, i);
            }
            else if (smartCanonBulletY[i] <= ninjaY) {
                eraseBulletOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                deleteSmartBulletDataFromArray(smartCanonBulletX, smartCanonBulletY, ratioX, ratioY, smartCanonBulletcount, smartBulletDirection, i);
            }
            else {
                eraseBulletOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                smartCanonBulletX[i] = smartCanonBulletX[i] + ratioX[i];
                smartCanonBulletY[i] = smartCanonBulletY[i] - ratioY[i];
                printFireOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                i++;
            }
        }
        else if (smartBulletDirection[i] == 'l') {
            char next = getCharAtxy(smartCanonBulletX[i] - 1, smartCanonBulletY[i] - 1);
            if (next != ' ' || next == '|') {
                eraseBulletOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                deleteSmartBulletDataFromArray(smartCanonBulletX, smartCanonBulletY, ratioX, ratioY, smartCanonBulletcount, smartBulletDirection, i);
            }
            else if (smartCanonBulletY[i] <= ninjaY) {
                eraseBulletOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                deleteSmartBulletDataFromArray(smartCanonBulletX, smartCanonBulletY, ratioX, ratioY, smartCanonBulletcount, smartBulletDirection, i);
            }
            else {
                eraseBulletOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                smartCanonBulletX[i] = smartCanonBulletX[i] - ratioX[i];
                smartCanonBulletY[i] = smartCanonBulletY[i] - ratioY[i];
                printFireOfCanon(smartCanonBulletX[i], smartCanonBulletY[i]);
                i++;
            }
        }
    }
}
int calculateGCD(int nOne, int nTwo) {
    int maxOne = max(nOne, nTwo);
    int divisor = 0;
    for (int i = 1; i < maxOne; i++) {
        if (nOne % i == 0 && nTwo % i == 0) {
            divisor = i;
        }
    }

    return divisor;
}
void generateBulletFromSmartCanon(int smartCanonBulletX[], int smartCanonBulletY[], int ratioX[], int ratioY[], int &smartCanonBulletcount, char smartBulletDirection[], int &ninjaX, int &ninjaY) {
    smartCanonBulletX[smartCanonBulletcount] = 27;
    smartCanonBulletY[smartCanonBulletcount] = 36;
    int x = ninjaX - smartCanonBulletX[smartCanonBulletcount];
    int y = ninjaY - smartCanonBulletY[smartCanonBulletcount];
    if (x < 0) {
        smartBulletDirection[smartCanonBulletcount] = 'l';
    }
    else {
        smartBulletDirection[smartCanonBulletcount] = 'r';
    }
    int gcd = calculateGCD(abs(x), abs(y));
    ratioX[smartCanonBulletcount] = abs(x / gcd);
    // cout << x << endl;
    ratioY[smartCanonBulletcount] = abs(y / gcd);
    // cout << y << endl;
    gotoxy(smartCanonBulletX[smartCanonBulletcount], smartCanonBulletY[smartCanonBulletcount]);
    setcolor(12);
    cout << "O";
    setcolor(15);
    smartCanonBulletcount++;
}
void deleteSmartBulletDataFromArray(int smartCanonBulletX[], int smartCanonBulletY[], int ratioX[], int ratioY[], int &smartCanonBulletcount, char smartBulletDirection[], int index) {
    for (int j = index; j < smartCanonBulletcount - 1; j++) {
        smartCanonBulletX[j] = smartCanonBulletX[j + 1];
        smartCanonBulletY[j] = smartCanonBulletY[j + 1];
        ratioX[j] = ratioX[j + 1];
        ratioY[j] = ratioY[j + 1];
        smartBulletDirection[j] = smartBulletDirection[j + 1];
    }
    smartCanonBulletcount--;
}

void generateRandomShield(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int lShieldX, int lShieldY, int rightShieldX[], int rightShieldY[], int &rightShieldCount, int rShieldX, int rShieldY, int &mainTick) {
    if (mainTick == 500 || mainTick == 1400 || mainTick == 2600 || mainTick == 3600 || mainTick == 4000) {
        generateRightShield(rightShieldX, rightShieldY, rightShieldCount, rShieldX, rShieldY);
    }
    if (mainTick == 800 || mainTick == 1900 || mainTick == 3400 || mainTick == 2700 || mainTick == 4000) {
        generateLeftShield(leftShieldX, leftShieldY, leftShieldCount, lShieldX, lShieldY);
    }
}

void generateRandomCoins(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int lCoinX, int lCoinY, int rightCoinX[], int rightCoinY[], int &rightCoinCount, int rCoinX, int rCoinY, int &mainTick) {
    if (mainTick == 200 || mainTick == 700 || mainTick == 1200 || mainTick == 1700 || mainTick == 2300 || mainTick == 2800 || mainTick == 3200 || mainTick == 400 || mainTick == 900 || mainTick == 1400 || mainTick == 1900 || mainTick == 2500 || mainTick == 3000 || mainTick == 3400) {
        generateRightCoin(rightCoinX, rightCoinY, rightCoinCount, rCoinX, rCoinY);
    }
    if (mainTick == 300 || mainTick == 800 || mainTick == 1300 || mainTick == 1800 || mainTick == 2400 || mainTick == 2900 || mainTick == 3300 || mainTick == 500 || mainTick == 1000 || mainTick == 1500 || mainTick == 2000 || mainTick == 2600 || mainTick == 3100 || mainTick == 3500) {
        generateLeftCoin(leftCoinX, leftCoinY, leftCoinCount, lCoinX, lCoinY);
    }
}
void moveNinjaUp(char ninjaLeft[4][5], char ninjaRight[4][5], int &ninjaX, int &ninjaY, char &moveStatus, bool isShieldActive) {
    char next = getCharAtxy(ninjaX, ninjaY - 1);
    if (next == ' ' || next == 'O') {
        eraseNinja(ninjaX, ninjaY);
        ninjaY--;
    }
    else {
        moveStatus = 'S';
    }
    if (ninjaX < 27) {
        printNinjaLeft(ninjaLeft, ninjaX, ninjaY, isShieldActive);
    }
    else {
        printNinjaRight(ninjaRight, ninjaX, ninjaY, isShieldActive);
    }
}
void moveNinjaDown(char ninjaLeft[4][5], char ninjaRight[4][5], int &ninjaX, int &ninjaY, char &moveStatus, bool isShieldActive) {
    char next = getCharAtxy(ninjaX, ninjaY + 4);
    if (next == ' ' || next == 'O') {
        eraseNinja(ninjaX, ninjaY);
        ninjaY++;
    }
    else {
        moveStatus = 'S';
    }
    if (ninjaX < 27) {
        printNinjaLeft(ninjaLeft, ninjaX, ninjaY, isShieldActive);
    }
    else {
        printNinjaRight(ninjaRight, ninjaX, ninjaY, isShieldActive);
    }
}

void generateLeftShield(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int lShieldX, int lShieldY) {
    char s = 3;
    leftShieldY[leftShieldCount] = lShieldY;
    leftShieldX[leftShieldCount] = lShieldX;
    gotoxy(lShieldX, lShieldY);
    setcolor(11);
    cout << s;
    setcolor(15);
    leftShieldCount++;
}
void generateRightShield(int rightShieldX[], int rightShieldY[], int &rightShieldCount, int rShieldX, int rShieldY) {
    char s = 3;
    rightShieldX[rightShieldCount] = rShieldX;
    rightShieldY[rightShieldCount] = rShieldY;
    gotoxy(rShieldX, rShieldY);
    setcolor(11);
    cout << s;
    setcolor(15);
    rightShieldCount++;
}
void printShield(int x, int y) {
    char s = 3;
    gotoxy(x, y);
    setcolor(11);
    cout << s;
    setcolor(15);
}
void eraseShield(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}
void deleteLeftShieldFromArray(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int index) {
    for (int j = index; j < leftShieldCount - 1; j++) {
        leftShieldX[j] = leftShieldX[j + 1];
        leftShieldY[j] = leftShieldY[j + 1];
    }
    leftShieldCount--;
}
void deleteRightShieldFromArray(int rightShieldX[], int rightShieldY[], int &rightShieldCount, int index) {
    for (int j = index; j < rightShieldCount - 1; j++) {
        rightShieldX[j] = rightShieldX[j + 1];
        rightShieldY[j] = rightShieldY[j + 1];
    }
    rightShieldCount--;
}
void moveLeftShield(int leftShieldX[], int leftShieldY[], int &leftShieldCount, int mazeYMax, int &score, bool &isShieldActive) {
    int i = 0;
    while (i < leftShieldCount) {
        char next = getCharAtxy(leftShieldX[i], leftShieldY[i] + 1);
        char next1 = getCharAtxy(leftShieldX[i] + 1, leftShieldY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/') {
            isShieldActive = 1;
            score += 50;
            eraseShield(leftShieldX[i], leftShieldY[i]);
            deleteLeftShieldFromArray(leftShieldX, leftShieldY, leftShieldCount, i);
        }
        else if (leftShieldY[i] == mazeYMax) {
            eraseShield(leftShieldX[i], leftShieldY[i]);
            deleteLeftShieldFromArray(leftShieldX, leftShieldY, leftShieldCount, i);
        }
        else {

            eraseShield(leftShieldX[i], leftShieldY[i]);
            leftShieldY[i] = leftShieldY[i] + 1;
            printShield(leftShieldX[i], leftShieldY[i]);
            i++;
        }
        // Sleep(10);
    }
}
void moveRightShield(int rightShieldX[], int rightShieldY[], int &rightShieldCount, int mazeYMax, int &score, bool &isShieldActive) {
    int i = 0;
    while (i < rightShieldCount) {
        char next = getCharAtxy(rightShieldX[i], rightShieldY[i] + 1);
        char next1 = getCharAtxy(rightShieldX[i] + 1, rightShieldY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/') {
            isShieldActive = 1;
            score += 50;
            eraseShield(rightShieldX[i], rightShieldY[i]);
            deleteRightShieldFromArray(rightShieldX, rightShieldY, rightShieldCount, i);
        }
        else if (rightShieldY[i] == mazeYMax) {
            eraseShield(rightShieldX[i], rightShieldY[i]);
            deleteRightShieldFromArray(rightShieldX, rightShieldY, rightShieldCount, i);
        }
        else {

            eraseShield(rightShieldX[i], rightShieldY[i]);
            rightShieldY[i] = rightShieldY[i] + 1;
            printShield(rightShieldX[i], rightShieldY[i]);
            i++;
        }
        // Sleep(10);
    }
}

void generateLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int lCoinX, int lCoinY) {
    char c = 4;
    leftCoinY[leftCoinCount] = lCoinY;
    leftCoinX[leftCoinCount] = lCoinX;
    gotoxy(lCoinX, lCoinY);
    setcolor(14);
    cout << "@";
    setcolor(15);
    leftCoinCount++;
}
void generateRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int rCoinX, int rCoinY) {
    char c = 4;
    rightCoinX[rightCoinCount] = rCoinX;
    rightCoinY[rightCoinCount] = rCoinY;
    gotoxy(rCoinX, rCoinY);
    setcolor(14);
    cout << "@";
    setcolor(15);
    rightCoinCount++;
}
void printCoin(int x, int y) {
    char c = 4;
    gotoxy(x, y);
    setcolor(14);
    cout << "@";
    setcolor(15);
}
void eraseCoin(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}
void deleteLeftCoinFromArray(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int index) {
    for (int j = index; j < leftCoinCount - 1; j++) {
        leftCoinX[j] = leftCoinX[j + 1];
        leftCoinY[j] = leftCoinY[j + 1];
    }
    leftCoinCount--;
}
void deleteRightCoinFromArray(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int index) {
    for (int j = index; j < rightCoinCount - 1; j++) {
        rightCoinX[j] = rightCoinX[j + 1];
        rightCoinY[j] = rightCoinY[j + 1];
    }
    rightCoinCount--;
}
void moveLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int mazeYMax, int &score) {
    int i = 0;
    while (i < leftCoinCount) {
        char next = getCharAtxy(leftCoinX[i], leftCoinY[i] + 1);
        char next1 = getCharAtxy(leftCoinX[i] + 1, leftCoinY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/') {
            score += 10;
            eraseCoin(leftCoinX[i], leftCoinY[i]);
            deleteLeftCoinFromArray(leftCoinX, leftCoinY, leftCoinCount, i);
        }
        else if (leftCoinY[i] == mazeYMax) {
            eraseCoin(leftCoinX[i], leftCoinY[i]);
            deleteLeftCoinFromArray(leftCoinX, leftCoinY, leftCoinCount, i);
        }
        else {

            eraseCoin(leftCoinX[i], leftCoinY[i]);
            leftCoinY[i] = leftCoinY[i] + 1;
            printCoin(leftCoinX[i], leftCoinY[i]);
            i++;
        }
        // Sleep(10);
    }
}
void moveRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int mazeYMax, int &score) {
    int i = 0;
    while (i < rightCoinCount) {
        char next = getCharAtxy(rightCoinX[i], rightCoinY[i] + 1);
        char next1 = getCharAtxy(rightCoinX[i] + 1, rightCoinY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/') {
            score += 10;
            eraseCoin(rightCoinX[i], rightCoinY[i]);
            deleteRightCoinFromArray(rightCoinX, rightCoinY, rightCoinCount, i);
        }
        else if (rightCoinY[i] == mazeYMax) {
            eraseCoin(rightCoinX[i], rightCoinY[i]);
            deleteRightCoinFromArray(rightCoinX, rightCoinY, rightCoinCount, i);
        }
        else {

            eraseCoin(rightCoinX[i], rightCoinY[i]);
            rightCoinY[i] = rightCoinY[i] + 1;
            printCoin(rightCoinX[i], rightCoinY[i]);
            i++;
        }
        // Sleep(10);
    }
}
void deleteRightSnakeFromArray(int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, int index) {
    for (int j = index; j < rightSnakeCount - 1; j++) {
        rightSnakeX[j] = rightSnakeX[j + 1];
        rightSnakeY[j] = rightSnakeY[j + 1];
    }
    rightSnakeCount--;
}
void moveRightSnake(char snakeRight[4][3], int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, bool &isShieldActive, int &hit, int mazeYMax) {
    int i = 0;
    while (i < rightSnakeCount) {
        char next = getCharAtxy(rightSnakeX[i], rightSnakeY[i] + 1);
        char next1 = getCharAtxy(rightSnakeX[i] + 1, rightSnakeY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/') {
            if (isShieldActive == false) {
                hit++;
            }
            eraseSnake(rightSnakeX[i], rightSnakeY[i]);
            deleteRightSnakeFromArray(rightSnakeX, rightSnakeY, rightSnakeCount, i);
        }
        else if (rightSnakeY[i] == mazeYMax) {
            eraseSnake(rightSnakeX[i], rightSnakeY[i]);
            deleteRightSnakeFromArray(rightSnakeX, rightSnakeY, rightSnakeCount, i);
        }
        else {

            eraseSnake(rightSnakeX[i], rightSnakeY[i]);
            rightSnakeY[i] = rightSnakeY[i] + 1;
            printRightSnake(snakeRight, rightSnakeX[i], rightSnakeY[i]);
            i++;
        }
    }
}
void deleteLeftSnakeFromArray(int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, int index) {
    for (int j = index; j < leftSnakeCount - 1; j++) {
        leftSnakeX[j] = leftSnakeX[j + 1];
        leftSnakeY[j] = leftSnakeY[j + 1];
    }
    leftSnakeCount--;
}
void moveLeftSnake(char snakeLeft[4][3], int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, bool &isShieldActive, int &hit, int mazeYMax) {
    int i = 0;
    while (i < leftSnakeCount) {
        char next = getCharAtxy(leftSnakeX[i], leftSnakeY[i] + 1);
        char next1 = getCharAtxy(leftSnakeX[i] + 1, leftSnakeY[i] + 1);
        if (next1 == '<' || next1 == '\\' || next == '<' || next == '\\') {
            if (isShieldActive == false) {
                hit++;
            }
            eraseSnake(leftSnakeX[i], leftSnakeY[i]);
            deleteLeftSnakeFromArray(leftSnakeX, leftSnakeY, leftSnakeCount, i);
        }
        else if (leftSnakeY[i] == mazeYMax) {
            eraseSnake(leftSnakeX[i], leftSnakeY[i]);
            deleteLeftSnakeFromArray(leftSnakeX, leftSnakeY, leftSnakeCount, i);
        }
        else {

            eraseSnake(leftSnakeX[i], leftSnakeY[i]);
            leftSnakeY[i] = leftSnakeY[i] + 1;
            printLeftSnake(snakeLeft, leftSnakeX[i], leftSnakeY[i]);
            i++;
        }
    }
}
void generateLeftSnake(char snakeLeft[4][3], int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, int lSnakeX, int lSnakeY) {
    leftSnakeX[leftSnakeCount] = lSnakeX;
    leftSnakeY[leftSnakeCount] = lSnakeY;
    int x = lSnakeX;
    int y = lSnakeY;
    setcolor(10);
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeLeft[row][col];
        }
        y--;
    }
    setcolor(15);
    leftSnakeCount++;
}
void generateRightSnake(char snakeRight[4][3], int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, int rSnakeX, int rSnakeY) {
    rightSnakeX[rightSnakeCount] = rSnakeX;
    rightSnakeY[rightSnakeCount] = rSnakeY;
    int x = rSnakeX;
    int y = rSnakeY;
    setcolor(10);
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeRight[row][col];
        }
        y--;
    }
    setcolor(15);
    rightSnakeCount++;
}
void eraseSnake(int x, int y) {
    // 3X4
    gotoxy(x, y - 3);
    for (int i = 0; i < 2; i++) {
        cout << " ";
    }
    gotoxy(x, y - 2);
    for (int i = 0; i < 2; i++) {
        cout << " ";
    }
    gotoxy(x, y - 1);
    for (int i = 0; i < 2; i++) {
        cout << " ";
    }
    gotoxy(x, y);
    for (int i = 0; i < 2; i++) {
        cout << " ";
    }
}
void printRightSnake(char snakeRight[4][3], int x, int y) {
    // 3X4
    setcolor(10);
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeRight[row][col];
        }
        y--;
    }
    setcolor(15);
}
void printLeftSnake(char snakeLeft[4][3], int x, int y) {
    // 3X4
    setcolor(10);
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeLeft[row][col];
        }
        y--;
    }
    setcolor(15);
}
void eraseLeftBulletFromArray(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int index) {
    for (int j = index; j < leftCanonBulletCount - 1; j++) {
        leftCanonBulletX[j] = leftCanonBulletX[j + 1];
        leftCanonBulletY[j] = leftCanonBulletY[j + 1];
    }
    leftCanonBulletCount--;
}
void moveBulletFromLeftCanon(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int mazeYMax, bool &isShieldActive, int &hit) {
    int i = 0;
    while (i < leftCanonBulletCount) {
        char next = getCharAtxy(leftCanonBulletX[i], leftCanonBulletY[i] + 1);
        char next2 = getCharAtxy(leftCanonBulletX[i] + 1, leftCanonBulletY[i] + 1);
        if (next == '<' || next == '\\' || next2 == '<' || next2 == '\\') {
            if (isShieldActive == false) {
                hit++;
            }
            eraseBulletOfCanon(leftCanonBulletX[i], leftCanonBulletY[i]);
            eraseLeftBulletFromArray(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, i);
        }

        if (leftCanonBulletY[i] == mazeYMax) {
            eraseBulletOfCanon(leftCanonBulletX[i], leftCanonBulletY[i]);
            eraseLeftBulletFromArray(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, i);
        }
        else {
            eraseBulletOfCanon(leftCanonBulletX[i], leftCanonBulletY[i]);
            leftCanonBulletY[i] = leftCanonBulletY[i] + 1;
            printFireOfCanon(leftCanonBulletX[i], leftCanonBulletY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void eraseRightBulletFromArray(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int index) {
    for (int j = index; j < rightCanonBulletCount - 1; j++) {
        rightCanonBulletX[j] = rightCanonBulletX[j + 1];
        rightCanonBulletY[j] = rightCanonBulletY[j + 1];
    }
    rightCanonBulletCount--;
}
void moveBulletFromRightCanon(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int mazeYMax, bool &isShieldActive, int &hit) {
    int i = 0;
    while (i < rightCanonBulletCount) {
        char next = getCharAtxy(rightCanonBulletX[i], rightCanonBulletY[i] + 1);
        char next2 = getCharAtxy(rightCanonBulletX[i] + 1, rightCanonBulletY[i] + 1);
        if (next == '>' || next == '/' || next2 == '>' || next2 == '/') {
            if (isShieldActive == false) {
                hit++;
            }
            eraseBulletOfCanon(rightCanonBulletX[i], rightCanonBulletY[i]);
            eraseRightBulletFromArray(rightCanonBulletX, rightCanonBulletY, rightCanonBulletCount, i);
        }
        else if (rightCanonBulletY[i] == mazeYMax) {
            eraseBulletOfCanon(rightCanonBulletX[i], rightCanonBulletY[i]);
            eraseRightBulletFromArray(rightCanonBulletX, rightCanonBulletY, rightCanonBulletCount, i);
        }

        else {

            eraseBulletOfCanon(rightCanonBulletX[i], rightCanonBulletY[i]);
            rightCanonBulletY[i] = rightCanonBulletY[i] + 1;
            printFireOfCanon(rightCanonBulletX[i], rightCanonBulletY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void printFireOfCanon(int x, int y) {
    gotoxy(x, y);
    setcolor(12);
    cout << "O";
    setcolor(15);
}
void eraseBulletOfCanon(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}
void generateBulletFromRightCanon(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int rightCanonX, int rightCanonY) {
    rightCanonBulletX[rightCanonBulletCount] = rightCanonX + 1;
    rightCanonBulletY[rightCanonBulletCount] = rightCanonY + 3;
    gotoxy(rightCanonBulletX[rightCanonBulletCount], rightCanonBulletY[rightCanonBulletCount]);
    setcolor(12);
    cout << "O";
    setcolor(15);
    rightCanonBulletCount++;
}
void generateBulletFromLeftCanon(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int leftCanonX, int leftCanonY) {
    leftCanonBulletX[leftCanonBulletCount] = leftCanonX + 1;
    leftCanonBulletY[leftCanonBulletCount] = leftCanonY + 3;
    gotoxy(leftCanonBulletX[leftCanonBulletCount], leftCanonBulletY[leftCanonBulletCount]);
    setcolor(12);
    cout << "O";
    setcolor(15);
    leftCanonBulletCount++;
}
void eraseLeftCanon(int leftCanonX, int leftCanonY) {
    gotoxy(leftCanonX, leftCanonY);
    for (int i = 0; i < 3; i++) {
        cout << " ";
    }
    gotoxy(leftCanonX, leftCanonY + 1);
    for (int i = 0; i < 3; i++) {
        cout << " ";
    }
    gotoxy(leftCanonX, leftCanonY + 2);
    for (int i = 0; i < 3; i++) {
        cout << " ";
    }
}
void printCanonLeft(char canonLeft[3][3], int leftCanonX, int leftCanonY) {
    int x = leftCanonX;
    int y = leftCanonY;
    for (int row = 0; row < 3; row++) {
        gotoxy(x, y);
        for (int col = 0; col < 3; col++) {
            cout << canonLeft[row][col];
        }
        y++;
    }
}
void eraseRightCanon(int rightCanonX, int rightCanonY) {
    gotoxy(rightCanonX, rightCanonY);
    for (int i = 0; i < 3; i++) {
        cout << " ";
    }
    gotoxy(rightCanonX, rightCanonY + 1);
    for (int i = 0; i < 3; i++) {
        cout << " ";
    }
    gotoxy(rightCanonX, rightCanonY + 2);
    for (int i = 0; i < 3; i++) {
        cout << " ";
    }
}
void printCanonRight(char canonRight[3][3], int rightCanonX, int rightCanonY) {
    int x = rightCanonX;
    int y = rightCanonY;
    for (int row = 0; row < 3; row++) {
        gotoxy(x, y);
        for (int col = 0; col < 3; col++) {
            cout << canonRight[row][col];
        }
        y++;
    }
}
void printNinjaRight(char ninjaRight[4][5], int x, int y, bool isShieldActive) {
    if (isShieldActive == true) {
        setcolor(11);
        for (int row = 0; row < 4; row++) {
            gotoxy(x, y);
            for (int col = 0; col < 4; col++) {
                cout << ninjaRight[row][col];
            }
            y++;
        }
        setcolor(15);
    }
    else {
        for (int row = 0; row < 4; row++) {
            gotoxy(x, y);
            for (int col = 0; col < 4; col++) {
                cout << ninjaRight[row][col];
            }
            y++;
        }
    }
}
void printNinjaLeft(char ninjaLeft[4][5], int x, int y, bool isShieldActive) {
    if (isShieldActive == true) {
        setcolor(11);
        for (int row = 0; row < 4; row++) {
            gotoxy(x, y);
            for (int col = 0; col < 4; col++) {
                cout << ninjaLeft[row][col];
            }
            y++;
        }
        setcolor(15);
    }
    else {
        for (int row = 0; row < 4; row++) {
            gotoxy(x, y);
            for (int col = 0; col < 4; col++) {
                cout << ninjaLeft[row][col];
            }
            y++;
        }
    }

}
void eraseNinja(int x, int y) {
    gotoxy(x, y);
    for (int i = 0; i < 4; i++) {
        cout << " ";
    }
    gotoxy(x, y + 1);
    for (int i = 0; i < 4; i++) {
        cout << " ";
    }
    gotoxy(x, y + 2);
    for (int i = 0; i < 4; i++) {
        cout << " ";
    }
    gotoxy(x, y + 3);
    for (int i = 0; i < 4; i++) {
        cout << " ";
    }
}
void loadingScreen(char loadingPageCharacter[16][45]) {
    system("cls");
    int x = 5;
    int y = 2;
    for (int row = 0; row < 16; row++) {
        gotoxy(x, y);
        for (int col = 0; col < 45; col++) {
            cout << loadingPageCharacter[row][col];
        }
        y++;
    }
    gotoxy(x, y);
    char a = 219;
    for (int i = 0; i < 44; i++) {
        cout << a;
        Sleep(100);
    }
    gotoxy(0, 0);
}
void printStage(char stage[39][55]) {
    // Grid Size = 54X39
    system("cls");
    for (int row = 0; row < 39; row++) {
        for (int col = 0; col < 54; col++) {
            cout << stage[row][col];
        }
        // Sleep(100);
        cout << endl;
    }
}
void header() {
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
void instructions() {
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
void story() {
}
void loadLoadingPageCharacter(char loadingPageCharacter[16][45]) {
    fstream file;
    char temp;
    int row = 0, col = 0;
    file.open("loadingCharacter.txt", ios::in);
    while (!file.eof()) {
        file >> noskipws >> temp;
        if (temp == '\n') {
            row++;
            col = 0;
        }
        else {
            loadingPageCharacter[row][col] = temp;
            col++;
        }
    }
    file.close();
}
void loadStage(char stage[39][55]) {
    fstream file;
    char temp;
    int row = 0, col = 0;
    file.open("stage.txt", ios::in);
    while (!file.eof()) {
        file >> noskipws >> temp;
        if (temp == '\n') {
            row++;
            col = 0;
        }
        else {
            stage[row][col] = temp;
            col++;
        }
    }
    file.close();
}
void gotoxy(int x, int y) {
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y) {
    CHAR_INFO ci;
    COORD xy = { 0, 0 };
    SMALL_RECT rect = { x, y, x, y };
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
string setcolor(unsigned short color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}