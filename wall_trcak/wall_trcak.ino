#include <SR04.h>

#define rightMotor1 3
#define rightMotor2 4
#define rightMotorPWM 5
#define leftMotor1 12
#define leftMotor2 13
#define leftMotorPWM 11

int WF_LEFT_US_SENSOR_TRIG = 18;
int WF_LEFT_US_SENSOR_ECHO = 17;
int WF_FRONT_US_SENSOR_TRIG = 16;
int WF_FRONT_US_SENSOR_ECHO = 15;


int NO_OBSTACLE = 0;
int OBSTACLE = 1;

int WF_DISTANCE = 12;
int WF_FRONT_DISTANCE = 16;

SR04 wf_sr04_left = SR04(WF_LEFT_US_SENSOR_ECHO,WF_LEFT_US_SENSOR_TRIG);
SR04 wf_sr04_front = SR04(WF_FRONT_US_SENSOR_ECHO,W

int WF_Left = 0;
int WF_Front = 0;


int WF_Left_Status = 0;
int WF_Front_Status = 0;
// PID Left
float WF_Kp = 30;
float WF_Ki = 0.003;
float WF_Kd = 8;
// PID Right
float MY_Kp_Front = 40;
float MY_Ki_Front = 0; 
float MY_Kd_Front = 20; 


float WF_Error = 0;
int WF_Correction = 0;
float WF_Integral = 0;
float WF_Derivative = 0;
float WF_LastError = 0;

float MY_Error_Front = 0;
float MY_Correction_F = 0;
float MY_Integral_Front = 0;
float MY_Derivative_Front = 0;
float MY_LastError_Front = 0;

int WF_LeftTurnSpeed = 0;
int WF_RightTurnSpeed = 0;

int rightTurnBegin = 0;
int leftTurnBegin = 0;
int straightLineBegin = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  
beginning:

    WF_Front_Status = WF_GET_FRONT_US_STATUS();
 

}
