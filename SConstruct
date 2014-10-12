import os

LUA_ROOT = os.environ['LUA_ROOT']
BOOST_ROOT = os.environ['BOOST_ROOT']
GTEST_DIR = os.environ['GTEST_DIR']

env = Environment(TARGET_ARCH='x86')
env.Append( CPPPATH=[GTEST_DIR + '/include'] )
env.Append( CPPPATH=[BOOST_ROOT] )
env.Append( CPPPATH=['./src'] )

env.Program(target='./bin/hfrtc', source=['./src/hfrtc.cpp'])
#, LIBS = ['gmock'], LIBPATH = ['./bin', LIB_PATH  ])