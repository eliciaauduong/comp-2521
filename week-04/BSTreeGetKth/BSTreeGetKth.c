
#include <stdlib.h>

#include "BSTree.h"

int counter = 0;

int BSTreeGetKth(BSTree t, int k) {
	if (t == NULL) {
		return 0;
	}
	
	BSTreeGetKth(t->left, k);
	counter++;
	if (k == counter) {
		return k;
	}
	BSTreeGetKth(t->right, k);
}

