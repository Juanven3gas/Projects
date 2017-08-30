#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIMENSION 23
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

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
	  int grains = sand_pile[i][j];
	  
	  if(grains == 1)
	    {
	       printf(BLU "%2d" RESET, sand_pile[i][j]);
       
	    }
	  else if(grains == 2)
	    {
	       printf(GRN "%2d" RESET, sand_pile[i][j]);
	    }
	  else if(grains == 3)
	    {
	       printf(MAG "%2d"RESET, sand_pile[i][j]);
	    }
	  else if (grains == 4)
	    {
	       printf(RED "%2d" RESET, sand_pile[i][j]);
	    }
	  else
	    {
	       printf(YEL "%2d" RESET , sand_pile[i][j]);
	    }
        }

        printf("\n");
    }

    printf("\n");

    usleep(50000);

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

