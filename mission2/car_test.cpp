#ifdef _DEBUG

#include "car.cpp"
#include "gmock/gmock.h"

using namespace testing;

// set functions

TEST(Group, TC1) {
	Car car;

	car.setCarType(SEDAN);

	EXPECT_EQ(car.carType, SEDAN);
}

TEST(Group, TC2) {
	Car car;

	car.setEngine(TOYOTA);

	EXPECT_EQ(car.engine, TOYOTA);
}

TEST(Group, TC3) {
	Car car;

	car.setBrakeSystem(MANDO);

	EXPECT_EQ(car.brakeSystem, MANDO);
}

TEST(Group, TC4) {
	Car car;

	car.setSteeringSystem(BOSCH_S);

	EXPECT_EQ(car.steeringSystem, BOSCH_S);
}

// validCheck()
TEST(validGroup, TC1) {
	Car car;

	car.setCarType(SEDAN);
	car.setEngine(GM);
	car.setBrakeSystem(MANDO);
	car.setSteeringSystem(MOBIS);

	int ret = car.validCheck(0);

	EXPECT_EQ(ret, true);
}

TEST(validGroup, TC2) {
	Car car;

	//SUV + TOYOTA fail
	car.setCarType(SUV);
	car.setEngine(TOYOTA);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.validCheck(0);

	EXPECT_EQ(ret, false);
}

TEST(validGroup, TC3) {
	Car car;

	//TRUCK + WIA fail
	car.setCarType(TRUCK);
	car.setEngine(WIA);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.validCheck(0);

	EXPECT_EQ(ret, false);
}

TEST(validGroup, TC4) {
	Car car;

	//SEDAN + CONTINENTAL fail
	car.setCarType(SEDAN);
	car.setEngine(WIA);
	car.setBrakeSystem(CONTINENTAL);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.validCheck(0);

	EXPECT_EQ(ret, false);
}

TEST(validGroup, TC5) {
	Car car;

	//TRUCK + MANDO fail
	car.setCarType(TRUCK);
	car.setEngine(TOYOTA);
	car.setBrakeSystem(MANDO);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.validCheck(0);

	EXPECT_EQ(ret, false);
}

TEST(validGroup, TC6) {
	Car car;

	//BOSCH_B + non BOSCH fail
	car.setCarType(SEDAN);
	car.setEngine(GM);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(MOBIS);

	int ret = car.validCheck(0);

	EXPECT_EQ(ret, false);
}


// run()
TEST(combiGroup, TC1) {
	Car car;

	car.setCarType(SEDAN);
	car.setEngine(GM);
	car.setBrakeSystem(MANDO);
	car.setSteeringSystem(MOBIS);

	int ret = car.run();

	EXPECT_EQ(ret, true);
}

TEST(combiGroup, TC2) {
	Car car;

	//SUV + TOYOTA fail
	car.setCarType(SUV);
	car.setEngine(TOYOTA);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.run();

	EXPECT_EQ(ret, false);
}

TEST(combiGroup, TC3) {
	Car car;

	//TRUCK + WIA fail
	car.setCarType(TRUCK);
	car.setEngine(WIA);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.run();

	EXPECT_EQ(ret, false);
}

TEST(combiGroup, TC4) {
	Car car;

	//SEDAN + CONTINENTAL fail
	car.setCarType(SEDAN);
	car.setEngine(WIA);
	car.setBrakeSystem(CONTINENTAL);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.run();

	EXPECT_EQ(ret, false);
}

TEST(combiGroup, TC5) {
	Car car;

	//TRUCK + MANDO fail
	car.setCarType(TRUCK);
	car.setEngine(TOYOTA);
	car.setBrakeSystem(MANDO);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.run();

	EXPECT_EQ(ret, false);
}

TEST(combiGroup, TC6) {
	Car car;

	//BOSCH_B + non BOSCH fail
	car.setCarType(SEDAN);
	car.setEngine(GM);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(MOBIS);

	int ret = car.run();

	EXPECT_EQ(ret, false);
}

TEST(combiGroup, TC7) {
	Car car;

	car.setEngine(END_Engine);

	int ret = car.run();

	EXPECT_EQ(ret, false);
}


// test()
TEST(combiGroupTestMode, TC1) {
	Car car;

	car.setCarType(SEDAN);
	car.setEngine(GM);
	car.setBrakeSystem(MANDO);
	car.setSteeringSystem(MOBIS);

	int ret = car.test();

	EXPECT_EQ(ret, true);
}

TEST(combiGroupTestMode, TC2) {
	Car car;

	//SUV + TOYOTA fail
	car.setCarType(SUV);
	car.setEngine(TOYOTA);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.test();

	EXPECT_EQ(ret, false);
}

TEST(combiGroupTestMode, TC3) {
	Car car;

	//TRUCK + WIA fail
	car.setCarType(TRUCK);
	car.setEngine(WIA);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.test();

	EXPECT_EQ(ret, false);
}

TEST(combiGroupTestMode, TC4) {
	Car car;

	//SEDAN + CONTINENTAL fail
	car.setCarType(SEDAN);
	car.setEngine(WIA);
	car.setBrakeSystem(CONTINENTAL);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.test();

	EXPECT_EQ(ret, false);
}

TEST(combiGroupTestMode, TC5) {
	Car car;

	//TRUCK + MANDO fail
	car.setCarType(TRUCK);
	car.setEngine(TOYOTA);
	car.setBrakeSystem(MANDO);
	car.setSteeringSystem(BOSCH_S);

	int ret = car.test();

	EXPECT_EQ(ret, false);
}

TEST(combiGroupTestMode, TC6) {
	Car car;

	//BOSCH_B + non BOSCH fail
	car.setCarType(SEDAN);
	car.setEngine(GM);
	car.setBrakeSystem(BOSCH_B);
	car.setSteeringSystem(MOBIS);

	int ret = car.test();

	EXPECT_EQ(ret, false);
}

#endif
