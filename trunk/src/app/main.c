#include "../../include/prj_common.h"
#include "../../utility/include/utility.h"


int main(int argc, char *argv[])
{
	int cpu_endian = -1;
	printf("==============================\n");
	printf("Project Lawliet : Start Sucess\n");
	printf("==============================\n");
	if(system("./boa &")){
		printf("Boa Server : Start Failed\n");
	}else{
		printf("Boa Server : Start Sucess\n");
	}

	cpu_endian = Lawliet_Check_CPUendian();

	if(cpu_endian == CPU_BIG_ENDIAN){
		printf("CPU Endian : CIt's Big Endian !\n");
	}else if(cpu_endian == CPU_LITTLE_ENDIAN){
		printf("CPU Endian : It's Little Endian !\n");
	}else{
		printf("CPU Endian : Error !\n");
	}
	
	while(1){
		
	}
	return 0;
}
