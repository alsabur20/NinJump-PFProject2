#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void moveNinjaUp(char ninjaLeft[4][5], char ninjaRight[4][5], int &ninjaX, int &ninjaY, char &moveStatus, bool isShieldActive);
void moveNinjaDown(char ninjaLeft[4][5], char ninjaRight[4][5], int &ninjaX, int &ninjaY, char &moveStatus, bool isShieldActive);
void generateLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int lCoinX, int lCoinY);
void generateRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int rCoinX, int rCoinY);
void moveLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int mazeYMax, int &score);
void moveRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int mazeYMax, int &score);
void eraseSnake(int x, int y);
void printRightSnake(char snakeRight[4][3], int x, int y);
void printLeftSnake(char snakeLeft[4][3], int x, int y);
void printFireOfLeftCanon(int x, int y);
void eraseBulletOfCanon(int x, int y);
void eraseLeftCanon(int leftCanonX, int leftCanonY);
void printCanonLeft(char canonLeft[3][3], int leftCanonX, int leftCanonY);
void eraseRightCanon(int rightCanonX, int rightCanonY);
void printCanonRight(char canonRight[3][3], int rightCanonX, int rightCanonY);
void printNinjaRight(char ninjaRight[4][5], int x, int y, bool isShieldActive);
void printNinjaLeft(char ninjaLeft[4][5], int x, int y, bool isShieldActive);
void eraseNinja(int x, int y);
void loadingScreen(char loadingPageCharacter[16][45]);
void moveRightSnake(char snakeRight[4][3], int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, bool &isShieldActive, int &hit, int mazeYMax);
void moveLeftSnake(char snakeLeft[4][3], int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, bool &isShieldActive, int &hit, int mazeYMax);
void generateLeftSnake(char snakeLeft[4][3], int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, int lSnakeX, int lSnakeY);
void deleteLeftSnakeFromArray(int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, int index);
void deleteRightSnakeFromArray(int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, int index);
void generateRightSnake(char snakeRight[4][3], int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, int rSnakeX, int rSnakeY);
void moveBulletFromLeftCanon(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int mazeYMax, bool &isShieldActive, int &hit);
void eraseLeftBulletFromArray(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int index);
void moveBulletFromRightCanon(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int mazeYMax, bool &isShieldActive, int &hit);
void eraseRightBulletFromArray(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int index);
void generateBulletFromRightCanon(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int rightCanonX, int rightCanonY);
void generateBulletFromLeftCanon(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int leftCanonX, int leftCanonY);
void printStage(char stage[39][55]);
void header();
void instructions();
void story();
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
string setcolor(unsigned short color);

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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    bool isShieldActive = 0;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    loadLoadingPageCharacter(loadingPageCharacter);
    loadStage(stage);

    system("cls");
    // loadingScreen(loadingPageCharacter);
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
                    generateLeftSnake(snakeLeft, leftSnakeX, leftSnakeY, leftSnakeCount, lSnakeX, lSnakeY);
                    // generateBulletFromLeftCanon(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, leftCanonX, leftCanonY);
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
                moveBulletFromLeftCanon(leftCanonBulletX, leftCanonBulletY, leftCanonBulletCount, mazeYMax, isShieldActive, hit);
                moveBulletFromRightCanon(rightCanonBulletX, rightCanonBulletY, rightCanonBulletCount, mazeYMax, isShieldActive, hit);
                moveLeftSnake(snakeLeft, leftSnakeX, leftSnakeY, leftSnakeCount, isShieldActive, hit, mazeYMax);
                moveRightSnake(snakeRight, rightSnakeX, rightSnakeY, rightSnakeCount, isShieldActive, hit, mazeYMax);
                moveLeftCoin(leftCoinX, leftCoinY, leftCoinCount, mazeYMax, score);
                moveRightCoin(rightCoinX, rightCoinY, rightCoinCount, mazeYMax, score);
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
            getch();
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void moveNinjaUp(char ninjaLeft[4][5], char ninjaRight[4][5], int &ninjaX, int &ninjaY, char &moveStatus, bool isShieldActive) {
    char next = getCharAtxy(ninjaX, ninjaY - 1);
    if (next == ' ' || next == 'O') {
        // if(next == 'O')
        // {
        //     hit++;
        // }
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
        // if(next == 'O')
        // {
        //     hit++;
        // }
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
void generateLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int lCoinX, int lCoinY) {
    leftCoinY[leftCoinCount] = lCoinY;
    leftCoinX[leftCoinCount] = lCoinX;
    gotoxy(lCoinX, lCoinY);
    cout << "@";
    leftCoinCount++;
}
void generateRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int rCoinX, int rCoinY) {
    rightCoinX[rightCoinCount] = rCoinX;
    rightCoinY[rightCoinCount] = rCoinY;
    gotoxy(rCoinX, rCoinY);
    cout << "@";
    rightCoinCount++;
}
void printCoin(int x, int y) {
    gotoxy(x, y);
    cout << "@";
}
void eraseCoin(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}
void moveLeftCoin(int leftCoinX[], int leftCoinY[], int &leftCoinCount, int mazeYMax, int &score) {
    int i = 0;
    while (i < leftCoinCount) {
        char next = getCharAtxy(leftCoinX[i], leftCoinY[i] + 1);
        char next1 = getCharAtxy(leftCoinX[i] + 1, leftCoinY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/') {
            score += 5;
            eraseCoin(leftCoinX[i], leftCoinY[i]);
            for (int j = i; j < leftCoinCount - 1; j++) {
                leftCoinX[j] = leftCoinX[j + 1];
                leftCoinY[j] = leftCoinY[j + 1];
            }
            leftCoinCount--;
        }
        else if (leftCoinY[i] == mazeYMax) {
            eraseCoin(leftCoinX[i], leftCoinY[i]);
            for (int j = i; j < leftCoinCount - 1; j++) {
                leftCoinX[j] = leftCoinX[j + 1];
                leftCoinY[j] = leftCoinY[j + 1];
            }
            leftCoinCount--;
        }
        else {

            eraseCoin(leftCoinX[i], leftCoinY[i]);
            leftCoinY[i] = leftCoinY[i] + 1;
            printCoin(leftCoinX[i], leftCoinY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void moveRightCoin(int rightCoinX[], int rightCoinY[], int &rightCoinCount, int mazeYMax, int &score) {
    int i = 0;
    while (i < rightCoinCount) {
        char next = getCharAtxy(rightCoinX[i], rightCoinY[i] + 1);
        char next1 = getCharAtxy(rightCoinX[i] + 1, rightCoinY[i] + 1);
        if (next1 == '>' || next1 == '/' || next == '>' || next == '/') {
            score += 5;
            eraseCoin(rightCoinX[i], rightCoinY[i]);
            for (int j = i; j < rightCoinCount - 1; j++) {
                rightCoinX[j] = rightCoinX[j + 1];
                rightCoinY[j] = rightCoinY[j + 1];
            }
            rightCoinCount--;
        }
        else if (rightCoinY[i] == mazeYMax) {
            eraseCoin(rightCoinX[i], rightCoinY[i]);
            for (int j = i; j < rightCoinCount - 1; j++) {
                rightCoinX[j] = rightCoinX[j + 1];
                rightCoinY[j] = rightCoinY[j + 1];
            }
            rightCoinCount--;
        }
        else {

            eraseCoin(rightCoinX[i], rightCoinY[i]);
            rightCoinY[i] = rightCoinY[i] + 1;
            printCoin(rightCoinX[i], rightCoinY[i]);
            // Sleep(50);
            i++;
        }
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
            // Sleep(50);
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
            // Sleep(50);
            i++;
        }
    }
}
void generateLeftSnake(char snakeLeft[4][3], int leftSnakeX[], int leftSnakeY[], int &leftSnakeCount, int lSnakeX, int lSnakeY) {
    leftSnakeX[leftSnakeCount] = lSnakeX;
    leftSnakeY[leftSnakeCount] = lSnakeY;
    int x = lSnakeX;
    int y = lSnakeY;
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeLeft[row][col];
        }
        y--;
    }
    leftSnakeCount++;
}
void generateRightSnake(char snakeRight[4][3], int rightSnakeX[], int rightSnakeY[], int &rightSnakeCount, int rSnakeX, int rSnakeY) {
    rightSnakeX[rightSnakeCount] = rSnakeX;
    rightSnakeY[rightSnakeCount] = rSnakeY;
    int x = rSnakeX;
    int y = rSnakeY;
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeRight[row][col];
        }
        y--;
    }
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
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeRight[row][col];
        }
        y--;
    }
}
void printLeftSnake(char snakeLeft[4][3], int x, int y) {
    // 3X4
    for (int row = 3; row >= 0; row--) {
        gotoxy(x, y);
        for (int col = 0; col < 2; col++) {
            cout << snakeLeft[row][col];
        }
        y--;
    }
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
            printFireOfLeftCanon(leftCanonBulletX[i], leftCanonBulletY[i]);
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
            printFireOfLeftCanon(rightCanonBulletX[i], rightCanonBulletY[i]);
            // Sleep(50);
            i++;
        }
    }
}
void printFireOfLeftCanon(int x, int y) {
    gotoxy(x, y);
    cout << "O";
}
void eraseBulletOfCanon(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}
void generateBulletFromRightCanon(int rightCanonBulletX[], int rightCanonBulletY[], int &rightCanonBulletCount, int rightCanonX, int rightCanonY) {
    rightCanonBulletX[rightCanonBulletCount] = rightCanonX + 1;
    rightCanonBulletY[rightCanonBulletCount] = rightCanonY + 3;
    gotoxy(rightCanonBulletX[rightCanonBulletCount], rightCanonBulletY[rightCanonBulletCount]);
    cout << "O";
    rightCanonBulletCount++;
}
void generateBulletFromLeftCanon(int leftCanonBulletX[], int leftCanonBulletY[], int &leftCanonBulletCount, int leftCanonX, int leftCanonY) {
    leftCanonBulletX[leftCanonBulletCount] = leftCanonX + 1;
    leftCanonBulletY[leftCanonBulletCount] = leftCanonY + 3;
    gotoxy(leftCanonBulletX[leftCanonBulletCount], leftCanonBulletY[leftCanonBulletCount]);
    cout << "O";
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
        setcolor(12);
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
        setcolor(12);
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