extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include "LuaUtil.h"
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sys/time.h>

#include "gmock/gmock.h"

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

int GetTimestamp(lua_State *pL)
{
	if(!pL) return 0;

	struct timeval tv;
	gettimeofday(&tv, NULL);
	lua_pushnumber(pL, tv.tv_sec);
	lua_pushnumber(pL, tv.tv_usec);
	return 2;
}

int SplitString(lua_State *pL)
{
    const char* str = luaL_checkstring(pL, 1);
    const char* sep = luaL_checkstring(pL, 2);

    const char* e = NULL;
    int i = 1;

    lua_newtable(pL);

    while((e = strchr(str, *sep))!=NULL)
    {
    	lua_pushlstring(pL, str, e-str);//the string in stack[-1]
    	lua_rawseti(pL, -2, i++);//set stack[-2][i++] = stack[-1], stack[-2] is the table,
    	str = e + 1;
    }

    lua_pushstring(pL, str);
    lua_rawseti(pL, -2, i);

    return 1;


}

int ListFiles(lua_State *pL)
{
	return 0;
}



TEST(LuaTest, ExecuteLuaScript)
{
	CLuaUtil aLuaUtil;
	int nRet = 0;


	lua_State* pL = aLuaUtil.GetLuaState();
	lua_pushcfunction(pL, GetTimestamp);
	lua_setglobal(pL, "GetTimestamp");

	lua_pushcfunction(pL, SplitString);
	lua_setglobal(pL, "SplitString");

	string strLuaCodes = "local sec, usec = GetTimestamp()\n"
		"print('sec=' ..sec .. ', usec='.. usec)"
		"local tbl = SplitString('/home/walter/source', '/')"
		"for key, value in pairs(tbl) do  "
		"print(key .. '->' ..value)  "
		"end ";
	aLuaUtil.ExecuteLuaCodes(strLuaCodes);
	//dump_lua_state(pL);
	//return nRet;
}
