#include "List.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DList::DList(){
    size = 0;
    Head = NULL;
    Tail = NULL;
}

// This function allocates memory for 
// a new node
ListNode* DList::CreateNode(char value){
    ListNode* node = new ListNode;
    node->val = value;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

// This function deallocates memory
// for the input node
void DList::RemoveNode(ListNode* node){
    assert(node);
    delete node;
}

// This function add a new node
// to the end of the list
void DList::AppendNode(char value){
    ListNode* node;
    node = CreateNode(value);
    assert(node);

    if(Tail){
        Tail->next = node;
        node->prev = Tail;
        Tail = node;
        size++;
    }
    else{
        Head = node;
        Tail = node;
        size++;
    }
}

// This function inserts a new node in front 
// of the input node
ListNode* DList::InsertNode(char value, ListNode* node){
    assert(node);
    ListNode* NewNode;
    NewNode = CreateNode(value);
    assert(NewNode);

    if(node == Head){
        node->prev = NewNode;
        NewNode->next = node;
        Head = node;
    }
    else{
        node->prev->next = NewNode;
        NewNode->prev = node->prev;
        node->prev = NewNode;
        NewNode->next = node;
    }
    size++;
    return NewNode;
}

// This function replaces the value of the 
// input node by the input value
void DList::ReplaceNode(char value, ListNode* node){
    assert(node);
    node->val = value;
}

// This function deletes the input node from
// the list
void DList::DeleteNode(ListNode* node){
    assert(node);
    if(node->prev){
        node->prev->next = node->next;
    }
    else{
        if(node->next){
            node->next->prev = NULL;
        }
        Head = node->next;
    }

    if(node->next){
        node->next->prev = node->prev;
    }
    else{
        if(node->prev){
            node->prev->next = NULL;
        }
        Tail = node->prev;
    }

    size--;
}

// This function deletes the whole
// list
void DList::DeleteList(){
    ListNode* curr = Head;
    ListNode* next;

    while(curr){
        next = curr->next;
        DeleteNode(curr);
        RemoveNode(curr);
        curr = next;
    }
}

// This function prints the content
// of the list (for debugging use)
void DList::PrintList(){
    ListNode* node = Head;

    while(node){
        printf("%c ", node->val);
        if(node == Tail){
            printf("\n");
        }
        node = node->next;
    }
}
