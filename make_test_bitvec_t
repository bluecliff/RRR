test_bitvec_t:test_bitvec_t.o bitvector.o commons.o
	g++ -o test_bitvec_t -g test_bitvec_t.o bitvector.o commons.o
test_bitvec_t.o:test_bitvec_t.cpp
	g++ -c -g test_bitvec_t.cpp
bitvector.o:bitvector.cpp bitvector.h
	g++ -c -g bitvector.cpp
commons.o:commons.cpp commons.h
	g++ -c -g commons.cpp
clean:
	rm test_bitvec_t test_bitvec_t.o bitvector.o commons.o
