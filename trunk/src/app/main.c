#include <signal.h>
#include <unistd.h>

#include "../../include/prj_common.h"
#include "../../utility/include/utility.h"

int lawliet_run = 1;

void ShutdownLawlietSystem(int signo)
{
 	lawliet_run = 0;
}

int LinuxSignalInitial(void)
{
 	int ret = 0; 
 	if(signal(SIGUSR2, ShutdownLawlietSystem) != SIG_ERR){
 		LDBG("Linux Signal Init !\t(Signal 12)\n");
 	}else{
 		ret = -1;
 	}

	return ret;
}

int main(int argc, char *argv[])
{
	int cpu_endian = -1;
	LDBG("====================================\n");
	LDBG("   Project Lawliet : Start Sucess\n");
	LDBG("====================================\n");

	if(LinuxSignalInitial() != 0){
		 LDBG("Linux Signal : register failed!\n");
    }
	
	/*
	if(system("./boa -c /etc/boa &")){
		LDBG("Boa Server : Start Failed\n");
	}else{
		LDBG("Boa Server : Start Sucess\n");
	}
	*/

	cpu_endian = Lawliet_Check_CPUendian();

	if(cpu_endian == CPU_BIG_ENDIAN){
		LDBG("CPU Endian : It's Big Endian !\n");
	}else if(cpu_endian == CPU_LITTLE_ENDIAN){
		LDBG("CPU Endian : It's Little Endian !\n");
	}else{
		LDBG("CPU Endian : Error !\n");
	}
	
	while(lawliet_run){
		LDBG("live... !\n");
		sleep(10);
	}

	LDBG("Lawliet Core Task 881... !\n");
	return 0;
}
