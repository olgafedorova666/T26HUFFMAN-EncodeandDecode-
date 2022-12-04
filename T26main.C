#include "HUFFMAN.H"
void main(void)
{  
  char dummy[12];
  EncodeFile("input.txt", "output.huf");
  DecodeFile("output.txt", "output2.huf");
  gets(dummy);
}