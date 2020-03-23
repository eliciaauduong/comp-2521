
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "InvertedIndexBST.h"
#include "invertedIndex.h"
#include "FileList.h"

// create an empty InvertedIndexBST
InvertedIndexBST newInvertedIndex (void) {
    return NULL;
}

// make a new node containing a value
static InvertedIndexBST newIndexNode (char *word, char *filename, double tf)
{
	InvertedIndexBST new = malloc (sizeof *new);
	new->word = word;
	FileList listFiles = createList();
    new->fileList = insertList(listFiles, filename, tf);
	new->left = new->right = NULL;
	return new;
}

// insert a new value into a InvertedIndexBST
InvertedIndexBST insertInvertedIndex (InvertedIndexBST b, char *word, char *filename, double tfidf) {
    if (b == NULL)
		return newIndexNode(word, filename, tfidf);
	else if (strcmp(word,b->word) < 0)
		b->left = insertInvertedIndex(b->left, word, filename, tfidf);
	else if (strcmp(word,b->word) > 0)
		b->right = insertInvertedIndex(b->right, word, filename, tfidf);
	else
		b->fileList = insertList(b->fileList, filename, tfidf);
	return b;
}

// count #nodes in InvertedIndexBST
int nodesInvertedIndex (InvertedIndexBST b) {
    if (b == NULL)
		return 0;
	else
		return 1 + nodesInvertedIndex (b->left) + nodesInvertedIndex (b->right);
}

// check whether a word is in a InvertedIndexBST
int findInvertedIndex (InvertedIndexBST b, char *word) {
    if (b == NULL)
		return 0;
	else if (strcmp(word,b->word) < 0)
		return findInvertedIndex(b->left, word);
	else if (strcmp(word,b->word) > 0)
		return findInvertedIndex(b->right, word);
	else // (v == b->word)
		return 1;
}