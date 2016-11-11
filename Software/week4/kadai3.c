#include <stdio.h>
int main()
{
    char *firstname = "Yoshihiro";
    char lastname[9] = "Kawahara";
    printf("Name: %s %s\n", firstname, lastname);//when you take pointer as parameter of string, we dont need to add *.
    return 0;
}
