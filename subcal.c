/*****************************************************************************/
/*                                                                           */
/* 큰 숫자 연산을 위한 함수                                                  */ 
/*                                                                           */
/*****************************************************************************/

#include "subcal.h"


/*****************************************************************************/
/*  숫자열 화면에 표시                                                       */
/*****************************************************************************/
void displayBigNumber ( BIG_NUMBER_DECIMAL bigNumber) 
{
	int	i, count;

	if (bigNumber.b_sign)											// '-' 일 경우
		printf("-");
	for (i = bigNumber.n_size-1; i>=0; i--)
		printf("%c", bigNumber.s_bigNumber[i]+48);

	printf("\n");

}

/*****************************************************************************/
/*  숫자열 길이 만큼 문자버퍼에 저장한다.                                    */
/*****************************************************************************/
void bigNumberChange (BIG_NUMBER_DECIMAL s[])
{
	int i, j;
	char	tmpBuffer[INPUT_MAX];
	
	memset(tmpBuffer, 0x00, INPUT_MAX);

	for (i = 0; i < nNumCount; i++)
	{
		strcpy(tmpBuffer, s[i].s_bigNumber);

		int	len = strlen(s[i].s_bigNumber);

		for (j = 0; j < len; j++)
		{
//			s[i].s_bigNumber[j] = tmpBuffer[len-j-1]-48;			// 숫자 코드로 변경
			s[i].s_bigNumber[j] = tmpBuffer[len-j-1]-0x30;			// 숫자 코드로 변경
		}
		s[i].n_size = len;
		s[i].b_sign = false;
	}

	return ;
}
/*****************************************************************************/
/*  숫자열 길이 만큼 문자버퍼에 저장한다.                                    */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberCreate(unsigned char* str, int len)
{
	int i;

	BIG_NUMBER_DECIMAL bigNumber;

	bigNumber.s_bigNumber = (unsigned char *)malloc(len);			// 반드시 프리 할것

	for ( i = 0; i < len; i++ )
	{
		bigNumber.s_bigNumber[i] = str[len-i-1]-48;					// 숫자 코드로 변경
	}
	bigNumber.n_size = len;
	bigNumber.b_sign = false;

	return bigNumber;
}

/*****************************************************************************/
/*  숫자열 길이 만큼 문자버퍼에 저장한다.                                    */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberCreate2(unsigned char* str)
{
	int i, len;

	BIG_NUMBER_DECIMAL bigNumber;

	len = strlen(str);
	bigNumber.s_bigNumber = (unsigned char *)malloc(len);			// 반드시 프리 할것

	for ( i = 0; i < len; i++ )
	{
		bigNumber.s_bigNumber[i] = str[len-i-1]-48;					// 숫자 코드로 변경
	}
	bigNumber.n_size = len;
	bigNumber.b_sign = false;

	return bigNumber;
}
/*****************************************************************************/
/*  입력값 분리							                                     */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberCreate3(unsigned char* str)
{
	int i, len;
	char	*token;
	BIG_NUMBER_DECIMAL bigNumber;
	unsigned char* strtemp;

	len = strlen(str);

	strtemp = (unsigned char *)malloc(len+1);
	strcpy(strtemp, str);

	token = strtok(strtemp, " = + / * %");   // 첫번째 토큰

	while (token != NULL)
	{
		printf ("token = %s\n", token);
		token = strtok(NULL, " = + / * %");
	}

	return bigNumber;
}


/*****************************************************************************/
/*  두 데이터를 비교한다	                                                 */
/*  TRUE : 같다.															 */
/*  FALAE : 다르다.															 */
/*****************************************************************************/
bool IsEqual(BIG_NUMBER_DECIMAL *A, BIG_NUMBER_DECIMAL *B)
{
	int i;

	if (A->n_size != B->n_size)
		return false;

	for (i = 0; i < A->n_size; i++)
	{
		if (A->s_bigNumber[i] != B->s_bigNumber[i])
			return false;
	}
	return true;
}
/*****************************************************************************/
/*  두 데이터를 비교한다	                                                 */
/*  TRUE : A가 크다															 */
/*  FALAE : B가 크다														 */
/*****************************************************************************/
bool IsBigger(BIG_NUMBER_DECIMAL *A, BIG_NUMBER_DECIMAL *B)
{
	int i;

	if (A->n_size > B->n_size)
		return true;
	else if (A->n_size < B->n_size)
		return false;
	else
	{
		for (i = A->n_size-1; i >= 0; i--)
		{
			if (A->s_bigNumber[i] > B->s_bigNumber[i])
				return true;
			else if (A->s_bigNumber[i] < B->s_bigNumber[i])
				return false;
		}
	}

	return true;
}

/*****************************************************************************/
/*  무개의 Big Number를 더한다                                               */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberADD (BIG_NUMBER_DECIMAL *a, BIG_NUMBER_DECIMAL *b)
{
	BIG_NUMBER_DECIMAL	returnVal;
	unsigned int 		min, max;
	
	BIG_NUMBER_DECIMAL	*biggerNum = a->n_size > b->n_size ? a:b;
	min = a->n_size > b->n_size ? b->n_size : a->n_size;
	max = a->n_size > b->n_size ? a->n_size : b->n_size;

	unsigned int size;
	size = max + 1;

	returnVal.s_bigNumber = (unsigned char *)malloc(size);
	memset(returnVal.s_bigNumber, 0x00, size);

	unsigned int i = 0;
	unsigned char temp = 0;

	for (; i < min; i++)								// 숫자 길이가 적은 부분까지 계산한다.
	{	

		returnVal.s_bigNumber[i] = a->s_bigNumber[i] + b->s_bigNumber[i] + temp;
		if (returnVal.s_bigNumber[i] > 0x09)
			temp = 0x01;
		else
			temp = 0x00;

		returnVal.s_bigNumber[i] %= 0x0A;
	}	

	for (; i < max; i++)								// 큰숫자 나머지 부분을 계산한다.
	{	

		returnVal.s_bigNumber[i] = biggerNum->s_bigNumber[i]  + temp;
		if (returnVal.s_bigNumber[i] > 0x09)
			temp = 0x01;
		else
			temp = 0x00;

		returnVal.s_bigNumber[i] %= 0x0A;

	}

	if (temp)
	{		
		returnVal.s_bigNumber[i] = temp;
		returnVal.n_size = size;
	}
	else
		returnVal.n_size = size - 1;


	returnVal.b_sign = 0;

	return returnVal;
}
/*****************************************************************************/
/*  무개의 뺴기를 하다. (음수를 아직 고려하지 않음)                          */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberMinus(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B)
{
	BIG_NUMBER_DECIMAL result;

	if (IsBigger(A,B))
	{
		result = MinusAbsolute(A,B);
		result.b_sign = 0;
	}
	else										// B가 큰경우는 '-'
	{
		result = MinusAbsolute(B,A);
		result.b_sign = 1;
	}
	return result;
}
/*****************************************************************************/
/*  무개의 뺴기를 하다. (A>B 크다는 조건		                             */
/*****************************************************************************/
BIG_NUMBER_DECIMAL MinusAbsolute(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B)
{
	BIG_NUMBER_DECIMAL result;

	result.s_bigNumber = (unsigned char*)malloc(A->n_size);			// 단드시 free

	int i = 0;
	unsigned char temp = 0;

	for (;  i < B->n_size ;i++) 
	{
		if (A->s_bigNumber[i] >= (B->s_bigNumber[i] + temp))
		{
			result.s_bigNumber[i] = A->s_bigNumber[i] - B->s_bigNumber[i] - temp;
			temp = 0;
		}
		else
		{
			result.s_bigNumber[i] = A->s_bigNumber[i] + 10 - B->s_bigNumber[i] - temp;
			temp = 1;
		}
	}
	for (; i < A->n_size; i++)
	{
		if (A->s_bigNumber[i] >= temp)
		{
			result.s_bigNumber[i] = A->s_bigNumber[i] - temp;
			temp = 0;
		}
		else
		{
			result.s_bigNumber[i] = A->s_bigNumber[i] + 10 - temp;
			temp = 1;
		}
	}

	result.n_size = A->n_size;

	while (!result.s_bigNumber[i-1] && i>1)
	{
		result.n_size--;
		i--;
	}

	result.b_sign = 0;

	return result;
}

/*****************************************************************************/
/*  무개의 Big Number를 곱한다 (*)                                           */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberMuliply(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B)
{
	BIG_NUMBER_DECIMAL result, temp, tempDigit;
	unsigned char * ptrTemp;

	result = bigNumberCreate((unsigned char*)"0", 1);

	temp.s_bigNumber = (unsigned char*)malloc(A->n_size + B->n_size);

	int i, j;

	for (i = 0; i < B->n_size; i++)
	{
		tempDigit = MultiplyDigit(A, B->s_bigNumber[i]);
		
		for (j=0; j<i; j++)
			temp.s_bigNumber[j] = 0x00;
		for (; j < tempDigit.n_size+i; j++)
			temp.s_bigNumber[j] = tempDigit.s_bigNumber[j-i];
		temp.n_size = tempDigit.n_size+i;

		//free(tempDigit.s_bigNumber);

		ptrTemp = result.s_bigNumber;
		result = bigNumberADD(&result, &temp);
		free(ptrTemp);
	}
	free(temp.s_bigNumber);

	return result;
}
/*****************************************************************************/
/*  Big Number와 일반숫자 하나를 곱한다                                      */
/*****************************************************************************/
BIG_NUMBER_DECIMAL MultiplyDigit(BIG_NUMBER_DECIMAL* A, unsigned char digit)
{
	BIG_NUMBER_DECIMAL result;

	unsigned int size = A->n_size + 1;
	result.s_bigNumber = (unsigned char*)malloc(size);

	int i;
	unsigned char temp = 0;

	for (i = 0; i < A->n_size; i++) 
	{
		result.s_bigNumber[i] = (A->s_bigNumber[i] * digit) + temp;

		temp = result.s_bigNumber[i] / 0x0A;
		result.s_bigNumber[i] %= 0x0A;
	}
	if (temp)
	{
		result.s_bigNumber[i] = temp;
		result.n_size = size;
	}
	else
		result.n_size = A->n_size;

	result.b_sign = false;

	return result;
}
/*****************************************************************************/
/*  무개의 Big Number를 나눈다 (/)                                           */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberDivide(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B)
{
	BIG_NUMBER_DECIMAL result;
	int i, j, count;

	if (!IsBigger(A,B))
	{
		result = bigNumberCreate((unsigned char*)"0",1);
		return result;
	}

	BIG_NUMBER_DECIMAL numerator;

	numerator.s_bigNumber = (unsigned char*)malloc(A->n_size);
	numerator.n_size = A->n_size;

	for(i = 0; i < numerator.n_size; i++)
		numerator.s_bigNumber[i] = A->s_bigNumber[i];

	i = A->n_size - B->n_size;
	result.s_bigNumber = (unsigned char*)malloc(i+1);

	for( j = 0; j <= i; j++)
		result.s_bigNumber[j] = 0x00;

	unsigned char* ptrForOrigin = numerator.s_bigNumber;
	numerator.s_bigNumber += (numerator.n_size - B->n_size);
	numerator.n_size = B->n_size;

	for (; i>=0; i--)
	{
		count = 0;

		while (IsBigger(&numerator, B))
		{
			count++;
			MinusForDivide(&numerator, B);
		}
		result.s_bigNumber[i] = (unsigned char)count;

		numerator.s_bigNumber--;

		if (numerator.s_bigNumber[numerator.n_size] != 0x00)
			numerator.n_size++;
	}

	free(ptrForOrigin);

	i = A->n_size - B->n_size;

	for (; i>0; i--)
		if (result.s_bigNumber[i] != 0x00)
			break;

	result.n_size = i + 1;
	result.b_sign = 0;

	return result;
}
/*****************************************************************************/
/*  무개의 Big Number를 나눈 나머지 계산기(%)                                */
/*****************************************************************************/
BIG_NUMBER_DECIMAL bigNumberMod(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* M)
{
	BIG_NUMBER_DECIMAL result;
	int i;

	result.s_bigNumber = (unsigned char*)malloc(A->n_size);
	for (i=0; i < A->n_size; i++)
		result.s_bigNumber[i] = A->s_bigNumber[i];

	result.n_size = A->n_size;
	result.b_sign = 0;

	if (!IsBigger(A, M))
		return result;

	unsigned char* ptrForOrigin = result.s_bigNumber;

	result.s_bigNumber += (result.n_size - M->n_size);
	result.n_size = M->n_size;

	for (i=(A->n_size - M->n_size); i>=0; i--)
	{
		while (IsBigger(&result, M))
			MinusForDivide(&result, M);
		
		result.s_bigNumber--;

		if (result.s_bigNumber[result.n_size] != 0)
			result.n_size++;
	}
	
	result.s_bigNumber = ptrForOrigin;

	i = A->n_size - 1;

	while (i > 0)
	{
		if (result.s_bigNumber[i] != 0x00)
			break;
		i--;
	}
	result.n_size = i+1;

	return result;
}
void MinusForDivide(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B)
{	
	int i;
	unsigned char temp = 0;

	for (i = 0; i < B->n_size; i++) 
	{
		if (A->s_bigNumber[i] >= (B->s_bigNumber[i] + temp))
		{
			A->s_bigNumber[i] = A->s_bigNumber[i] - B->s_bigNumber[i] - temp;
			temp = 0;
		}
		else
		{
			A->s_bigNumber[i] = A->s_bigNumber[i] + 0x0A - B->s_bigNumber[i] - temp;
			temp = 0x01;
		}
	}
	for (;i < A->n_size; i++)
	{
		if (A->s_bigNumber[i] >= temp)
		{
			A->s_bigNumber[i] = A->s_bigNumber[i] - temp;
			temp = 0;
		}
		else
		{
			A->s_bigNumber[i] = A->s_bigNumber[i] + 0x0A - temp;
			temp = 0x01;
		}
	}

	while (!A->s_bigNumber[i-1] && i>1)
	{
		A->n_size--;
		i--;
	}
}

/*****************************************************************************/
/*  무개의 Big Number를 곱한다                                              */
/*****************************************************************************/
/*
BIG_NUMBER_DECIMAL bigNumerMul(BIG_NUMBER_DECIMAL *a, BIG_NUMBER_DECIMAL *b)
{
    static char mul[MAX];

    char c[MAX];

    char temp[MAX];

    int la,lb;

    int i,j,k=0,x=0,y;

    long int r=0;

    long sum = 0;

    la=strlen(a)-1;

        lb=strlen(b)-1;

    

        for(i=0;i<=la;i++){

                a[i] = a[i] - 48;

        }




        for(i=0;i<=lb;i++){

                b[i] = b[i] - 48;

        }




    for(i=lb;i>=0;i--){

         r=0;

         for(j=la;j>=0;j--){

             temp[k++] = (b[i]*a[j] + r)%10;

             r = (b[i]*a[j]+r)/10; 

         }

         temp[k++] = r;

         x++;

         for(y = 0;y<x;y++){

             temp[k++] = 0;

         }

    }

    

    k=0;

    r=0;

    for(i=0;i<la+lb+2;i++){

         sum =0;

         y=0;

         for(j=1;j<=lb+1;j++){

             if(i <= la+j){

                 sum = sum + temp[y+i];

             }

             y += j + la + 1;

         }

         c[k++] = (sum+r) %10;

         r = (sum+r)/10;

    }

    c[k] = r;

    j=0;

    for(i=k-1;i>=0;i--){

         mul[j++]=c[i] + 48;

    }

    mul[j]='\0';

    return mul;

}

*/

















