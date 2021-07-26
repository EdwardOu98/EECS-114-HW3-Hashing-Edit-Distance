#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <iomanip>

#include "List.h"
#include "EditDist.h"

using namespace std;

void print_head()
{
  cout.setf(ios::left);
  cout << setw(16) << "Operation" 
       << setw(32) << "z" 
       << setw(8) << "Cost" 
       << setw(8) << "Total" << endl;

  for (int i=0; i<64; ++i) cout << "-";
  cout << endl;
}


int main(int argc, char* argv[])
{
  char* s1;
  char* s2;
  int size1 = -1;
  int size2 = -1;
  // If there are more than 2 command line
  // arguments, then use this if-block to
  // convert the arguments into the original
  // string and target string
  if(argc > 2){
      int len1 = 0;
      int len2 = 0;
      int ind = 0;
      // This for-loop keeps track of
      // the length of all the command
      // line arguments between index 0
      // and the index of "to", which 
      // separates the target string from
      // the original string
      for(int i = 1; i < argc; i++){
          if(0 == strcmp(argv[i], "to")){
              ind = i;
              break;
          }
          else{
              len1 = len1 + strlen(argv[i]) + 1;
          }
      }
      s1 = new char[len1];
      int j = 1;
      // This while-loop puts all the command
      // line arguments between index 0 and the
      // index of "to" into a string, which will
      // be the original string
      while(j < ind){
          if((j == 1) && (j != (ind-1))){
              strcpy(s1, argv[j]);
              strcat(s1, " ");
          }
          else if((j == 1) && (j == (ind-1))){
              strcpy(s1, argv[j]);
              s1[len1-1] = '\0';
          }
          else if (j != (ind-1)){
              strcat(s1, argv[j]);
              strcat(s1, " ");
          }
          else{
              strcat(s1, argv[j]);
              s1[len1-1] = '\0';
          }
          j++;
      }
      size1 = strlen(s1);
      // This for-loop keeps track of the length
      // of all the remaining command line arguments
      // after the index of "to"
      for(int l = ind+1; l < argc; l++){
          len2 = len2 + strlen(argv[l]) + 1;
      }
      s2 = new char[len2];
      int k = ind + 1;
      // This while-loop puts all the remaining command
      // line arguments after the index of "to" in to a
      // string, which will be the target string
      while(k < argc){
          if((k == (ind + 1)) && (k != (argc-1))){
              strcpy(s2, argv[k]);
              strcat(s2, " ");
          }
          else if((k == (ind + 1)) && (k == (argc-1))){
              strcpy(s2, argv[k]);
              s2[len2-1] = '\0';
          }
          else if(k != (argc-1)){
              strcat(s2, argv[k]);
              strcat(s2, " ");
          }
          else{
              strcat(s2, argv[k]);
              s2[len2-1] = '\0';
          }
          k++;
      }
      size2 = strlen(s2);
  }
  // If there are only 2 command line arguments, use the
  // following block of code the open the input file
  // specified by the seconde argument and read its content
  // as the original string and target string
  else if(argc == 2){
      FILE* fp;
      // if file isn't found, then show an error message
      // and terminate the program
      if((fp = fopen(argv[1], "r")) == NULL){
          printf("Failed to open file %s\n", argv[1]);
          exit(10);
      }
      char len1[5];
      char len2[5];
      // Read the length of the first string
      fgets(len1, 5, fp);
      size1 = atoi(len1);
      s1 = new char[size1+1];
      // Read the content of the first string
      fgets(s1, size1+1, fp);
      // Read the last two characters so that
      // the next fgets will start reading from the
      // next line
      fgets(len1, 2, fp);
      // Read the length of the second string
      fgets(len2, 5, fp);
      size2 = atoi(len2);
      s2 = new char[size2+1];
      // Read the content of the second string
      fgets(s2, size2+1, fp);
      fclose(fp);
  }
  // if there's only one command line argument, 
  // prompt the user about how to run this program
  else{

        fprintf(stderr, "usage: 1. %s <str1> to <str2>\n", argv[0]);
        fprintf(stderr, "          where <str1> is the original string and <str2> is the target string\n");
        fprintf(stderr, "       2. %s <filename>\n", argv[0]);
        fprintf(stderr, "          where <filename> is the name of the input file\n");
        return -1;
  }

  // The following lines of codes creates a 2d array
  // where the minimum number of operations will be 
  // stored
  int** memo;
  memo = new int*[size1];

  for(int i = 0; i < size1; i++){
      memo[i] = new int[size2];
  }

  // Initialize memo to -1
  for(int j = 0; j < size1; j++){
      for(int k = 0; k < size2; k++){
          memo[j][k] = -1;
      }
  }

  // Create an object used for calculating edit distance
  EditDist ed(s1, s2, size1, size2);
  // By calling the FindEditDist function we can find
  // the minimum number of operations to convert the original
  // string s1 to the target string s2
  ed.FindEditDist(s1, s2, size1-1, size2-1, memo);
  // This variable will be used to keep track of the total
  // cost of conversion when we retrace the transformation
  // sequence
  int* cost;
  int sum = 0;
  cost = &sum;
  if(argc > 2){
      // Find the minimum cost
      ed.TraceBack(memo, size1-1, size2-1, *cost);
      cout << "Edit Distance: " << *cost << endl;
      *cost = 0;
      print_head();
      cout.setf(ios::left);
      cout << setw(16) << "initial string"
           << "*" << setw(31) << s1
           << setw(8) << "0"
           << setw(8) << "0" << endl;
      // Retrace the transformation sequence and print the
      // sequence out
      ed.TraceBack(memo, size1-1, size2-1, ed.getList().getTail(), *cost);
  }
  else{
      // Find the minimum cosr
      ed.TraceBack(memo, size1-1, size2-1, *cost);
      cout << "Edit Distance: " << *cost << endl;
  }
  ed.DeleteObj();

  for(int l = 0; l < size1; l++){
      delete[] memo[l];
  }

  delete[] memo;

  delete[] s1;
  delete[] s2;
  
  return 0;
}
