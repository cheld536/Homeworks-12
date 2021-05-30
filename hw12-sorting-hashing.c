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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
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
		printf("----------[ �� �� �� ] -------------[ 2018038014 ] --------------\n");
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else // �ƴϸ� 
		temp = *a;		

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}
/*�����Ҵ� ���� �Լ� */
int freeArray(int *a)		
{
	if(a != NULL)
		free(a);
	return 0;
}
/*�迭�� ����ϴ� �Լ�*/
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

/*���� ����*/
int selectionSort(int *a)
{
	int min;						// �ּҰ��� �����ϴ� ����
	int minindex;					// �ּڰ��� ��ġ�� �����ϴ� ����
	int i, j;						// �迭�� ũ�� ��ŭ �ݺ����� ���� ����

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); 					// �����ϱ� ���� ���� ����Ѵ�.

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;				// �ּڰ��� ������ ����		
		min = a[i];					// �ּҰ��� a[i]��° ������ ����
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)			//�ּڰ��� Ž���Ѵ�.
		{
			if (min > a[j])			// ���� min�� a[j] ���� ũ�ٸ�
			{
				min = a[j];			// �ּҰ��� a[j] �� ����
				minindex = j;		// �ּҰ��� ��ġ ������ ����
			}
		}
		a[minindex] = a[i];					// �ּҰ��� i��° �迭�� ��ġ�� �ٲ��ش�.
		a[i] = min;							
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);					// ���� �� ��� ��ǥ
	return 0;
}
/*��������*/
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);					// ���� �� ���¸� ���
	// �ε��� 0�� �̹� ���ĵ� ������ ����.
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];			// ���� ���� �� ������ i��° ������ t ������ ����
		j = i;				// i�� ���� j�� ����
		while (a[j-1] > t && j > 0)	// �迭�� j - 1��° ���Һ��� t�� Ŭ��, j�� ������ �ƴҶ� ���� �ݺ�
		{
			a[j] = a[j-1];			// ���ڵ��� �������� �̵�
			j--;					// j���� ���� 
		}
		a[j] = t;					// j��° ��ġ�� t�� ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);			// ������ ���� ����� ���

	return 0;
}
/*���� ����*/
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		//���� �� ���¸� ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++)			
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{	// j - 1��° ��Ұ� j��° ��Һ��� ũ�� ������ ��ġ�� ���� ��Ų��.
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); 	// ������ �������Ƿ� ���� ���¸� ���

	return 0;
}
/*�� ����*/
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)				//h ���� ������ ���̱� ���� for�� h�� 1���� ������ ������.
	{
		for (i = 0; i < h; i++)								// �κ� ����Ʈ�� ������ h�� ����
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)		// h+i ��ҿ� ���� ���� ������ �Ѵ�.
			{
				v = a[j];
				k = j;
				// h���ݿ� �ִ� ������ ���� ����
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
/*�� ����*/
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)					// n�� 1���� Ŭ��
	{
		v = a[n-1];				// �Ǻ��� ���� ����
		i = -1;					// ������ -1�� ����
		j = n - 1;				// �������� n-1�� ����

		while(1)
		{
			while(a[++i] < v);		// �Ǻ� ���� ���� ���� ã��
			while(a[--j] > v);		// �Ǻ� ���� ū ���� ã��

			if (i >= j) break;
			t = a[i];				// �����ʰ� ���� ���� ���� swap �Ѵ�.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];					// �Ǻ��� ���� j�� ��ġ�� �����Ѵ�.
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);			// �Ǻ��� ���� �κ����տ� ���� �� ������ ��� ȣ��
		quickSort(a+i+1, n-i-1);	// �Ǻ��� ������ �κ����տ� ���� �� ������ ��� ȣ��
	}


	return 0;
}
// �ؽ� Function ����
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;	// key ���� ������ ������� ������ ������ �����Ѵ�.
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)			//�ؽ����̺� �ʱ�ȭ
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
		if (hashtable[hashcode] == -1)						// �ؽ����̺��� �ؽ��ڵ� ��ġ�� -1�̸� 
		{
			hashtable[hashcode] = key;						// �ؽ����̺� key�� ����
		} else 	{

			index = hashcode;								// �ƴϸ� �ε����� �ؽ��ڵ� ����

			while(hashtable[index] != -1)					// �ؽ����̺��� -1�� �ƴҶ� ����
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;   // �浹�� �Ͼ�� �� ���� ���̺� ����
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;							// �ε��� ��ġ�� key���� ����
		}
	}

	return 0;
}
/* �ؽ� Ű Ž�� */
int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)				// ã�� ���� �ε����� ��ġ�� ������ �ε����� ��ȯ
		return index;

	while(ht[++index] != key)  			// key���� ���� �ε����� ã�´�.
	{
		index = index % MAX_HASH_TABLE_SIZE;	// �ε����� 0~MAX_HASH_TABLE_SIZE ������ ���� 1�� ����
	}
	return index;							
}



