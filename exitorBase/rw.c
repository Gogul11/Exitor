#include "../types.h"
#include "../fcntl.h"
#include "../user.h"

enum mode { COMMAND, INSERT };
enum mode current_mode = COMMAND;

void clearScreen(){
    printf(1, "\033[2J");
    printf(1, "\033[H");
}

void ReadAndWrite(char *fileName) {
    int fd = open(fileName, O_RDWR | O_CREATE);
    if (fd < 0) {
        printf(1, "Error opening file\n");
        exit();
    }

    // Read existing content
    char buff[2048];
    int ind = read(fd, buff, sizeof(buff));
    int line = 1;

    printf(1, "\n\033[1;32mExitor - COMMAND MODE\033[0m\n");
    // printf(1, "%d\t", line);


    for (int i = 0; i < ind; i++) {
        printf(1, "%c", buff[i]);
        if (buff[i] == '\n') {
            printf(1, "%d\t", line);
            line++;
        }
    }

    char ch;
    int insert_index = ind;

    while (1) {
        if (current_mode == COMMAND) {
            if (read(0, &ch, 1) > 0) {
                if (ch == 'i') {
                    current_mode = INSERT;
                    clearScreen();
                    printf(1, "\n\033[1;34m-- INSERT MODE --\033[0m\n");
                    int il = 1;
                    // printf(1, "%d\t", il);

                    for (int i = 0; i < insert_index; i++) {
                        printf(1, "%c", buff[i]);
                        if (buff[i] == '\n') {
                            printf(1, "%d\t", il);
                            il++;
                        }
                    }
                    printf(1, "\n");
                } else if (ch == ':') {
                    char cmd[4] = {0};
                    int len = read(0, cmd, sizeof(cmd));

                    if (len >= 2 && cmd[0] == 'w' && cmd[1] == 'q') {
                        fd = open(fileName, O_WRONLY | O_CREATE);
                        write(fd, buff, insert_index);
                        close(fd);
                        break;
                    } else if (len >= 1 && cmd[0] == 'w') {
                        fd = open(fileName, O_WRONLY | O_CREATE);
                        write(fd, buff, insert_index);
                        close(fd);
                        printf(1, "\n\033[1;32mFile saved.\033[0m\n");
                        
                        current_mode = INSERT;
                        clearScreen();
                        printf(1, "\n\033[1;34m-- INSERT MODE --\033[0m\n");
                    
                        int il = 1;
                        for (int i = 0; i < insert_index; i++) {
                            printf(1, "%c", buff[i]);
                            if (buff[i] == '\n') {
                                printf(1, "%d\t", il++);
                            }
                        }
                    }
                    else if (len >= 1 && cmd[0] == 'q') {
                        printf(1, "BYE!\n");
                        break;
                    }
                    else{
                        
                    }
                }
            }
        } else if (current_mode == INSERT) {
            if (read(0, &ch, 1) > 0) {
                if (ch == 27) { 
                    current_mode = COMMAND;
                    clearScreen();
                    printf(1, "\n\033[1;32m-- COMMAND MODE --\033[0m\n");
                    int cl = 1;
                    for (int i = 0; i < insert_index; i++) {
                        printf(1, "%c", buff[i]);
                        if (buff[i] == '\n') {
                            printf(1, "%d\t", cl);
                            cl++;
                        }
                    }
                
                } else {
                    if (insert_index < sizeof(buff)) {
                        buff[insert_index++] = ch;
                        if (ch == '\n') {
                            printf(1, "%d\t", line);
                            line++;
                        }
                    }
                }
            }
        }
    }

    close(fd);
    exit();
}
