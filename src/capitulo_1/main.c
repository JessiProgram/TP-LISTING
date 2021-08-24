#include <stdio.h>
#include <stdlib.h>
#include "reciproco.hpp" 

int main(int argc, char ** argv)
{
	
    int i;
	i = atoi(argv[1]);
	printf("El reciproco de %d es %g\n", i, reciproco(i));


    return 0;
}
