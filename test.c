#include <stdio.h>
#include "ft_printf.h"
int main(){
	char *s = "mystring";
	void *p;
	p = &s;

	printf("Printf: %-.50zzzz", "Initializing...");
	printf("Printf: %##20d\n", 42); fflush(stdout);
	printf("Printf: %0-#0+15.20d\n%.11u\n%168p\n%---%%--%", 1674006569u, 2231710712u, (void*)8652210935049373690lu); fflush(stdout);

	printf("\n====MYCODE====\n\n"); 
	ft_printf ("Integers: %i %u \n", -3456, 1234);
	ft_printf ("Ints left just: % i %u\n", -3456, 3456);
	ft_printf ("Characters: %c %c \n", 'z', 80);
	ft_printf ("String: %s \n", s);
   ft_printf ("Pointer address: %p \n", p);
   ft_printf ("Decimals: %d %ld\n", 1997, 32000L);
   ft_printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
   ft_printf ("floats: %4.2f %+.0e %E \n", 3.14159, 3.14159, 3.14159);
   ft_printf ("Preceding with empty spaces: %10d \n", 1997);
   ft_printf ("Preceding with zeros: %010d \n", 1997);
   ft_printf ("Width: %*d \n", 15, 140);
   ft_printf ("Percent: %% ");
   ft_printf ("%s \n", "Educative");
   return 0;
}
