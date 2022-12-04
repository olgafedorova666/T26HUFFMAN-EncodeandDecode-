#include "HUFFMAN.H"
 
void CountFreq(FILE *F, int *freq)
{
  int c;
  for (c = 0; c < MAX_ALPHABET; c++)
    freq[c] = 0;
  while ((c = getc(F)) != EOF)
    freq[c]++;
}

void Inserttoforest(TREE **forest, int forestSize, TREE *newEl)
{
  int pos = forestSize;
  while (pos > 0 && newEl->freq > forest[pos - 1]->freq)
  {
    forest[pos] = forest[pos - 1];
    pos--;
  }                                                                                                                                                                                         
  forest[pos] = newEl;
}

void MergeForest(TREE **forest)
{
  int pos;
  for (pos = MAX_ALPHABET - 1 ; pos > 0; pos--)
  {
    if(forest[pos]->freq != 0)
    {
      TREE *newEl = malloc(sizeof(TREE)); 
      if (newEl == NULL)
      {
        printf("Error");
        return;
      }
      newEl->c = 0;
      newEl->freq = forest[pos]->freq + forest[pos - 1]->freq;
      newEl->left = forest[pos - 1];
      newEl->right = forest[pos];   
      Inserttoforest(forest, pos - 1, newEl);
    }
  }
}

TREE *BuildTREE(int *freq)
{
  TREE *forest[MAX_ALPHABET];
  int c = 0;
  for( ;c < MAX_ALPHABET; c++)
  {
    TREE *newEl = malloc(sizeof(TREE)); 
    if (newEl == NULL)
    {
      printf("Error");
      return 0;
    }
    newEl->c = c;
    newEl->freq = freq[c];
    newEl->right = NULL;
    newEl->left = NULL; 
    Inserttoforest(forest, c, newEl);  
  } 
  MergeForest(forest);
  return forest[0];
}   
void Display2(TREE *T, int h)
{
  if (T != NULL)
  if (T->right != NULL)
  {
    Display2(T->right, h + 1);
  }                   
    if(T->freq > 0)     /*  Test  */
    {
      printf("%*c(%i, %c)\n", 3 * h , ' ', T->freq, T->c);
    }
  if (T->left != NULL)
  {
    Display2(T->left, h + 1);
  }
}
char code[MAX_CODE];
char *codes[MAX_ALPHABET] = {0};

void TraverseTree(TREE *T, int depth)
{
  if (T->left == NULL)
  {
    code[depth] = 0;
    codes[T->c] = _strdup(code);
    return;
  }
  else
    code[depth] = '0';
    TraverseTree(T->left, depth + 1);
    code[depth] = '1';
    TraverseTree(T->right, depth + 1);
} 

int EncodeFile(char *inputFILEName, char *outputFILEName)
{
  FILE *inFile, *outFile; //forest[c].c = (byte*)c;
  //TREE *forest[MAX_ALPHABET];
  int c = 0;
  TREE *root = NULL;
  int freq[MAX_ALPHABET];
  printf("Encoding %s-->%s\n", inputFILEName, outputFILEName);
  inFile = fopen("inputFILEName.txt", "rt");
  if (inFile == NULL)
  {
    fprintf(stderr, "File %s couldn't be open\n", inputFILEName);
    return 0;
  }
  outFile = fopen("outputFILE.TXT", "wt");
  if (outFile == NULL)
  {
    printf("Error");
    return 0;
  }
  CountFreq(inFile, freq);
  rewind(inFile); 
  root = BuildTREE(freq);
  Display2(root, 1);
  for(c = 0;  c < MAX_ALPHABET; c++)
    fprintf(outFile, "%i ", freq[c]);
  TraverseTree(root, 0); 
  for(c = 0; c < MAX_ALPHABET; c++)
  {
    if(freq[c] > 0)
    {
      printf("%c, %s\n", c, codes[c]); 
    }

  }
  while ((c = getc(inFile)) != EOF)
  {
    printf("%s", codes[c]);
    fprintf(outFile,"%s ", codes[c]);
  }
  printf("\n\n\n\n\n");
  fclose(outFile);
  fclose(inFile); 
  return 1;
}

int DecodeFile(char *inputFILEName, char *outputFILEName)
{
  FILE *inFile, *outFile;
  TREE *root = NULL;
  TREE *T = NULL;
  int freq[MAX_ALPHABET];
  int c = 0;  
  inFile = fopen("outputFILE.TXT", "rt");
  if (inFile == NULL)
  {
    fprintf(stderr, "File %s couldn't be open\n", inputFILEName);
    return 0;
  }
  outFile = fopen("outputFILE2.TXT", "wt");
  if (outFile == NULL)
  {
    printf("Error");
    return 0;
  }
  for(c = 0;  c < MAX_ALPHABET; c++)
    fscanf(inFile, "%i", &freq[c]);
  root = BuildTREE(freq);
  T = root;
  Display2(root, 1); 
  while((c = getc(inFile)) != EOF)
  {
    if(c == '0')
      T = T->left;
    else if(c == '1')
      T = T->right;
    if(T->left == NULL && T->right == NULL)
    {
      printf("%c", T->c);
      fprintf(outFile,"%c", T->c);
      T = root;
    }
  }
  fclose(outFile);
  fclose(inFile);
  return 1;
} 