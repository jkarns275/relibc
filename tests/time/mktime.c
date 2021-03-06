#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check(time_t input) {
    struct tm* t = localtime(&input);

    printf("%ld = %ld\n", input, mktime(t));

    if (input != mktime(t)) {
        printf(
            "Year %d, Day of year: %d, Month %d, Day of month: %d, Day of week: %d, %d:%d:%d\n",
            t->tm_year, t->tm_yday, t->tm_mon, t->tm_mday, t->tm_wday, t->tm_hour, t->tm_min, t->tm_sec
        );
        puts("Failed!");
        return -1;
    }
    return 0;
}
int main() {
    struct tm t = {};

    t.tm_year = 71;
    t.tm_mday = 1;

    printf("%ld\n", mktime(&t));

    int day = 60 * 60 * 24;
    time_t inputs[] = { -(day * 33), -day, -500, 0, 1531454950 };
    for (int i = 0; i < 5; i += 1) {
        if (check(inputs[i])) {
            return -1;
        }
    }

    srand(time(NULL));

    for (int i = 0; i < 10; i += 1) {
        time_t input = (time_t) rand();
        struct tm* time = localtime(&input);
        time_t output = mktime(time);
        if (input != output) {
            // asctime has newline
            printf("Comparison %ld == %ld failed. Time: %s", input, output, asctime(time));
        }
    }
}
