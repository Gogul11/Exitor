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

    printf(1, " \033[0;31mEEEEE\033[0;m  \033[0;34mX   X\033[0;m  \033[0;31mIII\033[0;m  \033[0;34mTTTTT\033[0;m  \033[0;31mOOOO\033[0;m  \033[0;34mRRRR\033[0;m \n");
    printf(1, " \033[0;31mEE   \033[0;m  \033[0;34m X X \033[0;m  \033[0;31m I \033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mO  O\033[0;m  \033[0;34mR  R\033[0;m \n");
    printf(1, " \033[0;31mEEEE \033[0;m  \033[0;34m  X  \033[0;m  \033[0;31m I \033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mO  O\033[0;m  \033[0;34mRRRR\033[0;m \n");
    printf(1, " \033[0;31mEE   \033[0;m  \033[0;34m X X \033[0;m  \033[0;31m I \033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mO  O\033[0;m  \033[0;34mR R \033[0;m \n");
    printf(1, " \033[0;31mEEEEE\033[0;m  \033[0;34mX   X\033[0;m  \033[0;31mIII\033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mOOOO\033[0;m  \033[0;34mR  R\033[0;m \n");
}

int main()
{

    exitorPrint();
    sayHI();
    return 0;
}