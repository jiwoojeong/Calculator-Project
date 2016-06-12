#include "bignumsub.h"


/****************************************************************************/
/* 입력 오류 체크를 한다			                                        */
/****************************************************************************/
int intputErrorCheck(char *inVal)
{
	int i;
	int len;
	
	len = strlen(inVal);
	inVal[len-1] = 0x00;									//'\0' 값을 삭제(편의상)

	for (i = 0; i < len-1; i++ )	
	{

		if (('0' <= inVal[i] ) && (inVal[i] <= '9'))
			continue;

		if (('a' <= inVal[i] ) && (inVal[i] <= 'z'))
			continue;

		if (('A' <= inVal[i] ) && (inVal[i] <= 'Z'))
			continue;

		if (('+' == inVal[i]) || ('-' == inVal[i]) || ('*' == inVal[i]) || ('/' == inVal[i]) ||('%' == inVal[i]))
			continue;

		if ( ' ' == inVal[i] )								// space
			continue;

		if ( (0x08 == inVal[i] ) || ('=' == inVal[i] ) )	// back space
			continue;
		else
			return 1;
	}
	return 0;

}
/*****************************************************************************/
/*  변수 데이터를 파일에 저장한다.                                           */
/*****************************************************************************/
void varFileSave(FILE *fp,  BIG_NUMBER_VAR varSaveArray[])
{
	int i;

	for (i = 0; i < varCount; i++)
	{
		fprintf(fp, "%c = %s\n", varSaveArray[i].varName, varSaveArray[i].s_varbigNumber );
	}

}
/*****************************************************************************/
/*  변수 데이터를 파일에서 읽어온다.                                         */
/*****************************************************************************/
void varFileRead(FILE *fp,  BIG_NUMBER_VAR varSaveArray[])
{
	char	var;
	char	s_varbigNumber[INPUT_MAX];

	varCount = 0;

	memset(s_varbigNumber, 0x00, INPUT_MAX);
	while ( feof(fp) == 0 )
	{
		fscanf(fp, "%c = %s\n",&var, s_varbigNumber);

		varSaveArray[varCount].s_varbigNumber = (unsigned char *)malloc(INPUT_MAX);

		varSaveArray[varCount].varName = var;
		strcpy(varSaveArray[varCount].s_varbigNumber, s_varbigNumber);
		varSaveArray[varCount].n_size = strlen(s_varbigNumber);
		varSaveArray[varCount].b_sign = 0;			// 아직 음수에 대해서 생각하지 않고 있다.

		varCount ++;

	}
	return;
}

/****************************************************************************/
/* 입력된 값에서 Space를 제거 한다.                                         */
/****************************************************************************/
int spaceDelete( char *inputVal, char *calValue )
{
	int	iCount, iCount2;
	int nSize;

	iCount2 = 0;

	for (iCount = 0; iCount < MAX; iCount++)
	{
		if (inputVal[iCount] == 0x00) break;

		if (inputVal[iCount] != ' ')
		{
			calValue[iCount2] = inputVal[iCount];
			iCount2++;
		}
	}

	return 0;
}
/****************************************************************************/
/* 변수명으로 입력 된 값은 변수저장 Array에 저장한다.                       */
/* return value : 0 -> 정상													*/
/*                1 -> 변수만을 입력한 경우									*/
/*				  100 -> 입력 오류											*/
/****************************************************************************/
int VARChecking(char *calValue, BIG_NUMBER_VAR varSaveArray[])

{
														// 변수 체크
	if ((('a' <= calValue[0]) && (calValue[0] <= 'z')) ||
		(('A' <= calValue[0]) && (calValue[0] <= 'Z')))
	{

		if (calValue[1] == 0x00) return 1;				// 변수만 입력한 경우

		varSaveArray[varCount].varName = calValue[0];

		if (calValue[1] == '=')							// 변수 값 저장			{
		{
			int nSize = sizeof(&calValue[2]);
			if (calValue[2] == 0x00)
				return 100;

			varSaveArray[varCount].s_varbigNumber = (unsigned char *)malloc(nSize);
			strcpy(varSaveArray[varCount].s_varbigNumber, &calValue[2]);
			varSaveArray[varCount].n_size= nSize;
			varSaveArray[varCount].b_sign = 0;			// 아직 음수에 대해서 생각하지 않고 있다.
			varCount ++;
			
			if (varCount > 9)							// 변수는 10개 까지만 사용 가능
				printf("변수를 더 이상 사용할 수 없습니다.\n");

			return 2;
		}
		if ((calValue[1] != '+') &&
			(calValue[1] != '-') &&
			(calValue[1] != '*') &&
			(calValue[1] != '/') &&
			(calValue[1] != '%')) return 100;		// 입력 오류
		
	}

	return 0;
}
/****************************************************************************/
/* 연산할 Big Number를 저장한다							                    */
/****************************************************************************/
int calInputValueSave(char *calValue, BIG_NUMBER_DECIMAL *s, BIG_NUMBER_VAR varSaveArray[])
{
	int nSize, i, j;

	nSize = strlen(calValue);
	opCount = 0;
	nNumCount = 0;

	for (i = 0; i < nSize; i++)
	{
		if ((calValue[i] == '+') ||(calValue[i] == '-') ||
			(calValue[i] == '*') || (calValue[i] == '/') ||(calValue[i] == '%'))
		{
			operatorVal[opCount] = calValue[i];
			opCount ++;
			continue;
		}
		if (('0' <= calValue[i]) && (calValue[i] <= '9'))
		{
			s[nNumCount].s_bigNumber = (unsigned char *)malloc(INPUT_MAX);
			j = 0;
			for (; i< nSize; i++)
			{
				s[nNumCount].s_bigNumber[j] = calValue[i];
				if(!('0' <= calValue[i+1]) && (calValue[i+1] <= '9'))
					break;
				j++;
			}
			nNumCount++;
			
			continue;
		}
	
		if ((('a' <= calValue[i]) && (calValue[i] <= 'z')) ||
		(('A' <= calValue[i]) && (calValue[i] <= 'Z')))
		{
			s[nNumCount].s_bigNumber = (unsigned char *)malloc(INPUT_MAX);
	
			for (j = 0; j < varCount; j++)
			{
				if (calValue[i] == varSaveArray[j].varName)
				{
					strcpy(s[nNumCount].s_bigNumber, varSaveArray[j].s_varbigNumber);
					break;		
				}
			}
			if (j == varCount )
			{
				int t;
				for (t = 0; t < nNumCount; t++ )			// error 이므로 잡았던 메모리 free
					free( s[t].s_bigNumber );
				
				return 100;									// 변수명 에라
			}
				
			nNumCount++;
		}

	}
	return 0;
}
void bigNumberMemoryModify(BIG_NUMBER_DECIMAL returnVal, BIG_NUMBER_DECIMAL *s, BIG_NUMBER_DECIMAL *d, int i)
{
	int j;

	for(j = 0; j < returnVal.n_size; j++)
		s->s_bigNumber[j] = returnVal.s_bigNumber[j];

	s->n_size = returnVal.n_size;
	s->b_sign = returnVal.b_sign;

	j = i;
	for (; j < opCount-1 ; j++)
	{
		operatorVal[j] = operatorVal[j+1];

	}
	opCount --;

	j = i;
	int k = 0;
	int	t;

	for (; j < nNumCount-1 ; j++)
	{
		for (t = 0; t < (d+k+1)->n_size ; t++)
			(d+k)->s_bigNumber[t] = (d+k+1)->s_bigNumber[t];

		(d+k)->n_size = (d+k+1)->n_size;
		(d+k)->b_sign = (d+k+1)->b_sign;
		k++;
	}
	nNumCount --;

	return;
}



