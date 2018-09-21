
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLUMNS 6
int nCols = COLUMNS; // init counter to keep track of cols in print_number

void print_number(int n){
    printf("%10d", n);
    nCols--;

    if(nCols == 0) {
        nCols = COLUMNS;
        printf("\n");
    }
}

void print_sieves(int n){
    // Should print out all prime numbers less than 'n'
    // with the following formatting. Note that
    // the number of columns is stated in the define
    // COLUMNS

    int a[n]; // init array with indices 0 -> n
    for(int i = 0; i < n ; i++){  //fill array with 1
        a[i] = 1;
    }
    for(int i = 2; i*i <= n; i++){ //start at 2, increment i until it equals the sqrt of n
        if(a[i-1] == 1) { //if i-1 = 1 then i is prime
            for(int j=i*2; j<=n; j+=i){ //start filling zeros for the lowest i multiple, then increment with i.
                a[j-1]=0;
            }
        }
    }

    for(int i = 1; i < n; i++){
        if(a[i] == 1) {
            print_number(i+1); //indices are shifted left 1
        }
    }

    printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    if(argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}
