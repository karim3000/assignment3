//////////////////////////////////////////////////////////////
///This code is comprised of 3 sections: Initialization   ////
///(variables and setup), Task subroutines, and the main  ////
///loop. Variables are split among their relevant         ////
///subroutines with names indicative of their purpose.    ////
///The main loop will execute tasks based on their frequency//
///by dividing the current time by the task period then   ///
///checking for a remainder.                              ////
///                                                       ///
///The
/////////////////////////////////////////////////////////////
//#include semphr.h

///Task 1 variables
int pulse1 = 0.05 * 1000;  //Represents the duration of the Signal 1 pulse
int led1 = 21; //LED pin
///Task 2 variables
int button1 = 22; //Pin of Button 1
unsigned int buttonState; 
unsigned long timeRN; //Tracks current time
int counter = 0; //Used to reset the current time every 5000 ms
///Task 3 variables
int task3pin = 16;   ///orange wire (analog input)
int frequency = 0;  
unsigned int measure1; //Holds the first measurement
unsigned int time1; 
unsigned int time2;
///task 4 variables
int task4pin = 13;
int ANLGinput = 0;
///Task 5 variables
unsigned int task5avg;
int readcounter = 0;
int queue[] = {};
int compAvg = 0;
///Task 6 variables
int task6counter = 0;
///Task 7 variables
unsigned int error;
///Task 8 variables 
int led2 = 15;
//Task 9 variables
int pointer = 0;
int button2 = 0;

struct atask9{
  int buttonState;
  int frequency;
  int compAvg;
  int error;
};


void task1(void*parameter){ //Turn LED on and off for duration of "pulse1"
  while (1){
    digitalWrite(led1, HIGH); //This line coupled with the 2 below will run a signal 
    vTaskDelay(pulse1 / portTICK_PERIOD_MS);
    digitalWrite(led1, LOW);
    vTaskDelay(9 / portTICK_PERIOD_MS);}
  }
  
  
void task2(void * parameter){ //Store button state
  buttonState = digitalRead(button1);
  vTaskDelay(200 / portTICK_PERIOD_MS);}
  
void task3(void * parameter){ //Check task 3 pin then calculate the time it takes to change state
  measure1 = digitalRead(task3pin);
  time1 = millis();;
  while (digitalRead(task3pin) == frequency){
  }
  time2 = millis();
  frequency = 1 / (time2 - time1);
  vTaskDelay(1000 / portTICK_PERIOD_MS);}
  
void task4(void * parameter){ //Read and store an analog input from task4pin

  readcounter++;
  if (readcounter>=5){
    readcounter = 1;}
  ANLGinput = analogRead(task4pin);
  queue[readcounter] = ANLGinput;
  vTaskDelay(42 / portTICK_PERIOD_MS);}
  
  
void task5(void * parameter){ //Calculate average of the last 4 analog inputs
  task5avg = queue[1] + queue[2] + queue[3] + queue[4];
  compAvg = task5avg / 4;
  vTaskDelay(42 / portTICK_PERIOD_MS);
  }
    
void task6(void * parameter){ 
  while (task6counter <= 100){
    __asm__ __volatile__ ("nop");
    task6counter++;}
    vTaskDelay(100 / portTICK_PERIOD_MS);}
void task7(void * parameter){ //Check error state 
  if (compAvg > (0.5 * 1024)){
    error = 1;}
  else{
    error = 0;}
  vTaskDelay(333 / portTICK_PERIOD_MS);}
    
void task8(void * parameter){ //LED 2 reflects error state (on = error)
  digitalWrite(led2, error);
  delay(333);}
  
void task9(void * parameter){
  ///Prints data in the format of: "buttonState, frequency, average"
  pointer = pointer + 1;
  if (digitalRead(button2) == HIGH){
    Serial.print(buttonState);
    Serial.print(", " );
    Serial.print(frequency);
    Serial.print(", " );
    Serial.println(compAvg);
    Serial.print(", " );
    Serial.println(error);}

  atask9 table[pointer] = {buttonState,frequency,compAvg,error};
  
  vTaskDelay(5000 / portTICK_PERIOD_MS);}

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT); //Defines the directionality of the led 1 pin to output
  pinMode(led2, OUTPUT); //Defines the directionality of the led 2 pin to output
  pinMode(button1, INPUT); //Defines the directionality of the button 1 pin to input
  pinMode(task3pin, INPUT);
  pinMode(task4pin, INPUT);

  xTaskCreate(task1,"Task 1",1024,NULL,1,NULL);  
  xTaskCreate(task2,"Task 2", 1024, NULL, 1, NULL);
  xTaskCreate(task3,"Task 3",1024,NULL,1,NULL);  
  xTaskCreate(task4,"Task 4", 1024, NULL, 1, NULL);
  xTaskCreate(task5,"Task 5",1024,NULL,1,NULL);  
  xTaskCreate(task6,"Task 6", 1024, NULL, 1, NULL); 
  xTaskCreate(task7,"Task 7",1024,NULL,1,NULL);  
  xTaskCreate(task8,"Task 8", 1024, NULL, 1, NULL);  
  xTaskCreate(task9,"Task 9",1024,NULL,1,NULL);   
}

void loop() {
// put your main code here, to run repeatedly:
 
}
