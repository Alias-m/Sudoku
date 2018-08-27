#ifndef CASE_H
#define CASE_H

/**
 * \def SIZE
 * \brief The number of cells in a block
 * \see Block
 */

#define SIZE 9
/**
 * \def BLOCK
 * \brief The square root of SIZE for the squared block
 * \see SIZE
 * \see Block
 */
#define BLOCK 3

/**
 * \file "Case.h"
 * \brief Defines cell's structures and resolving functions
 * \author Mathieu L
 * \version 1
 */

/**
 * \typedef Cell
 * \brief The structure of a cell : a value and a list of possible values
 */
typedef struct{
    int value;          /*!< Known value of the cell (0 if unknown value) */
    int possibilities;  /*!< Binary mask of the possibilities the cell can accept */
}Cell;

/**
 * \typedef Block
 * \brief A list of cells' pointers which cannot share a common value
 */
typedef struct{
    Cell* cells[SIZE]; /*!< List of cells' pointers */
}Block;

/**
 * \fn int getBits(int num)
 * \brief Returns the number of bits with the value 1 in a number
 * \param num
 *          Bitmask
 * \return the number of bits with the value 1 in the bitmask
 */
int getBits(int num);

/**
 * \fn int clearBlock(Block*)
 * \brief Removes N values of N cells in the others cells of the block
 * \param *block
 *          A block to clear
 * \return 1 if the block has been changed, 0 otherwise
 */
int clear2(Block*, int used, int index, int possibilities, int others);
#endif // CASE_H
