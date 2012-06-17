IDIR = ./include
ODIR = obj
BDIR = bin

CC = g++
CFLAGS = -Wall -I$(IDIR) -O2
LIBS = -lpthread

EXE = montanharussa

_DEPS = passenger.h passengerCreator.h thread.h timeManager.h car.h \
		conditionvariable.h semaphoremonitor.h rollercoastermonitor.h

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Passenger.o PassengerCreator.o thread.o TimeManager.o \
	   semaphoremonitor.o car.o rollercoastermonitor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/$(EXE) *~ core $(INCDIR)/*~ 
