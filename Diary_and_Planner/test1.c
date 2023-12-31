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
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return;
    }

    fprintf(file, "%s", diaries[day - 1][month - 1].content);
    fclose(file);
    printf("%d錯 %d橾曖 橾晦陛 だ橾縑 盪濰腎歷蝗棲棻.\n", month, day);
}

void writePlannerToFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return;
    }

    fprintf(file, "%s", planners[day - 1][month - 1].content);
    fclose(file);
    printf("%d錯 %d橾曖 Ы楚傘陛 だ橾縑 盪濰腎歷蝗棲棻.\n", month, day);
}

void viewDiaryFromFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 橾晦陛 橈蝗棲棻.\n", month, day);
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
        printf("%d錯 %d橾縑 Ы楚傘陛 橈蝗棲棻.\n", month, day);
        return;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void writeDiary(int day, int month) {
    printf("%d錯 %d橾曖 橾晦蒂 噙撮蹂 (譆渠 %d旋濠):\n", month, day, MAX_LENGTH);
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writeDiaryToFile(day, month);
    printf("%d錯 %d橾曖 橾晦陛 盪濰腎歷蝗棲棻.\n", month, day);
}

void writePlanner(int day, int month) {
    printf("%d錯 %d橾曖 Ы楚傘蒂 噙撮蹂 (譆渠 %d旋濠):\n", month, day, MAX_LENGTH);
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writePlannerToFile(day, month);
    printf("%d錯 %d橾曖 Ы楚傘陛 盪濰腎歷蝗棲棻.\n", month, day);
}

void modifyDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 橾晦陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);

    printf("熱薑й 頂辨擊 殮溘ж撮蹂 (譆渠 %d旋濠):\n", MAX_LENGTH);
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writeDiaryToFile(day, month);

    printf("%d錯 %d橾曖 橾晦陛 熱薑腎歷蝗棲棻.\n", month, day);
}

void modifyPlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 Ы楚傘陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);

    printf("熱薑й 頂辨擊 殮溘ж撮蹂 (譆渠 %d旋濠):\n", MAX_LENGTH);
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writePlannerToFile(day, month);

    printf("%d錯 %d橾曖 Ы楚傘陛 熱薑腎歷蝗棲棻.\n", month, day);
}

void deleteDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 橾晦陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        printf("%d錯 %d橾曖 橾晦陛 餉薯腎歷蝗棲棻.\n", month, day);
    } else {
        printf("餉薯 褒ぬ: だ橾擊 瓊擊 熱 橈蝗棲棻.\n");
    }
}

void deletePlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 Ы楚傘陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        printf("%d錯 %d橾曖 Ы楚傘陛 餉薯腎歷蝗棲棻.\n", month, day);
    } else {
        printf("餉薯 褒ぬ: だ橾擊 瓊擊 熱 橈蝗棲棻.\n");
    }
}

void viewDiary(int day, int month) {
    char choice;
    viewDiaryFromFile(day, month);

    printf("熱薑 傳朝 餉薯ж衛啊蝗棲梱? (m/d/n): ");
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
    printf("熱薑 傳朝 餉薯ж衛啊蝗棲梱? (m/d/n): ");
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
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return false;
    }

    fgets(password, PASSWORD_LENGTH, file);
    fclose(file);

    if (strcmp(inputPassword, password) == 0) {
        return true; // 綠塵廓�� 橾纂
    } else {
        return false; // 綠塵廓�� 碳橾纂
    }
}

void setPassword() {
    char newPassword[PASSWORD_LENGTH];
    printf("綠塵廓�ㄧ� 殮溘ж撮蹂 (4濠葬 薑熱): ");
    scanf("%s", newPassword);

    FILE *file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    printf("綠塵廓�ㄟ� 撲薑腎歷蝗棲棻.\n");
}

void changePassword() {
    char currentPassword[PASSWORD_LENGTH], newPassword[PASSWORD_LENGTH];

    printf("⑷營 綠塵廓�ㄧ� 殮溘ж撮蹂: ");
    scanf("%s", currentPassword);

    if (!checkPassword(currentPassword)) {
        printf("橾纂ж雖 彊蝗棲棻.\n");
        return;
    }

    printf("億 綠塵廓�ㄧ� 殮溘ж撮蹂 (4濠葬 薑熱): ");
    scanf("%s", newPassword);

    FILE *file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    printf("綠塵廓�ㄟ� 滲唳腎歷蝗棲棻.\n");
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
            printf("綠塵廓�ㄧ� 撲薑ж衛啊蝗棲梱? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                setPassword();
            } else if (choice == 'n' || choice == 'N') {
                printf("籀擠戲煎 給嬴骨棲棻..\n");
                break;
            }
            passwordExists = true;
        } else {
            printf("綠塵廓�ㄧ� 滲唳ж衛啊蝗棲梱? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                changePassword();
            } else if (choice == 'n' || choice == 'N') {
                printf("籀擠戲煎 給嬴骨棲棻..\n");
                break;
            }
        }
    }

}

int menu_ui(){
	char currentPassword[PASSWORD_LENGTH], newPassword[PASSWORD_LENGTH];
    system("cls");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("        弛                詭景                 弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛              1. 橾晦                弛\n");
    printf("        弛              2. Ы楚傘              弛\n");
    printf("        弛              3. 碳楝螃晦            弛\n");
    printf("        弛              4. 撲薑                弛\n");
    printf("        弛              5. 謙猿                弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    
	int menu, day, view_select;
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛        殮溘 :                       弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    GotoXY(24, 11);
	scanf("%d", &menu);
    system("cls");
	int month = 1, year = 2023;
    int monthf;
	switch (menu) {
        case 1:
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
            printf("        弛              橾晦 詭景              弛\n");
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
            printf("        弛       錯擊 殮溘ж撮蹂 :             弛\n");
        	printf("        弛       橾蒂 殮溘ж撮蹂 :             弛\n", MAX_DAYS_IN_MONTH);
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            GotoXY(34, 4);
            scanf("%d", &monthf);
            GotoXY(34, 5);
        	scanf("%d", &day);
            system("cls");
            writeDiary(day, month);
            break;
        case 2:
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
            printf("        弛             Ы楚傘 詭景             弛\n");
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
            printf("        弛       錯擊 殮溘ж撮蹂 :             弛\n");
            printf("        弛       橾蒂 殮溘ж撮蹂 :             弛\n", MAX_DAYS_IN_MONTH);
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            GotoXY(34, 4);
            scanf("%d", &monthf);
            GotoXY(34, 5);
        	scanf("%d", &day);
            system("cls");
            writePlanner(day, month);
            break;
        case 3:
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
            printf("        弛             撲薑 詭景               弛\n");
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        	printf("        弛     綠塵廓�ㄧ� 殮溘ж撮蹂:          弛\n");      
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            GotoXY(37, 4);
    		scanf("%s", currentPassword);
            system("cls");
        	if (!checkPassword(currentPassword)) {
		        printf("綠塵廓�ㄟ� 橾纂ж雖 彊蝗棲棻.\n");
                Sleep(2000);
		        break;
		    }
            
        	printCalendar(year, month);
        	printf("陳瞼蒂 摹鷗ж撮蹂 : ", MAX_DAYS_IN_MONTH);
        	scanf("%d", &day);
        	printf("1. 橾晦 �挫垥n2. Ы楚傘 �挫垥n==>");
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
        	printf("Щ煎斜極擊 謙猿м棲棻.");
			exit(0);
        default:
            printf("澀跤脹 摹鷗殮棲棻. 棻衛 摹鷗п輿撮蹂.\n");
    }
}

int main() {
    while(1){
    	menu_ui();
	}

    return 0;
}

