#include <Arduino.h>

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define NOTE_F8 5588
#define NOTE_FS8 5920
#define REST 0

#define buzzerPin 9 // buzzer
#define ledPin 13 // led
#define buttonPin1 2 // button to play 1st melody - Once Upon a December (Ouad)
#define buttonPin2 4 // button to play 2nd melody - All Star

int melodyOuad[] = { // melody for button 1
  NOTE_FS4, NOTE_G4,
  NOTE_FS4,
  NOTE_A4, NOTE_G4,
  NOTE_E4,
  NOTE_G4, NOTE_E4,
  NOTE_FS4, NOTE_D4, NOTE_B3,
  NOTE_E4,
  NOTE_FS4,
  NOTE_FS4, NOTE_G4,
  NOTE_FS4, NOTE_FS4, NOTE_B4,
  NOTE_E4,
  NOTE_G4, NOTE_E4,
  NOTE_FS4, NOTE_D4, NOTE_B3,
  NOTE_CS4, NOTE_D4,
  NOTE_B3,
};

int tempoOuad[] = { // tempo for button 1
  2, 4, 
  2,
  2, 4,
  2,
  2, 4,
  4, 4, 4,
  2,
  2,
  2, 4,
  2, 2, 4,
  2,
  2, 4,
  4, 4, 4,
  2, 4,
  2,
};

int melodyAllStar[] = { // melody for button 2
  NOTE_FS4,
  NOTE_B4, NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_A4,
  NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_E4, 
  NOTE_E4,
  NOTE_B4, NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_CS4,
  NOTE_B3, REST, NOTE_E4, NOTE_E4,
  NOTE_B4, NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4,
  NOTE_E4, NOTE_E4, NOTE_A4,
  NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_B4,
  NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_FS4,
  NOTE_CS4,
};

int tempoAllStar[] = { // tempo for button 2
  4,
  8, 8, 4, 8, 8, 8, 4,
  8, 8, 8, 8, 4,
  8,
  8, 8, 8, 8, 8, 8, 8, 4,
  4, 8, 8, 8,
  8, 8, 8, 8, 8,
  8, 8, 4,
  8, 8, 8, 8, 8, 8, 4,
  8, 8, 4, 8, 8, 4,
  4,
};

int switchOne = 0; // initialize button 1
int switchTwo = 0; // initialize button 2

void setup(void) {
  pinMode(buzzerPin, OUTPUT); // Buzzer
  pinMode(ledPin, OUTPUT); // LED
  pinMode(buttonPin1, INPUT); // Button1
  pinMode(buttonPin2, INPUT); // Button2

  Serial.begin(9600); // For serial communication
}

void loop() {
  switchOne = digitalRead(buttonPin1);
  switchTwo = digitalRead(buttonPin2);
  
  if (switchOne == HIGH) { // if button 1 pressed, play OUAD
    sing(1);

  } else if (switchTwo == HIGH) { // if button 2 pressed, play All Star
    sing(2);
  }

}

int song = 0;

void sing(int song) {
  if (song == 1) {
    Serial.println("Button 1 pressed");
    Serial.println(" 'Playing: Once Upon a December' ");
    
    int size = sizeof(melodyOuad) / sizeof(int); // Calculate size of melody array

    // Iterate over the notes of the melody
    for (int thisNote = 0; thisNote < size; thisNote++) {
      
      // Calculate note duration based on tempo
      int noteDuration = 1000 / tempoOuad[thisNote]; // 1 second = 1000, so 1000 / note type
      // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

      // Play the note
      buzz(buzzerPin, melodyOuad[thisNote], noteDuration);

      // Add a pause between notes - set a minimum time between them
      int pauseBetweenNotes = noteDuration * 1.30; // Note duration + 1.30 seems to sound alright
      delay(pauseBetweenNotes);

      // Stop playing the note
      buzz(buzzerPin, 0, noteDuration);
        
     }

  } else if (song == 2) {
      Serial.println("Button 2 pressed");
      Serial.println(" 'Playing: All Star' ");
      
      int size = sizeof(melodyAllStar) / sizeof(int); // Calculate size of melody array

      // Iterate over the notes of the melody
      for (int thisNote = 0; thisNote < size; thisNote++) {
      
      // Calculate note duration based on tempo
      int noteDuration = 1000 / tempoAllStar[thisNote]; // 1 second = 1000, so 1000 / note type
      // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

      // Play the note
      buzz(buzzerPin, melodyAllStar[thisNote], noteDuration);

      // Add a pause between notes - set a minimum time between them
      int pauseBetweenNotes = noteDuration * 1.30; // Note duration + 1.30 seems to sound alright
      delay(pauseBetweenNotes);

      // Stop playing the note
      buzz(buzzerPin, 0, noteDuration);
        
      }
  }
  
}

void buzz(int targetPin, long frequency, long length) { // Function to play a note
  
  digitalWrite(13, HIGH); // Led lights up

  // Calculate the delay value between transitions
  long delayValue = 1000000 / frequency / 2; 
  // 1 second's worth of microseconds (1,000,000), divided by the frequency,
  // then split in half since there are two phases to each cycle - a sound wave has 2 phases

  // Calculate the number of cycles for proper timing
  long numCycles = frequency * length / 1000; 
  // Multiply frequency (cycles per second) by the length to get the total number of cycles needed
  // to produce the sound for the specified duration.
  // Divide by 1000 to convert from milliseconds to seconds

  // Generate the tone for the specified length of time
  for (long i = 0; i < numCycles; i++) { 
    
    digitalWrite(targetPin, HIGH); // Set buzzer pin to high to push out the diaphragm
    delayMicroseconds(delayValue); // Wait for the calculated delay value
    
    digitalWrite(targetPin, LOW); // Set buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // Wait again or the calculated delay value
  
  }
  
  digitalWrite(13, LOW); // Led turns off

}
