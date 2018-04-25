############################
# CS3377.501               #
#                          #
# General Purpose Makefile #
#                          #
# Makefile by: Eric Busch  #
############################

# Set up info for C++ implicit rules
CXX = g++
CXXFLAGS = -Wall -I /scratch/perkins/include -std=c++0x
CPPFLAGS = 

# compiler flags
LDLIBS = -l cdk -l curses

# linker flags
LDFLAGS = -L /scratch/perkins/lib

# name of project - for backup target
PROJECTNAME = Program6

# name of source files to include in compiling
SRCS = program6.cc

# name of executable to be created
EXEC = program6

# You normally don't need to change anything below here.
# ======================================================
OBJS = $(SRCS:cc=o)

all: $(EXEC)

clean:
	rm -f $(OBJS) *.d *~ \#* $(EXEC)

Makefile: $(SRCS:.cc=.d)

# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# This is a rule to link the files
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# Include the dependency files
-include $(SRCS:.cc=.d)

