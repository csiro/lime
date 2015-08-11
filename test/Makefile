
LIMEHOME=../src

CXXFLAGS=
INCLUDES=
LDFLAGS=

# Includes other makefiles?

SRCS=   readconfig.cc

INCLUDES:=$(INCLUDES) -I../include 

CXX = g++ 

CXXFLAGS:=$(CXXFLAGS) -Wall -W $(INCLUDES) -ansi -pedantic -g -ggdb -c 
CXXFASTFLAGS:=$(CXXFLAGS) -O2 -DNDEBUG $(INCLUDES) -ansi -c

EXES = readconfig

OBJS=$(patsubst %.cc,%.o,$(SRCS))

DEPEND_FILE=Makefile.depend.$(OS)

all: $(DEPEND_FILE) lastbuild.h readconfig

readconfig: readconfig.o $(OBJS) $(LIMEHOME)/limedev.a 
	lastbuildc -vf version
	$(CXX) $(LDFLAGS) -o $@ lastbuild.cc $^ 

%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

lastbuild.h:
	lastbuildc -vf version

clean:
	rm -f readconfig *.o

$(DEPEND_FILE):
	touch $(DEPEND_FILE)

.PHONY: depend
depend: 
	makedepend -f$(DEPEND_FILE)  --  $(CXXFLAGS) -- $(SRCS)
	makedepend -a -pfast/ -f$(DEPEND_FILE)  --  $(CXXFLAGS) -- $(SRCS)
	makedepend -a -pcluster/ -f$(DEPEND_FILE)  --  $(CXXFLAGS) -- $(SRCS)
	echo



include $(DEPEND_FILE)
