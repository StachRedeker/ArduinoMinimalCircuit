///*** ARDUINO MINIMAL CIRCUIT ***///
///*** STACH REDEKER ***///
///*** 2023 ***///

#define LED 8
#define b1 7
#define b2 6
#define sw1 13
#define sw2 12
#define sw3 11
#define sw4 10

// the only global variable is for keeping track of the status of the LED if the SR latch is activated
bool SRstatus = 0;


void setup() {
  
  pinMode(LED, OUTPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);

}

void loop() {

  int switchStatus = getSwitchStatus();
  
  switch (switchStatus) {
    case 1:
      digitalWrite(LED, wire());
    break;
    case 2:
      digitalWrite(LED, NOT());
    break;
    case 3:
      digitalWrite(LED, OR());
    break;
    case 4:
      digitalWrite(LED, AND());
    break;
    case 5:
      digitalWrite(LED, NOR());
    break;
    case 6:
      digitalWrite(LED, NAND());
    break;
    case 7:
      digitalWrite(LED, XOR());
    break;
    case 8:
      digitalWrite(LED, XNOR());
    break;
    case 9:
      SRlatch();
      digitalWrite(LED, SRstatus);
    break;
    default:
      digitalWrite(LED, LOW);
    break;
  }
  

}

int getSwitchStatus () {
  return (8*digitalRead(sw1) + 4*digitalRead(sw2) + 2*digitalRead(sw3) + digitalRead(sw4));
}

bool wire () {
  return digitalRead(b1);  
}

bool NOT () {
  return !digitalRead(b1);
}

bool OR () {
  return (digitalRead(b1) || digitalRead(b2));
}

bool AND () {
  return (digitalRead(b1) && digitalRead(b2));
}

bool NOR () {
  return !OR();
}

bool NAND () {
  return !AND();
}

bool XOR () {
  return (digitalRead(b1) ^ digitalRead(b2));
}

bool XNOR () {
  return !XOR();
}

void SRlatch () {

  if (digitalRead(b1) == 1) { // set
    SRstatus = 1;
    return;
  }

  if (digitalRead(b2) == 1) { // reset
    SRstatus = 0;
    return;
  }

  return; // implicit return if neither is the case, SRstatus remains unchanged
}
