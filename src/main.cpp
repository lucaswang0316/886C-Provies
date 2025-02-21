#include "main.h"
using namespace pros;

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



void PowerDrive(int powerforward, int powerturning){
	//left1 = powerforward + powerturning;
	//right1 = powerforward - powerturning;
	//left2 = powerforward + powerturning;
	//right2 = powerforward - powerturning;
	left1.move(powerforward + powerturning);
	right1.move(powerforward - powerturning);
	left2.move(powerforward + powerturning);
	right2.move(powerforward - powerturning);
}

void resetsens(){
	left1.tare_position();
	right1.tare_position();
	left2.tare_position();
	right2.tare_position();
}

void timedrive(int time, int power){
	int st = millis();
	while(time>millis() - st){
		PowerDrive(power,0);
	}
	PowerDrive(0,0);
}
void DrivePI(double distance, double KI, double kP){
	left1.tare_position();
	int integral = 0;
	int error = distance - left1.get_position();
	while(abs(error) > 10){ 
		error = distance - left1.get_position();
		PowerDrive(error*kP + integral*KI,0);
		if(abs(error) < 10){
			integral += error;
			}
		}
	PowerDrive(0,0);
}
void DrivePD(double distance, double kP, double kD){
	left1.tare_position();
	int error = distance - left1.get_position();
	int derivative = 0;
	int last_error = 0;
	while(abs(error) > 10){ 
		error = distance - left1.get_position();
		derivative = error - last_error;
		last_error = error;
		PowerDrive(std::min(error*kP + derivative*kD,90.0),0);
		}
	PowerDrive(0,0);
}
void DrivePID(double distance, double kP, double KI, double kD, double time = 3000){
	left1.tare_position();
	int integral = 0;
	int derivative = 0;
	int last_error = 0;
	int error = distance - left1.get_position();
	int getTime = pros::millis();
	while(abs(error) > 5 && time >= (pros::millis() - getTime)){
		error = distance - left1.get_position();
		derivative = error - last_error;
		last_error = error;
		PowerDrive(std::min(error*kP + integral*KI + derivative*kD,55.0),0);
		if(abs(error) < 10){
			integral += error;
		}
	}
PowerDrive(0,0);
}

void DrivePIDwithLimit(double distance, double kP, double KI, double kD, double maxSpeed, int time = 3000){
	left2.tare_position();
	int integral = 0;
	int derivative = 0;
	int last_error = 0;
	int error = distance - left2.get_position();
	int getTime = pros::millis();
	while(abs(error) > 5 && time >= (pros::millis() - getTime)){
		error = distance - left2.get_position();
		derivative = error - last_error;
		last_error = error;
		PowerDrive(std::min(error*kP + integral*KI + derivative*kD,maxSpeed),0);
		if(abs(error) < 10){
			integral += error;
		}
	}
PowerDrive(0,0);
}

void turnPI(double degrees, double KI ,double kP){
	imu.tare_rotation();
	int integral = 0;
	int error = degrees - imu.get_rotation();
	while(abs(error) > 10 ){
		error = degrees - imu.get_rotation();
		PowerDrive(error*kP + integral*KI,0);
		if(abs(error) < 10){
			integral += error;
			}
		}
	PowerDrive(0,0);
}

void turnPD(double degrees, double kP, double kD){
	imu.tare_rotation();
	int error = degrees - imu.get_rotation();
	int derivative = 0;
	int last_error = 0;
	while(abs(error) > 5){
		error = degrees - imu.get_rotation();
		derivative = error - last_error;
		last_error = error;
		PowerDrive(0,error*kP + derivative*kD);
	}
	PowerDrive(0,0);
}
void turnPID(double degrees, double kP, double KI, double kD, int time = 3000){
	imu.tare_rotation();
	int integral = 0;
	int error = degrees - imu.get_rotation();
	int derivative = 0;
	int last_error = 0;
	int getTime = pros::millis();
	while(abs(error) > 5 && time >= (pros::millis() - getTime)){
		error = degrees - imu.get_rotation();
		derivative = error - last_error;
		last_error = error;
		PowerDrive(0, error*kP + integral*KI + derivative*kD);
		if(abs(error) < 10){
			integral += error;
		}
	}
	PowerDrive(0,0);
}
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
	// Step 1: turn on intakes and score alliance stake
	hook.move(127);
	intake.move(-127);
	delay(1000);
	//  Step 2: goes to the top lrft mobile goal and clamp on
	DrivePID(600,1,5,5);
	delay(500);
	turnPID(70,3,30,5);
	delay(500);
	DrivePID(-1000,1,5,70);
	lock.set_value(1);
	delay(500);
	//step 3: go to the first ring and scores it on to the mobile goal
	turnPID(-63,3,10,5);
	delay(200);
	DrivePID(920,1,5,5);
	delay(200);
	//Step 4: go to second ring and scores it on to the mobile goal
	turnPID(-83,1,5,10);
	delay(200);
	DrivePID(1400,1,5,5);
	//step 5:go to the third ring and scores it onto the mobile goal
	turnPID(79,1.3,10,10);
	delay(200);
	DrivePID(955,1,5,5);
	delay(500);
	//Step 6: goes to the fourth and fifth ring and scores it onto the mobile goal
	turnPID(161,1.3,5,5);
	delay(200);
	DrivePID(2700,1,5,5);
	delay(200);
	//Step 7: goes to the sixth ring and scores it onto the mobile goal
		
	DrivePID(-500,1,5,5,1000);
	delay(200);
	turnPID(86,1.6,10,10);
	delay(200);
	DrivePID(500,1,5,5,1500);
	delay(600);
	//Step 8: drop the mobile goal into the corner

	turnPID(111,3,10,5);
	delay(200);
	DrivePID(-1400,1,5,5);
	delay(200);
	hook.move(-127);
	delay(200);
	lock.set_value(0);
	//Step 9: rams to the wall and faces toward the top right mobile goal
	DrivePID(200,1,5,5);
	delay(200);
	turnPID(-130,1.3,5,5);
	delay(200);
	timedrive(1000,80);
	delay(200);
	hook.move(127);
	// Step 10: clamp on to second mobile goal
	left1.tare_position();
	DrivePIDwithLimit(-3290,1.5,1,4,66);
	turnPID(14,1.3,1,4);
	delay(500);
	DrivePIDwithLimit(-650,1.3,1,2,30);
	lock.set_value(1);
	delay(500);
	/*// Step 11: go to first ring and score it onto 2nd mobile goal
	turnPID(80,3,10,10);
	delay(200);
	DrivePID(900,1,5,5);
	delay(200);
	// Step 12: go to second ring and score onto 2nd mobile goal
	turnPID(80,1,5,10);
	delay(200);
	DrivePID(1500,1,5,5);
	// Step 13: go to the third ring and score onto 2nd mobile goal
	turnPID(-75,1,10,10);
	delay(200);
	DrivePID(900,1,5,5);
	delay(500);
	// Step 14: go to the fourth and fifth ring and score on to 2nd mobile goal
	turnPID(-169,1,5,5);
	delay(200);
	DrivePID(2750,1,5,5);
	delay(200);
	// Step 15: go to the sixth ring and score onto 2nd mobile goal
	DrivePID(-700,1,5,5);
	delay(200);
	turnPID(-90,1,10,10);
	delay(200);
	DrivePID(700,1,5,5);
	delay(200);
	// Step 16: drop 2nd mobile goal into corner
	turnPID(-109,3,10,5);
	delay(200);
	DrivePID(-700,1,5,5);
	delay(200);
	lock.set_value(0);
	// Step 17: go to the wall and reset*/

	//new step 
	turnPID(160,1.3,5,5);
	delay(200);
	timedrive(2000,60);
	delay(200);
	DrivePID(-450,1.3,5,5); 
	delay(200); 
	turnPID(85,1.5,4,5); 
	delay(200);
	DrivePID(600,1.3,5,5); 
	delay(200); 
	turnPID(100,1.5,4,5);
	delay(500);
	DrivePID(-600,1.3,5,5);
	lock.set_value(0);
	DrivePID(200,1.3,5,5);

	intake.move(-127);
	hook.move(-127);

	//Wall square
	turnPID(-120,1.3,5,5);
	delay(200);
	timedrive(1300,80);
hook.move(0);
	//go to the other side 
	DrivePID(-3500,1.4,5,5);
	delay(500); 
	turnPID(140,1.3,5,5); 
	delay(500); 
	DrivePIDwithLimit(2800,1.4,5,4,100);
	delay(500); 
	turnPID(85,1.3,5,5);
	// push mogo 
	delay(500);
	timedrive(4000,100);
	delay(500);
	DrivePID(-1000,1.4,1,2); 
	delay(200); 
	turnPID(-40,1.3,5,5);
	delay(200);
	timedrive(2000,100);
	delay(200); 
	timedrive(1000,-60);
	turnPID(110,1.3,1,3);
	timedrive(5000,-100);


	// drive diagonally and stop.
	// turn and drive up.
	// turn and drive forward.
	//turn and drive up again.
	// turn to the mobile goal and drive it into the corner.

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
	pros::delay(20);
}
