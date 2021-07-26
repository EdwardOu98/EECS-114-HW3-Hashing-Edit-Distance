#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test();

int main(int argc, char* argv[]){
    
#ifdef DEBUG
    test();
#endif

#ifndef DEBUG
    int value;
    int nProbe;
    int nInsert = 0;
    int pSum = 0;
    int avg;
    HashTable ht;

    srand(time(0));

    // This while loop will fill the
    // table up to 90% full
    while(true){
        // generate a random number
        // between 0 and 100000
        value = rand() % 100000;
        // Try to put the value
        // into the table
        nProbe = ht.insert(value);
        // if the insert is successful
        // increment the number of insertions
        // and add the number of probes to 
        // the total number of probes up to
        // this successful insert
        if(nProbe != -1){
            nInsert++;
            pSum = pSum + nProbe;
        }

        // when the table is 50% full
        // calculate the average number of 
        // probes to insert a value into the
        // table
        if(ht.load_factor() == 0.5){
            avg = pSum / nInsert;
            printf("50%% full: %d\n", avg);
        }
        // when the table is 90% full
        // calculate the average number of
        // probes to insert a value into the
        // table
        else if(ht.load_factor() >= 0.9){
            avg = pSum / nInsert;
            printf("90%% full: %d\n", avg);
            break;
        }
    }

    ht.deleteTable();
#endif

    return 0;
}


void test(){

    int value;
    int nProbe;
    int Psum = 0;

    srand(time(0));
    
    HashTable ht;
/*
    for(int i = 0; i < 10; i++){
        value = rand() % 100000;
        printf("Value is: %d\n", value);
        nProbe = ht.insert(value);
        printf("nProbe = %d\n", nProbe);
        Psum = Psum + nProbe;

        printf("nProbe is: %d, sum is %d\n", nProbe, Psum);
    }
*/

    value = rand() % 100000;
    for(int i = 0; i < 5; i++){
        nProbe = ht.insert(value);
        printf("nProbe = %d\n", nProbe);
        Psum = Psum + nProbe;
    }
    int avg = Psum/10;
    printf("Average probes: %d\n", avg);
    ht.deleteTable();
}
