
OBJECTS = date.o

CFLAGS += -Wall -Wextra -Weffc++ -O2

all:

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

# Header dependencies
date.o: date.h
western_date.o: date.h western_date.h


.PHONY: clean
clean:
	-$(RM) $(OBJECTS)

