#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void convert_to_null_terminated(char* ibuffer, char* obuffer, int start, int end) {
    int i = start;
    int j = 0;
    while (i <= end) {
        obuffer[j++] = ibuffer[i++];
    }
    obuffer[j] = '\0';
};

int main(){

    const char *filename = "input.txt";
    FILE* file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(fileSize);
    fread(buffer, 1, fileSize, file);
    fclose(file);

    // printf("File size: %ld bytes\n", fileSize);

    char* tempbuffer = (char*)malloc(256);
    bool consumed = false;

    char direction;

    int32_t startPos = 50;
    uint32_t ans = 0;

    int index = 0;
    int rindex = 0;
    while(index <= fileSize) {

        if (buffer[index] == 'L' || buffer[index] == 'R') {
            consumed = true;
            direction = buffer[index];
            rindex = index + 1;
        } else {
            if (buffer[index] == '\n') {
                convert_to_null_terminated(buffer, tempbuffer, rindex, index);
                // printf("index:%d\n", index);
                // printf("rindex:%d\n", rindex);
                int num = atoi(tempbuffer);
                // printf("Direction: %c, Number: %d\n", direction, num);

                if (direction == 'L') {
                    if (num > startPos) {
                        startPos = (100 - (num - startPos)) % 100;
                    } else {
                        startPos = (startPos - num) % 100;
                    }
                } else {
                    startPos = (startPos + num) % 100;
                }

                if (startPos == 0) {
                    ans++;
                }
            }
        }
        index++;
    }


    printf("answer: %u\n", ans);
    return 0;
}
