#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char znak = '0';

void obslSyg(int nrSyg)
{
    printf("Odebrano sygnał o numerze %d.\n", nrSyg);
    switch (znak) {
        case '0': printf("zero\n"); break;
        case '1': printf("jeden\n"); break;
        case '2': printf("dwa\n"); break;
        case '3': printf("trzy\n"); break;
        case '4': printf("cztery\n"); break;
        case '5': printf("piec\n"); break;
        case '6': printf("szesc\n"); break;
        case '7': printf("siedem\n"); break;
        case '8': printf("osiem\n"); break;
        case '9': printf("dziewiec\n"); break;
    }

    exit(0);
}

int main()
{
    printf("Rozpoczęto proces %d\n", getpid());
    
    pid_t pid = fork();
    if (pid == 0){
        signal(SIGINT, obslSyg);
        while(1){
            sleep(1);
            if(znak < '9'){
                znak++;
            } else{
                znak = '0';
            }
        }
    return 0;
    }
}