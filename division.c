#include "head.h"
#include <stdio.h>

int division(FDLL **head1, FDLL **tail1,
             FDLL **head2, FDLL **tail2,
             FDLL **headR, FDLL **tailR)
{
    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    /* Check division by zero */
    FDLL *temp = *head2;

    while (temp != NULL && temp->data == 0)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    FDLL *rem = NULL, *rem_tail = NULL;
    FDLL *sub = NULL, *sub_tail = NULL;

    free_list(headR, tailR);

    temp = *head1;

    while (temp != NULL)
    {
        FDLL *new = malloc(sizeof(FDLL));

        if (new == NULL)
        {
            free_list(&rem, &rem_tail);
            free_list(headR, tailR);
            return FAILURE;
        }

        new->data = temp->data;
        new->prev = rem_tail;
        new->next = NULL;

        if (rem == NULL)
            rem = new;
        else
            rem_tail->next = new;

        rem_tail = new;

        while (rem != NULL && rem->data == 0 &&
               rem->next != NULL)
        {
            FDLL *del = rem;
            rem = rem->next;
            rem->prev = NULL;
            free(del);
        }

        int count = 0;

        while (rem != NULL && compare_num(rem, *head2) >= 0)
        {
            sub = NULL;
            sub_tail = NULL;

            if (subtraction(&rem, &rem_tail,
                            head2, tail2,
                            &sub, &sub_tail) == FAILURE)
            {
                free_list(&rem, &rem_tail);
                free_list(&sub, &sub_tail);
                free_list(headR, tailR);
                return FAILURE;
            }

            free_list(&rem, &rem_tail);

            rem = sub;
            rem_tail = sub_tail;

            sub = NULL;
            sub_tail = NULL;

            count++;
        }

        FDLL *q = malloc(sizeof(FDLL));

        if (q == NULL)
        {
            free_list(&rem, &rem_tail);
            free_list(headR, tailR);
            return FAILURE;
        }

        q->data = count;
        q->prev = *tailR;
        q->next = NULL;

        if (*headR == NULL)
            *headR = q;
        else
            (*tailR)->next = q;

        *tailR = q;

        temp = temp->next;
    }

    while (*headR != NULL && (*headR)->data == 0 &&
           (*headR)->next != NULL)
    {
        FDLL *del = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(del);
    }

    free_list(&rem, &rem_tail);

    return SUCCESS;
}