#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIMENSION 23

int sand_pile[DIMENSION][DIMENSION];

void init_sandpile(void)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < DIMENSION; i++)
    {
        for(j = 0; j < DIMENSION; j++)
        {
            sand_pile[i][j] = 0;
        }
    }
}

void print_sandpile(void)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < DIMENSION; i++)
    {
        for(j = 0; j < DIMENSION; j++)
        {

            printf("%2d", sand_pile[i][j]);
        }

        printf("\n");
    }

    printf("\n");

    usleep(500000);

}

void add_sand(int x, int y)
{
    sand_pile[x][y] += 1;

    int grains = sand_pile[x][y];

    if(grains > 4)
    {
        sand_pile[x][y] = grains - 4;

        if(x > 0)
        {
            add_sand(x - 1, y);
        }
        if(x < DIMENSION - 1)
        {
            add_sand(x + 1, y);
        }
        if(y > 0)
        {
            add_sand(x , y - 1);
        }
        if(y < DIMENSION - 1)
        {
            add_sand(x , y + 1);
        }

    }

}

int check_stable(void)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < DIMENSION; i++)
    {
        for (j = 0; j < DIMENSION; j++)
        {
            int sand =  sand_pile[i][j];

            if(sand !=  4)
            {
                return 0;
            }
        }
    }

    return 1;
}

int main(int argc, char* argv[])
{
    int stable = 0;
    int start = DIMENSION / 2;
    int num_arg = argc;

    int counter = 1;

    init_sandpile();

    while(num_arg > 1)
    {
        int x = atoi(argv[counter++]);
        int y = atoi(argv[counter++]);
        int h = atoi(argv[counter++]);
        num_arg -= 3;

        sand_pile[x][y] = h;

    }

    while (!stable)
    {
        add_sand(start, start);
        stable = check_stable();
        print_sandpile();

    }

    return 0;
}

