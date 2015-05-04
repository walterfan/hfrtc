#include "TinyUtil.h"
#include "TinyServer.h"
#include <memory>


static char the_day[10] = "";

#define EXECUTE_JOURNEY(date) do \
	{ \
		extern int journey##date(int argc, char *argv[]); \
        if(strlen(the_day) > 0) { \
            if(strncmp(#date, the_day, 8) ==0) { \
                printf("-----"#date"-----\n");\
                journey##date(argc, argv);  \
            } \
        }\
		else {\
            printf("-----"#date"-----\n");\
            journey##date(argc, argv) ; \
        } \
	} while(0)



int main(int argc, char *argv[])
{
    
    if(argc > 1 ) {
        if(strlen(argv[1]) == 8) {
            strncpy(the_day, argv[1], 8);
            the_day[8] = '\0';
        }
    } else {
        printf("--launch jouneries--\n");
	}
    EXECUTE_JOURNEY(20141031);
    return 0;
}

//For TSP three, five, fourteen, 
//the feature has five items. We had discussion with PM, and we got agreement of four items 
//--We will do three items in t30, postpone one to T thirty-one.
//we just have an issue of one item. The main change of the item is on TPGW side
//PM said he will talk with TPGW team. So, we hold on the item until PM get agreement from TPGW team
//test automation to avoid regression issue, it is not once change, we add more and more test automation cases