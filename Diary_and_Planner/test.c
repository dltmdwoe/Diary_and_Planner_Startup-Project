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

int LeapYear(int _year)	//彌喇, ゎ喇 掘碟擊 嬪и л熱
{
    int leapyear;

    if (_year % 400 == 0 || (_year % 4 == 0 && _year % 100 != 0))	//彌喇檜賊 1殮溘 嬴棲賊 0殮溘
    {
        leapyear = 1;
    }
    else
    {
        leapyear = 0;
    }

    return leapyear;	//彌喇1,ゎ喇0擊 奩��
}

int FirstDate(int _year, int _month)	//衛濛蹂橾擊 掘ж晦 嬪и л熱
{
    int lastyear = _year - 1;	
    int lastyeardate = 0;
    int inputyeardate = 0;
    int firstdate = 0;	
    int month = _month;	
    lastyeardate = lastyear * 365 + lastyear / 400 + lastyear / 4 - lastyear / 100 + 1;	
    int leapyear = LeapYear(_year);	

    for (int _month = 1; _month < month; _month++)
    {
        int date = LastDate(_year, _month);	
        inputyeardate += date;	
    }
    firstdate = (lastyeardate + inputyeardate) % 7;

    return firstdate;	
}

int LastDate(int _year, int _month)	//殮溘嫡擎 殖曖 葆雖虞陳瞼蒂 嬪и л熱
{
    int lastdate = 0;
    int leapyear = LeapYear(_year);	

    if (_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10 || _month == 12)
    {
        lastdate = 31;	
    }
    else if (_month == 4 || _month == 6 || _month == 9 || _month == 11)
    {
        lastdate = 30;	
    }
    else if (leapyear == 1 && _month == 2)
    {
        lastdate = 29;	
    }
    else if (leapyear == 0 && _month == 2)
    {
        lastdate = 28;	
    }

    return lastdate;
}

int PrintCalendar(int _firstdate, int _lastdate)
{
    for (int i = 0; i < _firstdate; i++)	
    {
        printf("   ");
    }
    for (int i = 1; i <= _lastdate; i++)	
    {
        printf("%3d", i);
        if ((_firstdate + i) % 7 == 0)	
        {
            printf("\n");
        }
    }
    printf("\n\n");
}

void FinalCalendar(int year, int month)
{
    int firstdate = FirstDate(year, month);	//殮溘嫡擎 year,month蒂 FirstDateл熱縑 殮溘, ��轎п 高擊 firstdate縑 盪濰
    int lastdate = LastDate(year, month);	//殮溘嫡擎 year,month蒂 LastDateл熱縑 殮溘, ��轎п 高擊 lastdate縑 盪濰
    printf("\n     %d喇  %d錯\n", year, month);
    printf("   ===============    \n");
    printf("----------------------\n");
    printf(" 橾 錯 �� 熱 跡 旎 饜 \n");
    printf("----------------------\n");
    PrintCalendar(firstdate, lastdate);	

}

void writeDiaryToFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return;
    }

    fprintf(file, "%s", diaries[day - 1][month - 1].content);
    fclose(file);
}

void writePlannerToFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return;
    }

    fprintf(file, "%s", planners[day - 1][month - 1].content);
    fclose(file);
}

void viewDiaryFromFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE* file = fopen(filename, "r");
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

    FILE* file = fopen(filename, "r");
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
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛   %d錯 %d橾曖 橾晦 (譆渠 %d旋濠)    弛\n", month, day, MAX_LENGTH);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writeDiaryToFile(day, month);
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛   %d錯 %d橾曖 橾晦陛 盪濰腎歷蝗棲棻   弛\n", month, day);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    Sleep(1800);
}

void writePlanner(int day, int month) {
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛  %d錯 %d橾曖 Ы楚傘 (譆渠 %d旋濠)   弛\n", month, day, MAX_LENGTH);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writePlannerToFile(day, month);
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛  %d錯 %d橾曖 Ы楚傘陛 盪濰腎歷蝗棲棻  弛\n", month, day);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    Sleep(1800);
}

void modifyDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 橾晦陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);
    system("cls");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛      熱薑й 頂辨擊 殮溘ж撮蹂       弛\n", MAX_LENGTH);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writeDiaryToFile(day, month);
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛   %d錯 %d橾曖 橾晦陛 熱薑腎歷蝗棲棻   弛\n", month, day);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    Sleep(1800);
}

void modifyPlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 Ы楚傘陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);

    system("cls");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛      熱薑й 頂辨擊 殮溘ж撮蹂       弛\n", MAX_LENGTH);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writePlannerToFile(day, month);
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛  %d錯 %d橾曖 Ы楚傘陛 熱薑腎歷蝗棲棻  弛\n", month, day);
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    Sleep(1800);
}

void deleteDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 橾晦陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        system("cls");
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛   %d錯 %d橾曖 橾晦陛 餉薯腎歷蝗棲棻  弛\n", month, day);
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        Sleep(1800);
    }
}

void deletePlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d錯 %d橾縑 Ы楚傘陛 橈蝗棲棻.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        system("cls");
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛  %d錯 %d橾曖 Ы楚傘陛 餉薯腎歷蝗棲棻  弛\n", month, day);
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        Sleep(1800);
    }
}

void viewDiary(int day, int month) {
    char choice;
    viewDiaryFromFile(day, month);
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛  熱薑 : m / 餉薯 : d / 菴煎陛晦 : n 弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
  
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛        殮溘 :                       弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    GotoXY(24, 5);
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
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛  熱薑 : m / 餉薯 : d / 菴煎陛晦 : n 弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");

    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛        殮溘 :                       弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    GotoXY(24, 5);
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

bool checkPassword(const char* inputPassword) {
    char password[PASSWORD_LENGTH];
    FILE* file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return false;
    }

    fgets(password, PASSWORD_LENGTH, file);
    fclose(file);

    if (strcmp(inputPassword, password) == 0) {
        return true; // 綠塵廓�� 橾纂
    }
    else {
        return false; // 綠塵廓�� 碳橾纂
    }
}

void setPassword() {
    char newPassword[PASSWORD_LENGTH];
    printf("綠塵廓�ㄧ� 殮溘ж撮蹂 (4濠葬 薑熱): ");
    scanf("%s", newPassword);

    FILE* file = fopen("password.txt", "w");
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
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛              撲薑 詭景              弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛     ⑷營 綠塵廓�ㄧ� 殮溘ж撮蹂      弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛        殮溘 :                       弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    GotoXY(24, 7);
    scanf("%s", currentPassword);

    if (!checkPassword(currentPassword)) {
        printf("\n");
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛          橾纂ж雖 彊蝗棲棻          弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        Sleep(1500);
        system("cls");
        return;
    }
    system("cls");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛      億 綠塵廓�ㄧ� 殮溘ж撮蹂       弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛      殮溘 (璋濠 4濠葬) :            弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    GotoXY(35, 4);
    scanf("%s", newPassword);
    
    FILE* file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("だ橾擊 翮 熱 橈蝗棲棻.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    system("cls");
    printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("        弛     綠塵廓�ㄟ� 滲唳腎歷蝗棲棻       弛\n");
    printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    Sleep(1500);
    system("cls");
    
}

int setting() {
    char choice;
    bool passwordExists = false;

    FILE* file = fopen("password.txt", "r");
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
            }
            else if (choice == 'n' || choice == 'N') {
                printf("籀擠戲煎 給嬴骨棲棻..\n");
                break;
            }
            passwordExists = true;
        }
        else {
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
            printf("        弛     綠塵廓�ㄧ� 滲唳ж衛啊蝗棲梱?    弛\n");
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
            printf("        弛     殮溘(y/n) :                     弛\n");
            printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
            GotoXY(26, 4);
            scanf(" %c", &choice);
            system("cls");

            if (choice == 'y' || choice == 'Y') {
                changePassword();
                break;
            }
            else if (choice == 'n' || choice == 'N') {
                printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
                printf("        弛         籀擠戲煎 給嬴骨棲棻         弛\n");
                printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
                Sleep(1500);
                break;
            }
        }
    }

}

int menu_ui() {
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
    int month = 0, year = 2023;
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
        scanf("%d", &month);
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
        scanf("%d", &month);
        GotoXY(34, 5);
        scanf("%d", &day);
        system("cls");
        writePlanner(day, month);
        break;
    case 3:
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛           碳楝螃晦 詭景             弛\n");
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
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛           碳楝螃晦 詭景             弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛     喇紫蒂 殮溘п輿撮蹂 :           弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        GotoXY(36, 4);
        scanf("%d", &year);
        printf("\n");
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛     殖擊 殮溘п輿撮蹂 :             弛\n", MAX_DAYS_IN_MONTH);
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        GotoXY(34, 7);
        scanf("%d", &month);
        system("cls");

        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛            碳楝螃晦 詭景            弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        FinalCalendar(year, month);
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛       陳瞼蒂 殮溘п輿撮蹂 :         弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        GotoXY(38, 16);
        scanf("%d", &day);
        system("cls");

        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛            碳楝螃晦 詭景            弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");

        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛   1. 橾晦 �挫�  弛  2. Ы楚傘 �挫�   弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛        殮溘 :                       弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        GotoXY(24, 7);
        scanf("%d", &view_select);
        system("cls");

        if (view_select == 1) {
            viewDiary(day, month);
        }
        else if (view_select == 2) {
            viewPlanner(day, month);
        }


        break;
    case 4:
        setting();
        break;
    case 5:
        printf("        忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
        printf("        弛       Щ煎斜極擊 謙猿м棲棻         弛\n");
        printf("        戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
        exit(0);
    }
}

int main() {
    while (1) {
        menu_ui();
    }

    return 0;
}

