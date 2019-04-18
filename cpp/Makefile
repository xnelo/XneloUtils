# <file>Makefile</file>
# <author> Spencer Hoffa </author>
#
# <copyright> 2019 Spencer Hoffa </copyright>
#
# <license>
# The zlib/libpng License
# Copyright(c) 2019 Spencer Hoffa
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from the
# use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions :
#
# 	1. The origin of this software must not be misrepresented; you must not
# 	claim that you wrote the original software.If you use this software in
# 	a product, an acknowledgment in the product documentation would be
# 	appreciated but is not required.
#
# 	2. Altered source versions must be plainly marked as such, and must not
# 	be misrepresented as being the original software.
#
# 	3. This notice may not be removed or altered from any source
# 	distribution.
#
# This liscense can also be found at : http ://opensource.org/licenses/Zlib
# </license>

Q = 

CXX = g++
CXXFLAGS = -Iinclude/ -g

SRCS	=	$(wildcard src/Core/*.cpp) \
			$(wildcard src/Logging/*.cpp) \
			$(wildcard src/Network/*.cpp) \
			$(wildcard src/Stream/*.cpp) \
			$(wildcard src/Testing/*.cpp)

OBJS	=	$(SRCS:.cpp=.o)
DEPS	=	$(OBJS:.o=.d)

LIB_DIR = ./lib
LIB_NAME = XneloUtils
LIB_FILENAME= lib$(LIB_NAME).a
LIB_FULLPATH= $(LIB_DIR)/$(LIB_FILENAME)

TEST_SRCS = TestCases/TestMain.cpp \
			TestCases/Core/BitwiseOperators.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_DEPS = $(TEST_OBJS:.o=.d)

TEST_DIR = ./test
TEST_EXE = Test
TEST_FULLPATH = $(TEST_DIR)/$(TEST_EXE)

all: build

build: $(LIB_FULLPATH) $(TEST_FULLPATH)
	$(Q)echo [Done]

test: $(LIB_FULLPATH) $(TEST_FULLPATH)
	$(Q)echo [Done]

$(LIB_FULLPATH): $(OBJS)
	$(Q)echo [Create] Directory '$(LIB_DIR)'
	$(Q)mkdir -p $(LIB_DIR)
	$(Q)echo [Build] $(LIB_FULLPATH)
	$(Q)ar rvs $(LIB_FULLPATH) $(OBJS)

$(TEST_FULLPATH): $(TEST_OBJS)
	$(Q)echo [Create] Directory '$(TEST_DIR)'
	$(Q)mkdir -p $(TEST_DIR)
	$(Q)echo [Build] $(TEST_FULLPATH)
	$(Q)$(CXX) $(TEST_OBJS) -L$(LIB_DIR) -l$(LIB_NAME) -o $(TEST_FULLPATH)

-include $(DEPS)

# compile and generate dependency info;
# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
%.o: %.cpp
	$(Q)echo [Compile] $<
	$(Q)$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o
	$(Q)$(CXX) $(CXXFLAGS) -MM $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

.PHONY: clean
clean:
	$(Q)echo [Remove] Lib .o files
	$(Q)rm -f $(OBJS)
	$(Q)echo [Remove] Lib .d files
	$(Q)rm -f $(DEPS)
	$(Q)echo [Remove] $(LIB_NAME)$(LIB_EXT) and $(LIB_DIR)
	$(Q)rm -rf $(LIB_DIR)
	$(Q)echo [Remove] Test .o files
	$(Q)rm -f $(TEST_OBJS)
	$(Q)echo [Remove] Test .d files
	$(Q)rm -f $(TEST_DEPS)
	$(Q)echo [Remove] $(TEST_EXE) and $(TEST_DIR)
	$(Q)rm -rf $(TEST_DIR)
	$(Q)echo [Done]
