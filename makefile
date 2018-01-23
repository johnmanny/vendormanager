all: proj4

proj4: proj4.o vendor.o collection.o
	g++ proj4.o vendor.o collection.o -o proj4

proj4.o: proj4.cpp
	g++ -c proj4.cpp

vendor.o: vendor.cpp
	g++ -c vendor.cpp

collection.o: collection.cpp
	g++ -c collection.cpp

.PHONY: clean
clean:
	rm -f proj4.o vendor.o collection.o
	rm -f proj4
