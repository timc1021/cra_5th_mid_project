#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "assemble.h"

using namespace std;

struct name_table {
    int enum_value;
    string name;
};

enum TestMode {
    RUN_MODE,
    TEST_MODE
};

class Car {
public:
    name_table CarTypeTable[END_CarType] = {
        {0, "invaild"},
        {SEDAN, "Sedan"},
        {SUV, "SUV"},
        {TRUCK, "Truck"},
    };

    name_table EngineTable[END_Engine] = {
        {0, "back"},
        {GM, "GM"},
        {TOYOTA, "TOYOTA"},
        {WIA, "WIA"},
    };

    name_table BrakeSystemTable[END_BrakeSystem] = {
        {0, "back"},
        {MANDO, "MANDO"},
        {CONTINENTAL, "CONTINENTAL"},
        {BOSCH_B, "BOSCH"},
    };

    name_table SteeringSystemTable[END_SteeringSystem] = {
        {0, "back"},
        {BOSCH_S, "BOSCH"},
        {MOBIS, "MOBIS"},
    };

    void setCarType(int type) {
        cout << "���� Ÿ������ " << CarTypeTable[type].name << "�� �����ϼ̽��ϴ�." << std::endl;
        this->carType = type;
    }
    void setEngine(int engine) {
        cout << EngineTable[engine].name << " ������ �����ϼ̽��ϴ�." << std::endl;
        this->engine = engine;
    }
    void setBrakeSystem(int brakeSystem) {
        cout << BrakeSystemTable[brakeSystem].name << " ������ġ�� �����ϼ̽��ϴ�." << std::endl;
        this->brakeSystem = brakeSystem;
    }
    void setSteeringSystem(int steeringSystem) {
        cout << SteeringSystemTable[steeringSystem].name << " ������ġ�� �����ϼ̽��ϴ�." << std::endl;
        this->steeringSystem = steeringSystem;
    }

    int validCheck(int test_mode) {
        int ret = false;

        if (this->carType == SEDAN && this->brakeSystem == CONTINENTAL)
        {
            if (test_mode == TEST_MODE) {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                printf("Sedan���� Continental������ġ ��� �Ұ�\n");
            }
        }
        else if (this->carType == SUV && this->engine == TOYOTA)
        {
            if (test_mode == TEST_MODE) {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                printf("SUV���� TOYOTA���� ��� �Ұ�\n");
            }
        }
        else if (this->carType == TRUCK && this->engine == WIA)
        {
            if (test_mode == TEST_MODE) {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                printf("Truck���� WIA���� ��� �Ұ�\n");
            }
        }
        else if (this->carType == TRUCK && this->brakeSystem == MANDO)
        {
            if (test_mode == TEST_MODE) {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                printf("Truck���� Mando������ġ ��� �Ұ�\n");
            }
        }
        else if (this->brakeSystem == BOSCH_B && this->steeringSystem != BOSCH_S)
        {
            if (test_mode == TEST_MODE) {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
                printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
            }
        }
        else
        {
            if (test_mode == TEST_MODE) {
                printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
            }
            ret = true;
        }

        return ret;
    }

    int run() {
        int ret = this->validCheck(RUN_MODE);
        if (ret == false)
        {
            printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        }
        else
        {
            if (this->engine == END_Engine)
            {
                printf("������ ���峪�ֽ��ϴ�.\n");
                printf("�ڵ����� �������� �ʽ��ϴ�.\n");
                ret = false;
            }
            else
            {
                cout << "Car Type : " << CarTypeTable[this->carType].name << std::endl;
                cout << "Engine : " << EngineTable[this->engine].name << std::endl;
                cout << "Brake System : " << BrakeSystemTable[this->brakeSystem].name << std::endl;
                cout << "Steering System : " << SteeringSystemTable[this->steeringSystem].name << std::endl;
                printf("�ڵ����� ���۵˴ϴ�.\n");
            }
        }

        return ret;
    }

    int test() {
        return this->validCheck(TEST_MODE);
    }

#ifndef _DEBUG
private:
#endif
    int carType;
    int engine;
    int brakeSystem;
    int steeringSystem;
};