#include "main.h"



pros::MotorGroup left1({-12});
pros::MotorGroup right1({14});
pros::MotorGroup left2({-13});
pros::MotorGroup right2({15});
pros::MotorGroup intake({-17});
pros::MotorGroup hook({20});
pros::MotorGroup arm({21});

bool lock1 = false;
bool pusher1 = false;
pros::ADIDigitalOut lock(1,lock1);
pros::ADIDigitalOut pusher(2,pusher1);
pros::Imu imu(18);



/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  imu.reset(true);
left1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
left2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
right1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
right2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
arm.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opco
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	redNegative();


}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() { 


	bool lock_check = 0;
	bool arm_check = 0;
	Controller master(pros::E_CONTROLLER_MASTER);
	while (true) {
	

	
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);

		left1.move(forward + turn);
		right1.move(forward - turn);
		left2.move(forward + turn);
		right2.move(forward - turn);
		
		if(master.get_digital(DIGITAL_L1)){
			intake.move(-127);
			hook.move(127);
		}
		else if(master.get_digital(DIGITAL_L2)){
			intake.move(127);
			hook.move(-127);
		}

		else{
			intake.move(0);
			hook.move(0);
		}
		if(master.get_digital_new_press(DIGITAL_X)){
			lock_check = !lock_check;
		}
		lock.set_value(lock_check);

		if(master.get_digital_new_press(DIGITAL_Y)){
			arm_check = !arm_check;
		}
		pusher.set_value(arm_check);

		
		
		if(master.get_digital_new_press(DIGITAL_R1)){
			arm.move_absolute(-108, 127);
		}
		if(master.get_digital_new_press(DIGITAL_R2)){
		 	arm.move_absolute(-900, 127);
		}
		
		if(master.get_digital_new_press(DIGITAL_A)) {
			arm.move_absolute(0,127);
		}
	}
}



