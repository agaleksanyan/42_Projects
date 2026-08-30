#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int ret1, ret2;

	char c = 'A';
	char *str = "Hello, ft_printf!";
	char *null_str = NULL;
	int i = 42;
	int neg = -42;
	unsigned int u = 4294967295U; // UINT_MAX
	void *ptr = str;
	void *null_ptr = NULL;

	// ----------------- Проверка %c -----------------
	ret1 = ft_printf("Char: [%c]\n", c);
	ret2 = printf("Char: [%c]\n", c);
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	// ----------------- Проверка %s -----------------
	ret1 = ft_printf("String: [%s]\n", str);
	ret2 = printf("String: [%s]\n", str);
	ft_printf("Return: ft=%d | std=%d\n", ret1, ret2);

	ret1 = ft_printf("NULL string: [%s]\n", null_str);
	ret2 = printf("NULL string: [%s]\n", null_str);
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	// ----------------- Проверка %p -----------------
	ret1 = ft_printf("Pointer: [%p]\n", ptr);
	ret2 = printf("Pointer: [%p]\n", ptr);
	ft_printf("Return: ft=%d | std=%d\n", ret1, ret2);

	ret1 = ft_printf("NULL pointer: [%p]\n", null_ptr);
	ret2 = printf("NULL pointer: [%p]\n", null_ptr);
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	// ----------------- Проверка %d и %i -----------------
	ret1 = ft_printf("Decimal: [%d]\n", i);
	ret2 = printf("Decimal: [%d]\n", i);
	ft_printf("Return: ft=%d | std=%d\n", ret1, ret2);

	ret1 = ft_printf("Negative: [%i]\n", neg);
	ret2 = printf("Negative: [%i]\n", neg);
	ft_printf("Return: ft=%d | std=%d\n", ret1, ret2);

	ret1 = ft_printf("INT_MAX: [%d]\n", INT_MAX);
	ret2 = printf("INT_MAX: [%d]\n", INT_MAX);
	ft_printf("Return: ft=%d | std=%d\n", ret1, ret2);

	ret1 = ft_printf("INT_MIN: [%i]\n", INT_MIN);
	ret2 = printf("INT_MIN: [%i]\n", INT_MIN);
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	// ----------------- Проверка %u -----------------
	ret1 = ft_printf("Unsigned: [%u]\n", u);
	ret2 = printf("Unsigned: [%u]\n", u);
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	// ----------------- Проверка %x и %X -----------------
	ret1 = ft_printf("Hex lower: [%x]\n", i);
	ret2 = printf("Hex lower: [%x]\n", i);
	ft_printf("Return: ft=%d | std=%d\n", ret1, ret2);

	ret1 = ft_printf("Hex upper: [%X]\n", i);
	ret2 = printf("Hex upper: [%X]\n", i);
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	ret1 = ft_printf("Zero hex: [%x]\n", 0);
	ret2 = printf("Zero hex: [%x]\n", 0);
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	// ----------------- Проверка %% -----------------
	ret1 = ft_printf("Percent: [%%]\n");
	ret2 = printf("Percent: [%%]\n");
	ft_printf("Return: ft=%d | std=%d\n\n", ret1, ret2);

	// ----------------- Смешанные варианты -----------------
	ret1 = ft_printf("Mix: char=%c, str=%s, ptr=%p, d=%d, u=%u, x=%x, X=%X, %%\n", 'Z', "Test", &i, -123, 123U, 255, 255);
	ret2 = printf("Mix: char=%c, str=%s, ptr=%p, d=%d, u=%u, x=%x, X=%X, %%\n", 'Z', "Test", &i, -123, 123U, 255, 255);
	ft_printf("Return: ft=%d | std=%d\n", ret1, ret2);

	return (0);
}
