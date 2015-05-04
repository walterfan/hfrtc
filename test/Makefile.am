AUTOMAKE_OPTIONS = foreign
AM_CPPFLAGS=-I$(top_srcdir)/util -I/usr/local/include

GMOCK_DIR=$(top_srcdir)/third_party/gmock-1.7.0
GTEST_DIR=$(top_srcdir)/third_party/gmock-1.7.0/gtest
PROTOBUF_DIR=$(top_srcdir)/third_party/protobuf
LUA_DIR=$(top_srcdir)/third_party/lua-5.3.0
#LUABIND_DIR=$(top_srcdir)/third_party/luabind-0.7.1-rc1

all-local:
	cd $(GMOCK_DIR) && $(MAKE) $(AM_MAKEFLAGS) all
	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) all
	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) macosx
#	cd $(LUABIND_DIR) && $(MAKE) $(AM_MAKEFLAGS) all
	
check-local:
	cd $(GMOCK_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
#	cd $(LUABIND_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
	
clean-local:
	cd $(GMOCK_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
#	cd $(LUABIND_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean


noinst_PROGRAMS = http_client rot13fork rot13select rot13event1 rot13event2 waltertest unittest jsenginetest


http_client_SOURCES = http_client_1st.cpp

rot13fork_SOURCES = rot13_fork_1st.cpp
rot13select_SOURCES = rot13_select_1st.cpp
rot13event1_SOURCES = rot13_libevent_1st.cpp
rot13event2_SOURCES = rot13_libevent_2nd.cpp

rot13event1_LDADD = -levent
rot13event2_LDADD = -levent


waltertest_SOURCES = waltertest.cpp 20141031.cpp
waltertest_LDADD=../util/.libs/libtinyutil.a 
waltertest_LDFLAGS=-D_GNU_SOURCE
DEFS+=-D_GNU_SOURCE

jsenginetest_SOURCES = SpiderMonkeyTest.cpp 
jsenginetest_CPPFLAGS = -I/usr/local/include/mozjs-31 -std=c++11
jsenginetest_LDADD = -lmozjs-31

unittest_SOURCES = UnitTest.cpp server_test.cpp lua_test.cpp
unittest_CPPFLAGS = -I$(GMOCK_DIR)/include -I$(GTEST_DIR)/include -I$(LUA_DIR)/src -I$(top_srcdir)/util
unittest_DEPENDENCIES = all-local
unittest_LDFLAGS = -L$(GMOCK_DIR)/lib -L$(GTEST_DIR)/lib -L$(PROTOBUF_DIR)/src -L$(LUA_DIR)/src -L$(top_srcdir)/util
unittest_LDADD = -lgmock -lgtest -llua -ltinyutil

