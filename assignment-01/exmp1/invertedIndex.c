////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    invertedIndex.c                                                         //
//    Written by Elicia AU DUONG (z5260173)                                   //
//    COMP2521 - Assignment 1 - Information Retrieval                         //
//    Completed functions for part 1 and part 2                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "invertedIndex.h"
#include "InvertedIndexBST.h"
#include "TfIdfList.h"

#define WORD_LEN_MAX 100

static void printIndex(FILE *file, InvertedIndexBST tree);
double calculateTf(char *term, char *document);
double calculateIdf(char *term, int d, InvertedIndexBST tree);
/**
 * Normalises a given string. See the spec for details. Note: you should
 * modify the given string - do not create a copy of it.
 */
char *normaliseWord(char *str) {
    int len = strlen(str);

    // remove leading space
    if (str[0] == ' ') {
        for (int i = 0; i < (len - 1); i++) {
            str[i] = str[i + 1];
        }
    }

    // remove trailing space
    if (str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }

    // convert all characters to lowercase
    for (int i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }

    // remove the following punctuation marks for the end of a word
    // . , ; ?
    if (str[len - 1] == '.' || 
        str[len - 1] == ',' || 
        str[len - 1] == ';' || 
        str[len - 1] == '?') {
        str[len - 1] = '\0';
        len--;
    }

    return str;
}

/**
 * This function opens the collection file with the given name, and then
 * generates an inverted index from those files listed in the collection
 * file,  as  discussed  in  the spec. It returns the generated inverted
 * index.
 */
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    // generate inverted index
    InvertedIndexBST index = newInvertedIndex();
    
    // open the collection file
    FILE *collection = fopen(collectionFilename, "r");
    
    // for every file in collection.txt
    char filename[100]; 
    char *saveFile;
    while (fscanf(collection, "%s", filename) != EOF) {
        saveFile = (char *)calloc(WORD_LEN_MAX, sizeof(char));
        strcpy(saveFile, filename);
        FILE *wordFile = fopen(filename, "r");
        // open each file and get the words from the file
        char word[100];
        char *saveWord;
        while (fscanf(wordFile, "%s", word) != EOF) {
            char *normWord = normaliseWord(word);
            saveWord = (char *)calloc(WORD_LEN_MAX, sizeof(char));
            strcpy(saveWord, normWord);

            //
            double tf = calculateTf(saveWord, saveFile);

            // insert word into inverted index
            index = insertInvertedIndex(index, saveWord, saveFile, tf);
        }
        fclose(wordFile);
    }
    fclose(collection);
    
    return index;

}

/**
 * Outputs  the  given inverted index to a file named invertedIndex.txt.
 * The output should contain one line per word, with the  words  ordered
 * alphabetically  in ascending order. Each list of filenames for a word
 * should be ordered alphabetically in ascending order.
*/
void printInvertedIndex(InvertedIndexBST tree) {
    if (tree == NULL) return;
    FILE *output = fopen("invertedIndex.txt", "w");
    printIndex(output, tree);
    fclose(output);
}

static void printIndex(FILE *file, InvertedIndexBST tree) {
    if (tree == NULL) return;

    printIndex(file, tree->left);
    fprintf(file, "%s ", tree->word);
    FileList curr = tree->fileList;
    while (curr != NULL) {
        fprintf(file, "%s ", curr->filename);
        curr = curr->next;
    }
    fprintf(file, "\n");
    printIndex(file, tree->right);
}

/**
 * Returns  an  ordered list where each node contains a filename and the 
 * corresponding tf-idf value for a given searchWord. You only  need  to
 * include documents (files) that contain the given searchWord. The list
 * must  be  in  descending order of tf-idf value. If there are multiple
 * files with same  tf-idf  value,  order  them  by  their  filename  in
 * ascending order.
*/
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    TfIdfList orderedTfIdf = createTfIdfList();

    // find documents with the search word
    InvertedIndexBST treeTerm = findInvertedIndex(tree, searchWord);

    FileList curr = treeTerm->fileList;
    while (curr != NULL) {
        // calculate tfidf
        double tf = calculateTf(searchWord, curr->filename);
        double idf = calculateIdf(searchWord, D, tree);
        double tfidf = tf * idf;

        // add to list
        orderedTfIdf = insertTfIdfList(orderedTfIdf, curr->filename, tfidf);
        curr = curr->next;
    }  

    return orderedTfIdf;
}

/**
    tf(t, d) = (frequency of term t in d) / (number of words in d). 
*/
double calculateTf(char *term, char *document) {
    FILE *openFile = fopen(document, "r");

    double tf = 0;
    double termFrequency = 0;
    double wordCount = 0;
    char word[100];
    while (fscanf(openFile, "%s", word) != EOF) {
        if (strcmp(normaliseWord(word), term) == 0) {
            termFrequency++;
        }
        wordCount++;
    }
    tf = (termFrequency / wordCount);
    fclose(openFile);
    return tf;
}

/**
    calculate inverse document frequency idf(t, D)
    dividing the total number of documents by the number of documents containing the term
    and then taking the logarithm of that quotient
*/
double calculateIdf(char *term, int d, InvertedIndexBST tree) {
    double idf = 0;
    double termDoc = 0;

    InvertedIndexBST treeTerm = findInvertedIndex(tree, term);
    FileList curr = treeTerm->fileList;
    while (curr != NULL) {
        termDoc++;
        curr = curr->next;
    }
    idf = log10(d / termDoc);
    return idf;
}
/**
 * Returns  an  ordered list where each node contains a filename and the
 * summation of tf-idf values of all the matching search words for  that
 * file.  You only need to include documents (files) that contain one or
 * more of the given search words. The list must be in descending  order
 * of summation of tf-idf values (tfIdfSum). If there are multiple files
 * with  the  same tf-idf sum, order them by their filename in ascending
 * order.
 */
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    
    TfIdfList unorderedTfIdf = createTfIdfList();
    int i = 0;
    while (searchWords[i] != NULL) {
        InvertedIndexBST wordNode = findInvertedIndex(tree, searchWords[i]);
        FileList curr = wordNode->fileList;
        while (curr != NULL) {
            
            // calculate tfidf
            double tf = curr->tf;
            double idf = calculateIdf(searchWords[i], D, tree);
            double tfidf = tf * idf;
            int check = inTfIdf(unorderedTfIdf, curr->filename);
            
            // if not in unordered list
            if (check == 0) {
                unorderedTfIdf = insertTfIdfList(unorderedTfIdf, curr->filename, tfidf);
            } 
            // in unordered list
            // update tfidf
            if (check != 0){ 
                unorderedTfIdf = updateTfIdfList(unorderedTfIdf, curr->filename, tfidf);
                curr->tf += tfidf;
            }
            curr = curr->next;
        }
        i++;
    }
    TfIdfList orderedTfIdf = createTfIdfList();
    TfIdfList uList = unorderedTfIdf;
    while (uList != NULL) {
        orderedTfIdf = insertTfIdfList(orderedTfIdf, uList->filename, uList->tfIdfSum);
        uList = uList->next;
    }
    return orderedTfIdf;

}