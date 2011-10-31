#define DRIVE_RIGHT(Value) CPhidgetMotorControl_setVelocity (motoControl, 1, round(0.75 * Value))
#define SERVO(Value) CPhidgetAdvancedServo_setPosition(servo, 0, Value)

void DRIVE_LEFT(double Value) {
  Movement move;
  if(Value > 0) { 
    move = Forwards; 
  } else if(Value == 0) {
    move = None;
  } else { 
    move = Backwards;
  }
  if(state.expectedMovement == move) {
    if(state.SpinSensor < 1)
      state.expectedFor++;
  } else {
    state.expectedMovement = move;
    state.expectedFor = 0;
  }
  CPhidgetMotorControl_setVelocity (motoControl, 0, round(-0.75 *Value));
}

//int firstRetreat = 1;

int stop()
{
  MovementLog("stop()");
	DRIVE_LEFT(0.0);
	DRIVE_RIGHT(0.0);
	return 0;
}



int turnOnSpotLeft()
{
  MovementLog("turnOnSpotLeft()");
	if(state.ServoPosition != 1) 
	{
		//stop();
		SERVO(50);
		//sleep(0.5);
		state.ServoPosition = 1;
	}
	DRIVE_RIGHT(100);
	DRIVE_LEFT(-80);
	return 0;
}


int turnOnSpotRight()
{
  MovementLog("turnOnSpotRight()");
	if(state.ServoPosition != -1)
	{
		//stop();
		SERVO(190);
		//sleep(0.5);
		state.ServoPosition = -1;
	}
	DRIVE_RIGHT(-80);
	DRIVE_LEFT(100);
}

int orientStraightAndDrive(double percent)
{
  MovementLog("orientStraightAndDrive()");
	SERVO(120);
	//sleep(0.8);
	DRIVE_RIGHT(70);
	DRIVE_LEFT(70);
	//goTowards(90);
	state.ServoPosition = 0;
	return 0;
}

int retreat(Direction direction)
{
  
	if(direction == Right)
	{
	  MovementLog("retreat(Right)");
		SERVO(190);
		DRIVE_LEFT(-10);
		DRIVE_RIGHT(-60);
	} else
	{
	  MovementLog("retreat(Left)");
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
	DRIVE_RIGHT(-75);
	DRIVE_LEFT(-75);
	sleep(1);
	return 0;
}


int sweepWithSonar() {
  SERVO(20);
  ResetMeasurements();
  msleep(500);
  for(state.ServoAngle = 20; state.ServoAngle < 120; state.ServoAngle += 5)
  {
    SERVO(state.ServoAngle);
    msleep(50);
  }
  SERVO(120);
}

int goTowards(double angle, double percent)
{
  MovementLog("goTowards(%f)", angle);
  orientStraightAndDrive(1);
	// angle must be within 0 and 180 degrees
	// 0 is the servo motor turned fully to the right
	// 180 is the servo motor turned fully to the left
	//SERVO(20+(angle*(10/9)));

	//DRIVE_RIGHT(80*(angle/180));
	//DRIVE_LEFT(80*(1-(angle/180)));
	return 0;
}

int randomMovement()
{//TODO define this. it can also be the spiral movement that we want our robot to make or just something random.
}

int ontoTheNextOne(int frequency)
{
  MovementLog("ontoTheNextOne(%f)", frequency);
  if (frequency == 1)
  {
    turnOnSpotLeft();
    sleep(5);
    orientStraightAndDrive(1);
    sleep(2);
  } else if (frequency == 2) {
    turnOnSpotRight();
    msleep(2600L);
    orientStraightAndDrive(1);
    sleep(2);
  } else if (frequency == 4) {
    turnOnSpotRight();
    sleep(7);
    orientStraightAndDrive(1);
    sleep(2);
  } else if (frequency == 8) {
    turnOnSpotLeft();
    sleep(8);
    orientStraightAndDrive(1);
    sleep(2);
  } else {
    // do some random movement to explore the area
    randomMovement();
  }
  return 0;
}
