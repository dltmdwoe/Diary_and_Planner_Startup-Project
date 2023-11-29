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

int LeapYear(int _year)	//����, ��� ������ ���� �Լ�
{
    int leapyear;

    if (_year % 400 == 0 || (_year % 4 == 0 && _year % 100 != 0))	//�����̸� 1�Է� �ƴϸ� 0�Է�
    {
        leapyear = 1;
    }
    else
    {
        leapyear = 0;
    }

    return leapyear;	//����1,���0�� ��ȯ
}

int FirstDate(int _year, int _month)	//���ۿ����� ���ϱ� ���� �Լ�
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

int LastDate(int _year, int _month)	//�Է¹��� ���� ��������¥�� ���� �Լ�
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
    int firstdate = FirstDate(year, month);	//�Է¹��� year,month�� FirstDate�Լ��� �Է�, ȣ���� ���� firstdate�� ����
    int lastdate = LastDate(year, month);	//�Է¹��� year,month�� LastDate�Լ��� �Է�, ȣ���� ���� lastdate�� ����
    printf("\n     %d��  %d��\n", year, month);
    printf("   ===============    \n");
    printf("----------------------\n");
    printf(" �� �� ȭ �� �� �� �� \n");
    printf("----------------------\n");
    PrintCalendar(firstdate, lastdate);	

}

void writeDiaryToFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
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
        printf("������ �� �� �����ϴ�.\n");
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
        printf("%d�� %d�Ͽ� �ϱⰡ �����ϴ�.\n", month, day);
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
        printf("%d�� %d�Ͽ� �÷��ʰ� �����ϴ�.\n", month, day);
        return;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void writeDiary(int day, int month) {
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��   %d�� %d���� �ϱ� (�ִ� %d����)    ��\n", month, day, MAX_LENGTH);
    printf("        ������������������������������������������������������������������������������\n");
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writeDiaryToFile(day, month);
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��   %d�� %d���� �ϱⰡ ����Ǿ����ϴ�   ��\n", month, day);
    printf("        ������������������������������������������������������������������������������\n");
    Sleep(1800);
}

void writePlanner(int day, int month) {
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��  %d�� %d���� �÷��� (�ִ� %d����)   ��\n", month, day, MAX_LENGTH);
    printf("        ������������������������������������������������������������������������������\n");
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writePlannerToFile(day, month);
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��  %d�� %d���� �÷��ʰ� ����Ǿ����ϴ�  ��\n", month, day);
    printf("        ������������������������������������������������������������������������������\n");
    Sleep(1800);
}

void modifyDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �ϱⰡ �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);
    system("cls");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��      ������ ������ �Է��ϼ���       ��\n", MAX_LENGTH);
    printf("        ������������������������������������������������������������������������������\n");
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writeDiaryToFile(day, month);
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��   %d�� %d���� �ϱⰡ �����Ǿ����ϴ�   ��\n", month, day);
    printf("        ������������������������������������������������������������������������������\n");
    Sleep(1800);
}

void modifyPlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �÷��ʰ� �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);

    system("cls");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��      ������ ������ �Է��ϼ���       ��\n", MAX_LENGTH);
    printf("        ������������������������������������������������������������������������������\n");
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writePlannerToFile(day, month);
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��  %d�� %d���� �÷��ʰ� �����Ǿ����ϴ�  ��\n", month, day);
    printf("        ������������������������������������������������������������������������������\n");
    Sleep(1800);
}

void deleteDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �ϱⰡ �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        system("cls");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��   %d�� %d���� �ϱⰡ �����Ǿ����ϴ�  ��\n", month, day);
        printf("        ������������������������������������������������������������������������������\n");
        Sleep(1800);
    }
}

void deletePlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �÷��ʰ� �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        system("cls");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��  %d�� %d���� �÷��ʰ� �����Ǿ����ϴ�  ��\n", month, day);
        printf("        ������������������������������������������������������������������������������\n");
        Sleep(1800);
    }
}

void viewDiary(int day, int month) {
    char choice;
    viewDiaryFromFile(day, month);
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��  ���� : m / ���� : d / �ڷΰ��� : n ��\n");
    printf("        ������������������������������������������������������������������������������\n");
  
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��        �Է� :                       ��\n");
    printf("        ������������������������������������������������������������������������������\n");
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
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��  ���� : m / ���� : d / �ڷΰ��� : n ��\n");
    printf("        ������������������������������������������������������������������������������\n");

    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��        �Է� :                       ��\n");
    printf("        ������������������������������������������������������������������������������\n");
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
        printf("������ �� �� �����ϴ�.\n");
        return false;
    }

    fgets(password, PASSWORD_LENGTH, file);
    fclose(file);

    if (strcmp(inputPassword, password) == 0) {
        return true; // ��й�ȣ ��ġ
    }
    else {
        return false; // ��й�ȣ ����ġ
    }
}

void setPassword() {
    char newPassword[PASSWORD_LENGTH];
    printf("��й�ȣ�� �Է��ϼ��� (4�ڸ� ����): ");
    scanf("%s", newPassword);

    FILE* file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    printf("��й�ȣ�� �����Ǿ����ϴ�.\n");
}

void changePassword() {
    char currentPassword[PASSWORD_LENGTH], newPassword[PASSWORD_LENGTH];
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��              ���� �޴�              ��\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��     ���� ��й�ȣ�� �Է��ϼ���      ��\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��        �Է� :                       ��\n");
    printf("        ������������������������������������������������������������������������������\n");
    GotoXY(24, 7);
    scanf("%s", currentPassword);

    if (!checkPassword(currentPassword)) {
        printf("\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��          ��ġ���� �ʽ��ϴ�          ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        Sleep(1500);
        system("cls");
        return;
    }
    system("cls");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��      �� ��й�ȣ�� �Է��ϼ���       ��\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��      �Է� (���� 4�ڸ�) :            ��\n");
    printf("        ������������������������������������������������������������������������������\n");
    GotoXY(35, 4);
    scanf("%s", newPassword);
    
    FILE* file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    system("cls");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��     ��й�ȣ�� ����Ǿ����ϴ�       ��\n");
    printf("        ������������������������������������������������������������������������������\n");
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
            printf("��й�ȣ�� �����Ͻðڽ��ϱ�? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                setPassword();
            }
            else if (choice == 'n' || choice == 'N') {
                printf("ó������ ���ư��ϴ�..\n");
                break;
            }
            passwordExists = true;
        }
        else {
            printf("        ������������������������������������������������������������������������������\n");
            printf("        ��     ��й�ȣ�� �����Ͻðڽ��ϱ�?    ��\n");
            printf("        ������������������������������������������������������������������������������\n");
            printf("        ������������������������������������������������������������������������������\n");
            printf("        ��     �Է�(y/n) :                     ��\n");
            printf("        ������������������������������������������������������������������������������\n");
            GotoXY(26, 4);
            scanf(" %c", &choice);
            system("cls");

            if (choice == 'y' || choice == 'Y') {
                changePassword();
                break;
            }
            else if (choice == 'n' || choice == 'N') {
                printf("        ������������������������������������������������������������������������������\n");
                printf("        ��         ó������ ���ư��ϴ�         ��\n");
                printf("        ������������������������������������������������������������������������������\n");
                Sleep(1500);
                break;
            }
        }
    }

}

int menu_ui() {
    char currentPassword[PASSWORD_LENGTH], newPassword[PASSWORD_LENGTH];
    system("cls");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��                �޴�                 ��\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��              1. �ϱ�                ��\n");
    printf("        ��              2. �÷���              ��\n");
    printf("        ��              3. �ҷ�����            ��\n");
    printf("        ��              4. ����                ��\n");
    printf("        ��              5. ����                ��\n");
    printf("        ������������������������������������������������������������������������������\n");

    int menu, day, view_select;
    printf("        ������������������������������������������������������������������������������\n");
    printf("        ��        �Է� :                       ��\n");
    printf("        ������������������������������������������������������������������������������\n");
    GotoXY(24, 11);
    scanf("%d", &menu);
    system("cls");
    int month = 0, year = 2023;
    int monthf;
    switch (menu) {
    case 1:
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��              �ϱ� �޴�              ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��       ���� �Է��ϼ��� :             ��\n");
        printf("        ��       �ϸ� �Է��ϼ��� :             ��\n", MAX_DAYS_IN_MONTH);
        printf("        ������������������������������������������������������������������������������\n");
        GotoXY(34, 4);
        scanf("%d", &month);
        GotoXY(34, 5);
        scanf("%d", &day);
        system("cls");
        writeDiary(day, month);
        break;
    case 2:
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��             �÷��� �޴�             ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��       ���� �Է��ϼ��� :             ��\n");
        printf("        ��       �ϸ� �Է��ϼ��� :             ��\n", MAX_DAYS_IN_MONTH);
        printf("        ������������������������������������������������������������������������������\n");
        GotoXY(34, 4);
        scanf("%d", &month);
        GotoXY(34, 5);
        scanf("%d", &day);
        system("cls");
        writePlanner(day, month);
        break;
    case 3:
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��           �ҷ����� �޴�             ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��     ��й�ȣ�� �Է��ϼ���:          ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        GotoXY(37, 4);
        scanf("%s", currentPassword);
        system("cls");
        if (!checkPassword(currentPassword)) {
            printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
            Sleep(2000);
            break;
        }
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��           �ҷ����� �޴�             ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��     �⵵�� �Է����ּ��� :           ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        GotoXY(36, 4);
        scanf("%d", &year);
        printf("\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��     ���� �Է����ּ��� :             ��\n", MAX_DAYS_IN_MONTH);
        printf("        ������������������������������������������������������������������������������\n");
        GotoXY(34, 7);
        scanf("%d", &month);
        system("cls");

        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��            �ҷ����� �޴�            ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        FinalCalendar(year, month);
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��       ��¥�� �Է����ּ��� :         ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        GotoXY(38, 16);
        scanf("%d", &day);
        system("cls");

        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��            �ҷ����� �޴�            ��\n");
        printf("        ������������������������������������������������������������������������������\n");

        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��   1. �ϱ� Ȯ��  ��  2. �÷��� Ȯ��   ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��        �Է� :                       ��\n");
        printf("        ������������������������������������������������������������������������������\n");
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
        printf("        ������������������������������������������������������������������������������\n");
        printf("        ��       ���α׷��� �����մϴ�         ��\n");
        printf("        ������������������������������������������������������������������������������\n");
        exit(0);
    }
}

int main() {
    while (1) {
        menu_ui();
    }

    return 0;
}

