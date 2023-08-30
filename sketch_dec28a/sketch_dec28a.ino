
int Yk_D0=8;
int Yk_D1=9;
int buzz=10;

void setup() {

  Serial.begin(9600);
    
 
  Serial.println(" logging time completed!");
  randomSeed(analogRead(0));
  pinMode(Yk_D0, INPUT);
  digitalWrite(Yk_D0, LOW);
   pinMode(Yk_D1, INPUT);
  digitalWrite(Yk_D1, LOW);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(Yk_D0) == HIGH){
  
  digitalWrite(buzz,HIGH);
  Serial.println(" Button Pressed");
  }
  if(digitalRead(Yk_D1) == HIGH){
  
  digitalWrite(buzz,LOW);
  Serial.println(" Buzzer Off");
  }


  

}
