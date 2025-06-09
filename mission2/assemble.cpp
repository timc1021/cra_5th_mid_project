#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "assemble.h"

using namespace std;

#define CLEAR_SCREEN "\033[H\033[2J"


#ifdef _DEBUG
#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else
#include "car.cpp"

int process_answer(Car &car, int step, int answer);
void delay(int ms);

void request_input(const Car &car, const int step);
void get_input(char  buf[100]);
int check_answer(char* no_number_str, const int step, const int answer);

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

void request_input(const Car &car, const int step)
{
    int i;
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
        for (i = 1; i < END_CarType; i++) {
            std::cout << i << ". " << car.CarTypeTable[i].name << std::endl;
        }
    }
    else if (step == Engine_Question)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ ž���ұ��?\n");
        printf("0. �ڷΰ���\n");
        for (i = 1; i < END_Engine; i++) {
            std::cout << i << ". " << car.EngineTable[i].name << std::endl;
        }
        std::cout << i << ". ���峭 ����" << std::endl;
    }
    else if (step == brakeSystem_Question)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        for (i = 1; i < END_BrakeSystem; i++) {
            std::cout << i << ". " << car.BrakeSystemTable[i].name << std::endl;
        }
    }
    else if (step == SteeringSystem_Question)
    {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n");
        printf("0. �ڷΰ���\n");
        for (i = 1; i < END_SteeringSystem; i++) {
            std::cout << i << ". " << car.SteeringSystemTable[i].name << std::endl;
        }
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

    if (step == CarType_Question && !(answer >= 1 && answer < END_CarType))
    {
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return 3;
    }

    if (step == Engine_Question && !(answer >= 0 && answer <= END_Engine))
    {
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
        delay(800);
        return 3;
    }

    if (step == brakeSystem_Question && !(answer >= 0 && answer < END_BrakeSystem))
    {
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
        delay(800);
        return 3;
    }

    if (step == SteeringSystem_Question && !(answer >= 0 && answer < END_SteeringSystem))
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

int process_answer(Car& car, int step, const int answer)
{
    int next_step = step;

    if (step == CarType_Question)
    {
        car.setCarType(answer);
        delay(800);
        next_step = Engine_Question;
    }
    else if (step == Engine_Question)
    {
        car.setEngine(answer);
        delay(800);
        next_step = brakeSystem_Question;
    }
    else if (step == brakeSystem_Question)
    {
        car.setBrakeSystem(answer);
        delay(800);
        next_step = SteeringSystem_Question;
    }
    else if (step == SteeringSystem_Question)
    {
        car.setSteeringSystem(answer);
        delay(800);
        next_step = Run_Test;
    }
    else if (step == Run_Test && answer == 1)
    {
        car.run();
        delay(2000);
    }
    else if (step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        car.test();
        delay(2000);
    }

    return next_step;
}

int main()
{
    char buf[100];
    int step = CarType_Question;
    Car car;

    while (1)
    {
        request_input(car, step);

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

        step = process_answer(car, step, answer);
    }

    return 0;
}

#endif