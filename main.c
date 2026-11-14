#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "head.h"

int validate_input(char *str)
{
    int i = 0;

    if (str[i] == '+' || str[i] == '-')
    {
        i++;
    }

    if (str[i] == '\0')
    {
        return FAILURE;
    }

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return FAILURE;
        }
        i++;
    }

    return SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("ERROR: Invalid input\n");
        printf("INFO: please give the command line arguments -> <num1> <operator> <num2>\n");
        return FAILURE;
    }

    char *num1 = argv[1];
    char *num2 = argv[3];

    if (validate_input(num1) == FAILURE ||
    validate_input(num2) == FAILURE)
    {
        printf("ERROR: Invalid input\n");
        return FAILURE;
    }

    int sign1, sign2;
    int start1, start2;
    int negative = 0;

    if (num1[0] == '-')
    {
        sign1 = -1;
        start1 = 1;
    }
    else if (num1[0] == '+')
    {
        sign1 = 1;
        start1 = 1;
    }
    else
    {
        sign1 = 1;
        start1 = 0;
    }

    if (num2[0] == '-')
    {
        sign2 = -1;
        start2 = 1;
    }
    else if (num2[0] == '+')
    {
        sign2 = 1;
        start2 = 1;
    }
    else
    {
        sign2 = 1;
        start2 = 0;
    }

    insert_number(num1, &head1, &tail1, start1);
    insert_number(num2, &head2, &tail2, start2);

    switch (*argv[2])
    {
        case '+':
            printf("Addition started\n");
            printf("Num1:\t");
            if (sign1 == -1) printf("-");
            print_list(head1);

            printf("Num2:\t");
            if (sign2 == -1) printf("-");
            print_list(head2);

            if (sign1 == sign2)
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                negative = (sign1 == -1);
            }
            else
            {
                int cmp = compare_num(head1, head2);

                if (cmp == 0)
                {
                    insert_value(&headR, &tailR, 0);
                    negative = 0;
                }
                else if (cmp > 0)
                {
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                    negative = (sign1 == -1);
                }
                else
                {
                    swap_number(&head1, &tail1, &head2, &tail2);
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                    negative = (sign2 == -1);
                }
            }

            printf("Result:\t");
            if (negative && !(headR == tailR && headR->data == 0))
                printf("-");
            print_list(headR);
            printf("INFO: Addition Successfully Done\n");
            break;

        case '-':
            printf("Substraction started\n");
            printf("Num1:\t");
            if (sign1 == -1) printf("-");
            print_list(head1);

            printf("Num2:\t");
            if (sign2 == -1) printf("-");
            print_list(head2);

            sign2 = -sign2;

            if (sign1 == sign2)
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                negative = (sign1 == -1);
            }
            else
            {
                int cmp = compare_num(head1, head2);

                if (cmp == 0)
                {
                    insert_value(&headR, &tailR, 0);
                    negative = 0;
                }
                else if (cmp > 0)
                {
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                    negative = (sign1 == -1);
                }
                else
                {
                    swap_number(&head1, &tail1, &head2, &tail2);
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                    negative = (sign2 == -1);
                }
            }

            printf("Result:\t");
            if (negative && !(headR == tailR && headR->data == 0))
                printf("-");
            print_list(headR);
            printf("INFO: Substraction Successfully Done\n");
            break;
        
        case '*':
        case 'X':
        case 'x':
            printf("Multiplication started\n");
            printf("Num1:\t");
            if (sign1 == -1) printf("-");
            print_list(head1);

            printf("Num2:\t");
            if (sign2 == -1) printf("-");
            print_list(head2);

            if (multiplication(&head1, &tail1,
                               &head2, &tail2,
                               &headR, &tailR) == SUCCESS)
            {
                printf("Result:\t");

                if (sign1 * sign2 == -1 &&
                    !(headR->data == 0 && headR->next == NULL))
                    printf("-");

                print_list(headR);
                printf("INFO: multiplication Successfully Done\n");
            }
            break;

        case '/':
            printf("Num1: ");
            if (sign1 == -1) printf("-");
            print_list(head1);

            printf("Num2: ");
            if (sign2 == -1) printf("-");
            print_list(head2);

            if (division(&head1, &tail1, &head2, &tail2,
                         &headR, &tailR) == SUCCESS)
            {
                printf("Result: ");

                if (sign1 * sign2 == -1 &&
                    !(headR->data == 0 && headR->next == NULL))
                    printf("-");

                print_list(headR);
                printf("INFO: Division Successfully Done\n");
            }
            break;

        default:
            printf("Enter the proper input\n");
            break;
    }

    return SUCCESS;
}