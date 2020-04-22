////////////////////////////////////////////////////////////////////////////////
//																			  //
//	Written by Elicia AU DUONG (z5260173)									  //
//	COMP2521 Midterm Exam 20T1								             	  //
//  Question 1 - listGetAbnormals    					                 	  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List addAbnormal(List l, int v);

// Take in a doubly-linked list of integers l and an integer threshold
// Return a new doubly-linked list with all "abnormal" values from the list

// Abnormal value if both of the following are true:
// abs(value - previous value) >= threshold
// abs(value - next value) >= threshold

// return new list of values in the same order as original
// assume threshold is non-negative
// DO NOT modify given list
// DO NOT use arrays
List listGetAbnormals(List l, int threshold) {
	List abnormal = newList();

	// for every value in the original list
	Node curr = l->first;
	while (curr != NULL) {
		// check if there are previous and next values to compare
		if (curr->prev != NULL && curr->next != NULL) {
			// check if a number is abnormal
			if (abs(curr->value - curr->prev->value) >= threshold
			&& abs(curr->value - curr->next->value) >= threshold) {
				// append to list of abnormal numbers
				abnormal = addAbnormal(abnormal, curr->value);
			}
		}
		curr = curr->next;
	}

	return abnormal;
}

// append to doubly-linked list
List addAbnormal(List l, int v) {
	Node new = newNode(v);
	if (l->first == NULL) {
		l->first = new;
		l->last = new;
	} else {
		l->last->next = new;
		new->prev = l->last;
		l->last = new;
	}
	l->size++;
	return l;
}