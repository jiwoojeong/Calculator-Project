#include "bignumsub.h"


/****************************************************************************/
/* �Է� ���� üũ�� �Ѵ�			                                        */
/****************************************************************************/
int intputErrorCheck(char *inVal)
{
	int i;
	int len;
	
	len = strlen(inVal);
	inVal[len-1] = 0x00;									//'\0' ���� ����(���ǻ�)

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
/*  ���� �����͸� ���Ͽ� �����Ѵ�.                                           */
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
/*  ���� �����͸� ���Ͽ��� �о�´�.                                         */
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
		varSaveArray[varCount].b_sign = 0;			// ���� ������ ���ؼ� �������� �ʰ� �ִ�.

		varCount ++;

	}
	return;
}

/****************************************************************************/
/* �Էµ� ������ Space�� ���� �Ѵ�.                                         */
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
/* ���������� �Է� �� ���� �������� Array�� �����Ѵ�.                       */
/* return value : 0 -> ����													*/
/*                1 -> �������� �Է��� ���									*/
/*				  100 -> �Է� ����											*/
/****************************************************************************/
int VARChecking(char *calValue, BIG_NUMBER_VAR varSaveArray[])

{
														// ���� üũ
	if ((('a' <= calValue[0]) && (calValue[0] <= 'z')) ||
		(('A' <= calValue[0]) && (calValue[0] <= 'Z')))
	{

		if (calValue[1] == 0x00) return 1;				// ������ �Է��� ���

		varSaveArray[varCount].varName = calValue[0];

		if (calValue[1] == '=')							// ���� �� ����			{
		{
			int nSize = sizeof(&calValue[2]);
			if (calValue[2] == 0x00)
				return 100;

			varSaveArray[varCount].s_varbigNumber = (unsigned char *)malloc(nSize);
			strcpy(varSaveArray[varCount].s_varbigNumber, &calValue[2]);
			varSaveArray[varCount].n_size= nSize;
			varSaveArray[varCount].b_sign = 0;			// ���� ������ ���ؼ� �������� �ʰ� �ִ�.
			varCount ++;
			
			if (varCount > 9)							// ������ 10�� ������ ��� ����
				printf("������ �� �̻� ����� �� �����ϴ�.\n");

			return 2;
		}
		if ((calValue[1] != '+') &&
			(calValue[1] != '-') &&
			(calValue[1] != '*') &&
			(calValue[1] != '/') &&
			(calValue[1] != '%')) return 100;		// �Է� ����
		
	}

	return 0;
}
/****************************************************************************/
/* ������ Big Number�� �����Ѵ�							                    */
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
				for (t = 0; t < nNumCount; t++ )			// error �̹Ƿ� ��Ҵ� �޸� free
					free( s[t].s_bigNumber );
				
				return 100;									// ������ ����
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



