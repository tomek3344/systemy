#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

const char *slowa[] = {
    "zero", "jeden", "dwa", "trzy", "cztery",
    "piec", "szesc", "siedem", "osiem", "dziewiec"
};

int is_txt(char *name){
    int len = strlen(name);
    return (len >= 4 && strcmp(name + len - 4, ".txt") == 0);
}

void convert_file(char *filename){
    FILE *in = fopen(filename, "r");
    FILE *out = fopen("tmp.txt", "w");

    if (!in || !out){
        perror("fopen");
        exit(1);
    }

    int c;
    while ((c = fgetc(in)) != EOF){
        if (c >= '0' && c <= '9'){
            fprintf(out, "%s", slowa[c - '0']);
        } else {
            fputc(c, out);
        }
    }
    fclose(in);
    fclose(out);
    remove(filename);
    rename("tmp.txt", filename);
}

int main()
{
    struct dirent *plik;
    DIR *sciezka = opendir(".");
    if (!sciezka){
        perror("opendir");
        return 1;
    }
    while ((plik = readdir(sciezka)) != NULL){
        if (is_txt(plik->d_name)){
            pid_t pid = fork();
            if (pid == 0){
                convert_file(plik->d_name);
                exit(0);
            }
        }
    }
    closedir(sciezka);
    while (wait(NULL) > 0);
    return 0;
}