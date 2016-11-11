#include <stdio.h>
int main()
{
    char *namelist[] = {"Kawahara", "Nakata", "Sakamoto", "Shinoda"};
    int i;
    for ( i = 0; i < 4; i++ ) {
    printf("Name: %s\n", namelist[i]);
    }
    return 0;
}
