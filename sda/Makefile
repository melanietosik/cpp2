### Compile edit distance and sequence alignment project
### Create doxygen documentation

# Values for Mac OS X and Linux
CPPCOMPILER				= g++
COMPILER_FLAGS			= -Os
COMPILER_OUTPUT_FLAGS	= -o
DELETE_RECURSIVE		= rm -rf
EXECUTABLE				= bin/sda
DOC_GENERATOR			= doxygen doc/doxyfile
INCLUDE_PATH			= class/
SRC_PATH				= src/
DOC_PATH				= doc/

# Option 1: Generate program and documentation
all : build documentation

# - Create the executable
build : $(SRC_PATH)main.cpp $(HEADERFILES)
	$(CPPCOMPILER) $(SRC_PATH)main.cpp $(COMPILER_FLAGS) $(COMPILER_OUTPUT_FLAGS) $(EXECUTABLE)

# - Headerfiles
$(HEADERFILES) : $(INCLUDE_PATH)min_max.hpp $(INCLUDE_PATH)edit_distance.hpp $(INCLUDE_PATH)sequence_alignment.hpp

# Option 2: Generate documentation
documentation :
	$(DOC_GENERATOR)

# Option 3: Test 
test : $(EXECUTABLE)
	$(EXECUTABLE) -m insertion
	$(EXECUTABLE) -m insertion execution
	$(EXECUTABLE) -l insertion execution
	$(EXECUTABLE) -a GCATGCU GATTACA
	$(EXECUTABLE) -h

# Option 4: Clean up
clean :
	$(DELETE_RECURSIVE) $(DOC_PATH)html
	$(DELETE_RECURSIVE) $(DOC_PATH)latex
