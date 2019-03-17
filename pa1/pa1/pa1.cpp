#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#define MAX 300000
#define MINI_MAX 500
#define BUFFERSIZE 30
#define numb 5
char *sentence_array[MAX];
char *sub_array[MAX];
char *size_array[MAX];
char *buffers;

char buffer2[MINI_MAX];

int count = 0;
int sentence_num = 0;
int cur = 0;
int size_num;

int save[10] = { 0 };

int first=0;
int last =0;

int Bsearch(int first,int last)
{

	if (count == 0) {
		first =0;
		last = size_num - 1;
		count++;
	}
	 int mid = (first + last) / 2;

	if (first > last )	{
		
		return first -1;
	}
	
	if (strcmp(buffers, size_array[mid]) == 0) {
		return mid;
	}
	else if (strcmp(buffers,size_array[mid])<0) {
			last = mid - 1;
			return Bsearch(first,last);
	}
	else {
			first = mid + 1;
			return Bsearch(first,last);
	}
	
	
}
void find() {
	int check = Bsearch(first, last);

	if (check == -1) {
		return;
	}

	else if (strcmp(buffers , size_array[check])!=0) {
		printf("Not found\n");
		printf("%s\n", size_array[check - 1]);
		printf("%s\n", size_array[check + 1]);
	}
	else {
		for (int i = check - numb; i < check + numb; i++) {
			if (strcmp(buffers, size_array[i]) == 0){
				save[cur] = i;
				cur++;
			}
		}
		printf("%d found\n", cur );
		for (int i = 0; i < cur; i++) {
			printf("%s\n", sentence_array[save[i]]);
			save[i] = 0;
		}
		
	}
}
void read()
{
	FILE *read_fp = fopen("dict.txt", "r");

	for (int i = 0; i < MAX; i++) {
		sentence_array[i] = (char *)malloc(sizeof(int)*MINI_MAX);
		sub_array[i] = (char *)malloc(sizeof(int)*MINI_MAX);
	}
	while (!feof(read_fp)) {
		
	
		fgets(sentence_array[sentence_num], MAX, read_fp);
		sub_array[sentence_num] = sentence_array[sentence_num];
		sentence_num++;
		fgetc(read_fp);
	}

	for (int i = MAX - 1; i >= sentence_num; i--) {
		free(sentence_array[i]);
		free(sub_array[i]);
	}

	fclose(read_fp);
}

void size()
{
	size_num = sentence_num;
	char space[] = " ";
	
	for (int i = 0; i < MAX; i++) {
		size_array[i] = (char *)malloc(sizeof(int)*MINI_MAX);
	}

	for (int i = 0; i < size_num; i++) {
		char *token = strtok(sub_array[i], space);
		sentence_array[0];

		size_array[i] = token;
	}
	for (int i = 0; i < size_num; i++) {
		if (i == size_num - 1)
			break;
		if (size_array[i] == size_array[i + 1]) {
			for (int j = i + 1; j < size_num; j++){
				if (j == size_num - 1)
					break;
				size_array[j] = size_array[j + 1];
			}
			size_array[size_num] = '\0';
			size_num--;
		}		
	}
	printf("단어의 갯수는 %d입니다.\n", size_num - 1);
}


int main()
{

	char buffer[MINI_MAX];
	
	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0)
			read();
		else if (strcmp(buffer, "find") == 0) {
			scanf("%s", buffer2);

			buffer2[0] = toupper(buffer2[0]);
			buffers = strdup(buffer2);
			find();
			for (int i = 0; i < cur; i++) {
				save[i] = 0;
			}
			cur = 0, count = 0;
		
		}
		else if (strcmp(buffer, "size") == 0)
			size();
	}
}