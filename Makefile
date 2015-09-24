# General definitions
CC=g++
CFLAGS=-c -Wall -O2 $(INCLUDE)
LDFLAGS=-lpthread

# Program specific definitions

# SOURCES must include relative paths to each C source
# from the location of the Makefile
# It is recommeded to locate all this files in a src
# directory below the directory where makefile is located
SOURCES_SERVER=src/mainRSServer.cpp src/Socket.cpp src/EventTable.cpp
SOURCES_CLIENT=src/mainRSClient.cpp src/Socket.cpp src/LogScanner.cpp


# CHECK_INCLUDES include header files that force
# recompilation
CHECK_INCLUDES=

# EXECUTABLE define the name of the final executable
# In will be generated on the location where this
# Makefile is located
EXECUTABLE_SERVER=rsserver
EXECUTABLE_CLIENT=rsclient

# Object files to be generated
# They will be located in the same place as the source files
OBJECTS_SERVER=src/mainRSServer.o src/Socket.o src/EventTable.o
OBJECTS_CLIENT=src/mainRSClient.o src/Socket.o src/LogScanner.o


# Include file paths include general "C" include location
# and the "include" directory below the location where
# this makefile is located
INCLUDE=\
	-I. \
	-Iinclude

# Make rules

all: make_server make_client

make_server: $(SOURCES_SERVER) $(EXECUTABLE_SERVER)

make_client: $(SOURCES_CLIENT) $(EXECUTABLE_CLIENT)

clean:
	rm -rf $(PWD)/src/*.o $(PWD)/$(EXECUTABLE_SERVER) $(PWD)/$(EXECUTABLE_CLIENT)
	touch $(PWD)/*
	touch $(PWD)/src/*
	@echo
	@echo Project clean is done
	@echo

$(EXECUTABLE_SERVER): $(OBJECTS_SERVER)
	$(CC) $(OBJECTS_SERVER) -o $@ $(LDFLAGS)
	@echo Server compilation is done

$(EXECUTABLE_CLIENT): $(OBJECTS_CLIENT)
	$(CC)  $(LDFLAGS) $(OBJECTS_CLIENT) -o $@
	@echo Client compilation is done

%.o: %.c $(CHECK_INCLUDES)
	$(CC) $(CFLAGS) $< -o $@
