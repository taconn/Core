#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include "f_printf.h"

static int f_putc(char c)
{
    if (write(1, &c, 1) != 1)
        return (-1);
    return (1);
}

static int f_putstr(const char *str)
{
    int count;
    int result;

    if (!str)
        str = "(null)";
    count = 0;
    while (*str)
    {
        result = f_putc(*str);
        if (result < 0)
            return (-1);
        count += result;
        str++;
    }
    return (count);
}

static int f_putnbr_base(uintmax_t n, const char *base)
{
    int count;
    int result;
    uintmax_t base_len;

    count = 0;
    base_len = 0;
    while (base[base_len])
        base_len++;
    if (n >= base_len)
    {
        result = f_putnbr_base(n / base_len, base);
        if (result < 0)
            return (-1);
        count += result;
    }
    result = f_putc(base[n % base_len]);
    if (result < 0)
        return (-1);
    return (count + result);
}

static int f_put_signed(int n)
{
    int count;
    int result;
    uintmax_t number;

    count = 0;
    if (n < 0)
    {
        result = f_putc('-');
        if (result < 0)
            return (-1);
        count += result;
        number = (uintmax_t)(-(intmax_t)n);
    }
    else
        number = (uintmax_t)n;
    result = f_putnbr_base(number, "0123456789");
    if (result < 0)
        return (-1);
    return (count + result);
}

static int f_format(char specifier, va_list args)
{
    if (specifier == 'c')
        return (f_putc((char)va_arg(args, int)));
    if (specifier == 's')
        return (f_putstr(va_arg(args, char *)));
    if (specifier == 'd' || specifier == 'i')
        return (f_put_signed(va_arg(args, int)));
    if (specifier == 'u')
        return (f_putnbr_base(va_arg(args, unsigned int),
                "0123456789"));
    if (specifier == 'x')
        return (f_putnbr_base(va_arg(args, unsigned int),
                "0123456789abcdef"));
    if (specifier == 'X')
        return (f_putnbr_base(va_arg(args, unsigned int),
                "0123456789ABCDEF"));
    if (specifier == 'p')
    {
        return (f_putstr("0x")
            + f_putnbr_base((uintptr_t)va_arg(args, void *),
                "0123456789abcdef"));
    }
    if (specifier == '%')
        return (f_putc('%'));
    return (f_putc('%') + f_putc(specifier));
}

int f_printf(const char *format, ...)
{
    va_list args;
    int i;
    int count;
    int result;

    if (!format)
        return (-1);
    va_start(args, format);
    i = 0;
    count = 0;
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1])
        {
            result = f_format(format[i + 1], args);
            i += 2;
        }
        else
        {
            result = f_putc(format[i]);
            i++;
        }
        if (result < 0)
        {
            va_end(args);
            return (-1);
        }
        count += result;
    }
    va_end(args);
    return (count);
}
