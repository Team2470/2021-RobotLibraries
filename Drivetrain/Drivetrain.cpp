#include "Drivetrain.h"
#include "util.h"

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
	setPower(0.0, 0.0);
}

void Drivetrain::arcade(double forward, double turn, bool squareInputs) {

	if (squareInputs) {
		if (forward < 0) { 
			forward *= -forward; 
		}
		else { 
			forward *= forward; 
		}

		if (turn < 0) { 
			turn *= -turn; 
		}
		else { 
			turn *= turn; 
		}
	}

	// (Ignore this) Preserve max input so a hard bank will still cause a significant response
	//double maxInput = max(forward, turn);
	double maxInput = forward;
	double left;
	double right;

	if (forward >= 0) {
		if (turn >= 0) {
			// I
			left = maxInput;
			right = forward - turn;
		}
		else {
			// II
			left = forward + turn;
			right = maxInput;
		}
	}
	else {
		if (turn >= 0) {
			// III
			left = forward + turn;
			right = maxInput;
		}
		else {
			// IV
			left = maxInput;
			right = forward - turn;
		}
	}

	left = clamp(left, -1.0, 1.0);
	right = clamp(right, -1.0, 1.0);

	setPower(left, right);
}

void Drivetrain::setPower(double left, double right) {
  setPower(LEFT, left);
  setPower(RIGHT, right);
}


/*************************************************************
 ******************* Private Functions ***********************
 *************************************************************/
  
void Drivetrain::setPower(int side, double power) {
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
    	Serial.println("FORWARD!");
    	Serial.println(DO_l_dir_fwd_);
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