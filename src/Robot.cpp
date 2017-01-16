#include <iostream>
#include <memory>
#include <string>

#include <IRShooter.h>

#include <HumanInterfaceDevices/IRJoystick.h>
#include <RobotDrive/IRRobotDrive.h>

#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Timer.h>

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public frc::SampleRobot
{
	IR::IRRobotDrive 	myDrive {0, 1, 2, 3};
	IR::IRJoystick 		joystick {0},
						gamePad {1};
	IRShooter 			irshooter {4, 5, 6};

	frc::SendableChooser<std::string> chooser;
	const std::string autoTestShoot = "Test Shooter";
	const std::string autoTestDrive = "Test Driver";

public:
	Robot()
	{
		myDrive.SetMotorsInverted(true);
	}

	void RobotInit()
	{
		chooser.AddDefault(autoTestShoot, autoTestShoot);
		chooser.AddObject(autoTestDrive, autoTestDrive);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}

	void Autonomous()
	{
		auto autoSelected = chooser.GetSelected();
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoTestDrive){
			//Custom Auto goes here
			std::cout << "Running " + autoTestDrive << std::endl;

			myDrive.Drive(0.1, 0.0);
			frc::Wait(10);
			myDrive.Drive(0.0, 0.0);
			frc::Wait(10);
			myDrive.Drive(0.2, 1);
			frc::Wait(10);
			myDrive.Drive(0.2, -1);
			frc::Wait(10);
			myDrive.Drive(0.0, 0.0);
		}
		else {
			//Default Auto goes here
			//place in front of low bar, drive forward, turn right, shoot
			std::cout << "Running " + autoTestShoot << std::endl;
			irshooter.TakeIn();
			frc::Wait(10);
			myDrive.Drive(0.2, 0.0);
			frc::Wait(10);
			myDrive.Drive(0.2, 0.2);
			frc::Wait(10);
			irshooter.Shoot();
		}
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()

	{
		while (IsOperatorControl() && IsEnabled())
		{
			myDrive.ArcadeDrive(joystick, true); // drive with arcade style (use right stick), boolean true if using deadZone

			if(gamePad.GetTriggerRight()) irshooter.Shoot();
			else if(!gamePad.GetTriggerRight())irshooter.StopShoot();

			if(gamePad.GetTriggerLeft()) irshooter.TakeIn();
			else if(gamePad.GetRawButton(4)) irshooter.TakeOut();
			else if(!gamePad.GetTriggerLeft() && !gamePad.GetRawButton(4)) irshooter.StopInTake();

			if(gamePad.GetRawButton(5)) irshooter.CurvedShoot(0.2);

			if(gamePad.GetRawButton(6)) irshooter.CurvedShoot(-0.2);

			if(gamePad.GetRawButton(1)) irshooter.ShootingSequence();

			frc::Wait(0.005);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
		irshooter.TakeIn();
		frc::Wait(10);
		irshooter.Shoot();
	}
};

START_ROBOT_CLASS(Robot);
