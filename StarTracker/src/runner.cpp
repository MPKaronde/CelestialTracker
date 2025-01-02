#include <Arduino.h>
#include <AccelStepper.h>
#include <QMC5883LCompass.h>
#include <Wire.h>
#define HALFSTEP 4

// (1 / 1.8) Steps per degree for motor * gear ratio
double YAW_STEPS_PER_DEGREE = 4.6 / 2.0;    //(1 / 1.8) * (30 / 120);
double PITCH_STEPS_PER_DEGREE = 4.45 / 2.0; //(1 / 1.8) * (30 / 110);

// Hardware
AccelStepper pitchMotor(HALFSTEP, 8, 9, 10, 11);
AccelStepper yawMotor(HALFSTEP, 2, 3, 4, 5);
QMC5883LCompass compass;

// Motor Constants
int MAX_SPEED = 1000;
int ACCELERATION = 1000000;

// current position (measured in degrees from last zero)
double currentPitch;
double currentYaw;

// zero axises out
// TODO: add bump switches and automatic zeroing
void zeroAxis()
{
    currentPitch = 0;
    currentYaw = 0;
}

// arduino setup code
void setup()
{
    Serial.begin(9600);
    Wire.begin();
    compass.init();
    compass.setMagneticDeclination(3, 8);
    compass.setSmoothing(10, true);

    pitchMotor.setMaxSpeed(MAX_SPEED);
    pitchMotor.setAcceleration(ACCELERATION);
    yawMotor.setMaxSpeed(MAX_SPEED);
    yawMotor.setAcceleration(ACCELERATION);

    zeroAxis();
}

// rotates pitch by degrees
// TODO: add limit functionality (stop from going over limits)
boolean rotatePitchByDegrees(double deg)
{
    pitchMotor.setCurrentPosition(0);
    pitchMotor.moveTo(deg * PITCH_STEPS_PER_DEGREE);

    while (pitchMotor.distanceToGo() != 0)
    {
        pitchMotor.run();
    }

    currentPitch += deg;
    return true;
}

// rotates yaw by degrees
// TODO: add limit functionality (stop from going over limits)
boolean rotateYawByDegrees(double deg)
{
    yawMotor.setCurrentPosition(0);
    yawMotor.moveTo(deg * YAW_STEPS_PER_DEGREE);

    while (yawMotor.distanceToGo() != 0)
    {
        yawMotor.run();
    }

    currentYaw += deg;
    return true;
}

// returns current azimuth from compass
int getAzimuth()
{
    compass.read();
    return compass.getAzimuth();
}

// point to given coordinates
boolean pointInDirection(double targetYaw, double targetPitch)
{
    boolean done = true;

    if (!rotateYawByDegrees(targetYaw - currentYaw))
    {
        done = false;
    }

    // move to appropriate pitch
    if (!rotatePitchByDegrees(targetPitch - currentPitch))
    {
        done = false;
    }

    return done;
}

void commands()
{
    String in = Serial.readString();
    Serial.println("go");

    // rotate yaw by degrees
    if (in.equals("y"))
    {
        Serial.println("recognized");
        String amt = Serial.readString();
        double deg = amt.toDouble();
        rotateYawByDegrees(deg);
    }

    // rotate pitch by degrees
    else if (in.equals("p"))
    {
        Serial.println("recognized");
        String amt = Serial.readString();
        double deg = amt.toDouble();
        rotatePitchByDegrees(deg);
    }

    // point in direction
    else if (in.equals("pid"))
    {
        Serial.println("recognized");
        String sec = Serial.readString();
        double yaw = sec.toDouble();
        sec = Serial.readString();
        double pitch = sec.toDouble();
        pointInDirection(yaw, pitch);
    }

    // zero axis
    else if (in.equals("z"))
    {
        Serial.println("recognized");
        zeroAxis();
    }

    // print debug output
    else if (in.equals("d"))
    {
        Serial.print("current pitch: ");
        Serial.println(currentPitch);
        Serial.print("currentYaw: ");
        Serial.println(currentYaw);
        delay(5000);
    }

    // command not recognized
    else
    {
        Serial.println("ERROR: unknown command");
    }
}

void loop()
{
    commands();
}
