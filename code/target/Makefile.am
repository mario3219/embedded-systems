AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic

noinst_LIBRARIES = \
									 libbandpass.a \
									 libPanTomp.a \
									 libPanTompData.a \
									 libutils.a

libbandpass_a_SOURCES = src/bandpass.cc include/bandpass.h
libPanTomp_a_SOURCES = src/PanTomp.cc include/PanTomp.h
libPanTompData_a_SOURCES = src/PanTompData.cc include/PanTompData.h
libutils_a_SOURCES = src/utils.cc include/utils.h

bin_PROGRAMS = app
app_SOURCES = src/main.cc
app_LDADD = \
    libPanTomp.a \
    libPanTompData.a \
    libbandpass.a \
    libutils.a
