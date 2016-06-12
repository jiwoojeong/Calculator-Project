/*****************************************************************************/
/*                                                                           */
/* 과  목 : 프로그램밍 기초 및 실습 (팀 프로젝트)                            */
/* 과제명 : 큰 숫자 계산기												     */
/* 이  름 : 전 연 준                                                         */
/* 학  번 : 20160325                                                         */
/* 학  과 : 소프트웨어                                                       */
/*                                                                           */
/*****************************************************************************/
#include "subcal.h"

int	main()
{
	BIG_NUMBER_DECIMAL	saveBigNumber[INPUT_MAX];				// 입력된 큰 숫자 저장소
	BIG_NUMBER_DECIMAL	returnVal;								// 연산 결과값 저장소
	BIG_NUMBER_VAR		varSaveArray[10];						// 변수 저장소
	
	char	inputVal[MAX];										// 화면으로 입력 받은 버퍼
	char	calValue[MAX];										// 입력된 값에서 space 제거된 버퍼
	int		i;

	varCount = 0;												// 변수 총수를 초기화

	while (1)
	{

		printf("[end :종료, clear:화면지우기, save:변수값 파일 저장, load:변수값 파일 읽기, VAR:변수값 표시]\n");

		i = 0;
		memset(inputVal, 0x00, MAX);							// 입력 값
		memset(calValue, 0x00, MAX);							// space 제거된 입력 값
		memset(operatorVal, 0x00, INPUT_MAX);					// 연산자 저장소

		fgets(inputVal, sizeof(inputVal)-1, stdin);				// 유저로부터 입력을 받는다.

		if (intputErrorCheck(inputVal))							// 유효 입력값 체크
		{
			printf("입력 Error 입니다. 다시 입력해주세요\n");
			continue;
		}

		if (strcmp(inputVal, "end") == 0)						// 종료
			break;

		if (strcmp(inputVal, "clear") == 0)						// 화면 클리어
		{
			system("clear");
			// 변수등 초기화 작업 예정

			continue;
		}
		if (strcmp(inputVal, "save") == 0)						// 변수값 파일에 저장
		{
			FILE *fp;
			if ((fp = fopen ("valfile.txt", "wt")) == NULL)
			{
				printf("valfile.txt 오픈 에라. \n");
				continue;
			}
			varFileSave(fp, varSaveArray);

			fclose(fp);
			continue;
		}
	
		if (strcmp(inputVal, "load") == 0)						// 변수값 로드
		{
			FILE *fp;
			if ((fp = fopen ("valfile.txt", "rt")) == NULL)
			{
				printf("valfile.txt 오픈 에라. \n");
				continue;
			}
			varFileRead(fp, varSaveArray);

			fclose(fp);

			continue;
		}
		if (strcmp(inputVal, "VAR") == 0)						// 변수값 표시
		{

			if (varCount == 0)
			{
				printf("정의 된 변수 명이 없습니다.\n");
				continue;
			}
			for (i = 0; i < varCount; i++)
			{
				printf("%c = %s\n", varSaveArray[i].varName, varSaveArray[i].s_varbigNumber );
			}
			continue;
		}

		spaceDelete(inputVal, calValue);						// 공백은 다 지운다.

		int	nCheckVal;
		nCheckVal = VARChecking(calValue, varSaveArray);		// 변수명 체크 한다
		if (nCheckVal == 1)
		{
			if (varCount == 0)
			{
				printf("undefined.\n");
				continue;
			}
			for (i = 0; i < varCount; i++)
			{
				if (calValue[0] == varSaveArray[i].varName)
				{
					printf("%c = %s\n", varSaveArray[i].varName, varSaveArray[i].s_varbigNumber );
					break;		
				}
			}
			continue;
		}
		if (nCheckVal == 100)									// 입력 오류
		{
			printf("입력 오류 입니다.\n");
			continue;
		}
		if (nCheckVal == 2)										// 변수 값만을 지정
			continue;

																// 연산할 Big Number를 저장한다.
		nCheckVal = calInputValueSave(calValue, saveBigNumber, varSaveArray );
		if (nCheckVal == 100)
		{
			printf("변수명이 존재 하지 않습니다.\n");
			continue;
		}

		bigNumberChange(saveBigNumber);							// Big Number 계산형으로 변환

		int npriorityCount= 0;
		for (i = 0; i < opCount; i++)							// 우선 처리해야 할 연산자를 count한다.
		{
			if ((operatorVal[i] == '*') ||(operatorVal[i] == '/') || (operatorVal[i] == '%'))
				npriorityCount++;
		}
		
		if (npriorityCount > 0)
		{
			for (i = 0; i < opCount; i++)
			{
				if (operatorVal[i] == '*')					// 곱하기 처리
				{
					returnVal = bigNumberMuliply (&saveBigNumber[i], &saveBigNumber[i+1]);
					bigNumberMemoryModify(returnVal, &saveBigNumber[i], &saveBigNumber[i+1], i);
					free(returnVal.s_bigNumber);
					i--;
				}
				if (operatorVal[i] == '/')					// 나누기 처리
				{
					returnVal = bigNumberDivide (&saveBigNumber[i], &saveBigNumber[i+1]);
					bigNumberMemoryModify(returnVal, &saveBigNumber[i], &saveBigNumber[i+1], i);
					free(returnVal.s_bigNumber);
					i--;
				}
				if (operatorVal[i] == '%')					// 나머지 처리
				{
					returnVal = bigNumberMod (&saveBigNumber[i], &saveBigNumber[i+1]);
					bigNumberMemoryModify(returnVal, &saveBigNumber[i], &saveBigNumber[i+1], i);
					free(returnVal.s_bigNumber);
					i--;
				}
			}
		}
		
		for (i = 0; i < opCount; i++)
		{
			if (operatorVal[i] == '+')						// 더하기
			{
				returnVal = bigNumberADD (&saveBigNumber[i], &saveBigNumber[i+1]);
				bigNumberMemoryModify(returnVal, &saveBigNumber[i], &saveBigNumber[i+1], i);
				free(returnVal.s_bigNumber);
				i--;
			}
			if (operatorVal[i] == '-')						// 뺴기
			{
				returnVal = bigNumberMinus (&saveBigNumber[i], &saveBigNumber[i+1]);
				bigNumberMemoryModify(returnVal, &saveBigNumber[i], &saveBigNumber[i+1], i);
				free(returnVal.s_bigNumber);
				i--;
			}

		}
		
		printf("  = ");										// 결과치 출력
		displayBigNumber (saveBigNumber[0]);

		for (i = 0; i < varCount; i++)					// 변수용으로 잡은 메모리 삭제
			free(saveBigNumber[varCount].s_bigNumber );

	}
	for (i = 0; i < varCount; i++)							// 변수용으로 잡은 메모리 삭제
		free(varSaveArray[varCount].s_varbigNumber );

}
