#include <stdio.h>
#include<math.h>

#define IN        1
#define OUT       0
#define MAXLEN    25
#define MAXNWORD  23000

int  get_max( int array[], int N )
{
  int max_num = array[0];
  for (int i = 0; i < N; i++){
    if (array[i] > max_num){
      max_num = array[i];
    }
  }
  return max_num;
}

double  get_average( int array[], int N )
{
  double sum;
  for (int i = 0; i < N; i++){
    sum += array[i];
  }
  return sum/(double)N;
}

double  get_variance( int array[], int N )
{
  double average = get_average(array, N);
  double variance;
 
  for (int i = 0; i < N; i++){
    variance += pow(array[i] - average, 2);
  }
  return variance/(double)N;
}
void bubble_sort( int array[], int N )
{
}

int main()
{
  FILE *fp;
  fp=fopen("news.txt","r");
  int c, nl, nw, nc, state;
  int i, j;
  int word_initial, word_final, len;
  int word_length[MAXLEN];
  int numbers[MAXNWORD];

  for( i = 0 ; i < MAXLEN ; ++i ) {
    word_length[i] = 0;
  }
  for( i = 0 ; i < MAXNWORD ; ++i ) {

    numbers[i] = 0;
  }

  state = OUT;
  nl = nw = nc = 0;
  while( ( c = fgetc(fp) ) != EOF ) {
    ++nc;

    if( c == ' ' || c == '\n' || c == '\t' ) {
      if( state == IN ) {
	word_final = nc;
	len = word_final - word_initial;
	++word_length[len];

	numbers[nw] = (nl+1)*len;
	++nw;
      }
      state = OUT;
    }
    else if( state == OUT ) {
      state = IN;
      word_initial = nc;
    }

    if( c == '\n' ) {
      ++nl;
    }
  }

  printf( "#line = %d #word = %d #character = %d\n", nl, nw, nc );
  printf( "max = %d, avg = %.3f, var = %.3f\n", get_max( numbers, nw ),
	  get_average( numbers, nw ), get_variance( numbers, nw ) );
    
    fclose(fp);
    
  return 0;
}
