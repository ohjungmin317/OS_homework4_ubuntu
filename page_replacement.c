#include "page.h"

int main (void) {
	char input_algorithm[MAX];
    p = (node *)malloc(sizeof(node));

    /* ------ For UI variable ------ */

	/* ------ referencestring and r_bit, w_bit file process variable ------ */
    FILE *fp1; // for save the data
    FILE *fp2; // for use reference stream file
    FILE *fp3; // for use bit stream file 
	char fname[FILE_NAME]; // for stream file 
    char fname1[FILE_NAME]; // for bit file
    char buffer[MAX];
    char buffer1[MAX];

    /* ------ select algorithm variable ------ */
    int argc_1;
    char *argv_1[10];
    int exception = 0;
    int selected[MAX];

    /* ------ select frame number ------ */
    int argc_2;
    char *argv_2[10];

	/* ------ way to input data  ------ */
    int argc_3;
    char *argv_3[10];
    srand((unsigned)time(NULL));
    
	/* ------ UI method ------ */
    while(1){ // selected algorithm
    exception = 0;
	memset(selected,0,sizeof(selected)); // selected 0 초기화	
	printf("A.Choose the Page Replacement Algorithm simulation (max:3) :\n");
    printf("(1) Optimal (2) FIFO (3) LIFO (4) LRU (5) LFU (6) SC (7) ESC (8) All\n");
	printf("write only number not use ()\n");

    fgets(input_algorithm,sizeof(input_algorithm),stdin); // get number selected algorithm 
        input_algorithm[strlen(input_algorithm)-1] = '\0';
        argc_1 = split(input_algorithm," ",argv_1); // split() 함수를 띄어쓰기 기준으로 argc_1에 해당 숫자를 저장 
    
    for(int i=0; i<argc_1; i++){ // 1 이하의 숫자거나 8번 이상의 숫자인 경우에는 예외 처리 
        if((argc_1>1 && !strcmp(argv_1[i],"8")) || (atoi(argv_1[i])<1 || atoi(argv_1[i])>8))
        exception = 1;
    }
    if(argc_1>3 || argc_1==0 || exception){ // 예외처리에 대한 에러 메세지 
		printf("Input error\nUsag : Choose the Page Replacement Algorithm simulation (max:3)\nYou can use only <OPT, FIFO, LIFO, LRU, LFU, SC, ESC, ALL>\n");
        printf("\n");
		continue;
	}

    if(!strcmp(argv_1[0], "8")){ // 8번을 선택하게 되면 모든 bit가 1로 되면서 해당 알고리즘 모두 출력을 하게 된다.
        for(int i = 0; i<7; i++) selected[i] = 1;
        break;
    }
    for(int i = 0; i<argc_1; i++){ // 알고리즘 선택을 1 - 8번 까지 받기 위해
        selected[atoi(argv_1[i])-1] = 1;
    }
    break;
    }

while(1){ // frame number 
    printf("B.Put the frame number.(3~10)\n");

    fgets(input_algorithm,sizeof(input_algorithm),stdin); // frame number 받는 변수 fgets 이용 
        input_algorithm[strlen(input_algorithm)-1]='\0';
        argc_2 = split(input_algorithm," ",argv_2);
		
        if(argc_2!=1){ // input error message 
            printf("Input error\nUsag: frame number(3~10)\n");
            printf("\n");
            continue;
        }
        page_frame_size = atoi(argv_2[0]);
        if(page_frame_size <3 || page_frame_size > 10){ // frame 개수가 3 이하 10 이상인 경우 error 메세지 출력 
			printf("Input error\nUsag: Put the frame number.(3~10)\n");
            printf("\n");
            continue;
        }
        break;
}

 while(1){ // for select input data way 
        printf("C.Choose the method of data input.(1,2)\n");

        fgets(input_algorithm,sizeof(input_algorithm),stdin); // 데이터 입력 방법을 받기 위한 fgets
        input_algorithm[strlen(input_algorithm) -1 ]='\0';
        argc_3=split(input_algorithm," ",argv_3);

        if(argc_3!=1||strcmp(argv_3[0],"1")&&strcmp(argv_3[0],"2")){ // 1 이나 2가 아닌 다른 숫자를 입력하였을시 출력해주는 error 메세지 
            printf("Input error\nUsag: Choose the method of data input.(1,2)\n");
            printf("\n");
            continue;
        }
        input_for_data=atoi(argv_3[0]);
        printf("C-1.write the number of page stream: ");
        scanf("%d",&NO_OF_PAGES);
        break;
    }

    if (input_for_data == 1){ // 만약에 input_data에 1을 입력시에는 난수 값에 의해 

        fp1 = fopen("referencestream.txt", "w");
        for (int i = 0; i < NO_OF_PAGES; i++)
        {
            p->ReferenceString[i] = rand() % 30 + 1; // 1 ~ 30 까지 난수 생성
            fprintf(fp1," %d", p->ReferenceString[i]);
        }
        fclose(fp1);

        fp1 = fopen("bitstream.txt", "w");
        for (int i = 0; i < NO_OF_PAGES; i++)
        {
            p->r_bit[i] = rand() % 2; // r_bit 0 또는 1 난수 생성
            p->w_bit[i] = rand() % 2; // w_bit 0 또는 1 난수 생성
            fprintf(fp1,"%d %d ", p->r_bit[i],p->w_bit[i]);
        }
        fclose(fp1);

    }

    else
    { // 파일로 직접 입력 받아서 출력 

        /*page stream과 r_bit w_bit 파일 입력 받기*/
        printf("C-2.write the stream_file name: ");
        scanf("%s",fname);
        printf("C-3.write the bit_file name: ");
        scanf("%s",fname1);

        /* ------ for use reference / r&w_bit file  ------ */
        if((fp2=fopen(fname, "r")) == NULL){
		fprintf(stderr, "Open error for %s\n",fname);
		exit(1);
	    }
        if((fp3=fopen(fname1, "r")) == NULL){
		fprintf(stderr, "Open error for %s\n",fname1);
		exit(1);
	    }

        fread(buffer,1, sizeof(buffer), fp2); // for read reference file
        fread(buffer1,1,sizeof(buffer1),fp3); // for read bit file

        char *argv_4[NUM]; 
        char *argv_5[NUM];

        int count = split(buffer, " ", argv_4); // split 함수를 사용 (띄어쓰기 기준으로 값을 추출)
        int count1=split(buffer1," ",argv_5); // split 함수를 사용 (띄어쓰기 기준으로 값을 추출)
        
        for (int i = 0; i < count; i++)
        {
            p->ReferenceString[i] = atoi(argv_4[i]);
            //printf("%d ", p->ReferenceString[i]);
        }

        for (int i = 0, j = 0; i < count1; i = i + 2, j++) // 비트 파일은 홀수번째가 reference bit 
        {
            p->r_bit[j] = atoi(argv_5[i]);
            //printf("%d ", p->r_bit[j]);
        }
    
        for (int i = 1, j = 0; i < count1; i = i + 2, j++) // 비트 파일은 짝수번 째가 dirty bit 
        {
            p->w_bit[j] = atoi(argv_5[i]);
            //printf("%d ", p->w_bit[j]);
        }
    }
    fp1 = fopen("test.txt", "a+");
    printf("\n");
    printf("page reference stream : ");

    fprintf(fp1, "\n");
    fprintf(fp1, "page reference stream : ");

    for (int i = 0; i < NO_OF_PAGES; i++){ // 출력 값에 reference stream 값 출력 
        printf("%d ", p->ReferenceString[i]);
    }

    for (int i = 0; i < NO_OF_PAGES; i++)
        fprintf(fp1, "%d ", p->ReferenceString[i]);

    printf("\n\n");
    fprintf(fp1, "\n\n");
    fclose(fp1);

    selected_replace_algorithm(argv_1, selected); // selected algorithm 함수 실행문   

    printf("D.END\n");
    exit(0);
    fclose(fp2); //for close file fp2
    fclose(fp3); // for close file fp3
    free(p); // p malloc free
}

/* ------ 옵션에 따른 알고리즘 기법 적용 ------ */
void selected_replace_algorithm(char *argv_1[], int selected[]){ // 0과 1을 나눠서 0일 때는 off 1일때는 on으로 해서 선택을 하게 되면 1로 변경이 되고 1이되면 해당 알고리즘 작동
    if (selected[0] == 1) // 1번을 누르면 해당 알고리즘이 1로 바뀌어서 실행이 된다.
    {
        Optimal();
    }

    if (selected[1] == 1) // 2번을 누르면 해당 알고리즘이 1로 바뀌어서 실행이 된다.
    {
        FIFO();
    }

    if (selected[2] == 1) // 3번을 누르면 해당 알고리즘이 1로 바뀌어서 실행이 된다.
    {
        LIFO();
    }

    if (selected[3] == 1) // 4번을 누르면 해당 알고리즘이 1로 바뀌어서 실행이 된다.
    {
        LRU();
    }

    if (selected[4] == 1) // 5번을 누르면 해당 알고리즘이 1로 바뀌어서 실행이 된다.
    {
        LFU();
    }
    
    if (selected[5] == 1) // 6번을 누르면 해당 알고리즘이 1로 바뀌어서 실행이 된다.
    {
        SecondChance();
    }

    if (selected[6] == 1) // 7번을 누르면 해당 알고리즘이 1로 바뀌어서 실행이 된다.
    {
        EnhancedSecondChance();
    }

 }

/* ------ Optimal ------ */
/* ------ Optimal : 가장 오랫동안 사용하지 않을 페이지를 교체하는 알고리즘 ------ */
 void Optimal() 
 {
     FILE *fp1;
     int frames[page_frame_size], temp[page_frame_size];
     int flag1, flag2, flag3;
     int i, j, k;
     int pos, max;
     int faults = 0;
     
     
     fp1 = fopen("test.txt", "a+");
     printf("======================Optimal======================\n");
     printf("time\t\t\t\t\tpage fault\n\n");

     fprintf(fp1,"======================Optimal======================\n");
     fprintf(fp1,"time\t\t\t\t\t\t\t\t\tpage fault\n\n");
     fclose(fp1);
     
     for (i = 0; i < page_frame_size; ++i) // page_frame_size 크기 만큼 frame table에 비어 있는 곳은 -1을 대입 
     {
         frames[i] = -1;
     }

     for (i = 0; i < NO_OF_PAGES; ++i) // page_size의 크기 만큼 탐색 
     {
         flag1 = flag2 = 0; // flag 1 , flag 2 0과 1을 기준으로 해당 테이블이 full인지 아닌지 확인 하기 위한 용도 
         replace = false; // page fault를 확인하기 위한 용도

         for (j = 0; j < page_frame_size; ++j)
         {
             if (frames[j] == p->ReferenceString[i]) // frames number와 referencestring이 일치하여 hit 하는 경우 
             {
                 flag1 = flag2 = 1; // flag1 = 1 -> hit 하는 경우 | flag2 = 1 -> 비어있다는 1
                 break;
             }
         }

         if (flag1 == 0) // flag1=0 이면  hit 하지 않는 경우 
         {
             for (j = 0; j < page_frame_size; ++j)
             {
                 if (frames[j] == -1) // frame table에서 -1 값을 찾게 되면 
                 {
                     faults++; // page fault 값 증가 
                     replace = true;
                     frames[j] = p->ReferenceString[i]; // reference string 값을 frame table에 넣어준다.
                     flag2 = 1;
                     break;
                 }
             }
         }

         if (flag2 == 0) // frame table이 full인 경우 
         {
             flag3 = 0;

             for (j = 0; j < page_frame_size; ++j)
             {
                 temp[j] = -1;

                 for (k = i + 1; k < NO_OF_PAGES; ++k)
                 {
                     if (frames[j] == p->ReferenceString[k]) // full 이고 hit 하는 경우 
                     {
                         temp[j] = k;
                         break;
                     }
                 }
             }

             for (j = 0; j < page_frame_size; ++j)
             {
                 if (temp[j] == -1) // 비어 있는 경우 
                 {
                     pos = j;
                     flag3 = 1;
                     break;
                 }
             }

             if (flag3 == 0) // full인 경우 victim을 선정하여 교체를 해야하는 경우 
             {
                 max = temp[0];
                 pos = 0;

                 for (j = 1; j < page_frame_size; ++j)
                 {
                     if (temp[j] > max) // 오랫동안 사용하지 않는 것을 탐색하여 서로 비교 
                     {
                         max = temp[j];
                         pos = j;
                     }
                 }
             }
             frames[pos] = p->ReferenceString[i]; // 해당 값을 찾게 되면 frame table에 reference 값을 변경 
             faults++; // reference string이 교체가 되었기 때문에 page fault 값 증가 
             replace = true;
         }

         /* ------ 결과 값을 출력하기 위한 구문 ------ */
        fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1); // times == page_size
        fprintf(fp1,"%-15d", i + 1); 

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++) // frames 테이블이 어떻게 변하는지 과정을 보여주기 위한 구문
        {
            if (frames[j] < 0)
                printf("%10c", ' ');
            else
                printf("%-10d", frames[j]); 

            if (frames[j] < 0)
                fprintf(fp1,"%10c", ' ');
            else
                fprintf(fp1,"%-10d", frames[j]);
        }
        if (replace)
            printf("F\n");
        else
            printf("\n");

        if (replace)
            fprintf(fp1,"F\n");
        else
            fprintf(fp1,"\n");
        fclose(fp1);
     }
     fp1 = fopen("test.txt","a+");

     printf("\n\nTotal Page Faults = %d\n", faults);
     printf("\n");

     fprintf(fp1,"\n\nTotal Page Faults = %d\n", faults);
     fprintf(fp1,"\n");

     fclose(fp1);
 }

/* ------ FIFO ------ */
/* ------ FIFO: 가장 먼저 들어온것을 가장 먼저 내보는 것 ------ */
void FIFO()
{
    FILE *fp1;
    int i, j;
    int flag;
    int faults = 0;
    int frames[page_frame_size];

    fp1 = fopen("test.txt","a+"); 
    printf("=======================FIFO=======================\n");
    printf("time\t\t\t\t\tpage fault\n\n");

    fprintf(fp1,"=======================FIFO=======================\n");
    fprintf(fp1,"time\t\t\t\t\t\t\t\t\tpage fault\n\n");

    fclose(fp1);

    for (i = 0; i < page_frame_size; i++)
    {
        frames[i] = -1; // frmae 테이블 -1로 초기화 
    }

    for (i = 0; i < NO_OF_PAGES; i++)
    {
        flag = 0;
        replace = false;

        for (j = 0; j < page_frame_size; j++)
        {
            if (p->ReferenceString[i] == frames[j]) // frame table에 있는 수와 reference sstring이 같은 경우 ==  hit
            {
                flag = 1; // 비어 있는 경우 1 
                faults--; 
                
            } 
        }
        faults++; // 아닌 경우에는 hit-miss -> fault값 증가 
        
        if ((faults <= page_frame_size) && (flag == 0)) // frame table이 꽉찬 경우 
        {
            frames[i] = p->ReferenceString[i]; // 
            replace = true;
        }
        else if (flag == 0) // 꽉찬 경우 victim을 정해야 할 때 
        {
            frames[(faults - 1) % page_frame_size] = p->ReferenceString[i]; // 먼저 들어온 것은 먼저 내보기 위한 식 
            replace = true;
        }

        /* ------ 결과 값을 출력하기 위한 구문 ------ */
        fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1);
        fprintf(fp1,"%-15d", i + 1);

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++) // frames 테이블이 어떻게 변하는지 과정 보여주기 위한 구문 
        {
            if (frames[j] < 0)
                printf("%10c", ' ');
            else
                printf("%-10d", frames[j]);

            if (frames[j] < 0)
                fprintf(fp1,"%10c", ' ');
            else
                fprintf(fp1,"%-10d", frames[j]);
        }
        if (replace)
            printf("F\n");
        else
            printf("\n");

        if (replace)
            fprintf(fp1,"F\n");
        else
            fprintf(fp1,"\n");
        fclose(fp1);
     }
     fp1 = fopen("test.txt","a+");

     printf("\n\nTotal Page Faults = %d\n", faults);
     printf("\n");

     fprintf(fp1,"\n\nTotal Page Faults = %d\n", faults);
     fprintf(fp1,"\n");

     fclose(fp1);

     compare_Optimal();
}

/* ------ LIFO ------ */
/* ------ LIFO : 가장 마지막에 들어온 것을 가장 처음에 내보느내는 알고리즘 ------ */
void LIFO()
{
    FILE *fp1;
    int i, j;
    int flag;
    int faults = 0;
    int frames[page_frame_size];

    fp1 = fopen("test.txt","a+");
    printf("=======================LIFO=======================\n");
    printf("time\t\t\t\t\tpage fault\n\n");

    fprintf(fp1,"=======================LIFO=======================\n");
    fprintf(fp1,"time\t\t\t\t\t\t\t\t\tpage fault\n\n");

    fclose(fp1);
    for (i = 0; i < page_frame_size; i++)
    {
        frames[i] = -1; // frames table -1로 초기화 
    }

    for (i = 0; i < NO_OF_PAGES; i++)
    {
        flag = 0; // FLAG
        replace = false;
        for (j = 0; j < page_frame_size; j++)
        {
            if (p->ReferenceString[i] == frames[j]) // hit 하는 경우 
            {
                flag++;
            }
        }
        if (flag) // frames table에 값이 변하는 과정 보여주기 위한 if 
        {
            fp1 = fopen("test.txt", "a+");
            printf("%-15d", i + 1);
            fprintf(fp1, "%-15d", i + 1);

            fclose(fp1);

            fp1 = fopen("test.txt", "a+");

            for (int j = 0; j < page_frame_size; j++)
            {
                if (frames[j] < 0)
                    printf("%10c", ' ');
                else
                    printf("%-10d", frames[j]);

                if (frames[j] < 0)
                    fprintf(fp1, "%10c", ' ');
                else
                    fprintf(fp1, "%-10d", frames[j]);
            }
            if (replace)
                printf("F\n");
            else
                printf("\n");

            if (replace)
                fprintf(fp1, "F\n");
            else
                fprintf(fp1, "\n");
            fclose(fp1);
            continue;
        }

        for (int n = 0; n < page_frame_size - 1; n++)
        {
            if (frames[n] == -1) // hit 하지 않고 frame table 순회하는 중 -1를 만나는 경우 
            {
                frames[n] = p->ReferenceString[i]; // frames table에 referencestring 값을 넣어준다.
                flag++;
                faults++; // hit-miss이기에 fault 값 증가 
                replace = true;
                break;
            }
        }
        if (flag) // frames table에 값이 변하는 과정 보여주기 위한 if 
        {
            fp1 = fopen("test.txt", "a+");
            printf("%-15d", i + 1);
            fprintf(fp1, "%-15d", i + 1);

            fclose(fp1);

            fp1 = fopen("test.txt", "a+");

            for (int j = 0; j < page_frame_size; j++)
            {
                if (frames[j] < 0)
                    printf("%10c", ' ');
                else
                    printf("%-10d", frames[j]);

                if (frames[j] < 0)
                    fprintf(fp1, "%10c", ' ');
                else
                    fprintf(fp1, "%-10d", frames[j]);
            }
            if (replace)
                printf("F\n");
            else
                printf("\n");

            if (replace)
                fprintf(fp1, "F\n");
            else
                fprintf(fp1, "\n");
            fclose(fp1);
            continue;
        }

        frames[page_frame_size - 1] = p->ReferenceString[i]; // 위의 모든 경우가 아닌 경우에는 가장 마지막에 있는 것을 계속 교체 
        faults++; // hit-miss 이기에 fault값 증가 
        replace = true;

        /* ------ 결과 값을 출력하기 위한 구문 ------ */
        fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1);
        fprintf(fp1,"%-15d", i + 1);

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] < 0)
                printf("%10c", ' ');
            else
                printf("%-10d", frames[j]);

            if (frames[j] < 0)
                fprintf(fp1,"%10c", ' ');
            else
                fprintf(fp1,"%-10d", frames[j]);
        }
        if (replace)
            printf("F\n");
        else
            printf("\n");

        if (replace)
            fprintf(fp1,"F\n");
        else
            fprintf(fp1,"\n");
        fclose(fp1);
     }
     fp1 = fopen("test.txt","a+");

     printf("\n\nTotal Page Faults = %d\n", faults);
     printf("\n");

     fprintf(fp1,"\n\nTotal Page Faults = %d\n", faults);
     fprintf(fp1,"\n");
    
     fclose(fp1);

     compare_Optimal();
}

/* ------ LRU ------ */
/* ------ LRU : 가장 오랫동안 사용하지 않은 페이지를 교체하는 알고리즘 ------ */
void LRU()
{
    FILE *fp1;
    int frames[page_frame_size], time[page_frame_size];
    int counter = 0;
    int flag1, flag2;
    int i, j;
    int pos;
    int faults = 0;

    fp1 = fopen("test.txt","a+");
    
    printf("=======================LRU=======================\n");    
    printf("time\t\t\t\t\tpage fault\n\n");

    fprintf(fp1,"=======================LRU=======================\n");
    fprintf(fp1,"time\t\t\t\t\t\t\t\t\tpage fault\n\n");
    fclose(fp1);
    
    for (i = 0; i < page_frame_size; ++i)
    {
        frames[i] = -1; // frame table -1로 초기화 
    }

    for (i = 0; i < NO_OF_PAGES; ++i) // page_size 만큼 순회
    {
        flag1 = flag2 = 0;
        replace = false;

        for (j = 0; j < page_frame_size; ++j)
        {
            if (frames[j] == p->ReferenceString[i]) // hit 하는 경우 
            {
                counter++; // 해당 값의 횟수 하나 증가
                time[j] = counter; // 나중에 비교하기 위해 time 배열에다가 넣어준다.
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) // frame table이 비어 있는 경우 
        {
            for (j = 0; j < page_frame_size; ++j)
            {
                if (frames[j] == -1) // frame table 탐색하면서 -1 값을 찾게 되면 
                {
                    
                    frames[j] = p->ReferenceString[i]; // referencestring의 값을 frame table에 넣어준다.
                    counter++; // 해당 reference 값은 하나 증가
                    faults++; // hit-miss 이기 때문에 fault값 증가
                    replace = true;
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) // frames table이 full인 경우 
        {
            pos = findLRU(time, page_frame_size);
            counter++;
            faults++;
            replace = true;
            frames[pos] = p->ReferenceString[i]; // 가장 오랫동안 사용하지 않는 알고리즘을 찾아서 reference string에 있는 값과 교체
            time[pos] = counter; // 참조한 값에 대한 counter는 증가 
        }

       /* ------ 결과 값을 출력하기 위한 구문 ------ */ 
       fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1);
        fprintf(fp1,"%-15d", i + 1);

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] < 0)
                printf("%10c", ' ');
            else
                printf("%-10d", frames[j]);

            if (frames[j] < 0)
                fprintf(fp1,"%10c", ' ');
            else
                fprintf(fp1,"%-10d", frames[j]);
        }
        if (replace)
            printf("F\n");
        else
            printf("\n");

        if (replace)
            fprintf(fp1,"F\n");
        else
            fprintf(fp1,"\n");
        fclose(fp1);
     }
     fp1 = fopen("test.txt","a+");

     printf("\n\nTotal Page Faults = %d\n", faults);
     printf("\n");

     fprintf(fp1,"\n\nTotal Page Faults = %d\n", faults);
     fprintf(fp1,"\n");

     fclose(fp1);

    compare_Optimal();
}

/* ------ LFU ------ */
/* ------ LFU : 참조횟수가 가장 작은 페이지를 교체하는 알고리즘 ------ */
void LFU()
{
    FILE *fp1;
    int i, j, k, n;
    int frames[page_frame_size], freq_time[30] = {0};
    int move_rp = 0, faults = 0;
    int flag;
    int replace_index, leastcount;

    fp1 = fopen("test.txt","a+");
    printf("=======================LFU=======================\n");
    printf("time\t\t\t\t\tpage fault\n\n");

    fprintf(fp1,"=======================LFU=======================\n");
    fprintf(fp1,"time\t\t\t\t\t\t\t\t\tpage fault\n\n");
    fclose(fp1);
    
    for (i = 0; i < page_frame_size; i++)
    {
        frames[i] = -1; // frame table에 대한 값을 -1로 초기화
    }
    for (i = 0; i < NO_OF_PAGES; i++) // page_size만큼 순회 
    {
        replace = false;
        flag = 0;

        fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1);
        fprintf(fp1,"%-15d", i + 1);

        fclose(fp1);

        for (j = 0; j < page_frame_size; j++)
        {
            if (p->ReferenceString[i] == frames[j]) // hit 하는 경우
            {
                flag = 1;
                freq_time[j]++; // 해당 값은 참조 횟수 증가
                print(page_frame_size, frames);
                break;
            }
        }
        if (flag == 0 && faults < page_frame_size) // hit하지 않고 비어 있는 겨우
        {
            frames[move_rp] = p->ReferenceString[i]; // 비어 있는 값에 reference string 값 대입 
            freq_time[move_rp] += 1; // 해당 참조 회수 증가 
            move_rp = (move_rp + 1) % page_frame_size; // move_rp = 0으로 시작
            faults++; // hit-miss이기 때문에 fault 값 증가
            replace = true;
            print(page_frame_size, frames);
        }
        else if (flag == 0) // frames가 full인 경우 
        {
            replace_index = 0;
            leastcount = freq_time[0]; // 참조 횟수 값 대입 
            for (j = 1; j < page_frame_size; j++)
            {
                if (freq_time[j] < leastcount) // 참조횟수가 가장 적은 것
                {
                    replace_index = j; // 해당 값을 대입 
                    leastcount = freq_time[j]; 
                }
            }

            frames[replace_index] = p->ReferenceString[i]; // 해당 값을 교체 -> index에 순서에서 가장 작은 index 값 교체
            freq_time[replace_index] = 1; // 값을 참조하였기 때문에 참조횟수 1
            faults++; // hit - miss 이기에 fault 값 증가  
            replace = true;
            print(page_frame_size, frames);
        }
        
        /* ------ 결과 값을 출력하기 위한 구문 ------ */
        fp1 = fopen("test.txt", "a+");

        if (replace)
            printf("F\n");
        else
            printf("\n");

        if (replace)
            fprintf(fp1, "F\n");
        else
            fprintf(fp1, "\n");
        fclose(fp1);
    }
    fp1 = fopen("test.txt", "a+");

    printf("\n\nTotal Page Faults = %d\n", faults);
    printf("\n");

    fprintf(fp1, "\n\nTotal Page Faults = %d\n", faults);
    fprintf(fp1, "\n");

    fclose(fp1);

    compare_Optimal();
}

/* ------ SecondChance ------ */
/* ------ SecondChance : r_bit를 이용하여 교체하기 전에 1인 경우에는 기회를 한 번 더 준다. -> circual queue 사용 (moduler) ------ */
void SecondChance() // 시작포인트의 다음것부터 뒤져서 확인을 해본다.
{
    FILE *fp1;
    int victim = 0;
    int frames[page_frame_size];
    int reference_bit[page_frame_size];
    int page_fault = 0;

    fp1 = fopen("test.txt","a+");
    printf("==========================SECOND-CHANCE============================\n");
    printf("time\t\t\t\t\t\t\tpage fault\n\n");

    fprintf(fp1,"============================SECOND-CHANCE============================\n");
    fprintf(fp1,"time\t\t\t\t\t\t\t\t\t\t\t\t\t\tpage fault\n\n");
    fclose(fp1);

    for (int i = 0; i <page_frame_size; i++)
    {
        frames[i] = -1; // frame table을 -1로 초기화 
    }

    for (int i = 0; i < NO_OF_PAGES; i++)
    {
        check = false;
        replace = false;

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] == p->ReferenceString[i]) // hit하는 경우
            {
                reference_bit[j] = 1; // 해당 값은 참조하기 떄문에 reference bit를 1로 준다.
                check = true;
                break;
            }

            if (frames[j] < 0) // hit 하지 않고 -1의 값을 찾는 경우
            { 
                frames[j] = p->ReferenceString[i]; // 해당 값을 reference string으로 교체 
                reference_bit[j] = 0; // reference bit = 0으로 할당
                page_fault++; // fault 값 증가 
                check = true; // 비어있는경우는 true -> false 다 차있는 경우 
                replace = true;
                break;
            }
        }

        if (!check)
        {
            int j=victim; // j는 victim으로 설정 -> j가 victim 값이 된다.
            for (int t = 0; t < page_frame_size; t++)
            {
                if(j==page_frame_size)
                    j=0;
                if (reference_bit[j] == 0) // reference bit가 0인 경우에는 break
                {
                    break;
                }
                    reference_bit[j] = 0;
                j++;
            }
            if(j==page_frame_size){ // reference bit가 같은 경우에는 circual queue로 순회하여 해당 포인터 기준으로 다음 포인터의 값을 내보낸다.
                j=0;
            }
            frames[j] = p->ReferenceString[i]; // reference bit가 0인 경우에는 해당 값을 변경
            page_fault++;
            replace = true;
            reference_bit[j]=0;
            victim = (j + 1)%page_frame_size;
            
        }

        if (victim == page_frame_size)
            victim = 0;

        /* ------ 결과 값을 출력하기 위한 구문 ------ */
       fp1 = fopen("test.txt","a+");
        printf("%-10d", i + 1);
        fprintf(fp1,"%-10d", i + 1);

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] < 0)
                printf("%9c", ' ');
            else
                printf("%-4d", frames[j]);

            if (frames[j] < 0)
                printf("%9c", ' ');
            else
                printf(" (%d)%-10c", reference_bit[j], ' ');

            if (frames[j] < 0)
                fprintf(fp1, "%9c", ' ');
            else
                fprintf(fp1, "%-4d", frames[j]);

            if (frames[j] < 0)
                fprintf(fp1, "%9c", ' ');
            else
                fprintf(fp1, " (%d)%-10c", reference_bit[j], ' ');
        }
        if (replace)
            printf("F\n");
        else
            printf("\n");

        if (replace)
            fprintf(fp1,"F\n");
        else
            fprintf(fp1,"\n");
        fclose(fp1);
     }
     fp1 = fopen("test.txt","a+");

     printf("\n\nTotal Page Faults = %d\n", page_fault);
     printf("\n");

     fprintf(fp1,"\n\nTotal Page Faults = %d\n", page_fault);
     fprintf(fp1,"\n");

     fclose(fp1);

     compare_Optimal();
}

/* ------ ESC ------ */
/* ------ ESC : reference_bit와 modify_bit를 이용하여 (0,0) / (0,1) / (1,0) / (1,1) 순서대로 확인하여 victim을 정해서 내보낸다. ------ */
void EnhancedSecondChance()
{
    FILE *fp1;
    int frames[page_frame_size];
    int frames_index[page_frame_size];
    int page_fault = 0;

    fp1 = fopen("test.txt","a+");
    printf("=====================ENHANCED-SECOND-CHANCE=====================\n");
    printf("time\t\t\t\t\t\t\tpage fault\n\n");

    fprintf(fp1,"=====================ENHANCED-SECOND-CHANCE=====================\n");
    fprintf(fp1,"time\t\t\t\t\t\t\t\t\t\t\t\t\t\tpage fault\n\n");
    fclose(fp1);

    for (int i = 0; i <page_frame_size; i++)
    {
        frames[i] = -1; // frame table을 -1로 초기화 해준다.
        frames_index[i] = -1;
    }

    for (int i = 0; i < NO_OF_PAGES; i++)
    {
        check = false;
        replace = false;

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] == p->ReferenceString[i]) // hit하는 경우
            {
                frames_index[j] = i;
                p->r_bit[frames_index[j]] = 1; // reference_bit는 1로 초기화
                check = true;
                break;
            }

            if (frames[j] < 0) // frame table에서 -1인 경우 (비어 있는 경우)
            {
                page_fault++;
                frames[j] = p->ReferenceString[i]; // referencestring값을 frames 값에 대입
                frames_index[j] = i;
                p->r_bit[frames_index[j]] = 1; // referece bit를 frames table 안에 다가 넣어준다.
                check = true;
                replace = true;
                break;
            }
        }

        if (!check) // frame table이 full이고 hit하지 않는 경우
        {
             bool check2 = false;

            for (int x = 0; x < page_frame_size; x++)
            {
                if (p->r_bit[frames_index[x]] == 0) // reference bit가 0인경우 break
                {
                    check2 = true;
                    break; 
                }
            }
            if (!check2) // reference bit가 1인 경우에는 frame table에 있는 r_bit는 0으로 변경
            {
                for (int a = 0; a < page_frame_size; a++)
                {
                    p->r_bit[frames_index[a]] = 0;
                }
            }
            /* ------ reference_bit와 modify bit를 통해 victim정하기 ------ */
            bool check3 = false;
            bool check4 = false;
            bool check5 = false;
            for (int t = 0; t < page_frame_size; t++)
            {
                if(p->r_bit[frames_index[t]] == 0 && p->w_bit[frames_index[t]]==0) // 우선순위(1) : r_bit = 0 / w_bit = 0 가장 먼저 교체
                {
                    page_fault++;
                    frames[t] = p->ReferenceString[i];
                    frames_index[t] = i;
                    p->r_bit[frames_index[t]] = 1;
                    check3 = true;
                    replace = true;
                    break;
                }
                          
            }
            if (!check3) // 우선순위(1) : r_bit = 0 / w_bit = 1 (0,0) 이 아니고 다음 순서로 교체
                {
                    for (int t = 0; t < page_frame_size; t++)
                    {
                        if (p->r_bit[frames_index[t]] == 0 && p->w_bit[frames_index[t]]==1)
                        {
                            page_fault++;
                            frames[t] = p->ReferenceString[i];
                            frames_index[t] = i;
                            p->r_bit[frames_index[t]] = 1;
                            check4 = true;
                            replace = true;
                            break;
                        }
                    }
                }
                if(!check3&&!check4) // 우선순위(1) : r_bit = 1 / w_bit = 0 (0,0) / (0,1) 도 아닌 다음 순서로 교체
                {
                   
                    for (int t = 0; t < page_frame_size; t++)
                    {
                        if (p->r_bit[frames_index[t]] == 1 && p->w_bit[frames_index[t]] == 0)
                        {
                            page_fault++;
                            frames[t] = p->ReferenceString[i];
                            frames_index[t] = i;
                            p->r_bit[frames_index[t]] = 1;
                            replace = true;
                            break;
                        }
                    }
                }
                if(!check3&&!check4&&!check5) // 우선순위(1) : r_bit = 1 / w_bit = 1 교체가 일어나지 않는다.
                {
                    for (int t = 0; t < page_frame_size; t++)
                    {
                        if (p->r_bit[frames_index[t]] == 1 && p->w_bit[frames_index[t]] == 1)
                        {
                            page_fault++;
                            frames[t] = p->ReferenceString[i];
                            frames_index[t] = i;
                            p->r_bit[frames_index[t]] = 1;
                            check5 = true;
                            replace = true;
                            break;
                        }
                    }
                } /* index 순을 서로 비교하여 r_bit와 w_bit가 동일하면 가장 앞에 있는 index가 vixtim으로 선정*/
        }

        /* ------ 결과 값을 출력하기 위한 구문 ------ */
        fp1 = fopen("test.txt", "a+");
        printf("%-5d", i + 1);
        fprintf(fp1,"%-10d", i + 1);

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] < 0)
                printf("%-9c", ' ');
            else
                printf("%4d", frames[j]);
            
            if(frames[j] < 0)
                printf("%-9c", ' ');
            else
                printf(" (%d%d)%9c", p->r_bit[frames_index[j]],p->w_bit[frames_index[j]],' ');

            if (frames[j] < 0)
                fprintf(fp1,"%-9c", ' ');
            else
                fprintf(fp1,"%4d", frames[j]);

            if (frames[j] < 0)
                fprintf(fp1,"%-9c", ' ');
            else
                fprintf(fp1," (%d%d)%9c", p->r_bit[frames_index[j]], p->w_bit[frames_index[j]], ' ');
        }
        if (replace)
            printf("F\n");
        else
            printf("\n");

        if (replace)
            fprintf(fp1,"F\n");
        else
            fprintf(fp1,"\n");
        fclose(fp1);
     }
     fp1 = fopen("test.txt","a+");

     printf("\n\nTotal Page Faults = %d\n", page_fault);
     printf("\n");

     fprintf(fp1,"\n\nTotal Page Faults = %d\n", page_fault);
     fprintf(fp1,"\n");

     fclose(fp1);

    compare_Optimal();
    }

/* ------ split : argc / argv function ------ */
int split(char *string, char *seperator, char *argv[]){ // split -> 띄어쓰기를 기준으로 값을 나누어 주는 함수 
    int argc=0;
    char *ptr=NULL;

    ptr=strtok(string,seperator); // strtok를 기준으로 서로 분리 
    while(ptr!=NULL){
        argv[argc++]=ptr;
        ptr=strtok(NULL," ");
    }

    return argc;
}

/* ------ For use LRU ------ */
int findLRU(int time[], int n){ // 가장 오랫동안 참조안한 값을 찾기 위한 LRU 함수 
    int i;
    int minimum = time[0];
    int pos = 0;
    
    for (i = 1; i < n; ++i)
    {
        if (time[i] < minimum) // 참조한 시간과 최소 시간을 서로 비교하여 더 작으면 해당 값을 교체하기 위한 time 선택
        {
            minimum = time[i]; 
            pos = i;
        }
    }
    return pos;
    }

/* ------ For use LFU ------ */
void print(int frameno,int frame[]){

    FILE *fp1;

    /* ------ 결과 값을 출력하기 위한 구문 ------ */
    fp1 = fopen("test.txt","a+");
    for (int j = 0; j < frameno; j++)
    {
        if (frame[j] < 0)
            printf("%10c",' ');
        else
            printf("%-10d", frame[j]);
        
        if (frame[j] < 0)
            fprintf(fp1,"%10c",' ');
        else
            fprintf(fp1,"%-10d", frame[j]);
    }
    fclose(fp1);
}

/* ------ For use compare algorithm (optimal) ------ */
/* ------ 각 알고리즘을 optimal 알고리즘과 비교 하기 위한 함수  ------ */
void compare_Optimal()
 {
     FILE *fp1;
     int frames[page_frame_size], temp[page_frame_size];
     int flag1, flag2, flag3;
     int i, j, k;
     int pos, max;
     int faults = 0;
    
     for (i = 0; i < page_frame_size; ++i)
     {
         frames[i] = -1;
     }

     for (i = 0; i < NO_OF_PAGES; ++i)
     {
         flag1 = flag2 = 0;
         replace = false;

         for (j = 0; j < page_frame_size; ++j)
         {
             if (frames[j] == p->ReferenceString[i])
             {
                 flag1 = flag2 = 1;
                 break;
             }
         }

         if (flag1 == 0)
         {
             for (j = 0; j < page_frame_size; ++j)
             {
                 if (frames[j] == -1)
                 {
                     faults++;
                     replace = true;
                     frames[j] = p->ReferenceString[i];
                     flag2 = 1;
                     break;
                 }
             }
         }

         if (flag2 == 0)
         {
             flag3 = 0;

             for (j = 0; j < page_frame_size; ++j)
             {
                 temp[j] = -1;

                 for (k = i + 1; k < NO_OF_PAGES; ++k)
                 {
                     if (frames[j] == p->ReferenceString[k])
                     {
                         temp[j] = k;
                         break;
                     }
                 }
             }

             for (j = 0; j < page_frame_size; ++j)
             {
                 if (temp[j] == -1)
                 {
                     pos = j;
                     flag3 = 1;
                     break;
                 }
             }

             if (flag3 == 0)
             {
                 max = temp[0];
                 pos = 0;

                 for (j = 1; j < page_frame_size; ++j)
                 {
                     if (temp[j] > max)
                     {
                         max = temp[j];
                         pos = j;
                     }
                 }
             }
             frames[pos] = p->ReferenceString[i];
             faults++;
             replace = true;
         }
 }
    fp1 = fopen("test.txt","a+");

     printf("Compare Optimal Page Faults = %d\n", faults);
     printf("\n");

     fprintf(fp1,"Compare Optimal Page Faults = %d\n", faults);
     fprintf(fp1,"\n");

     fclose(fp1);
    }
