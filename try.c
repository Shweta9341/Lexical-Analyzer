#include <stdio.h>
#define PI 3.14
 
int main() {
    // Variable declarations
    int 1num = 40;
    int a = 10, b = 20;
    float c = 15.5, area;
    char grade = 'A';
    const int LIMIT = 100;
 
    // Arithmetic operations
    area = a  b + (int)c / 2 - 5;
 
    // Relational & logical operators
    if ((a < b) && (c >= 10.0)) {
        printf("a is less than b and c is valid\n");
    }
    // Loop test
    for (int i = 0; i < 5; i++) {
        area += i;
    }
 
    // While loop test
    while (a < LIMIT) {
        a++;
    }
 
    // Do-while loop
    do {
        b--;
    } while (b > 10);
 
}
