#include "EditDist.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <iomanip>

using namespace std;

EditDist::EditDist(char* s1, char* s2, int size1, int size2){

    x = s1;
    y = s2;
    for(int i = 0; i < size1; i++){
        z.AppendNode(s1[i]);
    } 
}

int EditDist::FindEditDist(char* x, char* y, int i, int j, int** memo){
    
    // If x is empty, then we need
    // to insert (j+1) characters
    if(i < 0){
        return (j+1);
    }
    // If y is emptym then we need
    // to delete (x+1) characters
    if(j < 0){
        return (i+1);
    }
    // If memo[i][j] already exist
    // return memo[i][j]
    if(memo[i][j] != -1){
        return memo[i][j];
    }
    // If x[i] is the same as y[j]
    // then memo[i][j] depend on
    // memo[i-1][j-1]
    if(x[i] == y[j]){
        memo[i][j] = FindEditDist(x, y, i-1, j-1, memo);
        return memo[i][j];
    }
    // Otherwise find the minimum
    // among insert, delete, and 
    // replace, then +1
    else{
        int inst = FindEditDist(x, y, i, j-1, memo);
        int delt = FindEditDist(x, y, i-1, j, memo);
        int repl = FindEditDist(x, y, i-1, j-1, memo);
        int min = FindMin(inst, repl, delt);
        memo[i][j] = min+1;
        return memo[i][j];
    }
}

int EditDist::FindMin(int inst, int repl, int delt){
    
    int min = inst;

    if(repl <= min){
        min = repl;
    }

    if(delt <= min){
        min = delt;
    }

    return min;
}

// This function retraces and calculates the minimum edit distance
void EditDist::TraceBack(int** memo, int i, int j, int& sum){
    if((i > 0) && (j > 0)){
        int min = FindMin(memo[i][j-1], memo[i-1][j-1], memo[i-1][j]);
        if(min == memo[i][j]){ // Move to right
            TraceBack(memo, i-1, j-1, sum);
            sum += 0;
        }
        else if(min == memo[i-1][j]){ // Delete
            TraceBack(memo, i-1, j, sum);
            sum += 2;
        }
        else if(min == memo[i][j-1]){ // Insert
            TraceBack(memo, i, j-1, sum);
            sum += 3;
        }
        else if(min == memo[i-1][j-1]){ // Replace
            TraceBack(memo, i-1, j-1, sum);
            sum += 4;
        }
    }
    else if((i == 0) && (j > 0)){
        TraceBack(memo, i, j-1, sum);
        sum += 3;
    }
    else if((i > 0) && (j == 0)){
        TraceBack(memo, i-1, j, sum);
        sum += 2;
    }
    else if((i == 0) && (j == 0)){
        if(memo[i][j] == 0){
            sum += 0;
        }
        else{
            sum += 4;
        }
    }
}

// This function retraces and calculates the minimum edit distance
// and print each step of operations
void EditDist::TraceBack(int** memo, int i, int j, ListNode* node, int& sum){
    ListNode* iNode;
    cout.setf(ios::left);
    if((i > 0) && (j > 0)){ 
        int min = FindMin(memo[i][j-1], memo[i-1][j-1], memo[i-1][j]);
        if(min == memo[i][j]){ // Move to right
            TraceBack(memo, i-1, j-1, node->prev, sum);
            sum += 0;
            cout << setw(16) << "right";
            PrintObj(node);
            cout << setw(8) << "0";
            cout << setw(8) << sum << endl;
        }
        else if(min == memo[i-1][j]){ // Delete
            ListNode* n;
            TraceBack(memo, i-1, j, node->prev, sum);
            n = node->prev;
            z.DeleteNode(node);
            sum += 2;
            cout << setw(7) << "delete " << setw(9) << x[i];
            PrintObj(n);
            cout << setw(8) << "2";
            cout << setw(8) << sum << endl;
            z.RemoveNode(node);
        }
        else if(min == memo[i][j-1]){ // Insert
            TraceBack(memo, i, j-1, node, sum);
            iNode = z.InsertNode(y[j], node->next);
            sum += 3;
            cout << setw(7) << "insert " << setw(9) << y[j];
            PrintObj(iNode);
            cout << setw(8) << "3";
            cout << setw(8) << sum << endl;
        }
        else if(min == memo[i-1][j-1]){ // Replace
            TraceBack(memo, i-1, j-1, node->prev, sum);
            z.ReplaceNode(y[j], node);
            sum += 4;
            cout << setw(11) << "replace by " << setw(5) << y[j];
            PrintObj(node);
            cout << setw(8) << "4";
            cout << setw(8) << sum << endl;
        }
    }
    // if it reaches the head of string x while
    // there are still some more characters in
    // string y, then insert those characters into
    // string x
    else if((i == 0) && (j > 0)){
        ListNode* n;
        n = node->next;
        TraceBack(memo, i, j-1, node, sum);
        iNode = z.InsertNode(y[j], n);
        sum += 3;
        cout << setw(7) << "insert " << setw(9) << y[j];
        PrintObj(iNode);
        cout << setw(8) << "3";
        cout << setw(8) << sum << endl;
    }
    // if it reaches the head of string y while
    // there are still more characters in string x,
    // delete those extra characters from string x
    else if((i > 0) && (j == 0)){
        ListNode* n;
        TraceBack(memo, i-1, j, node->prev, sum);
        n = node->prev;
        z.DeleteNode(node);
        sum += 2;
        cout << setw(7) << "delete " << setw(9) << x[i];
        PrintObj(n);
        cout << setw(8) << "2";
        cout << setw(8) << sum << endl;
        z.RemoveNode(node);
    }
    // if we reach the head of both string x
    // and string y
    else if((i == 0) && (j == 0)){
        // if the first character in string x
        // is the same as the first character
        // in string y, then we simply move to
        // the next character
        if(memo[i][j] == 0){
            sum += 0;
            cout << setw(16) << "right";
            PrintObj(node);
            cout << setw(8) << "0";
            cout << setw(8) << sum << endl;
        }
        // if the first character in string x 
        // is different from the first character
        // of string y, then replace x[0] by y[0]
        else{
            z.ReplaceNode(y[j], node);
            sum += 4;
            cout << setw(11) << "replace by " << setw(5) << y[j];
            PrintObj(node);
            cout << setw(8) << "4";
            cout << setw(8) << sum << endl;
        }
    }
}

void EditDist::PrintObj(ListNode* node){
    ListNode* curr;
    ListNode* next;
    cout.setf(ios::left);
    curr = z.getHead();
    while(curr){
        next = curr->next;
        cout << curr->val;
        if(curr == node){
            cout << '*';
        }
        if(curr == z.getTail()){
            cout << setw(31 - z.getSize()) << ""; 
        }
        curr = next;
    }
}

void EditDist::DeleteObj(){
    z.DeleteList();
}
/* eof */
