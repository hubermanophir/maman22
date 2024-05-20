typedef unsigned char set[16];

void read_set(set *s);

void print_set(set *s);

void union_set(set *s1, set *s2, set *s3);

void intersect_set(set *s1, set *s2, set *s3);

void sub_set(set *s1, set *s2, set *s3);

void symdiff_set(set *s1, set *s2, set *s3);

int get_line(set *SETA, set *SETB, set *SETC, set *SETD, set *SETE, set *SETF);

#define READ_SET 1
#define PRINT_SET 2
#define UNION_SET 3
#define INTERSECT_SET 4
#define SUB_SET 5
#define SYMDIFF_SET 6

#define NUM_SETA 0
#define NUM_SETB 1
#define NUM_SETC 2
#define NUM_SETD 3
#define NUM_SETE 4
#define NUM_SETF 5
