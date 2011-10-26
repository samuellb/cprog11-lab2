
OBJECTS = date.o western_date.o gregorian.o julian.o kattistime.o

CFLAGS += -Wall -Wextra -Weffc++ -O2

all:

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

# Header dependencies
date.o: date.h kattistime.h
western_date.o: date.h western_date.h
gregorian.o: date.h western_date.h gregorian.h
julian.o: date.h western_date.h julian.h
test.o: date.h western_date.h gregorian.h julian.h
calendar.o: date.h calendar.h
calendar_test.o: date.h calendar.h
cprog09lab23.o: calendar.h date.h

test: $(OBJECTS) test.o
	$(CXX) $(CFLAGS) $(OBJECTS) test.o -o test

datetest: $(OBJECTS) datetest.o
	$(CXX) $(CFLAGS) $(OBJECTS) datetest.o -o datetest

calendar_test: $(OBJECTS) calendar_test.o
	$(CXX) $(CFLAGS) $(OBJECTS) calendar_test.o -o calendar_test

cprog09lab23: $(OBJECTS) cprog09lab23.o
	$(CXX) $(CFLAGS) $(OBJECTS) cprog09lab23.o -o cprog09lab23


.PHONY: clean
clean:
	-$(RM) $(OBJECTS)

