/* Journal on 2014-10-31 14:27:08*/
#include "TinyUtil.h"

#include <string>
#include <queue>

static void test(string msg) {
	string ret = ReplaceValueAsKey(msg, "bbb=", "***", "&");
	cout<<"ret="<<ret<<endl;
}

int journey20141031(int argc, char *argv[])
{
	test("aaa=111&bbb=222&ccc=333");
	test("aaa=111&bbb=222");
	test("aaa=111&ccc=333");
	test("aaa=111&bbb=&ccc=333");
	test("aaa=111&bbb=");
	test("bbb=111&bbb=");
	test("bbb=");
    return 0;
}
