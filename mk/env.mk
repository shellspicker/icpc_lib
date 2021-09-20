# 编译参数
CC = gcc
CXX = g++
AR = ar
RANLIB = ranlib
SHARE = -fpic -shared -o
INCLUDE = -I./\
	-Iinclude/\
	-I/usr/include/\
	-I/usr/local/include/
LIBS = -L./\
	-L/usr/lib/\
	-L/usr/lib32/\
	-L/usr/lib64/\
	-L/usr/local/lib/
LDFLAGS = $(LIBS) -Wl,-rpath=$(subst $(space),:,$(subst -L,,$(LIBS)))
DEFINES =
CFLAGS = -g -Wall -O2 $(INCLUDE) $(DEFINES)
CXXFLAGS = -std=c++17 $(CFLAGS) -DHAVE_CONFIG_H

# make工具, Makefile指定.
MAKE = make
MAKEFILE = Makefile

# 文件扩展名相关.
SRCEXT = .c .cc .cpp .cxx .c++

# default target
default: all
