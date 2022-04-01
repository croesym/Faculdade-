void soInit(void){
  pinMode(1,OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
}

void PulseEnClock(void){
  digitalWrite(1, HIGH);
  digitalWrite(1, LOW);
}

void PulseClockData(void){
  digitalWrite(0, HIGH);
  digitalWrite(0, LOW);
}

void PulseEnDisp(void){
  digitalWrite(3, HIGH);
  digitalWrite(3, LOW);
}

void PulseEnDisp2(void){
  digitalWrite(6, HIGH);
  digitalWrite(6, LOW);
}

void soWrite(char value){
  char i;
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  for(i=0; i<8; i++){
    digitalWrite(2, value & 0x80);
    PulseClockData();
    value<<=1;
  }
  PulseEnClock();
}


void pushByte(char value1, char value2, int rs, int rs2){
  
  //Bloco codado conforme vimos em sala de aula.
  char t1,t2,t3;
  t1= value2 >>4;
  t1= t1&0x0f;
  t2= value1 & 0xf0 >>4;
  t3=t1|t2;
  soWrite(t3);
  digitalWrite(4, rs);
  digitalWrite(6, rs2);
  PulseEnDisp();
  PulseEnDisp2();
  //////////////////////////////////////////////
  
  //Estamos em dúvida nesse bloco da "inversão" dos bits,
  //tentamos várias operações bitwise mas sem sucesso.
  t1= value2;
  t1= t1&0x0f;
  t2= value1 & 0xf0 >> 4;
  t3= t1|t2;
  soWrite(t3); 
  //////////////////////////////////////////////////////
}

//Passamos todos os parâmetros.
void lcdCommand(char value1, char value2){
  pushByte(value1, value2, LOW, LOW);
  delay(2);
}

//Passamos todos os parâmetros.
void lcdChar(char value1, char value2){
  pushByte(value1, value2, HIGH, HIGH);
  delay(1);
}


//Tentamos ajustar a função string para
//imprimir nos dois LCDs, sem sucesso.
void lcdString(char msg[], char msg2[]){
  int i=0;
  while (msg[i]& msg[i] !=0){
    lcdChar(msg[i], msg2[i]);
    i++;
  }
}


void lcdInit()
{
  //Definimos os pinos de saída do LCD 1 e 2.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  soInit();
  delay(10);
  
  //Passamos os parâmetros porém sem certeza
  //das operações bitwise pro segundo LCD.
  lcdCommand(0x01,0x01);
  lcdCommand(0x03,0x03);
  lcdCommand(0x06,0x06);
  lcdCommand(0x0C,0x0C);
  lcdCommand(0x28,0x28);
}

void setup(){
  lcdInit();
  lcdString("AA","AA");
}

  void loop(){
    
  }