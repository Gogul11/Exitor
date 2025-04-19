#include "../types.h"
#include "../fcntl.h"
#include "../user.h"
#include "copyPaste.c"

enum mode { COMMAND, INSERT };
enum mode current_mode = COMMAND;


void ReadAndWrite(char *fileName) {
    int fd = open(fileName, O_RDWR | O_CREATE);
    if (fd < 0) {
        printf(1, "Error opening file\n");
        exit();
    }

    // // Read existing content
    // char buff[2048];
    uint capacity = 8;
    char *buff = (char*) xmalloc(capacity);
    if(!buff){
        printf(1, "Memory Allocation failed!\n");
        exit();
    }

    int ind = 0;
    int bytes;
    while ((bytes = read(fd, buff+ind, capacity-ind)) > 0)
    {
        ind += bytes;
        if(ind == capacity){
            capacity *= 2;
            char *temp_buff = (char *)xrealloc(buff, capacity);
            if(!temp_buff){
                printf(1, "Memory Allocation failed!\n");
                xfree(buff);
                exit();
            }
            buff = temp_buff;
        }
    }
    
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

    int insert_index = ind;
    
    char ch;
    while (1) {
        if (current_mode == COMMAND) {
            printf(1, "\033[999;1H");  
            printf(1, "\033[2K");
            printf(1, "Enter the commands that starts with (:) ");
            if (read(0, &ch, 1) > 0) {
                if (ch == 'i') {
                    current_mode = INSERT;
                    clear();
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
                        int f1 = open(fileName, O_WRONLY | O_CREATE);
                        write(f1, buff, insert_index);
                        close(f1);
                        break;
                    } else if (len >= 1 && cmd[0] == 'w') {
                        int f2 = open(fileName, O_WRONLY | O_CREATE);
                        write(f2, buff, insert_index);
                        close(f2);    
                    }
                    else if (len >= 1 && cmd[0] == 'q') {
                        break;
                    }
                    else if(len >= 1 && cmd[0] == 'y'){
                        // char temp[8];
                        // int start, end;
                        // read(0, temp, sizeof(temp));
                        // start = atoi(temp);

                        // read(0, temp, sizeof(temp));
                        // end = atoi(temp);

                        // copy(buff, start+1, end+1);
                    }
                    else if(len >=1 && cmd[0] == 'p'){
                        // char *clip = paste();
                        // if (!clip || clip[0] == '\0') {
                        //     printf(1, "Clipboard is empty!\n");
                        //     continue;
                        // }
                        // int clip_len = 0;
                        // while(clip[clip_len] != '\0') clip_len++;

                        // for(int i = 0; i < clip_len; i++){
                        //     buff[insert_index++] = clip[i];
                        // }

                        // clear();
                        // printf(1, "\n\033[1;32m-- COMMAND MODE --\033[0m\n");
                        // int cl = 1;
                        // for (int i = 0; i < insert_index; i++) {
                        //     printf(1, "%c", buff[i]);
                        //     if (buff[i] == '\n') {
                        //         printf(1, "%d\t", cl);
                        //         cl++;
                        //     }
                        // }

                    }
                    else{
                        
                    }
                }
            }
        } else if (current_mode == INSERT) {
            if (read(0, &ch, 1) > 0) {
                if (ch == 27) { 
                    current_mode = COMMAND;
                    clear();
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
                    if (insert_index >= capacity) {
                        capacity *= 2;
                        char *new_buff = (char *)xrealloc(buff, capacity);
                        if (!new_buff) {
                            printf(1, "Reallocation failed!\n");
                            xfree(buff);
                            exit();
                        }
                        buff = new_buff;
                    }
                    
                    buff[insert_index++] = ch;
                    
                    if (ch == '\n') {
                        printf(1, "%d\t", line);
                        line++;
                    }
                }
            }
        }
    }

    xfree(buff);
    close(fd);
    clear();
    exit();
}
