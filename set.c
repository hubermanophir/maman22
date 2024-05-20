#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "set.h"
#define INITIAL_CAPACITY 5
#define UNDEFINED_SET "NULL"

int get_command(char *command);
int process_three_sets(int command_code);
int check_illegal_comma_command(char *command);
int get_single_set(char **possible_set_names, int len);
set *get_set_by_number(int number, set *SETA, set *SETB, set *SETC, set *SETD, set *SETE, set *SETF);

int get_line(set *SETA, set *SETB, set *SETC, set *SETD, set *SETE, set *SETF)
{
    char word[20];
    int command_code = -1;
    char *possible_set_names[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
    int possible_set_names_length = 6;
    int set_index;
    scanf("%s", word);

    if (!strcmp(word, "stop"))
    {
        printf("Exiting\n");
        return 1;
    }

    if (check_illegal_comma_command(word))
    {
        return 0;
    }
    command_code = get_command(word);
    if (command_code == -1)
    {
        printf("Invalid command\n");
        return 0;
    }

    switch (command_code)
    {
    case READ_SET:
        set_index = get_single_set(possible_set_names, possible_set_names_length);
        read_set(get_set_by_number(set_index, SETA, SETB, SETC, SETD, SETE, SETF));
        return 1;
    case PRINT_SET:
        set_index = get_single_set(possible_set_names, possible_set_names_length);
        return 1;
    default:
        return 1;
    }
}

/*add check for , to be equal to the number count*/

void get_numbers(int *numbers, int *size)
{
    char num[3];
    int i = 0;
    int input_number_count = 0;
    char c;
    int actual_number;
    int j;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
        if (c == ',')
        {
            actual_number = atoi(num);
            /*Negative number in the middle*/

            if (actual_number < 0)
            {
                printf("Invalid set member – value out of range\n");
            }

            memset(num, '\0', sizeof(num));
            i = 0;
            if (input_number_count >= *size / sizeof(int))
            {
                *size *= 2;
                numbers = realloc(numbers, *size);
            }
            numbers[input_number_count++] = actual_number;
            continue;
        }
        if (c == ' ')
        {
            continue;
        }
        num[i++] = c;
    }

    actual_number = atoi(num);

    /*Check if last item is -1*/
    if (actual_number != -1)
    {
        printf("List of set members is not terminated correctly\n");
    }

    printf("Numbers: ");
    for (j = 0; j < input_number_count; j++)
    {
        printf("%d ", numbers[j]);
    }
    printf("\n");
}

void read_set(set *s)
{
    int size = INITIAL_CAPACITY * sizeof(int);
    int *numbers = malloc(size);
    get_numbers(numbers, &size);
}

int get_set_index(char *name, char **possible_set_names, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (!strcmp(name, possible_set_names[i]))
        {
            return i;
        }
    }
    return -1;
}

int get_single_set(char **possible_set_names, int len)
{
    char set_name[4];
    int i = 0;
    char c;
    while ((c = getchar()) != EOF && c != ',')
    {
        if (c != ' ')
        {
            set_name[i++] = c;
        }
    }
    printf("Set name: %s\n", set_name);
    i = get_set_index(set_name, possible_set_names, len);
    return i;
}

set *get_set_by_number(int number, set *SETA, set *SETB, set *SETC, set *SETD, set *SETE, set *SETF)
{
    switch (number)
    {
    case NUM_SETA:
        return SETA;
    case NUM_SETB:
        return SETB;
    case NUM_SETC:
        return SETC;
    case NUM_SETD:
        return SETD;
    case NUM_SETE:
        return SETE;
    case NUM_SETF:
        return SETF;
    default:
        printf("Invalid set number\n");
        return NULL;
    }
}

int get_command(char *command)
{
    if (!strcmp(command, "read_set"))
    {
        return READ_SET;
    }
    else if (!strcmp(command, "print_set"))
    {
        return PRINT_SET;
    }
    else if (!strcmp(command, "union_set"))
    {
        return UNION_SET;
    }
    else if (!strcmp(command, "intersect_set"))
    {
        return INTERSECT_SET;
    }
    else if (!strcmp(command, "sub_set"))
    {
        return SUB_SET;
    }
    else if (!strcmp(command, "symdiff_set"))
    {
        return SYMDIFF_SET;
    }
    else
    {
        return -1;
    }
}

int check_illegal_comma_command(char *command)
{
    int i = 0;
    int command_length = strlen(command);
    for (i = 0; i < command_length; i++)
    {
        if (command[i] == ',')
        {
            printf("Illegal comma\n");
            return 1;
        }
    }
    return 0;
}