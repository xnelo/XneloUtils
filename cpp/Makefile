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

Q = @

CXX = g++
CXXFLAGS = -Iinclude/

SRCS	=	$(wildcard src/Core/*.cpp) \
			$(wildcard src/Logging/*.cpp) \
			$(wildcard src/Network/*.cpp) \
			$(wildcard src/Stream/*.cpp)

OBJS	=	$(SRCS:.cpp=.o)
DEPS	=	$(OBJS:.o=.d)

LIB_DIR = ./lib
LIB_NAME = XneloUtils.a
LIB_FULLPATH= $(LIB_DIR)/$(LIB_NAME)

all: build

build: $(LIB_FULLPATH)
	$(Q)echo [Done]

$(LIB_FULLPATH): $(OBJS)
	$(Q)echo [Create] Directory '$(LIB_DIR)'
	$(Q)mkdir -p $(LIB_DIR)
	$(Q)echo [Build] $(LIB_FULLPATH)
	$(Q)ar rvs $(LIB_FULLPATH) $(OBJS)

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
	$(Q)echo [Remove] .o files
	$(Q)rm -f $(OBJS)
	$(Q)echo [Remove] .d files
	$(Q)rm -f $(DEPS)
	$(Q)echo [Remove] $(LIB_NAME) and $(LIB_DIR)
	$(Q)rm -rf $(LIB_DIR)
	$(Q)echo [Done]
