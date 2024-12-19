// #include <Arduino.h>
// #include <AccelStepper.h>
// #define HALFSTEP 4

// // Motors
// AccelStepper x(HALFSTEP, 2, 3, 4, 5);
// AccelStepper y(HALFSTEP, 6, 7, 8, 9);

// // Motor Parameters
// const int MAX_SPEED = 1200;
// const int MIN_SPEED = 800;
// const int ACCELERATION = 1000000;

// // Rotation Translation Values
// const int X_STEPS_TO_DEGREES = 5;
// const int Y_STEPS_TO_DEGREES = 5;

// // Rotational Limits (in degrees)
// const double MAX_LEFT = -90;
// const double MAX_RIGHT = 90;
// const double MAX_BACK = -58;
// const double MAX_FOWARD = 58;

// // Current positions (in degrees)
// double currentX = 0;
// double currentY = 0;

// void setup()
// {
//   // Misc
//   Serial.begin(9600);

//   // X Motor Setup
//   x.setMaxSpeed(MAX_SPEED);
//   x.setSpeed(MAX_SPEED);
//   x.setAcceleration(ACCELERATION);

//   // Y Motor Setup
//   y.setMaxSpeed(MAX_SPEED);
//   y.setSpeed(MAX_SPEED);
//   y.setAcceleration(ACCELERATION);
// }

// // Zero out the axises (will be called via serial for now)
// boolean zeroAxis()
// {
//   currentX = 0;
//   currentY = 0;
//   return true;
// }

// // Rotate x by given number of degrees
// // Return false if did not complete rotation
// boolean rotateX(double degrees)
// {
//   if (!(MAX_LEFT < degrees + currentX && degrees + currentX < MAX_RIGHT))
//   {
//     Serial.println("ERROR: OUT OF BOUNDS MOVEMENT IN X - AXIS");
//     return false;
//   }
//   x.setCurrentPosition(0);
//   x.moveTo(degrees * X_STEPS_TO_DEGREES);

//   while (x.distanceToGo() != 0)
//   {
//     x.run();
//   }

//   currentX += degrees;
//   return true;
// }

// // Rotate y by given number of degrees
// // Return false if did not complete rotation
// boolean rotateY(double degrees)
// {
//   if (!(MAX_BACK < degrees + currentY && degrees + currentY < MAX_FOWARD))
//   {
//     Serial.println("ERROR: OUT OF BOUNDS MOVEMENT IN Y - AXIS");
//     return false;
//   }

//   y.setCurrentPosition(0);
//   y.moveTo(degrees * Y_STEPS_TO_DEGREES);

//   while (y.distanceToGo() != 0)
//   {
//     y.run();
//   }

//   currentY += degrees;
//   return true;
// }

// // Reads Serial in & executes incoming command
// // return false if command not recognized
// boolean serialRead()
// {
//   String command = Serial.readString();
//   boolean executed = false;

//   // 'z' = zero axis
//   if (command.equals("z"))
//   {
//     executed = zeroAxis();
//   }

//   // 'x' = rotate x
//   else if (command.equals("x"))
//   {
//     double degrees = Serial.readString().toDouble();
//     executed = rotateX(degrees);
//   }

//   // 'y' = rotate y
//   else if (command.equals("y"))
//   {
//     double degrees = Serial.readString().toDouble();
//     executed = rotateY(degrees);
//   }

//   // command not recognized
//   else
//   {
//     Serial.println("ERROR: COMMAND NOT RECOGNIZED");
//   }

//   // return code
//   if (executed)
//     Serial.println("EXECUTED");
//   else
//     Serial.println("FAILED EXECUTION");
//   return executed;
// }

// void loop()
// {
//   rotateX(50);
//   rotateY(50);
// }