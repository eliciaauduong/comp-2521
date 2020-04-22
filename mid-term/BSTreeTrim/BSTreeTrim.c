////////////////////////////////////////////////////////////////////////////////
//																			  //
//	Written by Elicia AU DUONG (z5260173)									  //
//	COMP2521 Midterm Exam 20T1								             	  //
//  Question 2 - BSTreeTrim								                 	  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree smallestNode(BSTree t);
BSTree deleteNode(BSTree t);

// take a BST and a lower and upper bound
// delete and free all nodes containing values between the bounds (inclusive)
// return the root of the updated BST

// assume lower <= upper & BST does not have duplicate values
// DO NOT use array
// DO NOT dynamically allocate memory (e.g. with malloc)
BSTree BSTreeTrim(BSTree t, int lower, int upper) {
	if (t == NULL) {
		return NULL;
	}

    t->left = BSTreeTrim(t->left, lower, upper); 
    t->right = BSTreeTrim(t->right, lower, upper); 
  
    if (t->value >= lower && t->value <= upper) {
        return deleteNode(t); 
	}

	return t;
}

// find the smallest node in a binary search tree
BSTree smallestNode(BSTree t) {
	if (t == NULL) {
		return NULL;
	}
	while (t->left != NULL) {
		t = t->left;
	}
	return t;
}

// delete and restructure the binary search tree
BSTree deleteNode(BSTree t) { 
	// delete leaf node
	if (t->left == NULL && t->right == NULL) {
		free(t);
		return NULL;
	}

	// only left subtree becomes new root
	if (t->left != NULL && t->right == NULL) {
		BSTree tmp = t->left;
		free(t);
		return tmp;
	}
	// only right subtree becomes new root
	if (t->left == NULL && t->right != NULL) {
		BSTree tmp = t->right;
		free(t);
		return tmp;
	}
  
    // node with two children
	BSTree tmp = t->right;
    BSTree next = smallestNode(tmp); 
	BSTree left = t->left;
	free(t);
	// connect left tree to right tree
    next->left = left;

    return tmp; 
} 
  
