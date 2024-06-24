#include <stdio.h>
#include "ft_printf.h"

int main(){
	char *s = "mystring";
	void *p;
	p = &s;
	static char     a01;
	static unsigned char a02;
	static short a03;
	static unsigned short a04;
	static int a05;
	static unsigned int a06;
	static long a07;
	static unsigned long a08;
	static long long a09;
	static unsigned long long a10;
	static char *a11;
	static void *a12;

	printf("Printf: %-.50szzzz", "Initializing...");
	printf("Printf: %+ 20d\n", 42); fflush(stdout);
	printf("Printf:_%-40.5d\n% u\n%+168p\n%---%%--%\n", 1674006569u, 2231710712u, (void*)8652210935049373690lu); fflush(stdout);
	printf("Printf:_%- +010.6d$_%10.8u$\n", 255, 1234);
	printf("Printf:_%- 010u$\n", 1234);
	printf("Printf:_pointer_%#p\n", p);
	printf("Printf:_ %s %s$", " ", "");
	printf("\n%.0s%.2s", "holla", "bitch");
	printf("\nNULL:_%7.3s_%7.3s_", NULL, NULL);
	printf("%s", NULL); printf("$"); printf("%2.5s", NULL); printf("$");
	printf("\n");
	printf("%23s", NULL);
	printf("\n_%7i_\n", -14);
	printf("_%-7i_\n", -14);
	printf("_%8.5i_", 34); printf("\n");
	printf("%07i\n", -54);
	printf("_%5.0i_", 0);

	printf("\n====MYCODE====\n\n");
	printf("\n====CHARS=====\n\n");
	printf("pf_%-5c_", 0); printf("\n");fflush(stdout);
	ft_printf("ft_%-5c_", 0); 
	printf("pf_%.c_\n", 'a'); fflush(stdout);
	ft_printf("ft_%.c_\n", 'a');
	printf("_"); printf("%-5c", '\0'); printf("_\n"); fflush(stdout);
	ft_printf("_"); ft_printf("%-5c", '\0'); ft_printf("_\n");
	printf("pf"); printf("{%3c}", 0); printf("_\n"); fflush(stdout);
	ft_printf("ft_"); ft_printf("{%3c}", 0); ft_printf("_\n");
	printf("%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c//%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c", ' ','!','"','#','$', '%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':', ';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q', 'R','S','T','U', 'V','W','X','Y','Z','[','\\',']','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p', 'q','r','s','t','u','v','w','x','y','z','{','|','~'); fflush(stdout);
	printf("\n\n");
	ft_printf("%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c//%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c", ' ','!','"','#','$', '%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':', ';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q', 'R','S','T','U', 'V','W','X','Y','Z','[','\\',']','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p', 'q','r','s','t','u','v','w','x','y','z','{','|','~'); fflush(stdout);

	printf("\n====POINTRS===\n\n");
	printf("pf_%5.0p\n", &a01);
	printf("pf_%p", NULL); ft_printf("\n"); fflush(stdout);
	ft_printf("ft_%p", NULL); printf("\n");
	printf("%p%p%p%p%p%p%p%p%p%p%p%p",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12); fflush(stdout);
	ft_printf("\n\n%p%p%p%p%p%p%p%p%p%p%p%p",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12); fflush(stdout);
	printf("\n%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12); fflush(stdout);
	ft_printf("\n%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p%-32p",&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12); fflush(stdout);

	printf("\n====HEXNUMS===\n\n");
	printf("%8.3X\n", 8375);
	ft_printf("%8.3X\n", 8375)	;
	printf("%5x\n", -52625);
	ft_printf("%5x\n", -52625);
	printf("\n====NUMBERS===\n\n");
	printf("p14 %5.0d\n", 100); fflush(stdout);
	ft_printf("p14 %5.0d\n", 100);
	printf("pf%.0i", 0); ft_printf("\n");
	ft_printf("ft%.0i", 0); ft_printf("\n");
	printf("_%8.3i\n", 8375);
	ft_printf("_%8.3i\n", 8375);
	ft_printf("_%5.0i_\n", 0);
	ft_printf("%07i\n", -54);
	ft_printf("_%8.5i_", 34); printf("\n");
	ft_printf("_%-7i_", -14); printf("\n");
	ft_printf("_%7i_", -14); printf("\n");
	printf("\n====STRINGS===\n\n");
	printf("pf%-s_", "hello"); printf("\n");
	ft_printf("ft%s_", "hello");
	printf("\n");
	ft_printf("%23s", NULL); printf("\n");
	ft_printf("%s", NULL);
	ft_printf("\nNULL:_%7.3s_%7.3s", NULL, NULL);
	ft_printf ("\n%.s%.2s$\n", "holla", NULL);	
	ft_printf ("%7.3s%7.3s", "hello", "world");

	printf("\n====MULTI=====\n\n");
	printf("_%-153p_%0110.8x%110p" ,(void*)17240180584784891087lu,2705171059u,(void*)1312307382483808423lu); fflush(stdout);
	ft_printf("\n_%-153p_%0110.8x%110p" ,(void*)17240180584784891087lu,2705171059u,(void*)1312307382483808423lu); 

	printf("\npf %lld %llu \n", (long long)17240180584784891087lu, 17240180584784891087lu); fflush(stdout);

	ft_printf ("Integers:_%- +010.6d$_% + +10.8u$ \n", 255, 1234);
	ft_printf ("Padding check: %50..i_% u_%+ p \n", 3456, 3456, p);
	ft_printf ("Characters: %c %c \n", 'z', 80);
	ft_printf ("String: %s \n", s);
	ft_printf ("Pointer address: %p \n", p);
	ft_printf ("Decimals: %d %ld\n", 1997, 32000L);
	ft_printf ("Some different radices: %d %x %X %#x \n", 100, 100, 100, 100, 100);
	ft_printf ("Preceding with empty spaces: %10d \n", 1997);
	ft_printf ("Preceding with zeros: %010d \n", 1997);
	ft_printf ("Width: %*d \n", 15, 140);
	ft_printf ("Percent: %% ");
	ft_printf ("%s \n", "Educative");
	return 0;
}
