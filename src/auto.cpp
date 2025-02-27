#include "main.h"

void redPositive(){

    //-----------------------------right side red--------------------------------------------------------------------
arm.move_absolute(-1500,127);
delay(1200);
arm.move_absolute(0,127);
turnPID(52.7,2.1,0,3);
//DrivePID(-100,1.3,5,5);
//turnPID(27,1.6,1,3);
hook.move(127);
intake.move(-127);
DrivePID(1000,1.3,1,5);
delay(400);
DrivePID(600,1.3,1,5);
hook.move(0);
intake.move(0);
turnPID(-25.4,1.3,1,2);
DrivePID(-900,1.3,1,5);
turnPID(-26,1.2,1,2);
delay(300);
DrivePID(-800,1.3,0,4);
delay(200);
DrivePID(-350,1.3,0,4);
lock.set_value(1);
delay(200);
hook.move(127);
intake.move(-127);
turnPID(-120,1.5,0,0);
DrivePID(900,1.3,5,5);
turnPID(60,1.3,1,2);
delay(400);
turnPID(-10,1,0,4);
DrivePID(1800,1.3,1.5,5);
delay(250); 
DrivePID(-400,1.3,1,2);

}


void skillsAuto(){
    //-------------------------------skills auto------------------------------------------
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
	// Step 11: go to first ring and score it onto 2nd mobile goal
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
	// Step 17: go to the wall and reset

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


void redNegative(){
    
}