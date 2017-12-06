#include "FastLED.h"

#define DATA_PIN 6
#define NUM_LEDS 100
#define COLOR_ORDER RGB
#define BRIGHTNESS 255

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

CRGB leds[NUM_LEDS];

// The alphabet to LED map
int A[] = {16, 0};
int B[] = {15, 0};
int C[] = {13, 0};
int D[] = {11, 0};
int E[] = {9, 0};
int F[] = {7, 0};
int G[] = {5, 0};
int H[] = {3, 0};
int I[] = {23, 0};
int J[] = {25, 0};
int K[] = {26, 0};
int L[] = {28, 0};
int M[] = {30, 0};
int N[] = {32, 0};
int O[] = {34, 0};
int P[] = {36, 0};
int Q[] = {38, 0};
int R[] = {64, 0};
int S[] = {63, 0};
int T[] = {61, 0};
int U[] = {60, 0};
int V[] = {58, 0};
int W[] = {57, 0};
int X[] = {55, 0};
int Y[] = {54, 0};
int Z[] = {52, 0};
int END[1] = {0};


// Words to say -> Maps to arrays of LEDs. This needs to be declared here
// because I can't deal with dynamic arrays right now

// 22

int* abc[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, END};
int* HELLO[] = {H,E,L,L,O, END};
int* ITSME[] = {I,T,S,M,E, END};
int* IMHERE[] = {I,M,H,E,R,E, END};
int* HELP[] = {H,E,L,P, END};
int* RUN[] = {R,U,N, END};
int* DICKBUTT[] = {D,I,C,K,B,U,T,T, END};
int* JOLLIERTHINGS[] = {J,O,L,L,I,E,R,T,H,I,N,G,S, END};

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

// Blink all the letters for the word, one at a time
void say(int** letters, int letter_duration=1000, int letter_spacing=500, int word_spacing=5000) {

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

      // Light it up
      leds[led] = CHSV(random(0, 255), 200, BRIGHTNESS);
      FastLED.show();

      // Wait a bit
      delay(letter_duration);
    
      // Turn it off
      leds[led] = CHSV(0, 0, 0);
      FastLED.show();

      // Wait a bit
      delay(letter_spacing);
    }

    i++;
  }

  // Wait a bit until the next word
  delay(word_spacing);
}

void loop() { 
  say(HELLO);
  say(ITSME);
  say(IMHERE);
  say(HELP);
  say(RUN);
  say(DICKBUTT);
  say(JOLLIERTHINGS);
}

