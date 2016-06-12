/*****************************************************************************/
/*                                                                           */
/* 계산에 필요한 모듈 헤터 파일                                              */ 
/*                                                                           */
/*************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 10000							// 최대 숫자 버퍼 사이즈
#define INPUT_MAX 100						// 최대 입력 숫자 버퍼 사이즈

// 연산을 위한 구조체
typedef struct _BIG_NUMBER_DECIMAL {
	unsigned char 	*s_bigNumber;
	int				n_size;
	bool			b_sign;
} BIG_NUMBER_DECIMAL;

typedef struct _BIG_NUMBER_VAR {
	char			varName;
	unsigned char 	*s_varbigNumber;
	int				n_size;
	bool			b_sign;
} BIG_NUMBER_VAR;
int		varCount;							// 변수 사용 카운트
int		opCount;							// 연산자 카운드
int		nNumCount;							// 입력된 Big Number 개수
char	operatorVal[INPUT_MAX];				// 연산자 저장 장소

// 문자열 표시
void displayBigNumber (BIG_NUMBER_DECIMAL bigNumber);
// 숫자를 문자 작업용 버퍼에 저장
void bigNumberChange (BIG_NUMBER_DECIMAL s[]);
BIG_NUMBER_DECIMAL bigNumberCreate(unsigned char* str, int len);
BIG_NUMBER_DECIMAL bigNumberCreate2 (unsigned char* str);
BIG_NUMBER_DECIMAL bigNumberCreate3 (unsigned char* str);

// 데이터 비교
bool IsEqual(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B);


// 두개의 버퍼 더하기
BIG_NUMBER_DECIMAL bigNumberADD (BIG_NUMBER_DECIMAL *a, BIG_NUMBER_DECIMAL *b);
BIG_NUMBER_DECIMAL bigNumberMinus(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B);
BIG_NUMBER_DECIMAL MinusAbsolute(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B);
BIG_NUMBER_DECIMAL bigNumberMuliply(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B);
BIG_NUMBER_DECIMAL MultiplyDigit(BIG_NUMBER_DECIMAL* A, unsigned char digit);
BIG_NUMBER_DECIMAL bigNumberDivide(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B);
void MinusForDivide(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* B);
BIG_NUMBER_DECIMAL bigNumberMod(BIG_NUMBER_DECIMAL* A, BIG_NUMBER_DECIMAL* M);


