#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_TICKETS 5
#define NUM_PER_TICKET 7

int contains_all(int ticket[], int tlen, int nums[], int n) {
    int found;
    for (int i = 0; i < n; i++) {
        found = 0;
        for (int j = 0; j < tlen; j++) {
            if (ticket[j] == nums[i]) { found = 1; break; }
        }
        if (!found) return 0;
    }
    return 1;
}

int main(void) {
    FILE *fp = fopen("lotto.txt", "r");
    if (!fp) {
        perror("無法開啟 lotto.txt");
        return 1;
    }

    int nums[3];
    printf("請輸入中獎號碼三個（以空白分隔，例如 5 7 9）：");
    if (scanf("%d %d %d", &nums[0], &nums[1], &nums[2]) != 3) {
        printf("輸入錯誤\n");
        fclose(fp);
        return 1;
    }

    char line[MAX_LINE];
    int ticket_idx = 0;
    int ticket_numbers[MAX_TICKETS][NUM_PER_TICKET];
    int ticket_len[MAX_TICKETS];
    int winning[MAX_TICKETS];
    for (int i = 0; i < MAX_TICKETS; i++) { ticket_len[i] = 0; winning[i] = 0; }

    while (fgets(line, sizeof(line), fp) != NULL) {

        char *p = line;

        while (*p == ' ' || *p == '\t') p++;

        if (*p == '[') {

            char *colon = strchr(p, ':');
            if (!colon) continue;

            char *q = colon + 1;

      
            if (strstr(q, "__") != NULL) {
             
                ticket_len[ticket_idx] = 0;
            } else {
              
                int val;
                int cnt = 0;
              
              
                char buf[MAX_LINE];
                strncpy(buf, q, sizeof(buf)-1);
                buf[sizeof(buf)-1] = '\0';

                char *tok = strtok(buf, " \t\r\n");
                while (tok != NULL && cnt < NUM_PER_TICKET) {
                    
                    if (sscanf(tok, "%d", &val) == 1) {
                        ticket_numbers[ticket_idx][cnt++] = val;
                    }
                    tok = strtok(NULL, " \t\r\n");
                }
                ticket_len[ticket_idx] = cnt;
            }
            ticket_idx++;
            if (ticket_idx >= MAX_TICKETS) break;
        }
    }

    fclose(fp);

  
    int any_win = 0;
    for (int i = 0; i < ticket_idx; i++) {
        if (ticket_len[i] == 0) {
            printf("[%d]: -- -- -- -- -- -- --\n", i+1);
            continue;
        }
        printf("[%d]:", i+1);
        for (int j = 0; j < ticket_len[i]; j++) {
            printf(" %02d", ticket_numbers[i][j]);
        }
        printf("\n");

        if (contains_all(ticket_numbers[i], ticket_len[i], nums, 3)) {
            printf("  -> 票 [%d] 包含所有輸入號碼，中獎！\n", i+1);
            winning[i] = 1;
            any_win = 1;
        }
    }

    if (!any_win) {
        printf("未中獎（沒有任何票同時包含你輸入的三個號碼）。\n");
    } else {
        printf("中獎票：");
        for (int i = 0; i < ticket_idx; i++) if (winning[i]) printf("%d ", i+1);
        printf("\n");
    }

    return 0;
}
