#include "main.h"

using namespace okapi;

Motor rightFront(rightFrontPort, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBack(rightBackPort, true , AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftFront(leftFrontPort, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftBack(leftBackPort, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftHigh(highLeftPort, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightHigh(highRightPort, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

IMU inertial_sensor(IMUPort, IMUAxes::z);
IMU inertial_sensor2(IMUport2, IMUAxes::z);

std::shared_ptr<ChassisController> drive =
  ChassisControllerBuilder()
  .withMotors({leftFront, leftBack, leftHigh}, {rightFront, rightBack, rightHigh})
  .withDimensions(AbstractMotor::gearset::blue, {{4_in, 10_in}, imev5BlueTPR})
  .build();

  typedef struct PID pid;

  pid translate;
  pid rotate;
  pid jankLeft;
  pid jankRight;

  double inertial_values;
  double error;
  double threshold;
  double integral;
  double derivative;
  double prevError;
  double kP;
  double ki;
  double kd;
  double p;
  double i;
  double d;
  double vel;
  double inertial_value;
  double derivative1;
  double derivative2;

  int timer;
  int brakeMode;

  int holdButton = 0;

void updateDrive()
{
  drive -> getModel() -> arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::leftX));

  if (controller.getDigital(ControllerDigital::A) == 1 && holdButton == 0)
  {
    rightFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    rightBack.setBrakeMode(AbstractMotor::brakeMode::hold);
    leftFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    leftBack.setBrakeMode(AbstractMotor::brakeMode::hold);
    leftHigh.setBrakeMode(AbstractMotor::brakeMode::hold);
    rightHigh.setBrakeMode(AbstractMotor::brakeMode::hold);
    holdButton = 1;
  }
  else if (controller.getDigital(ControllerDigital::A) == 1 && holdButton == 1)
  {
    rightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightBack.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftBack.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftHigh.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightHigh.setBrakeMode(AbstractMotor::brakeMode::coast);
    holdButton = 0;
  }

}




void translatePID(double distance, int ms)
{
  timer = 0;
  inertial_sensor.reset();
	drive -> getModel() -> setEncoderUnits(AbstractMotor::encoderUnits::degrees);

	translate.target = distance * (360 / (2 * 3.1415 * (4 / 2)));

	//PID constants
	translate.kP = 0.0045;
	translate.kI = 0;
	translate.kD = 0.0002;

	auto translateController = IterativeControllerFactory::posPID(translate.kP, translate.kI, translate.kD);

	drive -> getModel() -> resetSensors();

	while (timer < ms)
	{

    inertial_value = inertial_sensor.get();
		translate.error = translate.target - ((drive -> getModel() -> getSensorVals()[0] + drive -> getModel() -> getSensorVals()[1])/2 * 18 / 35);
		translate.power = translateController.step(translate.error);

    drive -> getModel() -> tank(-translate.power, -translate.power);

    if (abs(translate.error) < 6  && (rightFront.getActualVelocity() < 0.5 && rightBack.getActualVelocity() < 0.5 && leftFront.getActualVelocity() < 0.5 && leftBack.getActualVelocity() < 0.5))
		{
			break;
		}

    timer += 10;
		pros::delay(10);
	}

	drive -> getModel() -> tank(0, 0);
}

void rotatePID(double target, int ms)
{
  inertial_sensor.reset();
  timer = 0;
  error = target;
  threshold = 3;
  kP = 0.016;  //0.0158
  ki = 0.00003;
  kd = 0.0084;


  while (timer < ms)
  {
    error = target - inertial_sensor.get();
    integral = integral + error;
    derivative = error - prevError;
    prevError = error;
    p = error * kP;
    i = error * ki;
    d = error * kd;

    vel = p + i + d;

    drive -> getModel() -> tank(vel, -vel);

    if(abs(error) < threshold && rightFront.getActualVelocity() < 1 && rightBack.getActualVelocity() < 1 && leftFront.getActualVelocity() < 1 && leftBack.getActualVelocity() < 1)
    {
      break;
    }

    timer += 10;
    pros::delay(10);

  }
}
