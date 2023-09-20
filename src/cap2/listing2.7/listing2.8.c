#include<stdio.h>
int f(); //Declaramos la función

int main (){
	printf("%d", f());

	return f ();
}

/*Comandos para compilar*/
/* 
 gcc -c listing2.7.c -o listing2.7.o
 ar cr libtest.a listing2.7.o
 gcc listing2.8.c -o app -L. -ltest
 */

/*Comandos para compilar*/
/* 
 gcc -c listing2.7.c -o listing2.7.o
 gcc -c listing2.8.c -o listing2.8.o
 ar cr lib_listing_2.8.a listing_2.8.o
 gcc -o listing2.7 listing2.7.o lib_listing_2.8.a
 */