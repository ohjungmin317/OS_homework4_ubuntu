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
    char ReferenceString[STR_REF_NUM]; // 파일이나 랜덤 값으로 받는 reference 값을 넣어주는 배열 
    char r_bit[STR_REF_NUM]; // 파일이나 랜덤 값으로 받는 reference bit 값을 넣어주는 배열 (0또는 1)
    char w_bit[STR_REF_NUM]; // 파일이나 랜덤 값으로 받는 modify bit 값을 넣어주는 배열 (0또는 1)
} node;
node *p;


/* ------ algo for use 1-7 page streame ------ */
int page_frame_size; // frame_size 입력
int input_for_data; // data 방법 입력 (1: 랜덤 값 2: 파일로 처리)
bool check, replace; // check -> secondchance에서 사용 0이면 full or no hit | replace -> page_fault를 확인하기 위한 bool값 
int NO_OF_PAGES; // 페이지 개수 입력하는 변수