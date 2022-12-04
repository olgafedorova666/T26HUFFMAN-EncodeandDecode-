#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h>
#include <memcheck.h>
#define MAX_CODE 44
#define MAX_ALPHABET 256

typedef unsigned char byte;
typedef struct tagTREE TREE;
struct tagTREE
{
   TREE *left;
   TREE *right;
   unsigned char c;
   int freq;
};
int EncodeFile(char *inputFILEName, char *outputFILEName);
int DecodeFile(char *inputFILEName, char *outputFILEName);
/*void CountFreq(FILE *F, int *freq);
void InsertionSort(int *a, int n);
void Inserttoforest(TREE **forest, int forestSize, TREE *newEl);
void MergeForest(TREE **forest);
TREE *BuildTREE(int *freq);
void Display2(TREE *T, int h); */