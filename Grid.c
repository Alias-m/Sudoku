#include "Grid.h"

void parseSDK(Grid* g, const char* code, int size)
{
    int i, j;
    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            g->grid[i][j].value = 0;
            if(code[(SIZE+1)*i+j > 0x2F] && code[10*i+j] < 0x3A)
                g->grid[i][j].value = code[(SIZE+1)*i + j] - 0x30;

            if(g->grid[i][j].value)
                g->grid[i][j].possibilities = (1 << g->grid[i][j].value) >> 1;
            else
                g->grid[i][j].possibilities = ((1 << SIZE) - 1);

            g->blocks[i].cells[j] = &g->grid[i][j];
            g->blocks[i+SIZE].cells[j] = &g->grid[j][i];
            g->blocks[(j/BLOCK+BLOCK*(i/BLOCK))+(SIZE*2)].cells[j%BLOCK+BLOCK*(i%BLOCK)] = &g->grid[i][j];
        }
    }
}

Block* getCommonBlock(Grid* g, Block* b, int used)
{
    Block* common;
    int i, j, z;
    for(i = 0; i < SIZE*3; i++)
    {
        if(&g->blocks[i] != b)
        {
            common = &g->blocks[i];
            for(j = 0; (used >> j) && common != NULL; j++)
            {
                if((used >> j)&1)
                {
                    for(z = 0; z < SIZE && g->blocks[i].cells[z] != b->cells[j]; z++);
                    if(z == SIZE)
                        common = NULL;
                }
            }
            if(common != NULL)
                return common;
        }
    }
    return NULL;
}
int clearFromShared(Grid* g, Block* b, int used, int index)
{
    int edited = 0, others, i, x, z;
    int possibilities, result;
    for(i = index; i < SIZE -1; i++)
    {
        if(!b->cells[i]->value)
        {
            used += 1 << i;
            possibilities = 0;
            others = 0;
            for(x = 0; x < SIZE; x++)
            {
                if(((used >> x) & 1))
                    possibilities |= (b->cells[x]->possibilities);
                else if(!b->cells[x]->value)
                    others |= b->cells[x]->possibilities;
            }
            result = (possibilities & (possibilities ^ others));
            if(index > 0 && getBits(result))
            {
                Block* common = getCommonBlock(g, b, used);
                if(common != NULL)
                {
                    for(x = 0; x < SIZE; x++)
                        if(!common->cells[x]->value)
                        {
                            for(z = 0; z < SIZE && common->cells[x] != b->cells[z]; z++);
                            if(z == SIZE)
                            {
                                edited += (common->cells[x]->possibilities & result);
                                common->cells[x]->possibilities &= (~result);
                            }
                        }
                    return !!edited;
                }
            }
            else if(getBits(used) <= BLOCK && clearFromShared(g, b, used, i + 1))
                edited = 1;
            used -= 1 << i;
        }
    }
    return edited;
}

void solve(Grid* g)
{
    int i, edited = 1;
    do
    {
        edited = 0;
        for(i = 0; i < (SIZE*3); i++)
        {
            if(clear2(&g->blocks[i], 0, 0, 0, 0))
                edited = 1;
            /*else if(clearFromShared(g, &g->blocks[i], 0, 0))
            {
                printf("Error - 3\n");
                edited = 1;
            }*/
        }
    } while(edited);
}
#include <math.h>
void show(Grid* g)
{
    int i, j;
    for(i = 0; i < SIZE; i++)
    {
        if(!(i%BLOCK))
            printf("+---+---+---+\n");
        for(j = 0; j < SIZE; j++)
        {
            if(!(j%BLOCK))printf("|");
            if(!((g->grid[i][j].possibilities - 1) & g->grid[i][j].possibilities) && g->grid[i][j].possibilities)
                printf("%5d ", (int) log2(g->grid[i][j].possibilities) + 1);
            else
                printf("[%3d] ", g->grid[i][j].possibilities);
        }
        printf("\n");
    }
}
