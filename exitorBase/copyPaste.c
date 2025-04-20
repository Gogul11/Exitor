// #include "../types.h"
// #include "../user.h"

// #define CLIPBOARD_SIZE 1024

// static char clipboard[CLIPBOARD_SIZE];


// void copy(char* src, int start, int end) {
//     if (!src || start < 1 || end < start) return;
    
//     // Reset clipboard before copying
//     memset(clipboard, 0, CLIPBOARD_SIZE);
    
//     int i = 0;
//     int cnt = 1; // Line numbers start at 1
//     int j = 0;
    
//     // Find start line
//     while (src[i] && cnt < start) {
//         if (src[i] == '\n') cnt++;
//         i++;
//     }
    
//     // Copy until end line or buffer full
//     while (src[i] && cnt <= end && j < CLIPBOARD_SIZE - 1) {
//         clipboard[j++] = src[i++];
//         if (src[i-1] == '\n') cnt++;
//     }
    
//     clipboard[j] = '\0'; // Ensure null termination
// }

// char* paste() {
//     return clipboard;
// }
