#include <ModuleTeacher.h>

Module_Teacher MyTeacherModule;
ezOutput led1(_PIN_LED);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(_PIN_LED,OUTPUT);
  pinMode(_PIN_WARNING_R,INPUT);
  pinMode(_PIN_WARNING_W,OUTPUT);
  pinMode(_PIN_BUZZER,OUTPUT);
  pinMode(_PIN_WARNING_CLEAR_SW,INPUT);
  pinMode(_PIN_BUZZER_ON_OFF_SW,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  MyTeacherModule.check_warning_signal();
  MyTeacherModule.check_warning_time();
  MyTeacherModule.process_led();
  MyTeacherModule.process_buzzer();
  MyTeacherModule.process_switch1();
  MyTeacherModule.process_switch2();
  led1.loop();
}
