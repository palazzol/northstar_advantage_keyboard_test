
#define STROBE 2

// D0-D7
int data[8] = { 3,4,5,6,7,8,9,10 };

void writeAddress(int addr)
{
  // STROBE GOES LOW
  digitalWrite(STROBE, 0);
  delay(10);
  
  // ASSERT ADDRESS
  for(int i=0;i<8;i++) {
    digitalWrite(data[i], (addr>>i)&1); 
  }
  for(int i=0;i<8;i++) {
    pinMode(data[i], OUTPUT);
  }
  delay(10);
  
  // STROBE GOES HIGH
  digitalWrite(STROBE, 1);
  //delay(10);

  // DEASSERT ADDRESS
  for(int i=0;i<8;i++) {
    pinMode(data[i], INPUT);
  }
}

int readData()
{
  // READ BUS
  int rv = 0;
  for(int i=7;i>=0;i--) {
    rv <<= 1;
    rv = rv | digitalRead(data[i]);
  }
  return rv;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(STROBE, OUTPUT);
  digitalWrite(STROBE, 1);
  for(int i=0;i<8;i++) {
    pinMode(data[i], INPUT);
    digitalWrite(data[i], 0);
  }
  Serial.begin(115200);
}

void loop() {

  writeAddress(0x20);
  delay(200);
  writeAddress(0x10);
  delay(200);
  writeAddress(0x80);
  delay(200);
  writeAddress(0x40);
  delay(200);

  int d;
  for(int i=0;i<16;i++)
  {
    writeAddress(i);
    delay(20);
    d = readData();
    Serial.print(i,HEX);
    Serial.print(' ');
    Serial.println(d,HEX);
  }
  Serial.println();
}
