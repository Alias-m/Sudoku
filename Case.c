#include "Case.h"

//Hamming Weight
int getBits(int num)
{
    num = num - ((num >> 1) & 0x55555555);
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
    return (((num + (num >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
/*
int clear(Block* b, int used, int index, int __possibilities, int __others)
{
    int edited = 0, others, i, x;
    int possibilities, result;
    int nbr = getBits(used) + 1;
    for(i = index; i < SIZE -1; i++)
    {
        if(used != 0 && !((b->cells[i]->possibilities - 1) & b->cells[i]->possibilities))
            continue;
        used += 1 << i;
        possibilities = 0;
        others = 0;
        for(x = 0; x < SIZE; x++)
        {
            if(((used >> x) & 1))
                possibilities |= b->cells[x]->possibilities;
            else
                others |= b->cells[x]->possibilities;
        }
        result = (possibilities & (possibilities ^ others));
        if(getBits(possibilities) == nbr && (others & possibilities))
        {
            for(x = 0; x < SIZE; x++){
                if(!((used >> x) & 1) && ( (b->cells[x]->possibilities & (~possibilities)) != b->cells[x]->possibilities)){
                    b->cells[x]->possibilities &= (~possibilities);
                    edited = 1;
                }
            }
        }
        /*if(getBits(result) == nbr && possibilities != result){
            for(x = 0; x < SIZE; x++){
                if(((used >> x) & 1) && (b->cells[x]->possibilities & result) != b->cells[x]->possibilities){
                    b->cells[x]->possibilities &= result;
                    edited = 1;
                }
            }
        }
        if(!edited && nbr < SIZE && clear(b, used, i + 1, 0, 0))
            edited = 1;
        used -= 1 << i;
    }
    return edited;
}


*/
