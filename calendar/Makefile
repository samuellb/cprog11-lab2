
OBJECTS = date.o western_date.o gregorian.o kattistime.o

CFLAGS += -Wall -Wextra -Weffc++ -O2

all:

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

# Header dependencies
date.o: date.h kattistime.h
western_date.o: date.h western_date.h
gregorian.o: date.h western_date.h gregorian.h
test.o: date.h western_date.h gregorian.h


test: $(OBJECTS) test.o
	$(CXX) $(CFLAGS) $(OBJECTS) test.o -o test

datetest: $(OBJECTS) datetest.o
	$(CXX) $(CFLAGS) $(OBJECTS) datetest.o -o datetest


.PHONY: clean
clean:
	-$(RM) $(OBJECTS)

