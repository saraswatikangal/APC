#include "head.h"

int addition(FDLL **head1, FDLL **tail1,
             FDLL **head2, FDLL **tail2,
             FDLL **headR, FDLL **tailR)
{
    int sum, data1, data2;
    int carry = 0;

    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    FDLL *temp1 = *tail1;
    FDLL *temp2 = *tail2;

    while (temp1 != NULL || temp2 != NULL || carry != 0)
    {
        data1 = (temp1 != NULL) ? temp1->data : 0;
        data2 = (temp2 != NULL) ? temp2->data : 0;

        sum = data1 + data2 + carry;
        carry = sum / 10;
        sum = sum % 10;

        if (insert_value(headR, tailR, sum) == FAILURE)
            return FAILURE;

        if (temp1 != NULL)
            temp1 = temp1->prev;

        if (temp2 != NULL)
            temp2 = temp2->prev;
    }

    return SUCCESS;
}