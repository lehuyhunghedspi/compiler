#include <stdio.h>
#include "instructions.h"

#define MAX_BLOCK 10
/*void loadCode(CodeBlock* codeBlock, FILE* f) {
  Instruction* code = codeBlock->code;
  int n;

  codeBlock->codeSize = 0;
  while (!feof(f)) {
    n = fread(code, sizeof(Instruction), MAX_BLOCK, f);
    code += n;
    codeBlock->codeSize += n;
  }
}*/
int main(int argc, char *argv[]){	
FILE *f=fopen(argv[1],"r");


CodeBlock *codeBlock=createCodeBlock(200);
loadCode(codeBlock,f);
printCodeBlock(codeBlock);
}