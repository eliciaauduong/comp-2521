#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "invertedIndex.h"
#include "InvertedIndexBST.h"

#define WORD_LEN_MAX 100

static void printIndex(FILE *file, InvertedIndexBST tree);

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

            // insert word into inverted index
            index = insertInvertedIndex(index, saveWord, saveFile, 0);
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