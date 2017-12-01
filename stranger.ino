#include "FastLED.h"

#define DATA_PIN 6
#define NUM_LEDS 100
#define COLOR_ORDER RGB
#define BRIGHTNESS 100

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

CRGB leds[NUM_LEDS];

// The alphabet to LED map
int A[] = {1, 2, 3, 4, 0};
int B[] = {4, 5, 6, 0};
int C[] = {7, 8, 9, 0};
int D[] = {10, 11, 12, 0};
int E[] = {13, 14, 15, 0};
int F[] = {16, 17, 18, 0};
int G[] = {19, 20, 21, 0};
int H[] = {22, 23, 24, 0};
int I[] = {25, 26, 27, 0};
int J[] = {28, 29, 30, 0};
int K[] = {31, 32, 33, 0};
int L[] = {34, 35, 36, 0};
int M[] = {37, 38, 39, 0};
int N[] = {40, 41, 42, 0};
int O[] = {43, 44, 45, 0};
int P[] = {46, 47, 48, 0};
int Q[] = {49, 50, 51, 0};
int R[] = {52, 53, 54, 0};
int S[] = {55, 56, 57, 0};
int T[] = {58, 59, 60, 0};
int U[] = {61, 62, 63, 0};
int V[] = {64, 65, 66, 0};
int W[] = {67, 68, 69, 0};
int X[] = {70, 71, 72, 0};
int Y[] = {73, 74, 75, 0};
int Z[] = {76, 77, 78, 0};
int END[1] = {0};


// Words to say -> Maps to arrays of LEDs. This needs to be declared here
// because I can't deal with dynamic arrays right now
int* HELLO[] = {H,E,L,L,O, END};
int* DICKBUTT[] = {D,I,C,K,B,U,T,T, END};

int* IMHERE[] = {I,M,H,E,R,E, END};
int* RUN[] = {R,U,N, END};
int* HELP[] = {H,E,L,P, END};

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

void allOff() {
  // Power down all the letters
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, 0, 0);
    FastLED.show();
  }
}

// Turn on all the letters for the word, wait a bit, then turn off
void say(int** letters, int duration=5000, int wait=1000) {

  // Light up all the letters
  int i = 0;
  while (1) {
    // Break out if we found the END element
    if (letters[i][0] == 0) {
      break;
    }

    int key = 0;
    while (1) {
  
      int led = letters[i][key];
      key++;
      // Break out if we found the 0 element
      if (led == 0) {
        break;
      }
      
      leds[led] = CHSV(random(0, 255), 200, BRIGHTNESS);
      FastLED.show();
      delay(10);
    }

    i++;
  }

  // Leave them on for a while
  delay(duration);

  // Turn them off
  allOff();

  // Wait a bit until the next word
  delay(wait);
}

void loop() { 
  say(HELLO);
  say(IMHERE);
  say(HELP);
  say(RUN);
  say(DICKBUTT);
}

