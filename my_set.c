#include <stdio.h>
#include "set.h"

int main()
{
    set SETA, SETB, SETC, SETD, SETE, SETF;

    reset_set(&SETA);
    reset_set(&SETB);
    reset_set(&SETC);
    reset_set(&SETD);
    reset_set(&SETE);
    reset_set(&SETF);


while(1){

    get_line(&SETA, &SETB, &SETC, &SETD, &SETE, &SETF);

}

    return 0;
}
