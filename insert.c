#include "head.h"
#include <stdio.h>
#include <string.h>

FDLL *head1 = NULL;
FDLL *tail1 = NULL;
FDLL *head2 = NULL;
FDLL *tail2 = NULL;
FDLL *headR = NULL;
FDLL *tailR = NULL;

int insert_number(char *num, FDLL **head, FDLL **tail, int start)
{
    for (int i = strlen(num) - 1; i >= start; i--)
    {
        if (insert_value(head, tail, num[i] - '0') == FAILURE)
        {
            printf("Memory allocation failed\n");
            free_list(head, tail);
            return FAILURE;
        }
    }
    return SUCCESS;
}

int insert_value(FDLL **head, FDLL **tail, int data)
{
    FDLL *new = malloc(sizeof(FDLL));

    if (new == NULL)
    {
        return FAILURE;
    }

    new->data = data;
    new->prev = NULL;

    if (*head == NULL)
    {
        new->next = NULL;
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    new->next = *head;
    (*head)->prev = new;
    *head = new;

    return SUCCESS;
}

void print_list(FDLL *head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

int compare_num(FDLL *head1, FDLL *head2)
{
    FDLL *temp1 = head1;
    FDLL *temp2 = head2;

    int len1 = 0;
    int len2 = 0;

    while (temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
            return 1;

        if (head1->data < head2->data)
            return -1;

        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}

int swap_number(FDLL **head1, FDLL **tail1,
                FDLL **head2, FDLL **tail2)
{
    FDLL *temp;

    temp = *head1;
    *head1 = *head2;
    *head2 = temp;

    temp = *tail1;
    *tail1 = *tail2;
    *tail2 = temp;

    return SUCCESS;
}

void free_list(FDLL **head, FDLL **tail)
{
    FDLL *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}