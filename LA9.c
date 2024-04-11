#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 23

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

// Fill out this structure
struct HashType
{
	struct RecordType* data;
	struct HashType* next;
};

// Compute the hash function
int hash(int x)
{
	return (x % HASHTABLE_SIZE);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType* pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType** pHashArray, int hashSz)
{
	int i;
	struct HashType* temp;

	for (i = 0;i < hashSz;++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i] != NULL) {
			printf("index %d ", i);

			temp = pHashArray[i];
			while(temp != NULL){
				printf("-> %d %c %d ",temp->data->id,temp->data->name,temp->data->order);
				temp = temp->next;
			}
			printf("\n");

		}
	}
}

struct HashType **ArrayToHash(struct RecordType *array ,int arraysize) {
	int i, keydex;
	struct HashType** hashtable = (struct HashType**)calloc(HASHTABLE_SIZE, sizeof(struct HashType*));
	//initialize nodes within table

	struct HashType* tempnode;
	for (i = 0;i < arraysize; i++) {
		keydex = hash(array[i].id);
		tempnode = hashtable[keydex];

		//make new node
		struct HashType* newnode = (struct HashType*)calloc(1, sizeof(struct HashType));
		struct RecordType* newitem = (struct RecordType*)calloc(1, sizeof(struct RecordType));
		//copy data from array to new node
		newitem->id = array[i].id;
		newitem->name = array[i].name;
		newitem->order = array[i].order;
		newnode->data = newitem;

		newnode->next = tempnode;
		hashtable[keydex] = newnode;

		/*
		if (tempnode == NULL) {
			tempnode = newnode;
			continue;
		}
		while (tempnode->next != NULL) {
			tempnode = tempnode->next;
		}
		tempnode->next = newnode;
		*/

		//hashtable[i]->data = (struct RecordType*)malloc(1 * sizeof(struct RecordType));
	}
	return hashtable;


}

int main(void)
{
	struct RecordType* pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType **table = ArrayToHash(pRecords,recordSz);
	displayRecordsInHash(table, HASHTABLE_SIZE);

	return 0;
}
