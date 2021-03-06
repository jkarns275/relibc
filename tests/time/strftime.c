#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print(time_t timestamp, char* fmt) {
    char* out = malloc(50);
    size_t n = strftime(out, 50, fmt, localtime(&timestamp));
    printf("%zu: %s\n", n, out);
    free(out);
}
int main() {
    print(1531808742, "%a %A %b %B");
    print(1531808742, "The %Cst century");
    print(1531808742, "%I:%M:%S %p");
    print(1531839600, "%r");
    print(1531839600, "%R");
    print(1531839600, "%H %s %u");
    print(1531839600, "%j %U");
    print(1531839600, "%+");
}
