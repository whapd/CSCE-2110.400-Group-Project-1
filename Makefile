CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
OBJS = main.o Utils.o Resource.o ResourceManager.o ReservationSystem.o Reservation.o ReservationManager.o CancellationTracker.o

all: reservation_system

reservation_system: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o reservation_system

.PHONY: clean
