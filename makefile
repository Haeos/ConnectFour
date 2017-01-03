##################################################
#   GENERIC G++ MAKEFILE
#   MODIFY BELOW
##################################################
# You may replace this with another name if your executable is different
EXE = main.exe

# All cpp files in folder. Change if you want to use specific files
SRC = $(wildcard *.cpp)

# Modify compiler flags as desired
CXXFLAGS = -std=c++11 -Wconversion -Wextra -Wnarrowing -Wall -pedantic -Os

# Uncomment lines below for windows (FLTK) programs
# LDFLAGS = -mwindows
# LIBS = -lfltk -lfltk_forms -lfltk_gl -lfltk_images -l fltk_jpeg -l fltk_png -lwsock32 -lgdi32 -luser32 -lole32 -luuid -lcomctl32 

######################################################
#	GENERALLY WON'T CHANGE ANY OF THIS
######################################################
ifeq ($(strip $(EXE)),)
empty-exe-error:
	@echo FORGOT TO SUPPLY A NAME TO EXE IN MAKEFILE
endif

# .o file for every .cpp
OBJS = $(SRC:.cpp=.o)

# C++ Compiler
CXX = g++

# Run psuedo target
run: $(EXE)
	@$(EXE)
	
# Rule to build the executable
$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

# Rule for g++ to build .o files from .cpp files
%.o : %.cpp
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -c $<
	
# Remove object files from folder
clean:
	@del /Q *.o
	@del /Q *.obj
	@del /Q *.exe
	
