#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char **argv)
{
    int pid, wpid, mask;

	if(argc < 3)
    {
		printf(1, "only usage: ssu_trace [mask] [command]\n");
		exit();
	}

    mask = atoi(argv[1]);
    
    pid = fork();
    if(pid < 0){
        printf(1, "ssu_trace: fork failed\n");
        exit();
    }
    if(pid == 0){
        if(trace(mask) < 0)
        {
            printf(1, "ssu_trace: tracing failed\n");
            exit();
        }
        else
        {
            exec(argv[2], argv + 2); // [command] 실행
            exit();
        }
    }
    while((wpid=wait()) >= 0 && wpid != pid)
        printf(1, "zombie!\n");
  
    exit();
}