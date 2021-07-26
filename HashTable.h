#ifndef HASHTABLE_H
#define HASHTABLE_H

#define A 0.6180339887

class HashTable
{
  public:
  HashTable ();
  /* implement copy constructor, assignment, destructor if needed */

  int insert (int value); 
  /* insert the input value and return the number of probes
   * return -1 if the table is full and insert fails */

  bool find (int value, int& nProbes);  
  /* Search for the input value in table
   * Return true if the search is successful, otherwise false
   * Save # probes in 'nProbes' */

  void deleteTable();
  /* Deallocates the memory allocated for the table */

  // getters
  int capacity() { return nSlot; }
  int size() { return nElem; }
  double load_factor() { return load; }

  private:
  /* declare your data */
  double load;     // track the load factor of table
  int    nSlot;    // # slots i.e. max # elements can hold 
  int    nElem;    // current # elements in table
  int*   table;
};


#endif
