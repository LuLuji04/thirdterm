#include <stdio.h>
int main() {
    long int num, b=1;
    scanf("%d", &num);
    while (1) {

        if (num > b) {
            b *= 8;
            continue;
        }
        b /= 8;
        if (b == 0) {
            break;
        }
        printf("%ld", num/b);
        num %= b;
    }
}
