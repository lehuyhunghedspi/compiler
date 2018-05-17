/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"

#define MAX_BLOCK 50

WORD makeIntWORD(int a){
  WORD w;
  w.type=TP_INT;
  w.intValue=a;
    return w;
}
WORD makeFloatWORD(float a){
  WORD w;
  w.type=TP_FLOAT;
  w.floatValue=a;
    return w;
}

CodeBlock* createCodeBlock(int maxSize) {
  CodeBlock* codeBlock = (CodeBlock*) malloc(sizeof(CodeBlock));

  codeBlock->code = (Instruction*) malloc(maxSize * sizeof(Instruction));
  codeBlock->codeSize = 0;
  codeBlock->maxSize = maxSize;
  return codeBlock;
}

void freeCodeBlock(CodeBlock* codeBlock) {
  free(codeBlock->code);
  free(codeBlock);
}

int emitCode(CodeBlock* codeBlock, enum OpCode op, WORD p, WORD q) {
  Instruction* bottom = codeBlock->code + codeBlock->codeSize;

  if (codeBlock->codeSize >= codeBlock->maxSize) return 0;

  bottom->op = op;
  bottom->p = p;
  bottom->q = q;
  codeBlock->codeSize ++;
  return 1;
}

int emitLA(CodeBlock* codeBlock, WORD p, WORD q) { return emitCode(codeBlock, OP_LA, p, q); }
int emitLV(CodeBlock* codeBlock, WORD p, WORD q) { return emitCode(codeBlock, OP_LV, p, q); }
int emitLC(CodeBlock* codeBlock, WORD q) { return emitCode(codeBlock, OP_LC, makeIntWORD(DC_VALUE), q); }
int emitLI(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_LI, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitINT(CodeBlock* codeBlock, WORD q) { return emitCode(codeBlock, OP_INT, makeIntWORD(DC_VALUE), q); }
int emitDCT(CodeBlock* codeBlock, WORD q) { return emitCode(codeBlock, OP_DCT, makeIntWORD(DC_VALUE), q); }
int emitJ(CodeBlock* codeBlock, WORD q) { return emitCode(codeBlock, OP_J, makeIntWORD(DC_VALUE), q); }
int emitFJ(CodeBlock* codeBlock, WORD q) { return emitCode(codeBlock, OP_FJ, makeIntWORD(DC_VALUE), q); }
int emitHL(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_HL, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitST(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_ST, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitCALL(CodeBlock* codeBlock, WORD p, WORD q) { return emitCode(codeBlock, OP_CALL, p, q); }
int emitEP(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_EP, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitEF(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_EF, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitRC(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_RC, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitRI(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_RI, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitWRC(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_WRC, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitWRI(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_WRI, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitWLN(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_WLN, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitAD(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_AD, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitSB(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_SB, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitML(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_ML, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitDV(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_DV, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitNEG(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_NEG, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitCV(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_CV, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitEQ(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_EQ, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitNE(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_NE, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitGT(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_GT, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitLT(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_LT, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitGE(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_GE, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitLE(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_LE, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }


int emitRF(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_RF, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitWRF(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_WRF, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }

int emitBP(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_BP, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }
int emitMOD(CodeBlock* codeBlock) { return emitCode(codeBlock, OP_MOD, makeIntWORD(DC_VALUE), makeIntWORD(DC_VALUE)); }


void printInstruction(Instruction* inst) {
  switch (inst->op) {
  case OP_LA: printf("LA %d,%d", (inst->p).intValue, (inst->q).intValue); break;
  case OP_LV: printf("LV %d,%d",(inst->p).intValue, (inst->q).intValue); break;
  case OP_LC: 
    if((inst->q).type==TP_INT){
      printf("LC %d", (inst->q).intValue); break;}
    if((inst->q).type==TP_CHAR){
      printf("LC %d", (inst->q).charValue); break;
    }
    if((inst->q).type==TP_FLOAT){
      printf("LC %f", (inst->q).floatValue); break;
    }



  case OP_LI: printf("LI"); break;
  case OP_INT: printf("INT %d", (inst->q).intValue); break;
  case OP_DCT: printf("DCT %d", (inst->q).intValue); break;
  case OP_J: printf("J %d", (inst->q).intValue); break;
  case OP_FJ: printf("FJ %d", (inst->q).intValue); break;
  case OP_HL: printf("HL"); break;
  case OP_ST: printf("ST"); break;
  case OP_CALL: printf("CALL %d,%d", (inst->p).intValue, (inst->q).intValue); break;
  case OP_EP: printf("EP"); break;
  case OP_EF: printf("EF"); break;
  case OP_RC: printf("RC"); break;
  case OP_RI: printf("RI"); break;
  case OP_WRC: printf("WRC"); break;
  case OP_WRI: printf("WRI"); break;
  case OP_WLN: printf("WLN"); break;
  case OP_AD: printf("AD"); break;
  case OP_SB: printf("SB"); break;
  case OP_ML: printf("ML"); break;
  case OP_DV: printf("DV"); break;
  case OP_NEG: printf("NEG"); break;
  case OP_CV: printf("CV"); break;
  case OP_EQ: printf("EQ"); break;
  case OP_NE: printf("NE"); break;
  case OP_GT: printf("GT"); break;
  case OP_LT: printf("LT"); break;
  case OP_GE: printf("GE"); break;
  case OP_LE: printf("LE"); break;

  case OP_WRF: printf("WRF"); break;
  case OP_RF: printf("RF"); break;

  case OP_BP: printf("BP"); break;
  case OP_MOD: printf("MOD"); break;
  default: break;
  }
}

void printCodeBlock(CodeBlock* codeBlock) {
  Instruction* pc = codeBlock->code;
  int i;
  for (i = 0 ; i < codeBlock->codeSize; i ++) {
    printf("%d:  ",i);
    printInstruction(pc);
    printf("\n");
    pc ++;
  }
}


void loadCode(CodeBlock* codeBlock, FILE* f) {
  Instruction* code = codeBlock->code;
  int n;

  codeBlock->codeSize = 0;
  while (!feof(f)) {
    n = fread(code, sizeof(Instruction), MAX_BLOCK, f);
    code += n;
    codeBlock->codeSize += n;
  }
}


void saveCode(CodeBlock* codeBlock, FILE* f) {
    printCodeBlock(codeBlock);
  
  fwrite(codeBlock->code, sizeof(Instruction), codeBlock->codeSize, f);
}
