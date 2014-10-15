#include "TinyUtil.h"
#include "TinyServer.h"
#include <memory>

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

    
    auto_ptr<ITinyServer> pt(CTinyServerFactory::CreateServer(SVC_ECHO) );
    pt->Init();
    pt->Start();
    pt->Stop();
    pt->Clean();

    return 0;
}
