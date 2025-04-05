#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#include "exitorBase/hi.c"

#define O_TRUNC 0x200
#define MAX_SIZE 5120
char buffer[MAX_SIZE];

void exitorPrint()
{
    printf(1, "\n");

    printf(1, " EEEEE  X   X  III  TTTTT  OOOO  RRRR \n");
    printf(1, " EE      X X    I     T    O  O  R  R \n");
    printf(1, " EEEE     X     I     T    O  O  RRRR \n");
    printf(1, " EE      X X    I     T    O  O  R R  \n");
    printf(1, " EEEEE  X   X  III    T    OOOO  R  R \n");
}

int main()
{

    exitorPrint();
    sayHI();
    return 0;
}
