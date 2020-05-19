// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* 
    You will submit only this one file.

    Implement the function "mergeOrdered" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

List mergeOrdered(List list1, List list2) {
    List merged = newList();

    Node *node1 = list1->first;
    Node *node2 = list2->first;
    if (node1 == NULL) {
        Node *new = newNode(node2->value);
        merged->first = merged->last = new;
        node2 = node2->next;
        Node *curr = merged->first;
        while (node2 != NULL) {
            new = newNode(node2->value);
            curr->next = merged->last = new;
            node2 = node2->next;
            curr = curr->next;
        }
        return merged;
    }
    else if (node2 == NULL) {
        Node *new = newNode(node1->value);
        merged->first = merged->last = new;
        node1 = node1->next;
        Node *curr = merged->first;
        while (node1 != NULL) {
            new = newNode(node1->value);
            curr->next = merged->last = new;
            node1 = node1->next;
            curr = curr->next;
        }
        return merged;
    } 
    else {
        if (node1->value <= node2->value) {
            Node *new = newNode(node1->value);
            merged->first = merged->last = new;
            node1 = node1->next;
        } else {
            Node *new = newNode(node2->value);
            merged->first = merged->last = new;
            node2 = node2->next;
        }
        Node *curr = merged->first;
        while (node1 != NULL && node2 != NULL) {
            if (node1 == NULL) {
                Node *new = newNode(node2->value);
                curr->next = merged->last = new;
                node2 = node2->next;
                curr = merged->last;
                while (node2 != NULL) {
                    new = newNode(node2->value);
                    curr->next = merged->last = new;
                    node2 = node2->next;
                    curr = curr->next;
                }
                return merged;
            }
            else if (node2 == NULL) {
                Node *new = newNode(node1->value);
                curr->next = merged->last = new;
                node1 = node1->next;
                curr = merged->last;
                while (node1->value != list1->last->value) {
                    new = newNode(node1->value);
                    curr->next = merged->last = new;
                    node1 = node1->next;
                    curr = merged->last;
                }
                return merged;
            } 
            else {
                if (node1->value <= node2->value) {
                    Node *new = newNode(node1->value);
                    curr->next = merged->last = new;
                    node1 = node1->next;
                } else {
                    Node *new = newNode(node2->value);
                    curr->next = merged->last = new;
                    node2 = node2->next;
                }
            }
            curr = curr->next;
        }

        if (node1 != NULL) {
            Node *last = newNode(node1->value);
            curr->next = last;
        }
        else if (node2 != NULL) {
            curr->next = node2;
        }
    }

    return merged;
}