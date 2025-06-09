#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CANDIDATES 6
#define BUFFER 128

char *member_info[NUM_CANDIDATES][11]; // 11개 항목: 이름 ~ 소개
char group_name[BUFFER];

int calculate_age(const char *birthdate_str) {
    int birth_year, birth_month, birth_day;
    sscanf(birthdate_str, "%4d%2d%2d", &birth_year, &birth_month, &birth_day);

    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    int age = now->tm_year + 1900 - birth_year;

    if (now->tm_mon + 1 < birth_month || (now->tm_mon + 1 == birth_month && now->tm_mday < birth_day)) {
        age--;
    }

    return age;
}

int main() {
    char buffer[BUFFER];
    int i;

    // 오디션 그룹명 입력 받기
    printf("오디션 그룹명을 입력하세요: ");
    fgets(group_name, sizeof(group_name), stdin);
    group_name[strcspn(group_name, "\n")] = '\0'; // 개행 제거

    printf("\n#################################### [%s] 오디션 후보자 데이터 입력 ####################################\n", group_name);

    i = 0;
    while (i < NUM_CANDIDATES) {
        printf("\n%d번째 후보자의 정보를 입력합니다.\n", i + 1);
        printf("---------------------------------\n");

        printf("1. 성명: ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][0] = strdup(strtok(buffer, "\n"));

        printf("2. 생일(YYYY/MM/DD 형식): ");
        fgets(buffer, BUFFER, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        char *birth_noslash = malloc(9);
        sscanf(buffer, "%4c/%2c/%2c", &birth_noslash[0], &birth_noslash[4], &birth_noslash[6]);
        birth_noslash[8] = '\0';
        birth_noslash[4] = birth_noslash[5];
        birth_noslash[5] = '\0';
        member_info[i][1] = strdup(birth_noslash);
        free(birth_noslash);

        printf("3. 성별(여성이면 F 또는 남성이면 M): ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][2] = strdup(strtok(buffer, "\n"));

        printf("4. 메일 주소: ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][3] = strdup(strtok(buffer, "\n"));

        printf("5. 국적: ");
        member_info[i][4] = strdup(strtok(buffer, "\n"));

        printf("6. BMI: ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][5] = strdup(strtok(buffer, "\n"));

        printf("7. 주 스킬: ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][6] = strdup(strtok(buffer, "\n"));

        printf("8. 보조 스킬: ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][7] = strdup(strtok(buffer, "\n"));

        printf("9. 한국어 등급(TOPIK): ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][8] = strdup(strtok(buffer, "\n"));

        printf("10. MBTI: ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][9] = strdup(strtok(buffer, "\n"));

        printf("11. 소개: ");
        fgets(buffer, BUFFER, stdin);
        member_info[i][10] = strdup(strtok(buffer, "\n"));

        i++;
    }

    // 출력
    printf("\n#################################### [%s] 오디션 후보자 데이터 조회  ####################################\n", group_name);
    printf("=============================================================================================================\n");
    printf("성   명(나이) | 생   일 | 성별 | 메   일            | 국적 | BMI | 주스킬 | 보조스킬 | TOPIK | MBTI |\n");
    printf("=============================================================================================================\n");

    for (i = 0; i < NUM_CANDIDATES; i++) {
        const char *name = member_info[i][0];
        const char *birth = member_info[i][1];
        const char *gender = member_info[i][2];
        const char *email = member_info[i][3];
        const char *nation = member_info[i][4];
        const char *bmi = member_info[i][5];
        const char *skill_main = member_info[i][6];
        const char *skill_sub = member_info[i][7];
        const char *topik = member_info[i][8];
        const char *mbti = member_info[i][9];
        const char *intro = member_info[i][10];

        int age = calculate_age(birth);

        const char *topik_level;
        if (strcmp(topik, "0") == 0) {
            topik_level = "원어민";
        } else {
            topik_level = topik;
        }

        printf("%-10s(%2d)| %8s | %-2s | %-18s | %-4s | %-4s | %-6s | %-8s | %-6s | %-4s |\n",
               name, age, birth, gender, email, nation, bmi, skill_main, skill_sub, topik_level, mbti);

        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("%s\n", intro);
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
