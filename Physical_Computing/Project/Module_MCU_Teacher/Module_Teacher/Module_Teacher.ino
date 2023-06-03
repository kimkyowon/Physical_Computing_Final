#include <ModuleChild.h>
#include <SoftwareSerial.h>

SoftwareSerial MySerial(0,1,false); 

Module_Teacher MyTeacherModule;
Child_Status MyChild1Status;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MySerial.begin(9600);
  pinMode(C_LED,OUTPUT);
  pinMode(C_Buzzer,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent(){
  while(MySerial.available()){
    MyTeacherModule.ReadData = (char)Serial.read();
    inputString += MyTeacherModule.ReadData;
    if(MyTeacherModule.ReadData == '\n') stringComplete = true;
  }
}