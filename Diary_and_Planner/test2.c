#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <windows.h>
#define PASSWORD_LENGTH 5
#define MAX_LENGTH 1000 
#define MAX_DAYS_IN_MONTH 31
#define MAX_MONTHS_IN_YEAR 12
char password[MAX_LENGTH];

void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

typedef struct {
    char content[MAX_LENGTH];
} Diary;

typedef struct {
    char content[MAX_LENGTH];
} Planner;

Diary diaries[MAX_DAYS_IN_MONTH][MAX_MONTHS_IN_YEAR];
Planner planners[MAX_DAYS_IN_MONTH][MAX_MONTHS_IN_YEAR];

void printCalendar(int year, int month) {
    int daysInMonth, i, j, dayOfWeek = 0;
    int daysPerMonth[MAX_MONTHS_IN_YEAR] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        daysPerMonth[1] = 29;
    }
    daysInMonth = daysPerMonth[month - 1];
    printf("Sun Mon Tue Wed Thu Fri Sat\n");

    for (i = 1; i < month; i++) {
        dayOfWeek += daysPerMonth[i - 1];
    }
    dayOfWeek %= 7;
    for (i = 0; i < dayOfWeek; i++) {
        printf("    ");
    }
    for (i = 1; i <= daysInMonth; i++) {
        printf("%3d ", i);
        dayOfWeek++;
        if (dayOfWeek % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void writeDiaryToFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("ÆÄÀÏÀ» ¿­ ¼ö ¾ø½À´Ï´Ù.\n");
        return;
    }

    fprintf(file, "%s", diaries[day - 1][month - 1].content);
    fclose(file);
    printf("%d¿ù %dÀÏÀÇ ÀÏ±â°¡ ÆÄÀÏ¿¡ ÀúÀåµÇ¾ú½À´Ï´Ù.\n", month, day);
}

void writePlannerToFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("ÆÄÀÏÀ» ¿­ ¼ö ¾ø½À´Ï´Ù.\n");
        return;
    }

    fprintf(file, "%s", planners[day - 1][month - 1].content);
    fclose(file);
    printf("%d¿ù %dÀÏÀÇ ÇÃ·¡³Ê°¡ ÆÄÀÏ¿¡ ÀúÀåµÇ¾ú½À´Ï´Ù.\n", month, day);
}

void viewDiaryFromFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d¿ù %dÀÏ¿¡ ÀÏ±â°¡ ¾ø½À´Ï´Ù.\n", month, day);
        return;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void viewPlannerFromFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d¿ù %dÀÏ¿¡ ÇÃ·¡³Ê°¡ ¾ø½À´Ï´Ù.\n", month, day);
        return;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void writeDiary(int day, int month) {
    printf("%d¿ù %dÀÏÀÇ ÀÏ±â¸¦ ¾²¼¼¿ä (ÃÖ´ë %d±ÛÀÚ):\n", month, day, MAX_LENGTH);
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writeDiaryToFile(day, month);
    printf("%d¿ù %dÀÏÀÇ ÀÏ±â°¡ ÀúÀåµÇ¾ú½À´Ï´Ù.\n", month, day);
}

void writePlanner(int day, int month) {
    printf("%d¿ù %dÀÏÀÇ ÇÃ·¡³Ê¸¦ ¾²¼¼¿ä (ÃÖ´ë %d±ÛÀÚ):\n", month, day, MAX_LENGTH);
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writePlannerToFile(day, month);
    printf("%d¿ù %dÀÏÀÇ ÇÃ·¡³Ê°¡ ÀúÀåµÇ¾ú½À´Ï´Ù.\n", month, day);
}

void modifyDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d¿ù %dÀÏ¿¡ ÀÏ±â°¡ ¾ø½À´Ï´Ù.\n", month, day);
        return;
    }

    fclose(file);

    printf("¼öÁ¤ÇÒ ³»¿ëÀ» ÀÔ·ÂÇÏ¼¼¿ä (ÃÖ´ë %d±ÛÀÚ):\n", MAX_LENGTH);
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writeDiaryToFile(day, month);

    printf("%d¿ù %dÀÏÀÇ ÀÏ±â°¡ ¼öÁ¤µÇ¾ú½À´Ï´Ù.\n", month, day);
}

void modifyPlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d¿ù %dÀÏ¿¡ ÇÃ·¡³Ê°¡ ¾ø½À´Ï´Ù.\n", month, day);
        return;
    }

    fclose(file);

    printf("¼öÁ¤ÇÒ ³»¿ëÀ» ÀÔ·ÂÇÏ¼¼¿ä (ÃÖ´ë %d±ÛÀÚ):\n", MAX_LENGTH);
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writePlannerToFile(day, month);

    printf("%d¿ù %dÀÏÀÇ ÇÃ·¡³Ê°¡ ¼öÁ¤µÇ¾ú½À´Ï´Ù.\n", month, day);
}

void deleteDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d¿ù %dÀÏ¿¡ ÀÏ±â°¡ ¾ø½À´Ï´Ù.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        printf("%d¿ù %dÀÏÀÇ ÀÏ±â°¡ »èÁ¦µÇ¾ú½À´Ï´Ù.\n", month, day);
    } else {
        printf("»èÁ¦ ½ÇÆÐ: ÆÄÀÏÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù.\n");
    }
}

void deletePlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d¿ù %dÀÏ¿¡ ÇÃ·¡³Ê°¡ ¾ø½À´Ï´Ù.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        printf("%d¿ù %dÀÏÀÇ ÇÃ·¡³Ê°¡ »èÁ¦µÇ¾ú½À´Ï´Ù.\n", month, day);
    } else {
        printf("»èÁ¦ ½ÇÆÐ: ÆÄÀÏÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù.\n");
    }
}

void viewDiary(int day, int month) {
    char choice;
    viewDiaryFromFile(day, month);

    printf("¼öÁ¤ ¶Ç´Â »èÁ¦ÇÏ½Ã°Ú½À´Ï±î? (m/d/n): ");
    scanf(" %c", &choice);

    switch (choice) {
        case 'm':
        case 'M':
            modifyDiary(day, month);
            break;
        case 'd':
        case 'D':
            deleteDiary(day, month);
            break;
        default:
            break;
    }
}

void viewPlanner(int day, int month) {
    char choice;
    viewPlannerFromFile(day, month);
    printf("¼öÁ¤ ¶Ç´Â »èÁ¦ÇÏ½Ã°Ú½À´Ï±î? (m/d/n): ");
    scanf(" %c", &choice);

    switch (choice) {
        case 'm':
        case 'M':
            modifyPlanner(day, month);
            break;
        case 'd':
        case 'D':
            deletePlanner(day, month);
            break;
        default:
            break;
    }
}

bool checkPassword(const char *inputPassword) {
    char password[PASSWORD_LENGTH];
    FILE *file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("ÆÄÀÏÀ» ¿­ ¼ö ¾ø½À´Ï´Ù.\n");
        return false;
    }

    fgets(password, PASSWORD_LENGTH, file);
    fclose(file);

    if (strcmp(inputPassword, password) == 0) {
        return true; // ºñ¹Ð¹øÈ£ ÀÏÄ¡
    } else {
        return false; // ºñ¹Ð¹øÈ£ ºÒÀÏÄ¡
    }
}

void setPassword() {
    char newPassword[PASSWORD_LENGTH];
    printf("ºñ¹Ð¹øÈ£¸¦ ÀÔ·ÂÇÏ¼¼¿ä (4ÀÚ¸® Á¤¼ö): ");
    scanf("%s", newPassword);

    FILE *file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("ÆÄÀÏÀ» ¿­ ¼ö ¾ø½À´Ï´Ù.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    printf("ºñ¹Ð¹øÈ£°¡ ¼³Á¤µÇ¾ú½À´Ï´Ù.\n");
}

void changePassword() {
    char currentPassword[PASSWORD_LENGTH], newPassword[PASSWORD_LENGTH];

    printf("ÇöÀç ºñ¹Ð¹øÈ£¸¦ ÀÔ·ÂÇÏ¼¼¿ä: ");
    scanf("%s", currentPassword);

    if (!checkPassword(currentPassword)) {
        printf("ÀÏÄ¡ÇÏÁö ¾Ê½À´Ï´Ù.\n");
        return;
    }

    printf("»õ ºñ¹Ð¹øÈ£¸¦ ÀÔ·ÂÇÏ¼¼¿ä (4ÀÚ¸® Á¤¼ö): ");
    scanf("%s", newPassword);

    FILE *file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("ÆÄÀÏÀ» ¿­ ¼ö ¾ø½À´Ï´Ù.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    printf("ºñ¹Ð¹øÈ£°¡ º¯°æµÇ¾ú½À´Ï´Ù.\n");
}

int setting(){
	char choice;
    bool passwordExists = false;

    FILE *file = fopen("password.txt", "r");
    if (file != NULL) {
        fclose(file);
        passwordExists = true;
    }

    while (1) {
        if (!passwordExists) {
            printf("ºñ¹Ð¹øÈ£¸¦ ¼³Á¤ÇÏ½Ã°Ú½À´Ï±î? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                setPassword();
            } else if (choice == 'n' || choice == 'N') {
                printf("Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù..\n");
                break;
            }
            passwordExists = true;
        } else {
            printf("ºñ¹Ð¹øÈ£¸¦ º¯°æÇÏ½Ã°Ú½À´Ï±î? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                changePassword();
            } else if (choice == 'n' || choice == 'N') {
                printf("Ã³À½À¸·Î µ¹¾Æ°©´Ï´Ù..\n");
                break;
            }
        }
    }

}

int menu_ui(){
	char currentPassword[PASSWORD_LENGTH], newPassword[PASSWORD_LENGTH];
    system("cls");
    printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
	printf("        ¦¢                ¸Þ´º                 ¦¢\n");
    printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
    printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
    printf("        ¦¢              1. ÀÏ±â                ¦¢\n");
    printf("        ¦¢              2. ÇÃ·¡³Ê              ¦¢\n");
    printf("        ¦¢              3. ºÒ·¯¿À±â            ¦¢\n");
    printf("        ¦¢              4. ¼³Á¤                ¦¢\n");
    printf("        ¦¢              5. Á¾·á                ¦¢\n");
    printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
    
	int menu, day, view_select;
    printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
    printf("        ¦¢        ÀÔ·Â :                       ¦¢\n");
    printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
    GotoXY(24, 11);
	scanf("%d", &menu);
    system("cls");
	int month = 1, year = 2023;
    int monthf;
	switch (menu) {
        case 1:
            printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
            printf("        ¦¢              ÀÏ±â ¸Þ´º              ¦¢\n");
            printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
            printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
            printf("        ¦¢       ¿ùÀ» ÀÔ·ÂÇÏ¼¼¿ä :             ¦¢\n");
        	printf("        ¦¢       ÀÏ¸¦ ÀÔ·ÂÇÏ¼¼¿ä :             ¦¢\n", MAX_DAYS_IN_MONTH);
            printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
            GotoXY(34, 4);
            scanf("%d", &monthf);
            GotoXY(34, 5);
        	scanf("%d", &day);
            system("cls");
            writeDiary(day, month);
            break;
        case 2:
            printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
            printf("        ¦¢             ÇÃ·¡³Ê ¸Þ´º             ¦¢\n");
            printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
            printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
            printf("        ¦¢       ¿ùÀ» ÀÔ·ÂÇÏ¼¼¿ä :             ¦¢\n");
            printf("        ¦¢       ÀÏ¸¦ ÀÔ·ÂÇÏ¼¼¿ä :             ¦¢\n", MAX_DAYS_IN_MONTH);
            printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
            GotoXY(34, 4);
            scanf("%d", &monthf);
            GotoXY(34, 5);
        	scanf("%d", &day);
            system("cls");
            writePlanner(day, month);
            break;
        case 3:
            printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
            printf("        ¦¢             ¼³Á¤ ¸Þ´º               ¦¢\n");
            printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
            printf("        ¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤\n");
        	printf("        ¦¢     ºñ¹Ð¹øÈ£¸¦ ÀÔ·ÂÇÏ¼¼¿ä:          ¦¢\n");      
            printf("        ¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥\n");
            GotoXY(37, 4);
    		scanf("%s", currentPassword);
            system("cls");
        	if (!checkPassword(currentPassword)) {
		        printf("ºñ¹Ð¹øÈ£°¡ ÀÏÄ¡ÇÏÁö ¾Ê½À´Ï´Ù.\n");
                Sleep(2000);
		        break;
		    }
            
        	printCalendar(year, month);
        	printf("³¯Â¥¸¦ ¼±ÅÃÇÏ¼¼¿ä : ", MAX_DAYS_IN_MONTH);
        	scanf("%d", &day);
        	printf("1. ÀÏ±â È®ÀÎ\n2. ÇÃ·¡³Ê È®ÀÎ\n==>");
			scanf("%d", &view_select);
			if(view_select == 1){
				viewDiary(day, month);
			}else if(view_select == 2){
				viewPlanner(day, month);
			}
            
            
            break;
        case 4:
            setting();
            break;
        case 5 :
        	printf("ÇÁ·Î±×·¥À» Á¾·áÇÕ´Ï´Ù.");
			exit(0);
        default:
            printf("Àß¸øµÈ ¼±ÅÃÀÔ´Ï´Ù. ´Ù½Ã ¼±ÅÃÇØÁÖ¼¼¿ä.\n");
    }
}

int main() {
    while(1){
    	menu_ui();
	}

    return 0;
}

