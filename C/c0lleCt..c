#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
// Global variables
int isLocked = 0;
int isGameOver = 0;
int platformLeft = 0;
int playerScore = 0;
int consoleWidth, consoleHeight;
int platformStart, platformEnd;
HANDLE consoleHandle;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;


// Function to hide the console cursor
void hideCursor(){
   CONSOLE_CURSOR_INFO cursorInfo;
   cursorInfo.dwSize = 100;
   cursorInfo.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}


// Function to set cursor position on the console
void goToXY(int x, int y){
    while(isLocked){
        continue;
    }
    isLocked = 1;
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(consoleHandle, coordinates);
}


// Function to check if a given position is within the scorecard region
int isInPlatformRegion(int x){
    if(x <= 30 && x >= 0){
        return 1;
    }
    return 0;
}


// Function to display the scorecard
void displayScorecard(int a){
    if (a==0){
        goToXY(0,0);
        printf("Use A for right and D for left");
        isLocked = 0;
    }
    goToXY(0,1);
    printf("Score %2d",playerScore);
    isLocked = 0;
    if (a == 1 || a==0){
        goToXY(0,2);
        printf("Level %2d", platformLeft);
        isLocked = 0;
    }
}


// Function to move the zero
void movePlayer(int x){


    for(int i = 0; i < consoleHeight - 5; i++){
        if((i == 1 || i == 2 || i==0) && isInPlatformRegion(x)){
            continue;
        }
        goToXY(x, i);
        printf("0");
        isLocked = 0;
        Sleep(200 - 30 * platformLeft);
        goToXY(x, i);
        printf(" ");
        isLocked = 0;
    }

    if(x >= platformStart && x <= platformEnd){
        playerScore++;
    }
    else{
        isGameOver = 1;
    }
}
// Function to create the platform
void createPlatform(){
    goToXY(platformStart - 1, consoleHeight - 5);
    printf(" |||||||||| ");
    isLocked = 0;
}
// Function executed by the input thread
void *inputThread(void *arg) {
    char input;
    while (!isGameOver){
        input = getch();
        if(input == 'a'){
            if(platformStart > 1){
                platformStart--;
                platformEnd--;
                createPlatform();
            }
        }
        else if(input == 'd'){
            if (platformEnd < consoleWidth - 1){
                platformStart++;
                platformEnd++;
                createPlatform();
                }
        }
    }
    return NULL;
}




// Function to display the game over prompt
char gameOverPrompt() {
    system("cls");
    goToXY(consoleWidth / 2 - 5, consoleHeight / 2);
    printf("Game Over");
    isLocked =0;
    goToXY(consoleWidth / 2 - 8, consoleHeight / 2 + 2);
    printf("Your score was %d", playerScore);
    isLocked=0;
    goToXY(consoleWidth / 2 - 16, consoleHeight / 2 + 4);
    printf("Press 'r' to restart or 'e' to exit.");
    isLocked=0;
    char choice;
    do {
        choice = getch();
    } while (choice != 'r' && choice != 'e');
    return choice;
}


// Main function
int main() {
    // Initialization
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    consoleHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;


    time_t timeSeed;
    srand((unsigned) time(&timeSeed));


    platformStart = consoleWidth / 2 - 4;
    platformEnd = consoleWidth / 2 + 6;
    createPlatform();
    displayScorecard(0);


    pthread_t tid;
    restart:
    pthread_create(&tid, NULL, inputThread, NULL);


    // Game loop
    while(!isGameOver){
        movePlayer(rand() % (consoleWidth - 2) + 1);
        if(playerScore / 10 != platformLeft){
            platformLeft = playerScore / 10;
            displayScorecard(1);
        }
        else{
            displayScorecard(0);
        }
    }


    pthread_join(tid, NULL);
    char choice = gameOverPrompt();
    if (choice == 'r') {
        isGameOver = 0;
        playerScore = 0;
        platformLeft = 0;
        system("cls");
        createPlatform();
        displayScorecard(0);
        goto restart;
    }
    return 0;
}
