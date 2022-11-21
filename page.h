#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#define MAX 4096
#define FILE_NAME 100
#define STR_REF_NUM 1000
#define NUM 4096

/* ------ for use algorithm function ------ */
void Optimal();

void FIFO();

void LIFO();

void LRU();
int findLRU(int time[], int n);

void LFU();
void print(int frameno,int frame[]);

void SecondChance();

void EnhancedSecondChance();

void selected_replace_algorithm(char *argv_1[], int selected[]);
int split(char *string, char *seperator, char *argv[]);
void compare_Optimal();

/* ------ algo for use 1-7 page stream ------ */
typedef struct node
{
    char ReferenceString[STR_REF_NUM]; // �����̳� ���� ������ �޴� reference ���� �־��ִ� �迭 
    char r_bit[STR_REF_NUM]; // �����̳� ���� ������ �޴� reference bit ���� �־��ִ� �迭 (0�Ǵ� 1)
    char w_bit[STR_REF_NUM]; // �����̳� ���� ������ �޴� modify bit ���� �־��ִ� �迭 (0�Ǵ� 1)
} node;
node *p;


/* ------ algo for use 1-7 page streame ------ */
int page_frame_size; // frame_size �Է�
int input_for_data; // data ��� �Է� (1: ���� �� 2: ���Ϸ� ó��)
bool check, replace; // check -> secondchance���� ��� 0�̸� full or no hit | replace -> page_fault�� Ȯ���ϱ� ���� bool�� 
int NO_OF_PAGES; // ������ ���� �Է��ϴ� ����