#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

HashTable::HashTable(){
    load = 0;
    nElem = 0;
    nSlot = 65536;

    table = new int[nSlot];
    
    //Initialize the table with -1
    for(int i = 0; i < nSlot; i++){
        table[i] = -1;
    } 
}

int HashTable::insert (int value){
    int probe = 0;
    bool avail = false;


    int i = nSlot * fmod(value * A, 1);
    int k;

    for(int j = 0; j < nSlot; j++){
        // Calculate its hash value using
        // linear probing
        k = (i + probe) % nSlot;
        probe++;
        // If the table[k] is not initialzied
        // with any value, then set the slots
        // to the input value and increment the
        // number of elements in the table, then
        // recalculate the load factor of the table
        // and break from the loop
        if(table[k] == -1){
            table[k] = value;
            avail = true;
            nElem++;
            load = (double) nElem / (double) nSlot;
            break;
        }
    }
    // If there is not slots available after going through
    // the whole table, then set the number of probes to -1
    if(!avail){
        probe = -1;
    }

    return probe;
}

bool HashTable::find (int value, int& nProbes){

    int probe = 0;
    int i = nSlot * fmod(value * A, 1);
    int k;

    for(int j = 0; j < nSlot; j++){
        // Calculate the hash value using
        // linear probing
        k = (i + probe) % nSlot;
        probe++;
        // If the input value is found, 
        // store the current number of 
        // probes into variable nProbes
        // and return true
        if(table[k] == value){
            nProbes = probe;
            return true;
        }
        // If table[k] is -1, which means
        // that slot has never been initialized,
        // then store the number of probes and
        // return false
        else if(table[k] == -1){
            nProbes = probe;
            return false;
        }
    }
    // If the table is full and the input isn't
    // found, store number of probes and return
    // false
    nProbes = probe;
    return false;
}

void HashTable::deleteTable(){
    delete[] table;
}
