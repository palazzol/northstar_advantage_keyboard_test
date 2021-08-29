
#define STROBE 2

// D0-D7
//int data[8] = { 3,4,5,6,7,8,9,10 };
int data[8] = { 10,9,8,7,6,5,4,3 };
byte table[16][8] = { { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 }, 
                      { 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },  
                      { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 }, 
                      { 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f },  
                      { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27 }, 
                      { 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f },  
                      { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37 }, 
                      { 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f },  
                      { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47 }, 
                      { 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f },  
                      { 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57 }, 
                      { 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f },  
                      { 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67 }, 
                      { 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f },  
                      { 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77 }, 
                      { 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f }, };
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

void blinky(){
  writeAddress(0x20); //cursor on
  delay(200);
  writeAddress(0x10); //cursor off
  delay(200);
  writeAddress(0x80); //caps on
  delay(200);
  writeAddress(0x40); //caps off
  delay(200);
}

void loop() {

  blinky();

  int d;
  for(int i=0;i<16;i++)
  {
    writeAddress(i);
    delay(20);
    d = readData();
    printChar(i,d);
  }
  Serial.println();
}

void printChar(int addr, int data){
  boolean D0 = data & 0x80;
  boolean D1 = data & 0x40;
  boolean D2 = data & 0x20;
  boolean D3 = data & 0x10;
  boolean D4 = data & 0x08;
  boolean D5 = data & 0x04;
  boolean D6 = data & 0x02;
  boolean D7 = data & 0x01;
  if(!D0){
    Serial.print(table[addr][0], HEX);
    Serial.print(", ");
  }
  if(!D1){
    Serial.print(table[addr][1], HEX);
    Serial.print(", ");
  }
  if(!D2){
    Serial.print(table[addr][2], HEX);
    Serial.print(", ");
  }
  if(!D3){
    Serial.print(table[addr][3], HEX);
    Serial.print(", ");
  }
  if(!D4){
    Serial.print(table[addr][4], HEX);
    Serial.print(", ");
  }
  if(!D5){
    Serial.print(table[addr][5], HEX);
    Serial.print(", ");
  }
  if(!D6){
    Serial.print(table[addr][6], HEX);
    Serial.print(", ");
  }
  if(!D7){
    Serial.print(table[addr][7], HEX);
    Serial.print(", ");
  }
}
