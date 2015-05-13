AUTOMAKE_OPTIONS = foreign
LUA_DIR=$(top_srcdir)/third_party/lua-5.3.0
LIBEVENT_DIR=$(top_srcdir)/third_party/libevent-2.0.22-stable

lib_LTLIBRARIES = libtinyutil.la
libtinyutil_la_SOURCES = TinyUtil.cpp  TinyTimer.cpp  TinyServer.cpp  TinyClient.cpp  TinyRio.cpp LuaUtil.cpp
libtinyutil_la_CPPFLAGS = -I$(LUA_DIR)/src -I$(LIBEVENT_DIR)/include
#libtinyutil_la_LDFLAGS = -L$(LUA_DIR)/src
#libtinyutil_la_LIBADD = -llua
#libtinyutil_la_DEPENDENCIES = all-local
