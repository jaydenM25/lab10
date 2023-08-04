#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
typedef struct Trie {
    struct Trie * children[26];
    int count;
}Trie;

// Initializes a trie structure
Trie *createTrie() {
    Trie* newTrie = (Trie*) malloc(sizeof(Trie));
    newTrie->count = 0;
    for(int i = 0; i < 26; i++) 
        newTrie->children[i] = NULL;
    
    return newTrie;
}

// Inserts the word to the trie structure
void insert(Trie *pTrie, char *word, int k) {
    if(k == strlen(word)) {
        pTrie->count += 1;
        return;
    }
    int index = word[k] - 'a';
    if(pTrie->children[index] == NULL)
        pTrie->children[index] = createTrie();
    
    insert(pTrie->children[index], word, k+1);
}

// computes the number of occurances of the word
int numberOfOccurances(Trie *pTrie, char *word) {
    if(pTrie == NULL)
        return 0;
    Trie* temp = pTrie;
    int index;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) {
            return 0;
        }
        temp = temp->children[index];
    }
    return temp->count;
}

// deallocate the trie structure
Trie *deallocateTrie(Trie *pTrie) {
    if(pTrie == NULL) {
        free(pTrie);
        return NULL;
    }
    for(int i =0; i < 26; i++) {
        if(pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
            free(pTrie->children[i]);
        }
    }
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    FILE* File = fopen(filename,"r");
	int dataSz = 0;
	
	if (File)
	{
		fscanf(File,"%d\n",&dataSz);
		
        char word[100];
		for (int i  = 0; i<dataSz; i++) {
            fscanf(File, "%s\n", word);
		    pInWords[i] = (char*) malloc(sizeof(char) * (strlen(word)+1));
            strcpy(pInWords[i], word);
		}
		
	}
	 
	return dataSz;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("input.txt", inWords);
	for (int i=0;i<numWords;++i)
		printf("%s\n",inWords[i]);
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
		insert(pTrie, inWords[i], 0);
		
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
		
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
		
	return 0;
}