#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int car_info[10];

void selectCarType(int answer);
int process_answer(int step, int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

void request_input(const int step);
void get_input(char  buf[100]);
int check_answer(char* no_number_str, const int step, const int answer);

enum QuestionType
{
    CarType_Question,
    Engine_Question,
    brakeSystem_Question,
    SteeringSystem_Question,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void request_input(const int step)
{
    if (step == CarType_Question)
    {
        printf(CLEAR_SCREEN);

        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Question)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. ���峭 ����\n");
    }
    else if (step == brakeSystem_Question)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Question)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("0. ó�� ȭ������ ���ư���\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");
}

void get_input(char  buf[100])
{
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // ���� ���๮�� ����
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

int check_answer(char* no_number_str, const int step, const int answer)
{
    int retFlag = 1;

    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*no_number_str != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        delay(800);
        return 3;
    }

    if (step == CarType_Question && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return 3;
    }

    if (step == Engine_Question && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delay(800);
        return 3;
    }

    if (step == brakeSystem_Question && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return 3;
    }

    if (step == SteeringSystem_Question && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
        delay(800);
        return 3;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
        delay(800);
        return 3;
    }
    return retFlag;
}

int process_answer(int step, const int answer)
{
    int next_step = step;

    if (step == CarType_Question)
    {
        selectCarType(answer);
        delay(800);
        next_step = Engine_Question;
    }
    else if (step == Engine_Question)
    {
        selectEngine(answer);
        delay(800);
        next_step = brakeSystem_Question;
    }
    else if (step == brakeSystem_Question)
    {
        selectbrakeSystem(answer);
        delay(800);
        next_step = SteeringSystem_Question;
    }
    else if (step == SteeringSystem_Question)
    {
        selectSteeringSystem(answer);
        delay(800);
        next_step = Run_Test;
    }
    else if (step == Run_Test && answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }

    return next_step;
}

int main()
{
    char buf[100];
    int step = CarType_Question;

    while (1)
    {
        request_input(step);

        get_input(buf);

        if (!strcmp(buf, "exit"))
        {
            printf("���̹���\n");
            break;
        }

        char* no_number_str;
        int answer = strtol(buf, &no_number_str, 10); // ���ڿ��� 10������ ��ȯ

        int retFlag = check_answer(no_number_str, step, answer);
        if (retFlag == 3) continue;

        if (answer == 0)
        {
            if (step == Run_Test) {
                step = CarType_Question;
                continue;
            }

            if (step >= 1)
            {
                step -= 1;
                continue;
            }
        }

        step = process_answer(step, answer);
    }
}

void selectCarType(int answer)
{
    car_info[CarType_Question] = answer;
    if (answer == 1)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    car_info[Engine_Question] = answer;
    if (answer == 1)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    car_info[brakeSystem_Question] = answer;
    if (answer == 1)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    car_info[SteeringSystem_Question] = answer;
    if (answer == 1)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

int isValidCheck()
{
    if (car_info[CarType_Question] == SEDAN && car_info[brakeSystem_Question] == CONTINENTAL)
    {
        return false;
    }
    else if (car_info[CarType_Question] == SUV && car_info[Engine_Question] == TOYOTA)
    {
        return false;
    }
    else if (car_info[CarType_Question] == TRUCK && car_info[Engine_Question] == WIA)
    {
        return false;
    }
    else if (car_info[CarType_Question] == TRUCK && car_info[brakeSystem_Question] == MANDO)
    {
        return false;
    }
    else if (car_info[brakeSystem_Question] == BOSCH_B && car_info[SteeringSystem_Question] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (car_info[Engine_Question] == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            if (car_info[CarType_Question] == 1)
                printf("Car Type : Sedan\n");
            if (car_info[CarType_Question] == 2)
                printf("Car Type : SUV\n");
            if (car_info[CarType_Question] == 3)
                printf("Car Type : Truck\n");
            if (car_info[Engine_Question] == 1)
                printf("Engine : GM\n");
            if (car_info[Engine_Question] == 2)
                printf("Engine : TOYOTA\n");
            if (car_info[Engine_Question] == 3)
                printf("Engine : WIA\n");
            if (car_info[brakeSystem_Question] == 1)
                printf("Brake System : Mando");
            if (car_info[brakeSystem_Question] == 2)
                printf("Brake System : Continental\n");
            if (car_info[brakeSystem_Question] == 3)
                printf("Brake System : Bosch\n");
            if (car_info[SteeringSystem_Question] == 1)
                printf("SteeringSystem : Bosch\n");
            if (car_info[SteeringSystem_Question] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (car_info[CarType_Question] == SEDAN && car_info[brakeSystem_Question] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (car_info[CarType_Question] == SUV && car_info[Engine_Question] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (car_info[CarType_Question] == TRUCK && car_info[Engine_Question] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (car_info[CarType_Question] == TRUCK && car_info[brakeSystem_Question] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (car_info[brakeSystem_Question] == BOSCH_B && car_info[SteeringSystem_Question] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}