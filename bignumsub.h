#include "subcal.h"



int intputErrorCheck(char *inVal);
// ������ ���Ͽ� ����
void varFileSave(FILE *fp,  BIG_NUMBER_VAR varSaveArray[]);
void varFileRead(FILE *fp,  BIG_NUMBER_VAR varSaveArray[]);

int  spaceDelete(char *inputVal, char *calValue);
int VARChecking(char *calValue, BIG_NUMBER_VAR varSaveArray[]);
int calInputValueSave(char *calValue, BIG_NUMBER_DECIMAL *s, BIG_NUMBER_VAR varSaveArray[]);
void bigNumberMemoryModify(BIG_NUMBER_DECIMAL returnVal, BIG_NUMBER_DECIMAL *s, BIG_NUMBER_DECIMAL *d, int i);


