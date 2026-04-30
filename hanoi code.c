#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 8

int pegs[3][MAX_DISKS];
int top[3];
int total_disks;
int move_count = 0;

/* pause so user can see steps */
void wait_input()
{
    printf("\nPress ENTER...");
    getchar();
}

/* clear screen */
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* display the towers */
void display(int step, int src, int dst, int disk)
{
    int i, j, p, index, size;
    int width = MAX_DISKS + 2;

    printf("\nTOWERS OF HANOI\n");

    if (step == 0)
        printf("\nInitial state\n\n");
    else
        printf("\nMove %d: %d -> %d (disk %d)\n\n",
               step, src + 1, dst + 1, disk);

    for (i = total_disks - 1; i >= 0; i--) {
        for (p = 0; p < 3; p++) {

            index = top[p] - 1 - (total_disks - 1 - i);

            if (index >= 0 && index < top[p]) {
                size = pegs[p][index];

                for (j = 0; j < width - size; j++) printf(" ");
                for (j = 0; j < size; j++) printf("#");

                printf("|");

                for (j = 0; j < size; j++) printf("#");
                for (j = 0; j < width - size; j++) printf(" ");
            } else {
                for (j = 0; j < width; j++) printf(" ");
                printf("|");
                for (j = 0; j < width; j++) printf(" ");
            }

            if (p < 2) printf("   ");
        }
        printf("\n");
    }

    printf("\nMoves: %d / %d\n",
           move_count, (1 << total_disks) - 1);
}

/* initialize pegs */
void init(int n)
{
    int i;
    for (i = 0; i < 3; i++) top[i] = 0;

    for (i = n; i >= 1; i--)
        pegs[0][top[0]++] = i;
}

/* move one disk */
void move_disk(int src, int dst)
{
    if (top[src] == 0) return;

    int disk = pegs[src][--top[src]];
    pegs[dst][top[dst]++] = disk;

    move_count++;

    clear_screen();
    display(move_count, src, dst, disk);
    wait_input();
}

/* recursive solution */
void hanoi(int n, int src, int dst, int temp)
{
    if (n == 1) {
        move_disk(src, dst);
        return;
    }

    hanoi(n - 1, src, temp, dst);
    move_disk(src, dst);
    hanoi(n - 1, temp, dst, src);
}

int main()
{
    int n;

    printf("Number of disks (1-%d): ", MAX_DISKS);

    if (scanf("%d", &n) != 1) {
        printf("Error\n");
        return 1;
    }
    getchar();

    if (n <= 0 || n > MAX_DISKS) {
        printf("Invalid number\n");
        return 1;
    }

    total_disks = n;
    init(n);

    clear_screen();
    display(0, 0, 0, 0);
    getchar();

    hanoi(n, 0, 2, 1);

    printf("\nDone! Total moves: %d\n", move_count);

    return 0;
}
	

	
















