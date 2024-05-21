#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "set.h"
#define INITIAL_CAPACITY 5
#define UNDEFINED_SET "NULL"

int get_command(char *command);
int check_illegal_comma_command(char *command);
int get_single_set(char **possible_set_names, int len);
set *get_set_by_number(int number, set *SETA, set *SETB, set *SETC, set *SETD, set *SETE, set *SETF);
void print_set(set *s);
void get_multiple_sets(char **possible_set_names, int len, int *indexes);
int process_three_sets(int command_code, set *s1, set *s2, set *s3);
void skip_line();

int get_line(set *SETA, set *SETB, set *SETC, set *SETD, set *SETE, set *SETF)
{
    char word[100];
    int command_code = -1;
    char *possible_set_names[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
    int possible_set_names_length = 6;
    int set_index;
    int set_index_array[3];

    set *s1, *s2, *s3;
    scanf("%s", word);

    if (!strcmp(word, "stop"))
    {
        exit(1);
    }

    if (check_illegal_comma_command(word))
    {
        skip_line();
        return 0;
    }
    command_code = get_command(word);
    if (command_code == -1)
    {
        printf("Undefined command name\n");
        skip_line();
        return 0;
    }

    switch (command_code)
    {
    case READ_SET:
        set_index = get_single_set(possible_set_names, possible_set_names_length);
        s1 = get_set_by_number(set_index, SETA, SETB, SETC, SETD, SETE, SETF);
        if (s1 == NULL)
        {
            printf("Undefined set name\n");
            skip_line();
            return 0;
        }
        read_set(s1);
        return 1;
    case PRINT_SET:
        set_index = get_single_set(possible_set_names, possible_set_names_length);
        s1 = get_set_by_number(set_index, SETA, SETB, SETC, SETD, SETE, SETF);
        if (s1 == NULL)
        {
            printf("Undefined set name\n");
            skip_line();
            return 0;
        }
        print_set(s1);
        return 1;
    default:
        get_multiple_sets(possible_set_names, possible_set_names_length, set_index_array);
        if (set_index_array[0] == -1 || set_index_array[1] == -1 || set_index_array[2] == -1)
        {
            printf("Multiple consecutive commas\n");
            return 0;
        }

        s1 = get_set_by_number(set_index_array[0], SETA, SETB, SETC, SETD, SETE, SETF);
        s2 = get_set_by_number(set_index_array[1], SETA, SETB, SETC, SETD, SETE, SETF);
        s3 = get_set_by_number(set_index_array[2], SETA, SETB, SETC, SETD, SETE, SETF);

        if (s1 == NULL || s2 == NULL || s3 == NULL)
        {
            printf("Missing parameter\n");
            return 0;
        }

        process_three_sets(command_code, s1, s2, s3);

        return 1;
    }
}

int get_numbers(int *numbers, int *size)
{
    char num[4];
    int i = 0;
    int input_number_count = 0;
    char c;
    int actual_number;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
        if (c == ',')
        {
            i = 0;
            if (strlen(num) == 0)
            {
                printf("Multiple consecutive commas\n");
                continue;
            }

            actual_number = atoi(num);
            /*Negative number in the middle*/
            if (actual_number < 0 || actual_number > 127)
            {
                printf("Invalid set member – value out of range\n");
                skip_line();
                return 0;
            }

            memset(num, '\0', sizeof(num));

            if (input_number_count >= *size / sizeof(int))
            {
                *size *= 2;
                numbers = realloc(numbers, *size);
                if (numbers == NULL)
                {
                    exit(0);
                }
            }
            numbers[input_number_count++] = actual_number;
            continue;
        }
        if (c == ' ' || c == '\n')
        {
            continue;
        }
        if (c > '9' || c == '.')
        {
            printf("Invalid set member — not an integer\n");
            skip_line();
            return 0;
        }

        num[i++] = c;
    }

    actual_number = atoi(num);
    /*Check if last item is -1*/
    if (actual_number != -1)
    {
        printf("List of set members is not terminated correctly\n");
        return 0;
    }
    return input_number_count;
}

void reset_set(set *s)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        (*s)[i] = 0;
    }
}

void add_number_to_set(set *s, int number)
{
    int index = number / 8;
    int bit = 7 - number % 8;
    (*s)[index] |= 1 << bit;
}

void add_numbers_to_set(set *s, int *numbers, int numbers_count)
{
    int i;
    for (i = 0; i < numbers_count; i++)
    {
        add_number_to_set(s, numbers[i]);
    }
}

void print_set(set *s)
{
    int i, j;
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((*s)[i] & (1 << (7 - j)))
            {
                printf("%d ", i * 8 + j);
            }
        }
    }
    printf("\n");
}

void read_set(set *s)
{
    int size = INITIAL_CAPACITY * sizeof(int);
    int *numbers = malloc(size);
    int numbers_count;

    if (numbers == NULL)
    {
        exit(0);
    }

    numbers_count = get_numbers(numbers, &size);
    reset_set(s);
    add_numbers_to_set(s, numbers, numbers_count);
    free(numbers);
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
    while ((c = getchar()) != EOF && c != ',' && i < 4)
    {
        if (c != ' ' && c != '\n')
        {
            set_name[i++] = c;
        }
    }
    if (i < 4)
    {
        return -1;
    }

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

void union_set(set *s1, set *s2, set *s3)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        (*s3)[i] = (*s1)[i] | (*s2)[i];
    }
}

void intersect_set(set *s1, set *s2, set *s3)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        (*s3)[i] = (*s1)[i] & (*s2)[i];
    }
}

void sub_set(set *s1, set *s2, set *s3)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        (*s3)[i] = (*s1)[i] & ~(*s2)[i];
    }
}

void symdiff_set(set *s1, set *s2, set *s3)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        (*s3)[i] = (*s1)[i] ^ (*s2)[i];
    }
}

int process_three_sets(int command_code, set *s1, set *s2, set *s3)
{

    switch (command_code)
    {
    case UNION_SET:
        union_set(s1, s2, s3);
        return 1;
    case INTERSECT_SET:
        intersect_set(s1, s2, s3);
        return 1;
    case SUB_SET:
        sub_set(s1, s2, s3);
        return 1;
    case SYMDIFF_SET:
        symdiff_set(s1, s2, s3);
        return 1;
    default:
        printf("Undefined command\n");
        return 1;
    }
}

void get_multiple_sets(char **possible_set_names, int len, int *indexes)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        indexes[i] = get_single_set(possible_set_names, len);
    }
}

void skip_line()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}