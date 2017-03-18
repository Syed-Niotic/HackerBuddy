
  int LED2 = 4; //the Grove port No. you attached a button to
  int LED1 = 8; //the Grove port No. you attached an LED to
void setup(){
  pinMode(LED1, OUTPUT); //set button as an INPUT device
  pinMode(LED2, OUTPUT); //set LED as an OUTPUT device
  pinMode(12, OUTPUT);
}
void loop(){
  digitalWrite(12,HIGH);
  digitalWrite(LED1,HIGH); 
  digitalWrite(LED2,LOW);
  delay(200);
  digitalWrite(LED1,LOW); 
  digitalWrite(LED2,HIGH);
  delay(200);
  
}
