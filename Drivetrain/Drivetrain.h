#ifndef _DRIVETRAIN_H_
#define _DRIVETRAIN_H_

class Drivetrain {

/*************************************************************
 ******************** Public Variables ***********************
 *************************************************************/
public:

/*************************************************************
 ******************* Private Variables ***********************
 *************************************************************/
private:

	/* Holds pin assignments for the hardware */
	int PWM_l_speed_;
	int PWM_r_speed_;
	int DO_l_dir_fwd_;
	int DO_l_dir_rev_;
	int DO_r_dir_fwd_;
	int DO_r_dir_rev_;	


	/* The currently assigned speed */
	int speed_;

/*************************************************************
 ******************* Public Functions ***********************
 *************************************************************/
public:
	/**
	 * Configures the ios for the module.  Set the proper pins
	 * for your particular robot.
	 *
	 * @param[in] l_dir_fwd I/O to enable H-bridge forward
	 * @param[in] l_dir_rev I/O to enable H-bridge reverse
	 * @param[in] l_speed PWM I/O to control motor speed
	 * @param[in] r_dir_fwd I/O to enable H-bridge forward
	 * @param[in] r_dir_rev I/O to enable H-bridge reverse
	 * @param[in] r_speed PWM I/O to control motor speed
	 */
    void setup(int l_dir_fwd, int l_dir_rev, int l_speed, 
    	       int r_dir_fwd, int r_dir_rev, int r_speed);

    /**
     * Arcade drive to drive the robot based on a forward and
     * turn speed.  squareInputs can be used to adjust the dead
     * zone of the system.
     *
     * @param[in] foward The speed to drive (-1.0 to 1.0)
     * @param[in] turn The direction and speed to turn (-1.0 to 1.0)
     * @param[in] squareInputs squares the inputs, 
     *                     effectively creating a larger deadzone
     */
    void arcade(double forward, double turn, bool squareInputs);

    /**
     * Sets the power level / speed to use on the motors
     * "Power" is -1.0 to +1.0
     * This is equivalent to the WPILib TankDrive mode
     *
     * @param[in] left power for the left motor
     * @param[in] right power for the right motor
     */
    void setPower(double left, double right);

/*************************************************************
 ******************* Private Functions ***********************
 *************************************************************/
private:

	/**
	 * Helper function to set the direction of a given bank
	 * of motors.
	 *
	 * @param[in] The side to set the direction for
	 * @param[in] The direction to set it to
	 */
	void setDirection (int side, int direction);

	/**
	 * Helper function to set the speed to a specific motor
	 * bank.
	 *
	 * @param[in] side The side to set the direction for
	 * @param[in] speed The speed to set
	 */
	void setSpeed     (int side, int speed);

    /**
     * Sets the power level to a specific motor

     *
     * @param[in] side The motor to set
     * @param[in] power The power level
     */
    void setPower(int side, double power);

};

#endif // _DRIVETRAIN_H_