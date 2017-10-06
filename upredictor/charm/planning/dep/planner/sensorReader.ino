int nSensor = 30;
char pinStatuses[30];

void setup() {
  Serial.begin(9600);

  /*Pins 0&1 are serial I/O*/
  /*Pins 2-19 = Table screw holes 0-17*/
  /*Pins 20-21 are ignored for easier wiring
  /*Pins 22-33 = Rack holes 0 - 11*/
  for (int i = 0; i < nSensor; i++)  pinMode(i + 2, INPUT);

}

void loop() {
  char buffer[1];
  int messageAction;
  for (int i = 0 ; Serial.available() > 0; i++) {
    buffer[i] = Serial.read();
    messageAction = atoi(buffer);
  }
  switch (messageAction) {
    case 0:
      {
        for (int i = 0; i < nSensor; i++)  
          if (i < 18) {
            pinStatuses[i] = digitalRead(i + 2);
          } 
          else if (i >= 18) {
            pinStatuses[i] = digitalRead(i + 4);
          } 
         Serial.write(pinStatuses, 30);
      }
      break;
  }
}

