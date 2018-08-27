#ifndef GRID_H
#define GRID_H
#include "Case.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    Cell grid[9][9];
    Block blocks[27];
}Grid;

void parseSDK(Grid*, const char*, int);
void solve(Grid*);
void show(Grid* g);
#endif // GRID_H
