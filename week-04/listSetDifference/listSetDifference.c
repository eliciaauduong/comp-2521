#include "list.h"

List addDiff(List l, Node n);

List listSetDifference(List l1, List l2) {
    List difference = newList();
    Node curr1 = l1->head;
    Node curr2 = l2->head;

    int inList2 = 0;
    while (curr1 != NULL) {
        inList2 = 0;
        curr2 = l2->head;
        while (curr2 != NULL) {
            if (curr1->value == curr2->value) {
                inList2 = 1;
                break;
            }
            curr2 = curr2->next;
        }
        if (inList2 == 0) {
            Node new = newNode(curr1->value);
            difference = addDiff(difference, new);
        }
        curr1 = curr1->next;
    }
    return difference;
}

List addDiff(List l, Node n) {
    if (l->head == NULL) {
        l->head = n;
        return l;
    }
    
    Node tmp = l->head->next;
    l->head->next = n;
    n->next = tmp;

    return l;
}