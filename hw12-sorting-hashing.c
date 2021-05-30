/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");
		printf("----------[ 김 윤 희 ] -------------[ 2018038014 ] --------------\n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else // 아니면 
		temp = *a;		

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}
/*동적할당 해제 함수 */
int freeArray(int *a)		
{
	if(a != NULL)
		free(a);
	return 0;
}
/*배열을 출력하는 함수*/
void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

/*선택 정렬*/
int selectionSort(int *a)
{
	int min;						// 최소값을 저장하는 변수
	int minindex;					// 최솟값의 위치를 저장하는 변수
	int i, j;						// 배열의 크기 만큼 반복문을 돌릴 변수

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); 					// 정렬하기 전에 먼저 출력한다.

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;				// 최솟값의 정보를 저장		
		min = a[i];					// 최소값을 a[i]번째 값으로 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)			//최솟값을 탐색한다.
		{
			if (min > a[j])			// 만약 min이 a[j] 보다 크다면
			{
				min = a[j];			// 최소값을 a[j] 로 저장
				minindex = j;		// 최소값의 위치 정보를 저장
			}
		}
		a[minindex] = a[i];					// 최소값과 i번째 배열의 위치를 바꿔준다.
		a[i] = min;							
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);					// 정렬 후 결과 발표
	return 0;
}
/*삽입정렬*/
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);					// 정렬 전 상태를 출력
	// 인덱스 0은 이미 정렬된 것으로 본다.
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];			// 현재 삽입 될 숫자인 i번째 정수를 t 변수로 복사
		j = i;				// i의 값을 j에 저장
		while (a[j-1] > t && j > 0)	// 배열의 j - 1번째 원소보다 t가 클때, j가 음수가 아닐때 까지 반복
		{
			a[j] = a[j-1];			// 레코드의 왼쪽으로 이동
			j--;					// j값을 감소 
		}
		a[j] = t;					// j번째 위치에 t를 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);			// 정렬이 끝난 결과를 출력

	return 0;
}
/*버블 정렬*/
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//정렬 전 상태를 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)			
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{	// j - 1번째 요소가 j번째 요소보다 크면 서로의 위치를 변경 시킨다.
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); 	// 정렬이 끝났으므로 현재 상태를 출력

	return 0;
}
/*쉘 정렬*/
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)				//h 값을 반으로 줄이기 위한 for문 h가 1보다 작으면 끝난다.
	{
		for (i = 0; i < h; i++)								// 부분 리스트의 갯수는 h와 같다
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)		// h+i 요소에 대한 삽입 정렬을 한다.
			{
				v = a[j];
				k = j;
				// h간격에 있는 데이터 삽입 정렬
				while (k > h-1 && a[k-h] > v)				
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/*퀵 정렬*/
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)					// n이 1보다 클때
	{
		v = a[n-1];				// 피봇의 값을 저장
		i = -1;					// 왼쪽을 -1로 설정
		j = n - 1;				// 오른쪽을 n-1로 설정

		while(1)
		{
			while(a[++i] < v);		// 피봇 보다 작은 원소 찾기
			while(a[--j] > v);		// 피봇 보다 큰 원소 찾기

			if (i >= j) break;
			t = a[i];				// 오른쪽과 왼쪽 값을 서로 swap 한다.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];					// 피봇의 값을 j의 위치로 저장한다.
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);			// 피봇의 왼쪽 부분집합에 대해 퀵 정렬을 재귀 호출
		quickSort(a+i+1, n-i-1);	// 피봇의 오른쪽 부분집합에 대해 퀵 정렬을 재귀 호출
	}


	return 0;
}
// 해쉬 Function 구현
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;	// key 값이 들어오면 몇번으로 들어가는지 로직을 설정한다.
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)			//해시테이블 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)						// 해시테이블의 해시코드 위치가 -1이면 
		{
			hashtable[hashcode] = key;						// 해시테이블에 key을 저장
		} else 	{

			index = hashcode;								// 아니면 인덱스에 해시코드 저장

			while(hashtable[index] != -1)					// 해시테이블이 -1이 아닐때 까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;   // 충돌이 일어나면 그 다음 테이블에 삽입
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;							// 인덱스 위치에 key값을 저장
		}
	}

	return 0;
}
/* 해시 키 탐색 */
int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)				// 찾는 값이 인덱스의 위치에 있으면 인덱스를 반환
		return index;

	while(ht[++index] != key)  			// key값과 같은 인덱스를 찾는다.
	{
		index = index % MAX_HASH_TABLE_SIZE;	// 인덱스를 0~MAX_HASH_TABLE_SIZE 내에서 값이 1씩 증가
	}
	return index;							
}



