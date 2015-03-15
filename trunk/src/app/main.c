#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("==============================\n");
	printf("Project Lawliet : Start Sucess\n");
	printf("==============================\n");
	if(system("./boa &")){
		printf("Boa Server : Start Failed\n");
	}else{
		printf("Boa Server : Start Sucess\n");
	}
	while(1){
		
	}
	return 0;
}
