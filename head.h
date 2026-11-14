
#ifndef HEAD_H
#define HEAD_H

#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} FDLL;

extern FDLL *head1;
extern FDLL *tail1;
extern FDLL *head2;
extern FDLL *tail2;
extern FDLL *headR;
extern FDLL *tailR;

int insert_number(char *num, FDLL **head, FDLL **tail, int start);
int insert_value(FDLL **head, FDLL **tail, int num);
void print_list(FDLL *head);

int addition(FDLL **head1, FDLL **tail1,
             FDLL **head2, FDLL **tail2,
             FDLL **headR, FDLL **tailR);

int subtraction(FDLL **head1, FDLL **tail1,
                FDLL **head2, FDLL **tail2,
                FDLL **headR, FDLL **tailR);

int multiplication(FDLL **head1, FDLL **tail1,
                    FDLL **head2, FDLL **tail2,
                    FDLL **head3, FDLL **tail3);

int division(FDLL **head1, FDLL **tail1,
                FDLL **head2, FDLL **tail2, 
                FDLL **head3, FDLL **tail3);

int compare_num(FDLL *head1, FDLL *head2);
int swap_number(FDLL **head1, FDLL **tail1,
                FDLL **head2, FDLL **tail2);

void free_list(FDLL **head, FDLL **tail);


#endif
