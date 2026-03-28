int n_room=0;
int n_req=0;
int sensor[4]={A0,A1,A2,A3};
int ena=3;
int enb=4;
int in1=5;
int in2=6;
int in3=7;
int in4=8;
int sensor_value[4];

float kp=0.6;
float kd=10.0;
float ki=0;
int l_error=0;
float integral=0.0;
float derivative=0.0;
float correction_error=0.0;
int b_speed=150;
int max_speed=180;
int l_m_speed=0;
int r_m_speed=0;
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++)
  {
    pinMode(sensor[i],INPUT);
  }
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<4;i++)
  {
     sensor_value[i]=analogRead(sensor[i]);
  }
  int error=((-3*sensor_value[0])+(-1*sensor_value[1])+(1*sensor_value[2])+(3*sensor_value[3]));
  integral=integral + error;
  derivative=error-l_error;
   correction_error=(kp*error)+ (ki*integral)+ (kd*derivative);
   l_error=error;
   l_m_speed=b_speed+correction_error;
  r_m_speed=b_speed+correction_error;
  l_m_speed=constrain(l_m_speed,0, max_speed);
  r_m_speed=constrain(r_m_speed,0, max_speed);
  analogWrite(ena, l_m_speed);
   analogWrite(enb, r_m_speed);
}
