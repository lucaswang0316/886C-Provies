#ifndef _AUTOFUNCTIONS_HPP_
#define _AUTOFUNCTIONS__HPP_


void PowerDrive(int powerforward, int powerturning);
void resetsens();
void timedrive(int time, int power);
void DrivePI(double distance, double KI, double kP);
void DrivePD(double distance, double kP, double kD);
void DrivePID(double distance, double kP, double KI, double kD, int time = 3000);
void DrivePIDwithLimit(double distance, double kP, double KI, double kD, double maxSpeed, int time = 3000);
void turnPI(double degrees, double KI ,double kP);
void turnPD(double degrees, double kP, double kD);
void turnPID(double degrees, double kP, double KI, double kD, int time=3000);

#endif 