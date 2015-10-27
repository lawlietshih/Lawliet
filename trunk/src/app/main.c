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

#define SYS_OPTION	1

void ( *OperSys[] )(void)={shutdown_system,
                          };

int lawliet_run = 1;

int main(int argc, char *argv[])
{
	int choice = 0;
	int cpu_endian = -1;
	LDBG("=====================================\n");
	LDBG("   Project Lawliet : Start Success\n");
	LDBG("=====================================\n");

	if(LinuxSignalInitial() != 0){
		 LDBG("Linux Signal : register failed!\n");
    }
	
	if(system("./boa -c /etc/boa &") == -1){
		LDBG("Boa Server : Start Failed\n");
	}else{
		LDBG("Boa Server : Start Sucess\n");
	}

	/* Host byte order */
	cpu_endian = Lawliet_Check_CPUendian();

	if(cpu_endian == CPU_BIG_ENDIAN){
		LDBG("CPU Endian : It's Big Endian !\n");
	}else if(cpu_endian == CPU_LITTLE_ENDIAN){
		LDBG("CPU Endian : It's Little Endian !\n");
	}else{
		LDBG("CPU Endian : Error !\n");
	}
	
	Lawliet_APP_Start();

#ifdef SUPPORT_LAWLIET
	LDBG("SUPPORT_LAWLIET !\n");
#else
	LDBG("NOT SUPPORT_LAWLIET !\n");
#endif
	
	//-----------------------------------------------------------------------------------

	//if(system("clear") == -1){
	//	LDBG("Error : System Call Failed !");
	//}
	
	choice = sys_setting();
	
	//if(system("clear") == -1){
	//	LDBG("Error : System Call Failed !");
	//}

	while(lawliet_run)
	{
		if((choice >= 0) && (choice < SYS_OPTION)){
			( *OperSys[choice] )();

			if(choice != 0){
				choice = sys_setting();
				//if(system("clear") == -1){
				//	LDBG("Error : System Call Failed !");
				//}
				}
		}else{
			choice = 0;//shutdown
		}

		//LDBG("Lawliet Core Task live... !\n");
	}
	
	LDBG("Lawliet Core Task 881... !\n");

	LDBG("=====================================\n");
	LDBG("   Project Lawliet : Stop  Success\n");
	LDBG("=====================================\n");
	
#if 0
	int i = 0;
	for(i = 0; i < 140; ++i)
	{
		errno = i;
		print_errno(errno);
	}
#endif

	return 0;
}

int sys_setting(void)
{
	int key = 0;
	LDBG("\n");
	LDBG("-------- Project Lawliet : Sys Setting -----------\n");
	LDBG("\n");
	LDBG("Which option do you choose ? \n");
	LDBG("1.Shutdown \n");
	LDBG("\n");
	LDBG("others >> Quit \n");
	LDBG("--------------------------------------------------\n");
	LDBG("Please input digital number: 1-%d\n",SYS_OPTION);
	LDBG("\n");
	LDBG("Your choice is :");
	if(scanf("%d",&key) != 1){
		LDBG("Please input a arg -> digital number: 1-%d\n",SYS_OPTION);
		LDBG("\n");
	}
	return key-1;
}

void ShutdownLawlietSystem(int signo)
{
	Lawliet_APP_Stop();
	sleep(5);
	lawliet_run = 0;
}

void shutdown_system(void)
{
	ShutdownLawlietSystem(12);
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
