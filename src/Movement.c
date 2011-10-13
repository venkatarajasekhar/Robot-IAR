#define DRIVE_LEFT(Value) CPhidgetMotorControl_setVelocity (motoControl, 0, -0.75 *Value)
#define DRIVE_RIGHT(Value) CPhidgetMotorControl_setVelocity (motoControl, 1, 0.75 * Value)
#define SERVO(Value) CPhidgetAdvancedServo_setPosition(servo, 0, Value)

//int firstRetreat = 1;

int stop()
{
  MovementLog("stop()");
	DRIVE_LEFT(0.0);
	DRIVE_RIGHT(0.0);
	return 0;
}

int goTowards(double angle)
{
  MovementLog("goTowards(%d)", angle);
	// angle must be within 0 and 180 degrees
	// 0 is the servo motor turned fully to the right
	// 180 is the servo motor turned fully to the left
	SERVO(20+(angle*(10/9)));
	//sleep(0.2);
	DRIVE_RIGHT(60*(angle/180));
	DRIVE_LEFT(60*(1-(angle/180)));
	return 0;
}

int turnOnSpotRight()
{
  MovementLog("turnOnSpotRight()");
	if(state.ServoPosition != 1) 
	{
		//stop();
		SERVO(20);
		//sleep(0.5);
		state.ServoPosition = 1;
	}
	DRIVE_RIGHT(50);
	DRIVE_LEFT(-40);
	return 0;
}


int turnOnSpotLeft()
{
  MovementLog("turnOnSpotLeft()");
	if(state.ServoPosition != -1)
	{
		//stop();
		SERVO(220);
		//sleep(0.5);
		state.ServoPosition = -1;
	}
	DRIVE_RIGHT(-40);
	DRIVE_LEFT(50);
}

int orientStraightAndDrive()
{
  MovementLog("orientStraightAndDrive()");
	SERVO(120);
	//sleep(0.8);
	DRIVE_RIGHT(60);
	DRIVE_LEFT(60);
	//goTowards(90);
	state.ServoPosition = 0;
	return 0;
}

int retreat(int right)
{
  MovementLog("retreat(%d)", right);
	if(right==1)
	{
		SERVO(190);
		DRIVE_LEFT(-10);
		DRIVE_RIGHT(-60);
	} else
	{
		SERVO(50);
		DRIVE_LEFT(-60);
		DRIVE_RIGHT(-10);
	}
	//sleep(0.8);
	return 0;
}

int driveBack()
{
  MovementLog("driveBack()");
	SERVO(120);
	DRIVE_RIGHT(-40);
	DRIVE_LEFT(-40);
	sleep(1);
	return 0;
}
