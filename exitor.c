#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#include "exitorBase/rw.c"


int main(int argc, char *argv[])
{
    clear();
    exitor();
    if (argc == 2)
        ReadAndWrite(argv[1]);
    exit();
}
