import os
LIB_PATH = '/usr/lib'
LUA_ROOT = os.environ['LUA_ROOT']
BOOST_ROOT = os.environ['BOOST_ROOT']
GTEST_DIR = os.environ['GTEST_DIR']
GMOCK_DIR = os.environ['GMOCK_DIR']
env = Environment(TARGET_ARCH='x86')
env.Append( CPPPATH=[GTEST_DIR + '/include'] )
env.Append( CPPPATH=[BOOST_ROOT] )
env.Append( CPPPATH=['./src'] )
env.Append( CPPPATH=['/usr/include'])

env.Program(target='./bin/hfrtc', source=['./src/hfrtc.cpp'])
#, LIBS = ['gmock'], LIBPATH = ['./bin', LIB_PATH  ])
env.Program(target='./bin/sha256', source=['./test/sha256.cpp'], LIBS=['ssl', 'crypto'], LIBPATH = ['./bin', LIB_PATH  ])