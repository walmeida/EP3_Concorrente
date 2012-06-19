IDIR = ./include
ODIR = obj
BDIR = bin

CC = g++
CFLAGS = -Wall -I$(IDIR) -g -O0
LIBS = -lpthread

EXE = montanharussa

_DEPS = passenger.h passengercreator.h thread.h timemanager.h car.h \
		rollercoastermonitor.h semaphoremonitor.h rankconditionvariable.h \
		orderedconditionvariable.h timemanager.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o passenger.o passengercreator.o thread.o timemanager.o car.o \
	   rollercoastermonitor.o semaphoremonitor.o rankconditionvariable.o \
	   orderedconditionvariable.o timemanager.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/$(EXE) *~ core $(INCDIR)/*~ 
