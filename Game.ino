#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
uint16_t vert=0, horz=0;
byte vpos=0, hpos=0, frames=19, randomNumber=0,c=0,score=0;
byte lastVal[4]={0,0,0,0};
byte man[] = {
  B00110,
  B01110,
  B01111,
  B01110,
  B10110,
  B11110,
  B01100,
  B00100
};
byte ship[] = {
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
  B01111,
  B00111,
  B00011
};
void setup() {
  randomSeed(analogRead(A3));
  pinMode(A2,2);
 lcd.init();
 lcd.backlight();
 lcd.createChar(0,man);
 lcd.createChar(1,ship);
 lcd.home();
 lcd.write(0);
 Serial.begin(9600);
}

void loop() {
  vert=analogRead(A0);
  horz=analogRead(A1);

  if(vert>650){
    vpos--;
    lcd.setCursor(hpos,vpos+1);
    lcd.print(" ");
  }
  else if(vert<450){
    vpos++;
    lcd.setCursor(hpos,vpos-1);
    lcd.print(" ");
  }
  if(horz>650){
    hpos--;
    lcd.setCursor(hpos+1,vpos);
    lcd.print(" ");
  }
    if(horz<450){
    hpos++;
    lcd.setCursor(hpos-1,vpos);
    lcd.print(" ");
  }
  vpos=constrain(vpos,0,3);
  hpos=constrain(hpos,0,19);
  lcd.setCursor(hpos,vpos);
  lcd.write(0);
  lcd.setCursor(frames+1,randomNumber);
  lcd.print(" ");
  lcd.setCursor(frames,randomNumber);
  lcd.write(1);
  lcd.setCursor(frames+randomNumber+1,randomNumber);
  lcd.print(" ");
  lcd.setCursor(frames+randomNumber,randomNumber);
  lcd.write(1);
  if(hpos==frames&&vpos==randomNumber||hpos==frames+randomNumber&&vpos==randomNumber){
    score=0;
    Serial.println("Game over");
  }
  for(byte i=1;i<4;i++)
  if(hpos==i&&vpos==i&&lastVal[i]==i){
    lastVal[i]=0;
    score++;
    lcd.setCursor(i,i);
    lcd.print(" ");
    Serial.println(score);
  }
  if (frames-- == 0){
    if(frames+randomNumber-1>0)
    lastVal[randomNumber]=frames+randomNumber+1;
    for(byte i=0;i<4;i++)
    randomNumber=random(4);
    frames=19;
    for(byte i=0;i<4;i++){
    lcd.setCursor(0,i);
    lcd.print(" ");
    }
  }
  //frames=(--frames==0xFF)?19:frames;
  delay(100);
}
