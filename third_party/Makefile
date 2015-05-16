LIBEVENT_DIR=./libevent
GMOCK_DIR=./googlemock
GTEST_DIR=./googlemock/gtest
PROTOBUF_DIR=./protobuf
LUA_DIR=./lua-5.3.0
#LUABIND_DIR=./luabind-0.7.1-rc1
OS=generic

all:
	
	if [ "x"`cat /etc/redhat-release | grep CentOS | sed "s/.*CentOS.*/CentOS/"` = "xCentOS" ]; then \
			OS="linux";\
	else \
			OS="macosx";\
	fi
	
	(cd $(GMOCK_DIR) &&  autoreconf -fvi && ./configure && make ) 
	(cd $(PROTOBUF_DIR) && ./autogen.sh  && ./configure && make )
	(cd $(LIBEVENT_DIR) && ./autogen.sh  && ./configure && make )
	(cd $(LUA_DIR) && make $(OS) )

clean:
	(cd $(GMOCK_DIR) && && make clean)
	(cd $(PROTOBUF_DIR) && make clean)
	(cd $(LIBEVENT_DIR) && make clean)
	(cd $(LUA_DIR) && make clean )

