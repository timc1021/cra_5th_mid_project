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
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Question)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }
    else if (step == brakeSystem_Question)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Question)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");
}

void get_input(char  buf[100])
{
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

int check_answer(char* no_number_str, const int step, const int answer)
{
    int retFlag = 1;

    // 입력받은 문자가 숫자가 아니라면
    if (*no_number_str != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return 3;
    }

    if (step == CarType_Question && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return 3;
    }

    if (step == Engine_Question && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        delay(800);
        return 3;
    }

    if (step == brakeSystem_Question && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        delay(800);
        return 3;
    }

    if (step == SteeringSystem_Question && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        delay(800);
        return 3;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
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
            printf("바이바이\n");
            break;
        }

        char* no_number_str;
        int answer = strtol(buf, &no_number_str, 10); // 문자열을 10진수로 변환

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
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    car_info[Engine_Question] = answer;
    if (answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    car_info[brakeSystem_Question] = answer;
    if (answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    car_info[SteeringSystem_Question] = answer;
    if (answer == 1)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("MOBIS 제동장치를 선택하셨습니다.\n");
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
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (car_info[Engine_Question] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
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

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (car_info[CarType_Question] == SEDAN && car_info[brakeSystem_Question] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (car_info[CarType_Question] == SUV && car_info[Engine_Question] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (car_info[CarType_Question] == TRUCK && car_info[Engine_Question] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (car_info[CarType_Question] == TRUCK && car_info[brakeSystem_Question] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (car_info[brakeSystem_Question] == BOSCH_B && car_info[SteeringSystem_Question] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}