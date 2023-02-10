OBJDIR=obj
BINDIR=bin
TSTDIR=tests

DIRS=$(OBJDIR) $(BINDIR) $(TSTDIR)
OBJS=$(OBJDIR)/misc.o $(OBJDIR)/activation.o $(OBJDIR)/neuron.o $(OBJDIR)/layer.o $(OBJDIR)/network.o
TESTS=tests/color_recognition

all: $(DIRS) \
	 $(OBJS) \
	 $(TESTS)

CC=g++

# Default CFLAG - no code coverage
CFLAGS=-g -Wwrite-strings -fextended-identifiers -std=c++14

clean:
	rm $(OBJDIR)/*.o *.gcov *.gcno *.gcda

$(OBJDIR):
	if [ ! -f $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi

$(BINDIR):
	if [ ! -f $(BINDIR) ]; then mkdir -p $(BINDIR); fi

$(TSTDIR):
	if [ ! -f $(TSTDIR) ]; then mkdir -p $(TSTDIR); fi

$(OBJDIR)/misc.o: src/constants.h src/misc.cpp
	$(CC) -c src/misc.cpp -o $(OBJDIR)/misc.o $(CFLAGS)

$(OBJDIR)/activation.o: src/activation.h src/activation.cpp src/constants.h
	$(CC) -c src/activation.cpp -o $(OBJDIR)/activation.o $(CFLAGS)

$(OBJDIR)/neuron.o: src/neuron.h src/neuron.cpp $(OBJDIR)/activation.o src/constants.h
	$(CC) -c src/neuron.cpp -o $(OBJDIR)/neuron.o $(CFLAGS)

$(OBJDIR)/layer.o: src/layer.h src/layer.cpp $(OBJDIR)/neuron.o src/constants.h
	$(CC) -c src/layer.cpp -o $(OBJDIR)/layer.o $(CFLAGS)

$(OBJDIR)/network.o: src/network.h src/network.cpp $(OBJDIR)/layer.o src/constants.h
	$(CC) -c src/network.cpp -o $(OBJDIR)/network.o $(CFLAGS)

tests/color_recognition: src/tests/color_recognition.cpp $(OBJS)
	$(CC) src/tests/color_recognition.cpp $(OBJS) -o tests/color_recognition $(CFLAGS)







