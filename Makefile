CC = g++
COPTFLAGS = -O3 -g

default:
	@echo "================================================="
	@echo "To build your program, use:"
	@echo "  make insert_test          #For hash insertion"
	@echo "  make search_test          #For hash search"
	@echo "  make edit_distance        #For edit distance"
	@echo ""
	@echo "To clean this directory (remove object files"
	@echo "and other junk), use:"
	@echo " make clean"
	@echo "================================================="

# Hash insertion driver
insert_test: HashTable.o insert_test.cc
	$(CC) $(COPTFLAGS) -o $@ $^

# Hash search driver
search_test: HashTable.o search_test.cc
	$(CC) $(COPTFLAG) -o $@ $^

# Edit distance driver
edit_distance: List.o EditDist.o edit_distance.cc
	$(CC) $(COPTFLAGS) -o $@ $^

# Hash Table functions
HashTable.o: HashTable.cc
	$(CC) $(COPTFLAGS) -o $@ -c $< -lm

# Doubly Linked List
List.o: List.cc
	$(CC) $(COPTFLAGS) -o $@ -c $<

# Edit Distance Functions
EditDist.o: EditDist.cc
	$(CC) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ insert_test search_test edit_distance

#eof
