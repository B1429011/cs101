#include <stdio.h>
void print_sp(int i, int n) {
    for (int sp = 0; sp < n-i;sp++) {
        printf(" ");
    }
}

void print_num(int i) {
    for (int j = 0; j < i;j++) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int rows = 6;
    for (int i =0; i<= rows; i++) {
        print_sp(i, rows);
        print_num(i);
    }
    return 0;
}
