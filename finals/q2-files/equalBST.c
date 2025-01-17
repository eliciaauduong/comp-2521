// equalBST.c ... implementation of equalBST function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

/* 
    You will submit only this one file.

    Implement the function "equalBST" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

int equalBST(BSTree t1, BSTree t2) {
	if (t1 == NULL && t2 == NULL) {
        return 1;
    }
    else if (t1 == NULL && t2 != NULL) {
        return 0;
    } 
    else if (t1 != NULL && t2 == NULL) {
        return 0;
    }
    else {
        if (t1->key == t2->key && equalBST(t1->left, t2->left) && equalBST(t1->right, t2->right)) {
            return 1;
        } 
        else {
            return 0;
        }
    }
	return 0;
}

