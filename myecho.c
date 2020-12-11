#include <stdio.h>
#include <string.h>

int main(int ac, char* av[]){
	if (strcmp(av[1], "-n") != 0){
		for (int i = 1; i < ac - 1; i++){
				printf ("%s ", av[i]);
		}
		printf("%s\n", av[ac - 1]);
	} else if (strcmp(av[1], "-n") == 0){
                 for (int i = 2; i < ac - 1; i++){
                                printf ("%s ", av[i]);
                }
                printf("%s", av[ac - 1]);

	} 
	return 0;
}
