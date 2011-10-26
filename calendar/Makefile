
OBJECTS = date.o western_date.o gregorian.o kattistime.o test.o

CFLAGS += -Wall -Wextra -Weffc++ -O2

all:

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

# Header dependencies
date.o: date.h kattistime.h
western_date.o: date.h western_date.h
gregorian.o: date.h western_date.h gregorian.h
test.o: date.h western_date.h gregorian.h


test: $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o test

.PHONY: clean
clean:
	-$(RM) $(OBJECTS)

