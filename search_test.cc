#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

void test();

int main (int argc, char* argv[]){

#ifdef DEBUG
    test();
#endif

#ifndef DEBUG
    int value;
    int* nProbe;
    nProbe = new int;
    int pSum = 0;
    int avg;
    HashTable ht;

    srand(time(0));

   // This while loop will load the table
   // up to 50% full 
    while(true){
        value = rand() % 100000;
        ht.insert(value);
        if(ht.load_factor() == 0.5){
            break;
        }
    }

    // This for-loop does the following:
    // 1. Generate a random value between 0 and 100000
    // 2. Try to find it in the table
    // 3. Calculate the total number of probes
    //    required to perform a search when the
    //    table is 50% full
    for(int t = 0; t < 10000; t++){
        value = rand() % 100000;
        ht.find(value, *nProbe);
        pSum = pSum + *nProbe;
    }

    // Calculate the average number of probes
    // required to perform a search when the 
    // table is 50% full
    avg = pSum / 10000;
    printf("50%% full: %d\n", avg);

   // This while loop will load the table
   // up to 90% full 
    while(true){
        value = rand() % 100000;
        ht.insert(value);
        if(ht.load_factor() >= 0.9){
            break;
        }
    }

    // This for-loop does the following:
    // 1. Generate a random value between 0 and 100000
    // 2. Try to find it in the table
    // 3. Calculate the total number of probes
    //    required to perform a search when the
    //    table is 90% full
    for(int t = 0; t < 10000; t++){
        value = rand() % 100000;
        ht.find(value, *nProbe);
        pSum = pSum + *nProbe;
    }

    // Calculate the average number of probes
    // required to perform a search when the 
    // table is 90% full
    avg = pSum / 20000;
    printf("90%% full: %d\n", avg);

    ht.deleteTable();
    delete nProbe;
#endif
    return 0;
}

void test(){
    int value;
    int val;
    int* nProbe;
    nProbe = new int;
    int pSum = 0;
    bool isFound = false;
    HashTable ht;

    srand(time(0));

    val = value = rand() % 100000;
    *nProbe = ht.insert(value);
    printf("nProbe = %d\n", *nProbe);

    isFound = ht.find(val, *nProbe);
    if(isFound){
        printf("Value found! nProbe = %d\n", *nProbe);
    }
    else{
        printf("Value not found. nProbe = %d\n", *nProbe);
    }

    isFound = ht.find(150, *nProbe);
    if(isFound){
        printf("Value found! nProbe = %d\n", *nProbe);
    }
    else{
        printf("Value not found. nProbe = %d\n", *nProbe);
    }

    ht.deleteTable();
    delete nProbe;
}
