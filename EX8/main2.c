#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"
#define MAX_LOTTO_NUM 7
#define MAX_LOTTO_NUMSET 5

int num_in_numset(int num, int numset[], int Len) {
    for (int i = 0; i < Len; i++) {
        if (num == numset[i]) {
            return 1;
        }
    }
    return 0;
}

void printf_lotto_row(FILE* tmpfp, int n) {
    int numset[MAX_LOTTO_NUM];
    for (int i = 0; i < MAX_LOTTO_NUM; i++)
        numset[i] = 0;

    fprintf(tmpfp, "[%d]: ", n);

    
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ) {
        int num = (rand() % 69) + 1;
        if (num_in_numset(num, numset, MAX_LOTTO_NUM - 1)) {
            continue;
        } else {
            numset[i] = num;
            i++;
        }
    }

    
    int num = (rand() % 10) + 1;
    numset[MAX_LOTTO_NUM - 1] = num;

    
    for (int i = 0; i < MAX_LOTTO_NUM - 1; i++) {
        for (int j = 0; j < i; j++) {
            if (numset[j] > numset[i]) {
                int temp = numset[j];
                numset[j] = numset[i];
                numset[i] = temp;
            }
        }
    }

   
    for (int i = 0; i < MAX_LOTTO_NUM; i++) {
        fprintf(tmpfp, "%02d ", numset[i]);
    }
    fprintf(tmpfp, "\n");
}

void printf_lottofile(int num_set, int counter, char lotto_file[]) {
    time_t curtime;
    time(&curtime);
    srand(time(NULL));

    FILE* tmpfp = fopen(lotto_file, "w+");
    if (tmpfp == NULL) {
        printf("檔案開啟失敗！\n");
        exit(1);
    }

    fprintf(tmpfp, "========= lotto649 =========\n");
    fprintf(tmpfp, "========+ No.%05d +========\n", counter);
    fprintf(tmpfp, "= %.24s =\n", ctime(&curtime));

    for (int i = 0; i < MAX_LOTTO_NUMSET; i++) {
        if (i < num_set) {
            printf_lotto_row(tmpfp, i + 1);
        } else {
            fprintf(tmpfp, "[%d]: -- -- -- -- -- -- --\n", i + 1);
        }
    }

    fprintf(tmpfp, "========= csie@CGU =========\n");
    fclose(tmpfp);
}

void do_lotto_main(int counter) {
    char lotto_file[32];
    int num_set = 0;
    snprintf(lotto_file, 32, "lotto[%05d].txt", counter);

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩 : ");
    scanf("%d", &num_set);

    printf_lottofile(num_set, counter, lotto_file);
    printf("已將您購買的 %d 組樂透組合輸出至 %s\n", num_set, lotto_file);
}

void init_file() {
    int write_array[1] = {0};

    FILE* fp = fopen(COUNTER_FILE, "rb");
    if (fp == NULL) {
        FILE* tmpfp = fopen(COUNTER_FILE, "wb+");
        fwrite(write_array, sizeof(int), 1, tmpfp);
        fclose(tmpfp);
    } else {
        fclose(fp);
    }
}

int get_counter() {
    init_file();
    int counter = 0;

    FILE* fp = fopen(COUNTER_FILE, "rb+");
    fread(&counter, sizeof(int), 1, fp);
    counter++;
    fseek(fp, 0, SEEK_SET);
    fwrite(&counter, sizeof(int), 1, fp);
    fclose(fp);

    return counter;
}

int main() {
    int counter = get_counter();
    do_lotto_main(counter);
    return 0;
}
