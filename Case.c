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
int clear2(Block* b, int used, int index, int __possibilities, int __others)
{
    int edited = 0;
    int nbr_cells = getBits(used);
    int nbr_possibilities = getBits(__possibilities);
    if(index >= SIZE - 1) {
        if(nbr_possibilities == nbr_cells && (__others & __possibilities))
        {
            for(int x = 0; x < SIZE; x++){
                if(!((used >> x) & 1) && ( (b->cells[x]->possibilities & (~__possibilities)) != b->cells[x]->possibilities)){
                    b->cells[x]->possibilities &= (~__possibilities);
                    edited = 1;
                }
            }
        }
        //Should be required...
        /*
        int result = (__possibilities & (__possibilities ^ __others));
        if(getBits(result) == nbr_cells && __possibilities != result){
            for(int x = 0; x < SIZE; x++){
                if(((used >> x) & 1) && (b->cells[x]->possibilities & result) != b->cells[x]->possibilities){
                    b->cells[x]->possibilities &= result;
                    edited = 1;
                }
            }
        }*/
    }
    else {
        int additionnal_other = 0;
        for(int i = index; i < SIZE; i++)
        {
            // possibilities power of two   => do not add a value
            // !__possibilities             => excepts if first input
            if((((b->cells[i]->possibilities - 1) & b->cells[i]->possibilities)) || !__possibilities)
                edited |= clear2(b, used + (1 << i), i + 1, __possibilities | b->cells[i]->possibilities, __others | additionnal_other);
            additionnal_other |= b->cells[i]->possibilities;
        }
        // if nbr_possibilities                 => If there is at least one value
        // if nbr_possibilities == nbr_cells    => If this nombre of bits set is equal to the number of registered cells
        if(nbr_possibilities == nbr_cells && nbr_possibilities)
            edited |= clear2(b, used, SIZE, __possibilities, __others | additionnal_other);
    }
    return edited;
}
