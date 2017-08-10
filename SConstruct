import os
#brew install openssl, brew link openssl --force, libsrtp: make & make install
LIB_PATH = ['/usr/lib', '/usr/local/lib', '/usr/local/opt/openssl/lib', './lib', './bin']

env = Environment(TARGET_ARCH='x86')

env.Append( CPPPATH=['./src', './util', '/usr/include', '/usr/local/opt/openssl/include'])

env.Library('./lib/tinyutil', ['./util/TinyUtil.cpp', './util/TinyTimer.cpp', './util/TinyServer.cpp', './util/TinyClient.cpp', './util/TinyRio.cpp'])

env.Program(target='./bin/hfrtc', source=['./src/hfrtc.cpp'], LIBS = ['tinyutil', 'pthread'], LIBPATH = LIB_PATH)

env.Program(target='./bin/sha256', source=['./test/sha256.cpp'], LIBS=['ssl', 'crypto'], LIBPATH = LIB_PATH)

env.Program(target='./bin/waltertest', source=['./test/waltertest.cpp'], 
	LIBS = ['tinyutil', 'pthread', 'srtp2'], LIBPATH = LIB_PATH)


env.Program(target='./bin/packet_tool', source=['./src/packet_tool.cpp', './src/util.c'], 
	LIBS = ['tinyutil', 'pthread', 'srtp2'], LIBPATH = LIB_PATH)