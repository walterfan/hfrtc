AUTOMAKE_OPTIONS = foreign
AM_CPPFLAGS=-I$(top_srcdir)/util -I/usr/local/include

LIBEVENT_DIR=$(top_srcdir)/third_party/libevent
GMOCK_DIR=$(top_srcdir)/third_party/googlemock
GTEST_DIR=$(top_srcdir)/third_party/googlemock/gtest
PROTOBUF_DIR=$(top_srcdir)/third_party/protobuf
LUA_DIR=$(top_srcdir)/third_party/lua-5.3.0
#LUABIND_DIR=$(top_srcdir)/third_party/luabind-0.7.1-rc1
MOZJS_INC_DIR=/usr/local/include/mozjs-31

all-local:
#	cd $(GMOCK_DIR) &&  autoreconf -fvi && ./configure && $(MAKE) $(AM_MAKEFLAGS) 
#	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) 
#	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) posix
#	cd $(LUABIND_DIR) && $(MAKE) $(AM_MAKEFLAGS) all
	
check-local:
#	cd $(GMOCK_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
#	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
#	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
#	cd $(LUABIND_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
	
clean-local:
#	cd $(GMOCK_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
#	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
#	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
#	cd $(LUABIND_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean


noinst_PROGRAMS = http_client http_server rot13fork rot13select rot13event1 rot13event2 waltertest unittest SpiderMonkeyTest V8Test


http_client_SOURCES = http_client_1st.cpp

http_server_SOURCES = http_server_1st.cpp
http_server_CPPFLAGS= -I$(LIBEVENT_DIR) -I$(LIBEVENT_DIR)/include
http_server_LDFLAGS =-L$(LIBEVENT_DIR)
http_server_LDADD = -levent

rot13fork_SOURCES = rot13_fork_1st.cpp
rot13select_SOURCES = rot13_select_1st.cpp
rot13event1_SOURCES = rot13_libevent_1st.cpp
rot13event2_SOURCES = rot13_libevent_2nd.cpp

rot13event1_LDFLAGS = -L$(LIBEVENT_DIR)
rot13event2_LDFLAGS = -L$(LIBEVENT_DIR)

rot13event1_LDADD = -levent
rot13event2_LDADD = -levent

rot13event1_CPPFLAGS= -I$(LIBEVENT_DIR)/include
rot13event2_CPPFLAGS= -I$(LIBEVENT_DIR)/include


waltertest_SOURCES = waltertest.cpp 20141031.cpp
waltertest_CPPFLAGS = -I$(top_srcdir)/util -I$(top_srcdir)/src -Wall -g -O0 --coverage
# -fprofile-arcs -ftest-coverage
waltertest_LDADD=../util/.libs/libtinyutil.a 
waltertest_LDFLAGS=-D_GNU_SOURCE --coverage 
#-lgcov
DEFS+=-D_GNU_SOURCE

SpiderMonkeyTest_SOURCES = SpiderMonkeyTest.cpp 
SpiderMonkeyTest_CPPFLAGS = -I$(MOZJS_INC_DIR) -std=c++11
SpiderMonkeyTest_LDFLAGS=-L/usr/local/lib/ 
SpiderMonkeyTest_LDADD = -lmozjs-31

V8Test_SOURCES = v8test.cpp 
V8Test_CPPFLAGS = -I$(top_srcdir)/third_party/v8 -I$(top_srcdir)/util -pthread -lrt -stdlib=libstdc++ -std=c++11
V8Test_LDFLAGS =  -L/workspace/cpp/v8/xcodebuild/Release -L$(top_srcdir)/util -stdlib=libstdc++ -std=c++11
V8Test_LDADD = -lv8_base -lv8_libbase -lv8_snapshot -lv8_libplatform -licuuc -licui18n -licudata  -ltinyutil

unittest_SOURCES = UnitTest.cpp server_test.cpp lua_test.cpp TinyUtilTest.cpp
unittest_CPPFLAGS = -I$(GMOCK_DIR)/include -I$(GTEST_DIR)/include -I$(LUA_DIR)/src -I$(top_srcdir)/util
unittest_DEPENDENCIES = all-local
unittest_LDFLAGS = -L$(GMOCK_DIR)/lib -L$(GTEST_DIR)/lib -L$(PROTOBUF_DIR)/src -L$(LUA_DIR)/src -L$(top_srcdir)/util
unittest_LDADD = -lgmock -lgtest -llua -ltinyutil

