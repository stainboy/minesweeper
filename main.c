#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_LENGTH 9
#define MAP_HEIGHT 16
#define MAX_MINE 20
#define MARK_MINE '#'
#define MARK_EMPTY ' '

int increase_no_mine(int (*map)[MAP_HEIGHT], int x, int y) {

    if (x < 0 || x >= MAP_LENGTH || y < 0 || y >= MAP_HEIGHT) {
        return -1;
    }

    int mark = map[x][y];
    if (mark < 0) {
        return -2;
    }

    map[x][y]++;
    return 0;
}

int print_board(int (*map)[MAP_HEIGHT]) {
    for (int i = 0; i < MAP_LENGTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            int a = map[i][j];
            if (a < 0) {
                printf("%c ", MARK_MINE);
            } else if (a == 0) {
                printf("%c ", MARK_EMPTY);
            } else {
                printf("%d ", a);
            }
            if (j == MAP_HEIGHT - 1) {
                printf("\n");
            }
        }
    }
    return 0;
}

int reset_board(int (*map)[MAP_HEIGHT]) {
    for (int i = MAX_MINE; i > 0; i--) {
        int x = rand() % MAP_LENGTH;
        int y = rand() % MAP_HEIGHT;

        if (map[x][y] < 0) {
            // the given point is mine, run another loop
            i++;
            continue;
        } else {
            map[x][y] = -1;
            //printf("The %dth mine is at (%d,%d)\n", i, x, y);
            increase_no_mine(map, x, y+1);
            increase_no_mine(map, x, y-1);
            increase_no_mine(map, x+1, y+1);
            increase_no_mine(map, x+1, y-1);
            increase_no_mine(map, x-1, y+1);
            increase_no_mine(map, x-1, y-1);
            increase_no_mine(map, x+1, y);
            increase_no_mine(map, x-1, y);
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    printf("A random %dx%d map of minesweeper\n", MAP_LENGTH, MAP_HEIGHT);
    printf("\n");

    int map[MAP_LENGTH][MAP_HEIGHT] = {0};
    reset_board(map);
    print_board(map);

    printf("\n");
    printf("Enjoy!\n");
    return 0;
}