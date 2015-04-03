/*
	File name	:main.c
	Brief		:Core Task (System Init & System Control)
	Project		:Lawliet
	Author		:Lawliet
	History		:
    ---------------------------------------------------------------------------
     C0001 - Created by Lawliet 									2015-03-07
*/

#include <signal.h>
#include <unistd.h>

#include "../../include/prj_common.h"
#include "../../utility/include/utility.h"
#include "include/app_common.h"

int lawliet_run = 1;

void ShutdownLawlietSystem(int signo)
{
	Lawliet_APP_Stop();
	sleep(5);
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

void Lawliet_APP_Start(void)
{
	Init_System_Server();
}

void Lawliet_APP_Stop(void)
{
	Destroy_System_Server();
}

int main(int argc, char *argv[])
{
	int i = 0;
	int cpu_endian = -1;
	LDBG("=====================================\n");
	LDBG("   Project Lawliet : Start Success\n");
	LDBG("=====================================\n");

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
	
	Lawliet_APP_Start();
	
	//-----------------------------------------------------------------------------------
	
	while(lawliet_run){
		LDBG("Lawliet Core Task live... !\n");
		sleep(10);
	}
	
	LDBG("Lawliet Core Task 881... !\n");

	LDBG("=====================================\n");
	LDBG("   Project Lawliet : Stop  Success\n");
	LDBG("=====================================\n");

	for(i = 0; i < 140; ++i)
	{
		errno = i;
		print_errno(errno);
	}
	return 0;
}
