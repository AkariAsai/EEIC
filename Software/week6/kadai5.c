#include <stdio.h>
#include <math.h>

double newton(double x);
#define f(x) (x - 1) * (x - 2) // f(x)の定義
#define df(x) (2*x - 3)  // f'(x)の定義

int main() 
{
    // 初期値x0の設定
    double initial_value = -0.95;

    printf("x1 = %lf\n",newton(initial_value));
    // 別の初期値x0の設定
    initial_value = 3.0;
    printf("x2 = %lf\n",newton(initial_value));
    
    return 0;
}

double newton(double val) 
{
    double x1 = val - f(val) / df(val);
    
    if(fabs(x1 - val) < 0.0001) {
        return x1;
    } else {
        return newton(x1); //再帰呼び出し
    }
}
