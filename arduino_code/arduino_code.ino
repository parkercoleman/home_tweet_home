#include <toneAC.h>
#include <avr/pgmspace.h>

PROGMEM short maria_millis[] = {2283, 21, 381, 3, 381, 3, 2283, 21, 762, 6, 2283, 789, 1149, 3, 192, 0, 192, 0, 381, 3, 381, 3, 381, 3, 381, 3, 1521, 783, 693, 75, 1143, 9, 192, 0, 192, 0, 381, 3, 381, 3, 381, 3, 381, 3, 1521, 15, 1143, 9, 381, 3, 1143, 9, 381, 3, 255, 0, 255, 0, 258, 0, 255, 0, 255, 0, 258, 0, 2283, 21, 381, 3, 381, 3, 1038, 114, 381, 3, 255, 0, 255, 0, 258, 0, 255, 0, 255, 0, 258, 0, 1791, 0, 255, 258, 0, 171, 42, 0, 42, 0, 0, 255, 0, 258, 0, 2283, 21, 762, 6, 1143, 9, 348, 36, 573, 3, 192, 0, 573, 3, 192, 0, 573, 3, 192, 0, 1521, 15, 762, 6, 1143, 9, 348, 36, 255, 0, 255, 0, 258, 0, 255, 0, 255, 0, 258, 0, 2283, 21, 762, 6, 1143, 9, 381, 3, 573, 3, 192, 0, 255, 0, 255, 0, 258, 0, 573, 3, 192, 0, 1917, 3, 381, 3, 381, 3, 762, 6, 381, 3, 255, 0, 255, 0, 258, 0, 255, 0, 255, 0, 258, 0, 2283, 789, 2283, 21, 381, 3, 381, 3, 2685, 3, 381, 3, 3042, 3};
PROGMEM short maria_freqs[] = {932, 932, 880, 880, 932, 932, 1175, 1175, 1046, 1046, 932, 932, 1046, 1046, 587, 1175, 1046, 1046, 932, 932, 880, 880, 784, 784, 880, 880, 932, 932, 587, 1175, 1175, 1175, 1046, 1046, 932, 932, 880, 880, 784, 784, 587, 1175, 1319, 1319, 1175, 1175, 1109, 1109, 880, 880, 1046, 1046, 932, 932, 880, 880, 1046, 1046, 1175, 1175, 1245, 1245, 1046, 1046, 880, 880, 932, 932, 1175, 1175, 1046, 1046, 1046, 1046, 880, 880, 784, 523, 988, 659, 1175, 1175, 1397, 1397, 1175, 1175, 988, 659, 1046, 1046, 784, 880, 880, 932, 1046, 1046, 932, 932, 932, 880, 880, 784, 784, 698, 698, 698, 698, 1046, 1046, 1046, 1046, 1046, 1046, 988, 988, 1046, 1046, 1175, 1175, 1046, 1046, 1175, 1175, 932, 932, 932, 932, 1046, 1046, 1046, 1046, 1046, 1046, 988, 988, 1046, 1046, 1245, 1245, 1175, 1175, 1046, 1046, 932, 932, 932, 932, 1046, 1046, 1046, 1046, 1175, 1175, 1175, 1175, 1175, 1175, 1046, 1046, 1175, 1175, 1397, 1397, 1245, 1245, 1245, 1245, 784, 784, 1175, 1175, 1046, 1046, 1046, 1046, 932, 932, 880, 880, 932, 932, 1109, 1109, 1046, 1046, 932, 932, 1046, 1046, 932, 932, 880, 880, 932, 932, 1175, 1175, 1046, 1046, 932, 932};
PROGMEM short maria_volume[] = {5, 0, 6, 0, 6, 0, 7, 0, 6, 0, 5, 0, 5, 0, 6, 0, 6, 0, 6, 0, 5, 0, 5, 0, 6, 0, 7, 0, 5, 0, 6, 0, 5, 0, 5, 0, 6, 0, 5, 0, 7, 0, 6, 0, 6, 0, 6, 0, 5, 0, 6, 0, 5, 0, 6, 0, 6, 0, 6, 0, 6, 0, 5, 0, 5, 0, 6, 0, 7, 0, 6, 0, 6, 0, 8, 0, 6, 0, 6, 0, 6, 0, 7, 0, 5, 0, 5, 0, 6, 0, 5, 6, 0, 6, 6, 0, 5, 0, 0, 6, 0, 5, 0, 5, 0, 4, 0, 4, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 2, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 4, 0, 5, 0, 4, 0, 4, 0, 4, 0, 4, 0, 5, 0, 4, 0, 4, 0, 3, 0, 5, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 0, 5, 0, 4, 0, 4, 0, 5, 0, 4, 0, 4, 0, 4, 0, 5, 0, 4, 0, 4, 0};


int GREEN_PIN = 3;
int RED_PIN = 5;
int FIRE_PIN = 6;
int SWITCH_PIN = 2;

int CUR_GREEN = 255;
int CUR_RED = 0;

void setup() {
  int maria_len = 201;
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(FIRE_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  analogWrite(FIRE_PIN, 128);
  Serial.begin(9600);
}

void loop() {
  while(digitalRead(SWITCH_PIN) == 1){
    delay(10);
    
  }
  analogWrite(FIRE_PIN, 128);
  play_maria();
}

void play_maria(){
  int maria_len = 201;
  int i = 0;
  int lightTick = 0;
  int musicTick = 0;
  /*Start playing the first note*/
  toneAC(pgm_read_word(&(maria_freqs[i])), pgm_read_word(&(maria_volume[i])), pgm_read_word(&(maria_millis[i])), true);
  
  while(true){
    /*Check to see if we've been switched off*/
    if(digitalRead(SWITCH_PIN) == 1){
      /*We've been switched off*/
      shut_down();
      return;
    }
    
    lightTick++;
    musicTick++;
    if(musicTick >= pgm_read_word(&(maria_millis[i]))){
      /*If this is the case, we need to change notes*/
      i++;
      musicTick = 0;
      if(i > maria_len){
        return; /*The song is over*/
      }
      toneAC(pgm_read_word(&(maria_freqs[i])), pgm_read_word(&(maria_volume[i])), pgm_read_word(&(maria_millis[i])), true);
    }
    if(lightTick > 500){
      /*If this is the case, we need to flip the lights*/
      flop_lights();
      lightTick = 0;
    }
    delay(1);
  }
}

void shut_down(){
  toneAC(0, 0, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(RED_PIN, 0);
  analogWrite(FIRE_PIN, 0);
}

void flop_lights(){
  if(CUR_GREEN == 255){
    CUR_GREEN = 0;
    CUR_RED = 255;
  }
  else{
    CUR_GREEN=255;
    CUR_RED=0;
  }
  analogWrite(GREEN_PIN, CUR_GREEN);
  analogWrite(RED_PIN, CUR_RED);
}
