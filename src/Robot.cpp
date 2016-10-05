#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();

	RobotDrive robot;
	Joystick stick;

	//CAMERA
	Servo camX;
	double camdY;
	Servo camY;
	double camdX;
	//CAMERA

	//Toggle Control
	 //arm
	 //starts down
	 boolean arm_bool = true;

	 //finger
	 //starts in
	 boolean finger_bool = true;

	 //comp
	 //starts running
	 boolean comp_bool = true;

	 //launcher
	 //true is down (once again only a toggle value)
	 boolean launcher_bool = true;
	 //we only really need a toggle value to control a solenoid because of blank.set(!blanck.get())
	 //the reason all the others have location values is because of the anti-bummper-quick-release
	 //seems to me now that those are not even necessary
	 //Toggle Control

	 //Pneumatics
	 Compressor comp;
	 DoubleSolenoid sol1;
	 DoubleSolenoid sol2;
	 //Pneumatics

	 //Launcher
	 //Launcher status
	 int intake_num = 0;
	 //Launcher motors
	 CANTalon motor1;
	 CANTalon motor2;
	 //Intake motor
	 CANTalon motor3;
	 //Launcher


	void RobotInit()
	{
		robot = RobotDrive(0, 1);
		sitck = Joystick(0);
		robot.SetExpiration(0.1);
		comp = Compressor();
		comp.start();

		//Solenoids
		//0
		sol1 = DoubleSolenoid(0,1);
		//3
		sol2 = DoubleSolenoid(2,3);

		sol1.set(DoubleSolenoid.Value.kForward);
		slo2.set(DoubleSolenoid.Value.kReverse);
		//Solenoids

		//Camera
		camY = Servo(4);
		camX = Servo(3);
		//Camera
	}



	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{


	}

	void TeleopPeriodic()
	{
		robot.ArcadeDrive(stick.GetY(), -stick.GetX());

		if(stick.GetRawButton(2)&&arm_bool){
			if(sol1.Get()==DoubleSolenoid.Value.kForward){
				sol1.Set(DoubleSolenoid.Value.kReverse);
			} else {
				sol1.Set(DoubleSolenoid.Value.kForward);
			}
			arm_bool=false;
		} else if (stick.GetRawButton(2)&&arm_bool==false) {
				/* Zilch */
		} else if (arm_bool==false){
		  	arm_bool=true;
		}

		//SHOOTER SOLENOID CONTROL
		if(stick.GetRawButton(4)&&launcher_bool) {
			 launcher_bool=false;
			if(sol1.Get()==DoubleSolenoid.Value.kForward){
				sol2.Set(DoubleSolenoid.Value.kReverse);
			} else {
				sol2.Set(DoubleSolenoid.Value.kForward);
			}

		} else if(stick.GetRawButton(4)&&!launcher_bool)  {

		} else if(!launcher_bool) {
			launcher_bool = !launcher_bool;
		}

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
