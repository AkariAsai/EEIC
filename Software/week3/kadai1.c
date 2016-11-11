#include<stdio.h>

/*prints num!! if a number is including digit 4 like 33, 3, 103...etc, or can be divided into three.
It keeps printing until it reaches 1000.
The output shoud be
1
2
3!!!
4
5
*/

int is_three_included(int n);
int main() {
  for (int i = 1; i < 1000; i++){
    if (i % 3 == 0 || is_three_included(i)) {
      //後述のis_three_included関数が1を返すもしくは3で割り切れる時
      printf("%d!!!\n", i);
    } else {
      printf("%d\n", i);
    }
  }
  return 0;
}

/*この関数がある数字が３を含んでいないかいるかを判断します。
以下の関数で実行しているのはある数字nについて（nのケタ数は何桁でもよい）、
1.10であったあまりが３になるかどうかを確認する（例えば、103なら103 %  3 == 0よりtrueとなります。）
2.余りが３となるなら（＝３を桁の中に含んでいるなら）return 1(return true)を返す。
3.そうでなければnを１０でわると、101 / 10 = 10のように、元の数字から一番小さな桁の数を消した数字となる
4.これに対し同様に3で割り切れるかどうか確認する。
というのをnが０より大きい（すなわち桁の数字がまだ存在する）間続けています。

e.g. n = 1245
1345 % 10 = 5-> not 0
1345 // 10 = 134
134 % 10 = 4 -> not 0
134 // 10 = 13
13 % 10 = 3 -> return 1
*/
int is_three_included(int n){
  while (n > 0){
    if (n % 10 == 3){
      return 1;
    }
    n = n / 10;
  }
  return 0;
}
