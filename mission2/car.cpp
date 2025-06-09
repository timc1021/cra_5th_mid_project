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
        cout << "차량 타입으로 " << CarTypeTable[type].name << "을 선택하셨습니다." << std::endl;
        this->carType = type;
    }
    void setEngine(int engine) {
        cout << EngineTable[engine].name << " 엔진을 선택하셨습니다." << std::endl;
        this->engine = engine;
    }
    void setBrakeSystem(int brakeSystem) {
        cout << BrakeSystemTable[brakeSystem].name << " 제동장치를 선택하셨습니다." << std::endl;
        this->brakeSystem = brakeSystem;
    }
    void setSteeringSystem(int steeringSystem) {
        cout << SteeringSystemTable[steeringSystem].name << " 조향장치를 선택하셨습니다." << std::endl;
        this->steeringSystem = steeringSystem;
    }

    int validCheck(int test_mode) {
        int ret = false;

        if (this->carType == SEDAN && this->brakeSystem == CONTINENTAL)
        {
            if (test_mode == TEST_MODE) {
                printf("자동차 부품 조합 테스트 결과 : FAIL\n");
                printf("Sedan에는 Continental제동장치 사용 불가\n");
            }
        }
        else if (this->carType == SUV && this->engine == TOYOTA)
        {
            if (test_mode == TEST_MODE) {
                printf("자동차 부품 조합 테스트 결과 : FAIL\n");
                printf("SUV에는 TOYOTA엔진 사용 불가\n");
            }
        }
        else if (this->carType == TRUCK && this->engine == WIA)
        {
            if (test_mode == TEST_MODE) {
                printf("자동차 부품 조합 테스트 결과 : FAIL\n");
                printf("Truck에는 WIA엔진 사용 불가\n");
            }
        }
        else if (this->carType == TRUCK && this->brakeSystem == MANDO)
        {
            if (test_mode == TEST_MODE) {
                printf("자동차 부품 조합 테스트 결과 : FAIL\n");
                printf("Truck에는 Mando제동장치 사용 불가\n");
            }
        }
        else if (this->brakeSystem == BOSCH_B && this->steeringSystem != BOSCH_S)
        {
            if (test_mode == TEST_MODE) {
                printf("자동차 부품 조합 테스트 결과 : FAIL\n");
                printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
            }
        }
        else
        {
            if (test_mode == TEST_MODE) {
                printf("자동차 부품 조합 테스트 결과 : PASS\n");
            }
            ret = true;
        }

        return ret;
    }

    int run() {
        int ret = this->validCheck(RUN_MODE);
        if (ret == false)
        {
            printf("자동차가 동작되지 않습니다\n");
        }
        else
        {
            if (this->engine == END_Engine)
            {
                printf("엔진이 고장나있습니다.\n");
                printf("자동차가 움직이지 않습니다.\n");
                ret = false;
            }
            else
            {
                cout << "Car Type : " << CarTypeTable[this->carType].name << std::endl;
                cout << "Engine : " << EngineTable[this->engine].name << std::endl;
                cout << "Brake System : " << BrakeSystemTable[this->brakeSystem].name << std::endl;
                cout << "Steering System : " << SteeringSystemTable[this->steeringSystem].name << std::endl;
                printf("자동차가 동작됩니다.\n");
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