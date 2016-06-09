
DEPEND_FILE=Makefile.depend.$(OS)

ifeq "$(OS)" "Windows_NT"
HOME=/cygdrive/c/home
endif

INCLUDES=-I../include 
TARGET=..

CXX = g++ 
LD = g++
CXXFLAGS = -Wall -W $(INCLUDES) -ansi -pedantic -g -ggdb -c -o
CXXFASTFLAGS = -O2 -DNDEBUG $(INCLUDES) -ansi -c -o 
ARFLAGS = r

DEVLIB = limedev.a
PROFLIB = limeprof.a
CLUSLIB = limeclus.a
FASTLIB = lime.a

LIBSRCS = \
	activeobject.cc boundingbox.cc configreader.cc			\
	configreader.cc debug.cc dig.cc error.cc geomutil.cc		\
	limetok.cc line.cc lockfile.cc numutil.cc point.cc rand.cc	\
	reader.cc scheduler.cc shortestpath.cc spnode.cc strutil.cc	\
	stat.cc timekeeper.cc


all: $(DEPEND_FILE) $(DEVLIB) 

rand.o: rand.cc
	$(CXX) $(CXXFASTFLAGS) $@ -O2 $<

%.o: %.cc
	$(CXX) $(CXXFLAGS) $@ $<

install: $(TARGET)/$(FASTLIB) $(TARGET)/$(DEVLIB)

$(TARGET)/$(FASTLIB): $(FASTLIB)
	cp $(FASTLIB) $(TARGET)/$(FASTLIB)

$(TARGET)/$(DEVLIB): $(DEVLIB)
	cp $(DEVLIB) $(TARGET)/$(DEVLIB)

TAGS: *.cc ../include/lime/*.h
	etags *.cc ../include/lime/*.h

$(DEPEND_FILE):
	touch $(DEPEND_FILE)

.PHONY: depend
depend: $(DEPEND_FILE)
	makedepend -f$(DEPEND_FILE)  --  $(CXXFLAGS) -- $(LIBSRCS)
	makedepend -a -pfast/ -f$(DEPEND_FILE)  --  $(CXXFLAGS) -- $(LIBSRCS)

.PHONY:	fast_
fast_: fast $(FASTLIB)

fast: 
	mkdir -pv fast

fast/%.o: %.cc
	$(CXX) $(CXXFASTFLAGS) $@ $<

.PHONY:	profile_
profile_: profile $(PROFLIB)

.PHONY:	cluster_
cluster_: cluster $(CLUSLIB)

profile: 
	mkdir -pv profile

cluster: 
	mkdir -pv cluster

profile/%.o: %.cc
	$(CXX) -pg $(CXXFASTFLAGS) $@ $<

cluster/%.o: %.cc
	$(CXX) $(CXXFASTFLAGS) $@ $<

LIBOBJS=$(LIBSRCS:.cc=.o) 
$(DEVLIB): $(LIBOBJS)
	ar $(ARFLAGS) $(DEVLIB) $(LIBOBJS)
	ranlib $(DEVLIB)

FASTOBJS=$(patsubst %.cc,fast/%.o,$(LIBSRCS))
$(FASTLIB): fast $(FASTOBJS)
	cd fast ; ar $(ARFLAGS) ../$(FASTLIB) *.o
	ranlib $(FASTLIB)

PROFOBJS=$(patsubst %.cc,profile/%.o,$(LIBSRCS))
$(PROFLIB): profile $(PROFOBJS)
	cd profile ; ar $(ARFLAGS) ../$(PROFLIB) *.o
	ranlib $(PROFLIB)

CLUSOBJS=$(patsubst %.cc,cluster/%.o,$(LIBSRCS))
$(CLUSLIB): cluster $(CLUSOBJS)
	cd cluster ; ar $(ARFLAGS) ../$(CLUSLIB) *.o
	ranlib $(CLUSLIB)
	cp $(CLUSLIB) ..

clean:
	rm -f *.o profile/*.o cluster/*.o fast/*.o $(DEVLIB) $(PROFLIB) $(CLUSLIB) $(FASTLIB) $(TARGET)/$(FASTLIB)

include $(DEPEND_FILE)
