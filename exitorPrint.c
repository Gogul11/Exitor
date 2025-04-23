#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


void printChar(int count, char* c) {
    for (int i = 0; i < count; i++) {
        cprintf("%s", c);
    }
  }
  
  
  int
  sys_exitor(void){
    cprintf("\n\033[1;35m====================[ Welcome to ]====================\033[0m\n\n");
  
    printChar(8, " ");
    cprintf("\033[1;31mEEEEE \033[1;34mX   X \033[1;31mIII \033[1;34mTTTTT \033[1;31mOOOO \033[1;34mRRRR\033[0m\n");
    printChar(8, " ");
    cprintf("\033[1;31mEE    \033[1;34m X X  \033[1;31m I   \033[1;34m T   \033[1;31mO  O \033[1;34mR  R\033[0m\n");
    printChar(8, " ");
    cprintf("\033[1;31mEEEE  \033[1;34m  X   \033[1;31m I   \033[1;34m T   \033[1;31mO  O \033[1;34mRRRR\033[0m\n");
    printChar(8, " ");
    cprintf("\033[1;31mEE    \033[1;34m X X  \033[1;31m I   \033[1;34m T   \033[1;31mO  O \033[1;34mR R \033[0m\n");
    printChar(8, " ");
    cprintf("\033[1;31mEEEEE \033[1;34mX   X \033[1;31mIII \033[1;34m  T   \033[1;31mOOOO \033[1;34mR  R\033[0m\n");
  
    cprintf("\n\033[1;33m>> \033[0;32mExitor - A minimal VI-like text editor for xv6\033[0m\n\n");
  
    cprintf("\033[1;36mUsage:\033[0m exitor <filename>\n");
    cprintf("\033[1;36mModes:\033[0m\n");
    cprintf("  \033[1;35mInsert Mode\033[0m        - Press \033[1;34mi\033[0m\n");
    cprintf("  \033[1;35mCommand Mode\033[0m       - Press \033[1;34mESC\033[0m\n\n");
  
    cprintf("\033[1;36mCommands (in Command Mode):\033[0m\n");
    cprintf("  \033[1;33m:w\033[0m      - Save file\n");
    cprintf("  \033[1;33m:q\033[0m      - Quit without saving\n");
    cprintf("  \033[1;33m:wq\033[0m     - Save and quit\n");
  
    cprintf("\n\033[1;35m=======================================================\033[0m\n");  
    return;
  }