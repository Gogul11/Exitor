#include "../types.h"
#include "../user.h"

#define CLIPBOARD_SIZE 1024

static char clipboard[CLIPBOARD_SIZE];

void copy(char* src,int start,int end) {
    if (!src) return;

  

    if(end<start){
        printf(1,"The start line is greater than end line!");
        return;
    }
    int i=0;
    int cnt=0;
    while(src[i]!='\0' && cnt<(start-1)){
        if(src[i++]=='\n')cnt++;
    }
    if(cnt!=start-1){
        printf(1,"The buffer does not contains such lines!!");
        return;
    }
    int j=0;
    while(src[i]!='\0' && cnt<end){
       clipboard[j++]=src[i];
       if(src[i]=='\n')cnt++;
       i++;
    }
    clipboard[j] = '\0';
    return;
}

char* paste() {
    return clipboard;
}
