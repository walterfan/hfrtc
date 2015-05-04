AUTOMAKE_OPTIONS = foreign
AM_CPPFLAGS=-I$(top_srcdir)/util -I/usr/local/include

LIBEVENT_DIR=$(top_srcdir)/third_party/libevent-2.0.22-stable
PROTOBUF_DIR=$(top_srcdir)/third_party/protobuf
LUA_DIR=$(top_srcdir)/third_party/lua-5.3.0

all-local:
	cd $(LIBEVENT_DIR) && $(MAKE) $(AM_MAKEFLAGS)
	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) all
	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) macosx
	
check-local:
	cd $(LIBEVENT_DIR) && $(MAKE) $(AM_MAKEFLAGS) verify
	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) test
	
clean-local:
	cd $(LIBEVENT_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
	cd $(PROTOBUF_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean
	cd $(LUA_DIR) && $(MAKE) $(AM_MAKEFLAGS) clean

noinst_PROGRAMS = hfrtc admin

hfrtc_SOURCES = hfrtc.cpp
hfrtc_CPPFLAGS = -I$(top_srcdir)/util
hfrtc_LDFLAGS = -L$(top_srcdir)/util -L$(PROTOBUF_DIR)/src -L$(LUA_DIR)/src
hfrtc_LDADD = -ltinyutil -llua -levent
hfrtc_DEPENDENCIES = all-local

admin_SOURCES = admin.cpp
admin_CPPFLAGS = -I$(top_srcdir)/util
admin_LDFLAGS = -L$(top_srcdir)/util -L$(PROTOBUF_DIR)/src -L$(LUA_DIR)/src
admin_LDADD = -ltinyutil -llua
admin_DEPENDENCIES = all-local
