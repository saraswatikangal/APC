#include "head.h"
#include <stdio.h>

int subtraction(FDLL **head1, FDLL **tail1,
                FDLL **head2, FDLL **tail2,
                FDLL **headR, FDLL **tailR)
{
    int dif, data1, data2;

    if (*head1 == NULL || *head2 == NULL)
    {
        return FAILURE;
    }

    int cmp = compare_num(*head1, *head2);

    if (cmp < 0)
    {
        return FAILURE;
    }

    if (cmp == 0)
    {
        if (insert_value(headR, tailR, 0) == FAILURE)
        {
            return FAILURE;
        }
        return SUCCESS;
    }

    int borrow = 0;
    FDLL *temp1 = *tail1;
    FDLL *temp2 = *tail2;

    while (temp1 != NULL || temp2 != NULL)
    {
        if (temp1 == NULL)
            data1 = 0;
        else
            data1 = temp1->data;

        if (temp2 == NULL)
            data2 = 0;
        else
            data2 = temp2->data;

        // previous borrow
        data1 = data1 - borrow;
        borrow = 0;

        if (data1 < data2)
        {
            data1 = data1 + 10;
            borrow = 1;
        }

        dif = data1 - data2;

        if (insert_value(headR, tailR, dif) == FAILURE)
        {
            free_list(headR, tailR);
            return FAILURE;
        }

        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
        }

        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }

    while (*headR != NULL && (*headR)->data == 0 &&
           (*headR)->next != NULL)
    {
        FDLL *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}