#pragma once

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
    TRUCK,
    END_CarType,
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    END_Engine,
};

enum BrakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    END_BrakeSystem
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS,
    END_SteeringSystem
};
