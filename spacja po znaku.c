#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int is_txt(char *name){
    int len = strlen(name);
    if(len >= 4 && strcmp(name + len - 4, ".txt")) return 1;
    return 0;
}

void convert_file(const char *input, const char *output){
    FILE* in = fopen(input, "rb");
    FILE* out = fopen(output, "wb");
    int c;
    while((c = fgetc(in)) != EOF){
    if(c == '.' || c == ',' || c == ':' || c == ';' || c == '?' || c == '!'){
            fputc(c, out);
            fputc(' ', out);
        } else{
            fputc(c, out);
        }
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        char *name = entry->d_name;
        if(is_txt(name)){
            char input[512], output[512];
            snprintf(input, sizeof(input), "%s%s", name);
            snprintf(output, sizeof(output), "%s%s.out", name);
            pid_t pid = fork();
            if(pid == 0){
                convert_file(input, output);
                exit(0);
            }
        }
    }
    closedir(dir);
    return 0;
}