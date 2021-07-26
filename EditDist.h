#ifndef EDITDIST_H
#define EDITDIST_H

#include "List.h"

class EditDist{
    public:
    EditDist(char* s1, char* s2, int size1, int size2);

    /* Functions */
    int FindEditDist(char* x, char* y, int i, int j, int** memo);
    int FindMin(int inst, int repl, int delt);
    void TraceBack(int** memo, int i, int j, int& sum);
    void TraceBack(int** memo, int i, int j, ListNode* node, int& sum);
    void PrintObj(ListNode* node);
    void DeleteObj();

    /* Getter */
    DList getList() { return z; }

    /* Parameters */
    private:
    char* x;
    char* y;
    DList z;
};

#endif
