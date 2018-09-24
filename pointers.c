


#include <stdio.h>

char * text1 = "This is a string.";
char * text2 = "Yet another thing.";

int list1[80];
int list2[80];
int count = 0;

void printlist(const int* lst){
    printf("ASCII codes and corresponding characters.\n");
    while(*lst != 0){
        printf("0x%03X '%c' ", *lst, (char)*lst);
        lst++;
    }
    printf("\n");
}

void endian_proof(const char* c){
    printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
           (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
}

void copycodes(char *a, int *b, int *c){
    while(1){
        char x = *a;    // lb    $t0,0($a0)
        if(x == 0) {    // beq   $t0,$0,done
            return;
        }
        *b = x;         // sw    $t0,0($a1)

        a = a+1;        // addi  $a0,$a0,1
        b = b+1;        // addi  $a1,$a1,4

        int y = *c;     // lw    $t1,0($a2)
        y = y+1;        // addi  $t1,$t1,1
        *c = y;         // sw    $t1,0($a2)
    }
}

void work(){
    char *a = text1;        // la    $a0,text1
    int *b = &list1[0];     // la    $a1,list1
    int *c = &count;        // la    $a2,count
    copycodes(a, b, c);     // jal    copycodes

    a = text2;          // la    $a0,text2
    b = &list2[0];      // la    $a1,list2
    c = &count;         // la    $a2,count
    copycodes(a, b, c); // jal    copycodes
}

int main(void){
    work();

    printf("\nlist1: ");
    printlist(list1);
    printf("\nlist2: ");
    printlist(list2);
    printf("\nCount = %d\n", count);

    endian_proof((char*) &count);
}
