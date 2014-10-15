#include "TinyUtil.h"


using namespace std;
using namespace wfan;

#define EXECUTE_JOURNEY(date) do \
	{ \
		extern int journey##date(int argc, char *argv[]); \
		journey##date(argc, argv) ; \
	} while(0)

int main(int argc, char *argv[])
{
    printf("== WebRTC signal and media server start...===\n");


    
    return 0;
}
