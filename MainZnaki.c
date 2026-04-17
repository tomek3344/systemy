#include <stdio.h>
#include "znaki.h"

int main()
{
    char napis[] = "DUZE i male LiTeRy. 12345";

    for(int i = 0; napis[i] != '\0'; i++){
        napis[i] = na_duza(napis[i]);
    }

    printf("%s\n", napis);

    return 0;
}