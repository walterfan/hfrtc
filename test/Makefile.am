INCLUDES=-I$(top_srcdir)/util
noinst_PROGRAMS = http_client rot13fork rot13select rot13event1 rot13event2 waltertest

waltertest_SOURCES = waltertest.cpp 20141031.cpp
http_client_SOURCES = http_client_1st.cpp

rot13fork_SOURCES = rot13_fork_1st.cpp
rot13select_SOURCES = rot13_select_1st.cpp
rot13event1_SOURCES = rot13_libevent_1st.cpp
rot13event2_SOURCES = rot13_libevent_2nd.cpp

waltertest_LDADD=../util/.libs/libtinyutil.a 
waltertest_LDFLAGS=-D_GNU_SOURCE
DEFS+=-D_GNU_SOURCE

rot13event1_LDADD = -levent
rot13event2_LDADD = -levent