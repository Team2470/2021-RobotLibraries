#include "Drivetrain.h"
#include "util.h"
#include <math.h>

// Libraries need to include Arduino.h or WProgram.h to use Serial
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/*************************************************************
 ********************* Local Defines *************************
 *************************************************************/
#define FORWARD 0
#define BACKWARD 1
#define BRAKE 3
#define RIGHT 0
#define LEFT 1
#define DEFAULT_SPEED 0
#define MAX_SPEED 255

/*************************************************************
 ******************** Public Functions ***********************
 *************************************************************/

void Drivetrain::setup(int l_dir_fwd, int l_dir_rev, int l_speed, 
    	       	       int r_dir_fwd, int r_dir_rev, int r_speed) {
	PWM_l_speed_ = l_speed;
	PWM_r_speed_ = r_speed;
	DO_l_dir_fwd_ = l_dir_fwd;
	DO_l_dir_rev_ = l_dir_rev;
	DO_r_dir_fwd_ = r_dir_fwd;
	DO_r_dir_rev_ = r_dir_rev;	

	pinMode(PWM_l_speed_, OUTPUT);
	pinMode(PWM_r_speed_, OUTPUT);
	pinMode(DO_l_dir_fwd_, OUTPUT);
	pinMode(DO_l_dir_rev_, OUTPUT);
	pinMode(DO_r_dir_fwd_, OUTPUT);
	pinMode(DO_r_dir_rev_, OUTPUT);
	setPower(0.0f, 0.0f);
}

// TODO make a private function
float applyDeadband(float value, float deadband) {
  if (abs(value) > deadband) {
    if (value > 0.0) {
      return (value - deadband) / (1.0 - deadband);
    } else {
      return (value + deadband) / (1.0 - deadband);
    }
  } else {
    return 0.0;
  }
}

void Drivetrain::arcade(float xSpeed, float zRotation, bool squareInputs) {
	xSpeed = clamp(xSpeed, (float)-1.0, (float)1.0);
  xSpeed = applyDeadband(xSpeed, 0.1);
	zRotation = clamp(zRotation, (float)-1.0, (float)1.0);
  zRotation = applyDeadband(zRotation, 0.1);
	
	// Square the inputs (while preserving the sign) to increase fine control
    // while permitting full power.
	if (squareInputs) {
		xSpeed = copysign(xSpeed*xSpeed, xSpeed);
		zRotation = copysign(zRotation*zRotation,zRotation);
	}

  float leftMotorOutput;
  float rightMotorOutput;

	float maxInput = copysign(max(abs(xSpeed), abs(zRotation)), xSpeed);

 	if (xSpeed >= 0.0) {
      // First quadrant, else second quadrant
      if (zRotation >= 0.0) {
        leftMotorOutput = maxInput;
        rightMotorOutput = xSpeed - zRotation;
      } else {
        leftMotorOutput = xSpeed + zRotation;
        rightMotorOutput = maxInput;
      }
    } else {
      // Third quadrant, else fourth quadrant
      if (zRotation >= 0.0) {
        leftMotorOutput = xSpeed + zRotation;
        rightMotorOutput = maxInput;
      } else {
        leftMotorOutput = maxInput;
        rightMotorOutput = xSpeed - zRotation;
      }
    }
  
	leftMotorOutput = clamp(leftMotorOutput, (float)-1.0, (float)1.0);
	rightMotorOutput = clamp(rightMotorOutput, (float)-1.0, (float)1.0);

	setPower(leftMotorOutput, rightMotorOutput);
}

void Drivetrain::setPower(float left, float right) {
  setPower(LEFT, left);
  setPower(RIGHT, right);
}


/*************************************************************
 ******************* Private Functions ***********************
 *************************************************************/
  
void Drivetrain::setPower(int side, float power) {
  if (power > 0) {
    setDirection(side, FORWARD);
  }
  if (power < 0) {
    setDirection(side, BACKWARD);
  }
  if (power == 0) {
    // Force power to 1 to power brake
    // This is probably undesirable, but we'll see
    setDirection(side, BRAKE);
    setSpeed(side, MAX_SPEED);
    return;
  }
  // Denormalize speed
  int denormalized = (int)(abs(power) * MAX_SPEED);
  setSpeed(side, denormalized);
}

void Drivetrain::setDirection(int side, int direction) {
  if (side == LEFT) {
    if (direction == FORWARD) {
      digitalWrite(DO_l_dir_fwd_, HIGH);
      digitalWrite(DO_l_dir_rev_, LOW);
    }
    if (direction == BACKWARD) {
      digitalWrite(DO_l_dir_fwd_, LOW);
      digitalWrite(DO_l_dir_rev_, HIGH);
    }
    if (direction == BRAKE) {
      digitalWrite(DO_l_dir_fwd_, HIGH);
      digitalWrite(DO_l_dir_rev_, HIGH);
    }
  }
  if (side == RIGHT) {
    if (direction == FORWARD) {
      digitalWrite(DO_r_dir_fwd_, LOW);
      digitalWrite(DO_r_dir_rev_, HIGH);
    }
    if (direction == BACKWARD) {
      digitalWrite(DO_r_dir_fwd_, HIGH);
      digitalWrite(DO_r_dir_rev_, LOW);
    }
    if (direction == BRAKE) {
      digitalWrite(DO_r_dir_fwd_, HIGH);
      digitalWrite(DO_r_dir_rev_, HIGH);
    }
  }
}

void Drivetrain::setSpeed(int side, int speed) {
  if (side == LEFT) {
    analogWrite(PWM_l_speed_, speed);
  }
  if (side == RIGHT) {
    analogWrite(PWM_r_speed_, speed);
  }
}