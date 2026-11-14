#include "head.h"
#include <stdio.h>

int multiplication(FDLL **head1, FDLL **tail1,
                   FDLL **head2, FDLL **tail2,
                   FDLL **head3, FDLL **tail3)
{
    if (*head1 == NULL || *head2 == NULL)
    {
        return FAILURE;
    }
     if (((*head1)->data == 0 && (*head1)->next == NULL) ||
        ((*head2)->data == 0 && (*head2)->next == NULL))
        {
            free_list(head3, tail3);
            insert_value(head3, tail3, 0);
            return SUCCESS;
        }

    int carry = 0, result, count = 0;

    FDLL *temp1 = *tail1;
    FDLL *temp2 = *tail2;

    FDLL *headR1 = NULL;
    FDLL *tailR1 = NULL;
    FDLL *headR2 = NULL;
    FDLL *tailR2 = NULL;
    FDLL *headR = NULL;
    FDLL *tailR = NULL;

    /* First partial multiplication */
    while (temp1 != NULL)
    {
        result = (temp2->data * temp1->data) + carry;
        carry =  result / 10;

        insert_value(&headR1, &tailR1, result % 10);
        temp1 = temp1->prev;
    }

    if (carry > 0)
    {
        insert_value(&headR1, &tailR1, carry);
    }

    temp2 = temp2->prev;

    while (temp2 != NULL)
    {
        carry = 0;
        temp1 = *tail1;

        /* Add zeros for shifting */
        for (int i = 0; i <= count; i++)
        {
            insert_value(&headR2, &tailR2, 0);
        }

        while (temp1 != NULL)
        {
            result= (temp2->data * temp1->data) + carry;
            carry = result / 10;

            insert_value(&headR2, &tailR2, result % 10);
            temp1 = temp1->prev;
        }

        if (carry > 0)
        {
            insert_value(&headR2, &tailR2, carry);
        }

        count++;

        /* Add partial products */
        addition(&headR1, &tailR1,
                 &headR2, &tailR2,
                 &headR, &tailR);

        /* Delete old partial-product lists */
        free_list(&headR1, &tailR1);
        free_list(&headR2, &tailR2);

        /* Update headR1 and tailR1 */
        headR1 = headR;
        tailR1 = tailR;

        headR = NULL;
        tailR = NULL;

        temp2 = temp2->prev;
    }

    /* Store final result */
    *head3 = headR1;
    *tail3 = tailR1;

    return SUCCESS;
}