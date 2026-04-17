#include "znaki.h"

char na_duza(char c){
    if(c >= 'a' && c <= 'z'){
        return c - 32;
    }
    return c;
}