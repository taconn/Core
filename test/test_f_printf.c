#include "f_colors.h"
#include "f_printf.h"

int main(void)
{
    f_printf(BRIGHT_YELLOW);

    f_printf("==test_f_printf.c==\n");
    f_printf("Hello, %s!\n", "world");
    f_printf("Char: %c\n", 'A');
    f_printf("Signed: %d\n", -42);
    f_printf("Hex: %x\n", 255u);
    f_printf("Percent: %%\n");
f_printf("Unsigned: %u\n", 42);
f_printf("Upper hex: %X\n", 255);
f_printf("Pointer: %p\n", (void *)main);
f_printf("Zero: %d\n", 0);
    f_printf("===================");
    return (0);
}

