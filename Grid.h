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
/**
 * \fn int clearBlock(Block*)
 * \brief Removes N values of N cells in the others cells of the block
 * \param *block
 *          A block to clear
 * \return 1 if the block has been changed, 0 otherwise
 */
int clear2(Grid*, Block*, int used, int index, int possibilities, int others);
#endif // GRID_H
