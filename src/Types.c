#define TURNING_DURATION 4
#define LIGHT_INCREASE_THRESHOLD 0.12
struct stateT {
	unsigned int ServoPosition;
	unsigned int LeftWhisker;
	unsigned int RightWhisker;
	int FrontFacingIR;
  int LeftLight;
  int RightLight;
  int TopRightLight;
  int TopLeftLight;
  float AverageBaseLight;
  float AverageTopLeftLight;
  float AverageTopRightLight;
} state;

struct timerT {
  int iteration;
  int threshold;
  time_t lastTimeChange;
  double frequency;
} timer;

