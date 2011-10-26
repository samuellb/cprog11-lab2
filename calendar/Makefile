
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
cprog09lab22a.o: date.h julian.h
cprog09lab22b.o: date.h gregorian.h
cprog09lab22c.o: date.h julian.h gregorian.h
cprog09lab23.o: calendar.h date.h

test: $(OBJECTS) test.o
	$(CXX) $(CFLAGS) $(OBJECTS) test.o -o test

datetest: $(OBJECTS) datetest.o
	$(CXX) $(CFLAGS) $(OBJECTS) datetest.o -o datetest

calendar_test: $(OBJECTS) calendar_test.o
	$(CXX) $(CFLAGS) $(OBJECTS) calendar_test.o -o calendar_test

cprog09lab22a: $(OBJECTS) cprog09lab22a.o
	$(CXX) $(CFLAGS) $(OBJECTS) cprog09lab22a.o -o cprog09lab22a

cprog09lab22b: $(OBJECTS) cprog09lab22b.o
	$(CXX) $(CFLAGS) $(OBJECTS) cprog09lab22b.o -o cprog09lab22b

cprog09lab22c: $(OBJECTS) cprog09lab22c.o
	$(CXX) $(CFLAGS) $(OBJECTS) cprog09lab22c.o -o cprog09lab22c

cprog09lab23: $(OBJECTS) cprog09lab23.o
	$(CXX) $(CFLAGS) $(OBJECTS) cprog09lab23.o -o cprog09lab23


.PHONY: clean
clean:
	-$(RM) $(OBJECTS) cprog09lab22a.o cprog09lab22a cprog09lab22b.o cprog09lab22b cprog09lab22c.o cprog09lab22c cprog09lab23.o cprog09lab23 calendar_test.o calendar_test datetest.o datetest test.o test

