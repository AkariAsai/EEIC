#include <stdio.h>
#include<string.h>

int is_kaibun(char str[]);

int main () {
    char s[] = "151";
    if (is_kaibun(s)){
        printf("%s string is kaibnu.\n", s);
    } else {
        printf("%s string is not kaibun.\n", s);
    }
    return 0;
}

int is_kaibun(char str[]){
    for (int i = 0; i < strlen(str)/2; i ++){
        if (str[i] != str[strlen(str) - i - 1]){
            return 0;
        }
    }
    return 1;
}
