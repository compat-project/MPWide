INCLUDE_DIR       = 
LIBRARY_DIR       = 
LDFLAGS         = -L.
LDLIBS = -lMPW -lpthread
CXXFLAGS    = -O3 -g -fPIC -DPERF_TIMING
TARGET_ARCH =  #-arch i386
INSTALL_PREFIX    = .

Test_objects = tests/Test.o
UnitTests_objects = tests/UnitTests.o
TestConcurrent_objects = tests/TestConcurrent.o
Amuse_objects = amuse/AmuseAgent.o
TestRestart_objects = tests/TestRestart.o
dg_objects   = DataGather.o
fw_objects = Forwarder.o
wcp_objects =  mpw-cp.o

# OS X
#SO_EXT = dylib
#SHARED_LINK_FLAGS = -dynamiclib

# Linux
SO_EXT = so
SHARED_LINK_FLAGS = -shared

all : MPWUnitTests MPWTest MPWTestConcurrent MPWDataGather MPWForwarder MPWFileCopy libMPW.a libMPW.$(SO_EXT)

install: libMPW.a libMPW.$(SO_EXT) MPWForwarder
	mkdir -p $(INSTALL_PREFIX)/lib
	mkdir -p $(INSTALL_PREFIX)/bin
	mkdir -p $(INSTALL_PREFIX)/include
	cp libMPW.$(SO_EXT)* $(INSTALL_PREFIX)/lib/
	cp libMPW.a  $(INSTALL_PREFIX)/lib/
	cp MPWForwarder $(INSTALL_PREFIX)/bin/
	cp MPWide.h $(INSTALL_PREFIX)/include/

libMPW.a: mpwide_perf.o MPWide.o Socket.o
	$(AR) $(ARFLAGS) $@ $^

libMPW.$(SO_EXT):  mpwide_perf.o MPWide.o Socket.o
	$(CXX) $(CXXFLAGS) $(SHARED_LINK_FLAGS) $(TARGET_ARCH) -dynamiclib -o $@ $^
#    ld -shared -soname libMPW.so.1 -o libMPW.so.1.0 -lc MPWide.o Socket.o

LINK_EXE = $(CXX) $(LDFLAGS) $(TARGET_ARCH) $< $(LOADLIBES) $(LDLIBS) -o $@

MPWUnitTests: $(UnitTests_objects) libMPW.a
	$(LINK_EXE)

MPWTest: $(Test_objects) libMPW.so
	$(LINK_EXE)

MPWTestConcurrent: $(TestConcurrent_objects) libMPW.a
	$(LINK_EXE)

MPWAmuseAgent: $(Amuse_objects) libMPW.a
	$(LINK_EXE)

MPWForwarder: $(fw_objects) libMPW.a
	$(LINK_EXE)

MPWDataGather: $(dg_objects) libMPW.a
	$(LINK_EXE)

MPWFileCopy: $(wcp_objects) libMPW.a
	$(LINK_EXE)

Test: tests/Test.cpp
TestConcurrent: tests/TestConcurrent.cpp
Forwarder: Forwarder.cpp

clean:
	rm -f *.o MPWUnitTests MPWTest MPWTestConcurrent MPWDataGather MPWForwarder MPWAmuseAgent MPWFileCopy libMPW.a libMPW.$(SO_EXT)* bin lib include tests/*.o
