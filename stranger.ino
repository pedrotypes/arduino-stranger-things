#include "FastLED.h"

#define DATA_PIN 6
#define NUM_LEDS 100
#define COLOR_ORDER RGB
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

// Map letter char code => LED position index
// { CHAR CODE , LED INDEX }
int letter_map[][2] = {
    /* a */ {97, 16},
    /* b */ {98, 15},
    /* c */ {99, 13},
    /* d */ {100, 11},
    /* e */ {101, 9},
    /* f */ {102, 7},
    /* g */ {103, 5},
    /* h */ {104, 3},
    /* i */ {105, 23},
    /* j */ {106, 25},
    /* k */ {107, 26},
    /* l */ {108, 28},
    /* m */ {109, 30},
    /* n */ {110, 32},
    /* o */ {111, 34},
    /* p */ {112, 36},
    /* q */ {113, 38},
    /* r */ {114, 64},
    /* s */ {115, 63},
    /* t */ {116, 61},
    /* u */ {117, 60},
    /* v */ {118, 58},
    /* w */ {119, 57},
    /* x */ {120, 55},
    /* y */ {121, 54},
    /* z */ {122, 52},
};

int get_led_pos(int letter) {
    for (int i = 0; letter_map[i] > 0; i++) {
        if (letter_map[i][0] == letter) {
            return letter_map[i][1];
        }
    }

    return 999; // position doesn't exist in the string
}

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

// Blink all the letters for the word, one at a time
void say(char* word, int letter_duration=1000, int letter_spacing=500, int word_spacing=5000) {

  for (int i = 0; word[i] != 0; i++) {
    int led = get_led_pos(word[i]);

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

  // Wait a bit until the next word
  delay(word_spacing);
}

void loop() {
  say("hello");
  say("itsme");
  say("imhere");
  say("help");
  say("run");
  say("dickbutt");
  say("jollierthings");
}




