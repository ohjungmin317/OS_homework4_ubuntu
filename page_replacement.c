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
	memset(selected,0,sizeof(selected)); // selected 0 �ʱ�ȭ	
	printf("A.Choose the Page Replacement Algorithm simulation (max:3) :\n");
    printf("(1) Optimal (2) FIFO (3) LIFO (4) LRU (5) LFU (6) SC (7) ESC (8) All\n");
	printf("write only number not use ()\n");

    fgets(input_algorithm,sizeof(input_algorithm),stdin); // get number selected algorithm 
        input_algorithm[strlen(input_algorithm)-1] = '\0';
        argc_1 = split(input_algorithm," ",argv_1); // split() �Լ��� ���� �������� argc_1�� �ش� ���ڸ� ���� 
    
    for(int i=0; i<argc_1; i++){ // 1 ������ ���ڰų� 8�� �̻��� ������ ��쿡�� ���� ó�� 
        if((argc_1>1 && !strcmp(argv_1[i],"8")) || (atoi(argv_1[i])<1 || atoi(argv_1[i])>8))
        exception = 1;
    }
    if(argc_1>3 || argc_1==0 || exception){ // ����ó���� ���� ���� �޼��� 
		printf("Input error\nUsag : Choose the Page Replacement Algorithm simulation (max:3)\nYou can use only <OPT, FIFO, LIFO, LRU, LFU, SC, ESC, ALL>\n");
        printf("\n");
		continue;
	}

    if(!strcmp(argv_1[0], "8")){ // 8���� �����ϰ� �Ǹ� ��� bit�� 1�� �Ǹ鼭 �ش� �˰��� ��� ����� �ϰ� �ȴ�.
        for(int i = 0; i<7; i++) selected[i] = 1;
        break;
    }
    for(int i = 0; i<argc_1; i++){ // �˰��� ������ 1 - 8�� ���� �ޱ� ����
        selected[atoi(argv_1[i])-1] = 1;
    }
    break;
    }

while(1){ // frame number 
    printf("B.Put the frame number.(3~10)\n");

    fgets(input_algorithm,sizeof(input_algorithm),stdin); // frame number �޴� ���� fgets �̿� 
        input_algorithm[strlen(input_algorithm)-1]='\0';
        argc_2 = split(input_algorithm," ",argv_2);
		
        if(argc_2!=1){ // input error message 
            printf("Input error\nUsag: frame number(3~10)\n");
            printf("\n");
            continue;
        }
        page_frame_size = atoi(argv_2[0]);
        if(page_frame_size <3 || page_frame_size > 10){ // frame ������ 3 ���� 10 �̻��� ��� error �޼��� ��� 
			printf("Input error\nUsag: Put the frame number.(3~10)\n");
            printf("\n");
            continue;
        }
        break;
}

 while(1){ // for select input data way 
        printf("C.Choose the method of data input.(1,2)\n");

        fgets(input_algorithm,sizeof(input_algorithm),stdin); // ������ �Է� ����� �ޱ� ���� fgets
        input_algorithm[strlen(input_algorithm) -1 ]='\0';
        argc_3=split(input_algorithm," ",argv_3);

        if(argc_3!=1||strcmp(argv_3[0],"1")&&strcmp(argv_3[0],"2")){ // 1 �̳� 2�� �ƴ� �ٸ� ���ڸ� �Է��Ͽ����� ������ִ� error �޼��� 
            printf("Input error\nUsag: Choose the method of data input.(1,2)\n");
            printf("\n");
            continue;
        }
        input_for_data=atoi(argv_3[0]);
        printf("C-1.write the number of page stream: ");
        scanf("%d",&NO_OF_PAGES);
        break;
    }

    if (input_for_data == 1){ // ���࿡ input_data�� 1�� �Է½ÿ��� ���� ���� ���� 

        fp1 = fopen("referencestream.txt", "w");
        for (int i = 0; i < NO_OF_PAGES; i++)
        {
            p->ReferenceString[i] = rand() % 30 + 1; // 1 ~ 30 ���� ���� ����
            fprintf(fp1," %d", p->ReferenceString[i]);
        }
        fclose(fp1);

        fp1 = fopen("bitstream.txt", "w");
        for (int i = 0; i < NO_OF_PAGES; i++)
        {
            p->r_bit[i] = rand() % 2; // r_bit 0 �Ǵ� 1 ���� ����
            p->w_bit[i] = rand() % 2; // w_bit 0 �Ǵ� 1 ���� ����
            fprintf(fp1,"%d %d ", p->r_bit[i],p->w_bit[i]);
        }
        fclose(fp1);

    }

    else
    { // ���Ϸ� ���� �Է� �޾Ƽ� ��� 

        /*page stream�� r_bit w_bit ���� �Է� �ޱ�*/
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

        int count = split(buffer, " ", argv_4); // split �Լ��� ��� (���� �������� ���� ����)
        int count1=split(buffer1," ",argv_5); // split �Լ��� ��� (���� �������� ���� ����)
        
        for (int i = 0; i < count; i++)
        {
            p->ReferenceString[i] = atoi(argv_4[i]);
            //printf("%d ", p->ReferenceString[i]);
        }

        for (int i = 0, j = 0; i < count1; i = i + 2, j++) // ��Ʈ ������ Ȧ����°�� reference bit 
        {
            p->r_bit[j] = atoi(argv_5[i]);
            //printf("%d ", p->r_bit[j]);
        }
    
        for (int i = 1, j = 0; i < count1; i = i + 2, j++) // ��Ʈ ������ ¦���� °�� dirty bit 
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

    for (int i = 0; i < NO_OF_PAGES; i++){ // ��� ���� reference stream �� ��� 
        printf("%d ", p->ReferenceString[i]);
    }

    for (int i = 0; i < NO_OF_PAGES; i++)
        fprintf(fp1, "%d ", p->ReferenceString[i]);

    printf("\n\n");
    fprintf(fp1, "\n\n");
    fclose(fp1);

    selected_replace_algorithm(argv_1, selected); // selected algorithm �Լ� ���๮   

    printf("D.END\n");
    exit(0);
    fclose(fp2); //for close file fp2
    fclose(fp3); // for close file fp3
    free(p); // p malloc free
}

/* ------ �ɼǿ� ���� �˰��� ��� ���� ------ */
void selected_replace_algorithm(char *argv_1[], int selected[]){ // 0�� 1�� ������ 0�� ���� off 1�϶��� on���� �ؼ� ������ �ϰ� �Ǹ� 1�� ������ �ǰ� 1�̵Ǹ� �ش� �˰��� �۵�
    if (selected[0] == 1) // 1���� ������ �ش� �˰����� 1�� �ٲ� ������ �ȴ�.
    {
        Optimal();
    }

    if (selected[1] == 1) // 2���� ������ �ش� �˰����� 1�� �ٲ� ������ �ȴ�.
    {
        FIFO();
    }

    if (selected[2] == 1) // 3���� ������ �ش� �˰����� 1�� �ٲ� ������ �ȴ�.
    {
        LIFO();
    }

    if (selected[3] == 1) // 4���� ������ �ش� �˰����� 1�� �ٲ� ������ �ȴ�.
    {
        LRU();
    }

    if (selected[4] == 1) // 5���� ������ �ش� �˰����� 1�� �ٲ� ������ �ȴ�.
    {
        LFU();
    }
    
    if (selected[5] == 1) // 6���� ������ �ش� �˰����� 1�� �ٲ� ������ �ȴ�.
    {
        SecondChance();
    }

    if (selected[6] == 1) // 7���� ������ �ش� �˰����� 1�� �ٲ� ������ �ȴ�.
    {
        EnhancedSecondChance();
    }

 }

/* ------ Optimal ------ */
/* ------ Optimal : ���� �������� ������� ���� �������� ��ü�ϴ� �˰��� ------ */
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
     
     for (i = 0; i < page_frame_size; ++i) // page_frame_size ũ�� ��ŭ frame table�� ��� �ִ� ���� -1�� ���� 
     {
         frames[i] = -1;
     }

     for (i = 0; i < NO_OF_PAGES; ++i) // page_size�� ũ�� ��ŭ Ž�� 
     {
         flag1 = flag2 = 0; // flag 1 , flag 2 0�� 1�� �������� �ش� ���̺��� full���� �ƴ��� Ȯ�� �ϱ� ���� �뵵 
         replace = false; // page fault�� Ȯ���ϱ� ���� �뵵

         for (j = 0; j < page_frame_size; ++j)
         {
             if (frames[j] == p->ReferenceString[i]) // frames number�� referencestring�� ��ġ�Ͽ� hit �ϴ� ��� 
             {
                 flag1 = flag2 = 1; // flag1 = 1 -> hit �ϴ� ��� | flag2 = 1 -> ����ִٴ� 1
                 break;
             }
         }

         if (flag1 == 0) // flag1=0 �̸�  hit ���� �ʴ� ��� 
         {
             for (j = 0; j < page_frame_size; ++j)
             {
                 if (frames[j] == -1) // frame table���� -1 ���� ã�� �Ǹ� 
                 {
                     faults++; // page fault �� ���� 
                     replace = true;
                     frames[j] = p->ReferenceString[i]; // reference string ���� frame table�� �־��ش�.
                     flag2 = 1;
                     break;
                 }
             }
         }

         if (flag2 == 0) // frame table�� full�� ��� 
         {
             flag3 = 0;

             for (j = 0; j < page_frame_size; ++j)
             {
                 temp[j] = -1;

                 for (k = i + 1; k < NO_OF_PAGES; ++k)
                 {
                     if (frames[j] == p->ReferenceString[k]) // full �̰� hit �ϴ� ��� 
                     {
                         temp[j] = k;
                         break;
                     }
                 }
             }

             for (j = 0; j < page_frame_size; ++j)
             {
                 if (temp[j] == -1) // ��� �ִ� ��� 
                 {
                     pos = j;
                     flag3 = 1;
                     break;
                 }
             }

             if (flag3 == 0) // full�� ��� victim�� �����Ͽ� ��ü�� �ؾ��ϴ� ��� 
             {
                 max = temp[0];
                 pos = 0;

                 for (j = 1; j < page_frame_size; ++j)
                 {
                     if (temp[j] > max) // �������� ������� �ʴ� ���� Ž���Ͽ� ���� �� 
                     {
                         max = temp[j];
                         pos = j;
                     }
                 }
             }
             frames[pos] = p->ReferenceString[i]; // �ش� ���� ã�� �Ǹ� frame table�� reference ���� ���� 
             faults++; // reference string�� ��ü�� �Ǿ��� ������ page fault �� ���� 
             replace = true;
         }

         /* ------ ��� ���� ����ϱ� ���� ���� ------ */
        fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1); // times == page_size
        fprintf(fp1,"%-15d", i + 1); 

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++) // frames ���̺��� ��� ���ϴ��� ������ �����ֱ� ���� ����
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
/* ------ FIFO: ���� ���� ���°��� ���� ���� ������ �� ------ */
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
        frames[i] = -1; // frmae ���̺� -1�� �ʱ�ȭ 
    }

    for (i = 0; i < NO_OF_PAGES; i++)
    {
        flag = 0;
        replace = false;

        for (j = 0; j < page_frame_size; j++)
        {
            if (p->ReferenceString[i] == frames[j]) // frame table�� �ִ� ���� reference sstring�� ���� ��� ==  hit
            {
                flag = 1; // ��� �ִ� ��� 1 
                faults--; 
                
            } 
        }
        faults++; // �ƴ� ��쿡�� hit-miss -> fault�� ���� 
        
        if ((faults <= page_frame_size) && (flag == 0)) // frame table�� ���� ��� 
        {
            frames[i] = p->ReferenceString[i]; // 
            replace = true;
        }
        else if (flag == 0) // ���� ��� victim�� ���ؾ� �� �� 
        {
            frames[(faults - 1) % page_frame_size] = p->ReferenceString[i]; // ���� ���� ���� ���� ������ ���� �� 
            replace = true;
        }

        /* ------ ��� ���� ����ϱ� ���� ���� ------ */
        fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1);
        fprintf(fp1,"%-15d", i + 1);

        fclose(fp1);

        fp1 = fopen("test.txt", "a+");

        for (int j = 0; j < page_frame_size; j++) // frames ���̺��� ��� ���ϴ��� ���� �����ֱ� ���� ���� 
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
/* ------ LIFO : ���� �������� ���� ���� ���� ó���� ���������� �˰��� ------ */
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
        frames[i] = -1; // frames table -1�� �ʱ�ȭ 
    }

    for (i = 0; i < NO_OF_PAGES; i++)
    {
        flag = 0; // FLAG
        replace = false;
        for (j = 0; j < page_frame_size; j++)
        {
            if (p->ReferenceString[i] == frames[j]) // hit �ϴ� ��� 
            {
                flag++;
            }
        }
        if (flag) // frames table�� ���� ���ϴ� ���� �����ֱ� ���� if 
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
            if (frames[n] == -1) // hit ���� �ʰ� frame table ��ȸ�ϴ� �� -1�� ������ ��� 
            {
                frames[n] = p->ReferenceString[i]; // frames table�� referencestring ���� �־��ش�.
                flag++;
                faults++; // hit-miss�̱⿡ fault �� ���� 
                replace = true;
                break;
            }
        }
        if (flag) // frames table�� ���� ���ϴ� ���� �����ֱ� ���� if 
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

        frames[page_frame_size - 1] = p->ReferenceString[i]; // ���� ��� ��찡 �ƴ� ��쿡�� ���� �������� �ִ� ���� ��� ��ü 
        faults++; // hit-miss �̱⿡ fault�� ���� 
        replace = true;

        /* ------ ��� ���� ����ϱ� ���� ���� ------ */
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
/* ------ LRU : ���� �������� ������� ���� �������� ��ü�ϴ� �˰��� ------ */
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
        frames[i] = -1; // frame table -1�� �ʱ�ȭ 
    }

    for (i = 0; i < NO_OF_PAGES; ++i) // page_size ��ŭ ��ȸ
    {
        flag1 = flag2 = 0;
        replace = false;

        for (j = 0; j < page_frame_size; ++j)
        {
            if (frames[j] == p->ReferenceString[i]) // hit �ϴ� ��� 
            {
                counter++; // �ش� ���� Ƚ�� �ϳ� ����
                time[j] = counter; // ���߿� ���ϱ� ���� time �迭���ٰ� �־��ش�.
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) // frame table�� ��� �ִ� ��� 
        {
            for (j = 0; j < page_frame_size; ++j)
            {
                if (frames[j] == -1) // frame table Ž���ϸ鼭 -1 ���� ã�� �Ǹ� 
                {
                    
                    frames[j] = p->ReferenceString[i]; // referencestring�� ���� frame table�� �־��ش�.
                    counter++; // �ش� reference ���� �ϳ� ����
                    faults++; // hit-miss �̱� ������ fault�� ����
                    replace = true;
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) // frames table�� full�� ��� 
        {
            pos = findLRU(time, page_frame_size);
            counter++;
            faults++;
            replace = true;
            frames[pos] = p->ReferenceString[i]; // ���� �������� ������� �ʴ� �˰����� ã�Ƽ� reference string�� �ִ� ���� ��ü
            time[pos] = counter; // ������ ���� ���� counter�� ���� 
        }

       /* ------ ��� ���� ����ϱ� ���� ���� ------ */ 
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
/* ------ LFU : ����Ƚ���� ���� ���� �������� ��ü�ϴ� �˰��� ------ */
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
        frames[i] = -1; // frame table�� ���� ���� -1�� �ʱ�ȭ
    }
    for (i = 0; i < NO_OF_PAGES; i++) // page_size��ŭ ��ȸ 
    {
        replace = false;
        flag = 0;

        fp1 = fopen("test.txt","a+");
        printf("%-15d", i + 1);
        fprintf(fp1,"%-15d", i + 1);

        fclose(fp1);

        for (j = 0; j < page_frame_size; j++)
        {
            if (p->ReferenceString[i] == frames[j]) // hit �ϴ� ���
            {
                flag = 1;
                freq_time[j]++; // �ش� ���� ���� Ƚ�� ����
                print(page_frame_size, frames);
                break;
            }
        }
        if (flag == 0 && faults < page_frame_size) // hit���� �ʰ� ��� �ִ� �ܿ�
        {
            frames[move_rp] = p->ReferenceString[i]; // ��� �ִ� ���� reference string �� ���� 
            freq_time[move_rp] += 1; // �ش� ���� ȸ�� ���� 
            move_rp = (move_rp + 1) % page_frame_size; // move_rp = 0���� ����
            faults++; // hit-miss�̱� ������ fault �� ����
            replace = true;
            print(page_frame_size, frames);
        }
        else if (flag == 0) // frames�� full�� ��� 
        {
            replace_index = 0;
            leastcount = freq_time[0]; // ���� Ƚ�� �� ���� 
            for (j = 1; j < page_frame_size; j++)
            {
                if (freq_time[j] < leastcount) // ����Ƚ���� ���� ���� ��
                {
                    replace_index = j; // �ش� ���� ���� 
                    leastcount = freq_time[j]; 
                }
            }

            frames[replace_index] = p->ReferenceString[i]; // �ش� ���� ��ü -> index�� �������� ���� ���� index �� ��ü
            freq_time[replace_index] = 1; // ���� �����Ͽ��� ������ ����Ƚ�� 1
            faults++; // hit - miss �̱⿡ fault �� ����  
            replace = true;
            print(page_frame_size, frames);
        }
        
        /* ------ ��� ���� ����ϱ� ���� ���� ------ */
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
/* ------ SecondChance : r_bit�� �̿��Ͽ� ��ü�ϱ� ���� 1�� ��쿡�� ��ȸ�� �� �� �� �ش�. -> circual queue ��� (moduler) ------ */
void SecondChance() // ��������Ʈ�� �����ͺ��� ������ Ȯ���� �غ���.
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
        frames[i] = -1; // frame table�� -1�� �ʱ�ȭ 
    }

    for (int i = 0; i < NO_OF_PAGES; i++)
    {
        check = false;
        replace = false;

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] == p->ReferenceString[i]) // hit�ϴ� ���
            {
                reference_bit[j] = 1; // �ش� ���� �����ϱ� ������ reference bit�� 1�� �ش�.
                check = true;
                break;
            }

            if (frames[j] < 0) // hit ���� �ʰ� -1�� ���� ã�� ���
            { 
                frames[j] = p->ReferenceString[i]; // �ش� ���� reference string���� ��ü 
                reference_bit[j] = 0; // reference bit = 0���� �Ҵ�
                page_fault++; // fault �� ���� 
                check = true; // ����ִ°��� true -> false �� ���ִ� ��� 
                replace = true;
                break;
            }
        }

        if (!check)
        {
            int j=victim; // j�� victim���� ���� -> j�� victim ���� �ȴ�.
            for (int t = 0; t < page_frame_size; t++)
            {
                if(j==page_frame_size)
                    j=0;
                if (reference_bit[j] == 0) // reference bit�� 0�� ��쿡�� break
                {
                    break;
                }
                    reference_bit[j] = 0;
                j++;
            }
            if(j==page_frame_size){ // reference bit�� ���� ��쿡�� circual queue�� ��ȸ�Ͽ� �ش� ������ �������� ���� �������� ���� ��������.
                j=0;
            }
            frames[j] = p->ReferenceString[i]; // reference bit�� 0�� ��쿡�� �ش� ���� ����
            page_fault++;
            replace = true;
            reference_bit[j]=0;
            victim = (j + 1)%page_frame_size;
            
        }

        if (victim == page_frame_size)
            victim = 0;

        /* ------ ��� ���� ����ϱ� ���� ���� ------ */
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
/* ------ ESC : reference_bit�� modify_bit�� �̿��Ͽ� (0,0) / (0,1) / (1,0) / (1,1) ������� Ȯ���Ͽ� victim�� ���ؼ� ��������. ------ */
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
        frames[i] = -1; // frame table�� -1�� �ʱ�ȭ ���ش�.
        frames_index[i] = -1;
    }

    for (int i = 0; i < NO_OF_PAGES; i++)
    {
        check = false;
        replace = false;

        for (int j = 0; j < page_frame_size; j++)
        {
            if (frames[j] == p->ReferenceString[i]) // hit�ϴ� ���
            {
                frames_index[j] = i;
                p->r_bit[frames_index[j]] = 1; // reference_bit�� 1�� �ʱ�ȭ
                check = true;
                break;
            }

            if (frames[j] < 0) // frame table���� -1�� ��� (��� �ִ� ���)
            {
                page_fault++;
                frames[j] = p->ReferenceString[i]; // referencestring���� frames ���� ����
                frames_index[j] = i;
                p->r_bit[frames_index[j]] = 1; // referece bit�� frames table �ȿ� �ٰ� �־��ش�.
                check = true;
                replace = true;
                break;
            }
        }

        if (!check) // frame table�� full�̰� hit���� �ʴ� ���
        {
             bool check2 = false;

            for (int x = 0; x < page_frame_size; x++)
            {
                if (p->r_bit[frames_index[x]] == 0) // reference bit�� 0�ΰ�� break
                {
                    check2 = true;
                    break; 
                }
            }
            if (!check2) // reference bit�� 1�� ��쿡�� frame table�� �ִ� r_bit�� 0���� ����
            {
                for (int a = 0; a < page_frame_size; a++)
                {
                    p->r_bit[frames_index[a]] = 0;
                }
            }
            /* ------ reference_bit�� modify bit�� ���� victim���ϱ� ------ */
            bool check3 = false;
            bool check4 = false;
            bool check5 = false;
            for (int t = 0; t < page_frame_size; t++)
            {
                if(p->r_bit[frames_index[t]] == 0 && p->w_bit[frames_index[t]]==0) // �켱����(1) : r_bit = 0 / w_bit = 0 ���� ���� ��ü
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
            if (!check3) // �켱����(1) : r_bit = 0 / w_bit = 1 (0,0) �� �ƴϰ� ���� ������ ��ü
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
                if(!check3&&!check4) // �켱����(1) : r_bit = 1 / w_bit = 0 (0,0) / (0,1) �� �ƴ� ���� ������ ��ü
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
                if(!check3&&!check4&&!check5) // �켱����(1) : r_bit = 1 / w_bit = 1 ��ü�� �Ͼ�� �ʴ´�.
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
                } /* index ���� ���� ���Ͽ� r_bit�� w_bit�� �����ϸ� ���� �տ� �ִ� index�� vixtim���� ����*/
        }

        /* ------ ��� ���� ����ϱ� ���� ���� ------ */
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
int split(char *string, char *seperator, char *argv[]){ // split -> ���⸦ �������� ���� ������ �ִ� �Լ� 
    int argc=0;
    char *ptr=NULL;

    ptr=strtok(string,seperator); // strtok�� �������� ���� �и� 
    while(ptr!=NULL){
        argv[argc++]=ptr;
        ptr=strtok(NULL," ");
    }

    return argc;
}

/* ------ For use LRU ------ */
int findLRU(int time[], int n){ // ���� �������� �������� ���� ã�� ���� LRU �Լ� 
    int i;
    int minimum = time[0];
    int pos = 0;
    
    for (i = 1; i < n; ++i)
    {
        if (time[i] < minimum) // ������ �ð��� �ּ� �ð��� ���� ���Ͽ� �� ������ �ش� ���� ��ü�ϱ� ���� time ����
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

    /* ------ ��� ���� ����ϱ� ���� ���� ------ */
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
/* ------ �� �˰����� optimal �˰���� �� �ϱ� ���� �Լ�  ------ */
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
