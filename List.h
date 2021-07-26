#ifndef LIST_H
#define LIST_H

struct ListNode{
    /* define a list node type */
    char val;
    ListNode* prev;
    ListNode* next;
};

class DList {
    public:
    DList();

    /* Functions for Modifying the List */
    ListNode* CreateNode(char value);
    void RemoveNode(ListNode* node);
    void AppendNode(char value);
    ListNode* InsertNode(char value, ListNode* node);
    void ReplaceNode(char value, ListNode* node);
    void DeleteNode(ListNode* node);
    void DeleteList();
    void PrintList();

    /* Getters */
    int getSize() { return size; }
    ListNode* getHead() { return Head; }
    ListNode* getTail() { return Tail; }

    private:
    int size;
    ListNode* Head;
    ListNode* Tail;
};

#endif
