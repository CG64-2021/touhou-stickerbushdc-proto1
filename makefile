# Compiler flags
CC=kos-cc
CFLAGS=-Wall -g -O0

# Target executable
TARGET=main.elf

# Source files
OBJS=main.o m_utils.o s_dataLoader.o s_sprCache.o s_video.o s_state.o s_input.o s_mobj.o p_user.o p_enemy.o

# Include KOS Makefile rules
#include $(KOS_BASE)/Makefile.rules

# Standard compiling rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Clean generated files
clean:
	rm -rf $(OBJS) $(TARGET)
