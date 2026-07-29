AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -Wall -Wextra -Wpedantic

noinst_LIBRARIES = libstats.a
libstats_a_SOURCES = src/stats.c include/stats.h

bin_PROGRAMS = sensor-stats
sensor_stats_SOURCES = src/main.c
sensor_stats_LDADD = libstats.a
