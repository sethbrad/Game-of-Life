#include <iostream>
#include <chrono>
#include <thread>

/*
Any live cell with fewer than two live neighbors dies, as if caused by under population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/

static int M = 10;
static int N = 10;

static char grid[10][10];

static int deaths = 0;
static int births = 0;

void initialize();
void generate();
void printLoop();

int main()
{
    initialize();

    while (1) {
        generate();
        printLoop();
    }
}

void initialize() {

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {

            float chance = (rand() % 10) / 10.0; //implement random live cells

            if (chance < 0.8) {
                grid[i][j] = '*';
            }
            else {
                grid[i][j] = '-';
            }
        }
    }
}

int countNeighbors(int i, int j) {
    int sum = 0;

    if (grid[i - 1][j] == '*') {
        sum++;
    }
    if (grid[i + 1][j] == '*') {
        sum++;
    }
    if (grid[i][j - 1] == '*') {
        sum++;
    }
    if (grid[i][j + 1] == '*') {
        sum++;
    }

    return sum;
}

void generate() {

    for (int i = 1; i < M - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            
            bool alive = grid[i][j] == '*';
            int neighbors = countNeighbors(i, j); //check num of neighbors

            if (alive && (neighbors < 2)) {
                grid[i][j] = '-';
                deaths++;
            }
            if (alive && (neighbors == 2 || neighbors == 3)) {
                grid[i][j] = '*';
            }
            if (alive && neighbors > 3) {
                grid[i][j] = '-';
                deaths++;
            }
            if (!alive && neighbors == 3) {
                grid[i][j] = '*';
                births++;
            }

            //add perturbation
        }
    }
}

void printLoop() {

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c  ", grid[i][j]);
        }
        printf("\n");
    }
    
    puts("New deaths: ");
    printf("%d\n", deaths);
    puts("New births: ");
    printf("%d\n", births);

    deaths = 0;
    births = 0;

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    system("cls");
}
