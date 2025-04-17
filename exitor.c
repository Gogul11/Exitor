// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"

// #include "exitorBase/hi.c"

// #define O_TRUNC 0x200
// #define MAX_SIZE 5120
// char buffer[MAX_SIZE];

// void exitorPrint()
// {
//     printf(1, "\n");

//     printf(1, " \033[0;31mEEEEE\033[0;m  \033[0;34mX   X\033[0;m  \033[0;31mIII\033[0;m  \033[0;34mTTTTT\033[0;m  \033[0;31mOOOO\033[0;m  \033[0;34mRRRR\033[0;m \n");
//     printf(1, " \033[0;31mEE   \033[0;m  \033[0;34m X X \033[0;m  \033[0;31m I \033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mO  O\033[0;m  \033[0;34mR  R\033[0;m \n");
//     printf(1, " \033[0;31mEEEE \033[0;m  \033[0;34m  X  \033[0;m  \033[0;31m I \033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mO  O\033[0;m  \033[0;34mRRRR\033[0;m \n");
//     printf(1, " \033[0;31mEE   \033[0;m  \033[0;34m X X \033[0;m  \033[0;31m I \033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mO  O\033[0;m  \033[0;34mR R \033[0;m \n");
//     printf(1, " \033[0;31mEEEEE\033[0;m  \033[0;34mX   X\033[0;m  \033[0;31mIII\033[0;m  \033[0;34m  T  \033[0;m  \033[0;31mOOOO\033[0;m  \033[0;34mR  R\033[0;m \n");
// }

// int main()
// {

//     exitorPrint();
//     sayHI();
//     return 0;
// }
// 
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#include "exitorBase/hi.c"
#include "exitorBase/alloc.c"

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

void* xmalloc(uint nbytes);
void* xcalloc(uint num, uint size);
void* xrealloc(void* ptr, uint new_size);
void xfree(void*);

int main()
{
    exitorPrint();

    // --- xmalloc test ---
    int *arr_malloc = (int *)xmalloc(5 * sizeof(int)); 
    if (arr_malloc == 0) {
        printf(1, "Malloc failed!\n");
    } else {
        printf(1, "Malloc success!\n");
        for (int i = 0; i < 5; i++) {
            arr_malloc[i] = i + 1; 
            printf(1, "arr_malloc[%d] = %d\n", i, arr_malloc[i]);
        }
    }

    // --- xcalloc test ---
    int *arr_calloc = (int *)xcalloc(5, sizeof(int)); 
    if (arr_calloc == 0) {
        printf(1, "Calloc failed!\n");
    } else {
        printf(1, "Calloc success!\n");
        for (int i = 0; i < 5; i++) {
            printf(1, "arr_calloc[%d] = %d\n", i, arr_calloc[i]); 
        }
    }

    // --- xrealloc test ---
    int *arr_realloc = (int *)xmalloc(3 * sizeof(int));
    if (arr_realloc == 0) {
        printf(1, "Initial malloc for realloc test failed!\n");
    } else {
        for (int i = 0; i < 3; i++) {
            arr_realloc[i] = i + 10;
        }

        printf(1, "Before realloc:\n");
        for (int i = 0; i < 3; i++) {
            printf(1, "arr_realloc[%d] = %d\n", i, arr_realloc[i]);
        }

        arr_realloc = (int *)xrealloc(arr_realloc, 6 * sizeof(int));

        if (arr_realloc == 0) {
            printf(1, "xrealloc failed!\n");
        } else {
            for (int i = 3; i < 6; i++) {
                arr_realloc[i] = i + 10;
            }

            printf(1, "After realloc:\n");
            for (int i = 0; i < 6; i++) {
                printf(1, "arr_realloc[%d] = %d\n", i, arr_realloc[i]);
            }
        }
    }

    sayHI();
    exit();
}

