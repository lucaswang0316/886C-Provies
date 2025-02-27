#include "main.h"

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
void DrivePID(double distance, double kP, double KI, double kD, double time){
	left1.tare_position();
	left2.tare_position(); 
	int integral = 0;
	int derivative = 0;
	int last_error = 0;
	int error = distance - (left2.get_position());
	int getTime = pros::millis();
	while(abs(error) > 5 && time >= (pros::millis() - getTime)){
		error = distance - ((left1.get_position()+left2.get_position())/2);
		derivative = error - last_error;
		last_error = error;
		PowerDrive(std::min(error*kP + integral*KI + derivative*kD,55.0),0);
		if(abs(error) < 10){
			integral += error;
		}
	}
PowerDrive(0,0);
}

void DrivePIDwithLimit(double distance, double kP, double KI, double kD, double maxSpeed, int time){
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
void turnPID(double degrees, double kP, double KI, double kD, int time){
	imu.tare_rotation();
	int integral = 0;
	int error = degrees - imu.get_rotation();
	int derivative = 0;
	int last_error = 0;
	int getTime = pros::millis();
	while(abs(error) > 5 && time >= (pros::millis() - getTime)){ // tune this
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