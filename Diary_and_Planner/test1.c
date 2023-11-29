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
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s", diaries[day - 1][month - 1].content);
    fclose(file);
    printf("%d�� %d���� �ϱⰡ ���Ͽ� ����Ǿ����ϴ�.\n", month, day);
}

void writePlannerToFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s", planners[day - 1][month - 1].content);
    fclose(file);
    printf("%d�� %d���� �÷��ʰ� ���Ͽ� ����Ǿ����ϴ�.\n", month, day);
}

void viewDiaryFromFile(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
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

    FILE *file = fopen(filename, "r");
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
    printf("%d�� %d���� �ϱ⸦ ������ (�ִ� %d����):\n", month, day, MAX_LENGTH);
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writeDiaryToFile(day, month);
    printf("%d�� %d���� �ϱⰡ ����Ǿ����ϴ�.\n", month, day);
}

void writePlanner(int day, int month) {
    printf("%d�� %d���� �÷��ʸ� ������ (�ִ� %d����):\n", month, day, MAX_LENGTH);
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);
    writePlannerToFile(day, month);
    printf("%d�� %d���� �÷��ʰ� ����Ǿ����ϴ�.\n", month, day);
}

void modifyDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �ϱⰡ �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);

    printf("������ ������ �Է��ϼ��� (�ִ� %d����):\n", MAX_LENGTH);
    getchar();
    fgets(diaries[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writeDiaryToFile(day, month);

    printf("%d�� %d���� �ϱⰡ �����Ǿ����ϴ�.\n", month, day);
}

void modifyPlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �÷��ʰ� �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);

    printf("������ ������ �Է��ϼ��� (�ִ� %d����):\n", MAX_LENGTH);
    getchar();
    fgets(planners[day - 1][month - 1].content, MAX_LENGTH, stdin);

    writePlannerToFile(day, month);

    printf("%d�� %d���� �÷��ʰ� �����Ǿ����ϴ�.\n", month, day);
}

void deleteDiary(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-diary.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �ϱⰡ �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        printf("%d�� %d���� �ϱⰡ �����Ǿ����ϴ�.\n", month, day);
    } else {
        printf("���� ����: ������ ã�� �� �����ϴ�.\n");
    }
}

void deletePlanner(int day, int month) {
    char filename[MAX_LENGTH];
    sprintf(filename, "%d-%d-planner.txt", month, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("%d�� %d�Ͽ� �÷��ʰ� �����ϴ�.\n", month, day);
        return;
    }

    fclose(file);

    if (remove(filename) == 0) {
        printf("%d�� %d���� �÷��ʰ� �����Ǿ����ϴ�.\n", month, day);
    } else {
        printf("���� ����: ������ ã�� �� �����ϴ�.\n");
    }
}

void viewDiary(int day, int month) {
    char choice;
    viewDiaryFromFile(day, month);

    printf("���� �Ǵ� �����Ͻðڽ��ϱ�? (m/d/n): ");
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
    printf("���� �Ǵ� �����Ͻðڽ��ϱ�? (m/d/n): ");
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
        printf("������ �� �� �����ϴ�.\n");
        return false;
    }

    fgets(password, PASSWORD_LENGTH, file);
    fclose(file);

    if (strcmp(inputPassword, password) == 0) {
        return true; // ��й�ȣ ��ġ
    } else {
        return false; // ��й�ȣ ����ġ
    }
}

void setPassword() {
    char newPassword[PASSWORD_LENGTH];
    printf("��й�ȣ�� �Է��ϼ��� (4�ڸ� ����): ");
    scanf("%s", newPassword);

    FILE *file = fopen("password.txt", "w");
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

    printf("���� ��й�ȣ�� �Է��ϼ���: ");
    scanf("%s", currentPassword);

    if (!checkPassword(currentPassword)) {
        printf("��ġ���� �ʽ��ϴ�.\n");
        return;
    }

    printf("�� ��й�ȣ�� �Է��ϼ��� (4�ڸ� ����): ");
    scanf("%s", newPassword);

    FILE *file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s", newPassword);
    fclose(file);
    printf("��й�ȣ�� ����Ǿ����ϴ�.\n");
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
            printf("��й�ȣ�� �����Ͻðڽ��ϱ�? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                setPassword();
            } else if (choice == 'n' || choice == 'N') {
                printf("ó������ ���ư��ϴ�..\n");
                break;
            }
            passwordExists = true;
        } else {
            printf("��й�ȣ�� �����Ͻðڽ��ϱ�? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                changePassword();
            } else if (choice == 'n' || choice == 'N') {
                printf("ó������ ���ư��ϴ�..\n");
                break;
            }
        }
    }

}

int menu_ui(){
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
	int month = 1, year = 2023;
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
            scanf("%d", &monthf);
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
            scanf("%d", &monthf);
            GotoXY(34, 5);
        	scanf("%d", &day);
            system("cls");
            writePlanner(day, month);
            break;
        case 3:
            printf("        ������������������������������������������������������������������������������\n");
            printf("        ��             ���� �޴�               ��\n");
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
            
        	printCalendar(year, month);
        	printf("��¥�� �����ϼ��� : ", MAX_DAYS_IN_MONTH);
        	scanf("%d", &day);
        	printf("1. �ϱ� Ȯ��\n2. �÷��� Ȯ��\n==>");
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
        	printf("���α׷��� �����մϴ�.");
			exit(0);
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �������ּ���.\n");
    }
}

int main() {
    while(1){
    	menu_ui();
	}

    return 0;
}

