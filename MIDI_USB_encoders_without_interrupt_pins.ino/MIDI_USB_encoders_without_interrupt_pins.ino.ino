
#include <MIDIUSB.h>


int value_buttons = analogRead(A3);
int rotary12pos2 = analogRead(A1);
int rotary12pos = analogRead(A2);

unsigned long previousMillis = 0;
const long interval = 1;
int firstPartDuration = 50; // czas trwania części pierwszej w milisekundach
int secondPartDuration = 2; // czas trwania części drugiej w milisekundach

  static uint8_t Old_AB_1 = 3;
  static uint8_t Old_AB_2 = 3;
  static uint8_t Old_AB_3 = 3;
  static uint8_t Old_AB_4 = 3;
  static uint8_t Old_AB_5 = 3;
  static uint8_t Old_AB_6 = 3;
  
  
    // Lookup table index
  static int8_t encval_1 = 0; 
  static int8_t encval_2 = 0; 
  static int8_t encval_3 = 0; 
  static int8_t encval_4 = 0; 
  static int8_t encval_5 = 0; 
  static int8_t encval_6 = 0; 
  
    // Encoder value  
static const int8_t enc_states[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table

// rotary encoders

#define PIN_A_1 2   // rotar prawy góra
#define PIN_B_1 3

#define PIN_A_2 4   // rotar prawy dół
#define PIN_B_2 5

#define PIN_A_3 7   // rotar prawy środek
#define PIN_B_3 6

#define PIN_A_4 8   // rotar lewy góra
#define PIN_B_4 9

#define PIN_A_5 10    // rotar lewy dół
#define PIN_B_5 16

#define PIN_A_6 14    // rotar lewy środek
#define PIN_B_6 15

#define PIN_A_7 A0  // rotar środek
#define PIN_B_7 A1


int pinToButtonMap = A0;
int set_rotary = -1;

// Last state of the button
int lastButtonState = 0;

int rotary_1_pos= 0;
int rotary_1_pos_old = rotary_1_pos;

int rotary_2_pos= 0;
int rotary_2_pos_old = rotary_2_pos;

int rotary_3_pos= 0;
int rotary_3_pos_old = rotary_3_pos;

int rotary_4_pos= 0;
int rotary_4_pos_old = rotary_4_pos;

int scale = 4;


int button_delay= 10;

void setup(){


/////////////// rotary encoders

pinMode(PIN_A_1, INPUT_PULLUP);
pinMode(PIN_B_1, INPUT_PULLUP);

pinMode(PIN_A_2, INPUT_PULLUP);
pinMode(PIN_B_2, INPUT_PULLUP);

pinMode(PIN_A_3, INPUT_PULLUP);
pinMode(PIN_B_3, INPUT_PULLUP);

pinMode(PIN_A_4, INPUT_PULLUP);
pinMode(PIN_B_4, INPUT_PULLUP);

}

void loop() {
///////////////// rotary encoders
read_encoder_1();
read_encoder_2();
read_encoder_3();
read_encoder_4();

  // If count has changed print the new value to serial
  if(set_rotary != -1){
    delay(100);
    
    set_rotary = -1;
    
  }


if(rotary_1_pos != rotary_1_pos_old){
  Serial.println(rotary_1_pos);
  controlChange(1,1,rotary_1_pos);
  MidiUSB.flush();
  rotary_1_pos_old = rotary_1_pos;
}
if(rotary_2_pos != rotary_2_pos_old){
  Serial.println(rotary_2_pos);
  controlChange(2,1,rotary_2_pos);
  MidiUSB.flush();
  rotary_2_pos_old = rotary_2_pos;
}
if(rotary_3_pos != rotary_3_pos_old){
  Serial.println(rotary_3_pos);
  controlChange(3,1,rotary_3_pos);
  MidiUSB.flush();
  rotary_3_pos_old = rotary_3_pos;
}
if(rotary_4_pos != rotary_4_pos_old){
  Serial.println(rotary_4_pos);
  controlChange(4,1,rotary_4_pos);
  MidiUSB.flush();
  rotary_4_pos_old = rotary_4_pos;
}

}


void read_encoder_1() {
 
  // Encoder interrupt routine for both pins.
  // if they are valid and have rotated a full indent

  Old_AB_1 <<=2;  // Remember previous state

  if (digitalRead(PIN_A_1)) Old_AB_1 |= 0x02; // Add current state of pin A
  if (digitalRead(PIN_B_1)) Old_AB_1 |= 0x01; // Add current state of pin B
  
  encval_1 += enc_states[( Old_AB_1 & 0x0f )];

  // Update counter_1 if encoder has rotated a full indent, that is at least 4 steps
  if( encval_1 > 3 ) {        // Four steps forward

     if(rotary_1_pos<=0){
      rotary_1_pos=0;
      }else{rotary_1_pos=rotary_1_pos-scale;}

    encval_1 = 0;
  }
  else if( encval_1 < -3 ) {        // Four steps backward

    if(rotary_1_pos>=127){
      rotary_1_pos=127;
      }else{rotary_1_pos=rotary_1_pos+scale;}
             
    encval_1 = 0;
  }
} 



void read_encoder_2() {
 
  // Encoder interrupt routine for both pins.
  // if they are valid and have rotated a full indent

  Old_AB_2 <<=2;  // Remember previous state

  if (digitalRead(PIN_A_2)) Old_AB_2 |= 0x02; // Add current state of pin A
  if (digitalRead(PIN_B_2)) Old_AB_2 |= 0x01; // Add current state of pin B
  
  encval_2 += enc_states[( Old_AB_2 & 0x0f )];

  // Update counter_1 if encoder has rotated a full indent, that is at least 4 steps
  if( encval_2 > 3 ) {        // Four steps forward

    if(rotary_2_pos<=0){
        rotary_2_pos=0;
      }else{rotary_2_pos=rotary_2_pos-scale;}
    encval_2 = 0;
  }
  else if( encval_2 < -3 ) {        // Four steps backward

              // Update counter_1
      if(rotary_2_pos>=127){
        rotary_2_pos=127;
      }else{rotary_2_pos=rotary_2_pos+scale;}
    encval_2 = 0;
  }
} 

void read_encoder_3() {
 
  // Encoder interrupt routine for both pins.
  // if they are valid and have rotated a full indent

  Old_AB_3 <<=2;  // Remember previous state

  if (digitalRead(PIN_A_3)) Old_AB_3 |= 0x02; // Add current state of pin A
  if (digitalRead(PIN_B_3)) Old_AB_3 |= 0x01; // Add current state of pin B
  
  encval_3 += enc_states[( Old_AB_3 & 0x0f )];

  // Update counter_1 if encoder has rotated a full indent, that is at least 4 steps
  if( encval_3 > 3 ) {        // Four steps forward

    if(rotary_3_pos<=0){
        rotary_3_pos=0;
      }else{rotary_3_pos=rotary_3_pos-scale;}

    encval_3 = 0;
  }
  else if( encval_3 < -3 ) {        // Four steps backward

      if(rotary_3_pos>=127){
        rotary_3_pos=127;
      }else{rotary_3_pos=rotary_3_pos+scale;}

    encval_3 = 0;
  }
} 

void read_encoder_4() {
 
  // Encoder interrupt routine for both pins.
  // if they are valid and have rotated a full indent

  Old_AB_4 <<=2;  // Remember previous state

  if (digitalRead(PIN_A_4)) Old_AB_4 |= 0x02; // Add current state of pin A
  if (digitalRead(PIN_B_4)) Old_AB_4 |= 0x01; // Add current state of pin B
  
  encval_4 += enc_states[( Old_AB_4 & 0x0f )];

  // Update counter_1 if encoder has rotated a full indent, that is at least 4 steps
  if( encval_4 > 3 ) {        // Four steps forward

    if(rotary_4_pos<=0){
        rotary_4_pos=0;
      }else{rotary_4_pos=rotary_4_pos-scale;}

    encval_4 = 0;
  }
  else if( encval_4 < -3 ) {        // Four steps backward


      if(rotary_4_pos>=127){
        rotary_4_pos=127;
      }else{rotary_4_pos=rotary_4_pos+scale;}
    encval_4 = 0;
  }
} 

void controlChange(byte channel, byte control, byte value){
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value };
  MidiUSB.sendMIDI(event);
}








  


