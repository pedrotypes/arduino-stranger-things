#include "FastLED.h"

#include <SPI.h>
#include <Ethernet.h>

#include <elapsedMillis.h> //load the library

elapsedMillis timeElapsed;//Create an Instance


// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168, 14, 177);

// fill in your Domain Name Server address here:
//IPAddress myDns(1, 1, 1, 1);

// initialize the library instance:
EthernetClient client;

//char server[] = "www.thatbulb.com/jt";
IPAddress server(18,217,187,12);

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

#define DATA_PIN 6
#define NUM_LEDS 100
#define COLOR_ORDER RGB
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];



String phrases[] = {
  "one",
  "two",
  "three",
  "four",
  "five"
};

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

//set default strings in an array
//overwrite the default values

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
    // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // give the ethernet module time to boot up:
  delay(1000);  
  
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  
  // start the Ethernet connection using a fixed IP address and DNS server:
  //Ethernet.begin(mac);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  httpRequest();
  
}
int phrase_counter = 0;
boolean can_do_next = true;
  String phrase = "";
  int i = 0;

// Blink all the letters for the word, one at a time
void say(char* word, int letter_duration=1000, int letter_spacing=500, int word_spacing=5000) {
  //for (int i = 0; word[i] != 0; i++) {//changed i to w
  int w = 0;
  timeElapsed = 0;
  //  for debugging
  //  letter_duration=100;
  //  letter_spacing=50;
  //  word_spacing=500;

  Serial.print("strlen(word): ");
  Serial.println(strlen(word));
  //each letter has duration + spacing
  while(w <= strlen(word)){
     //do the getting of the phrases
  
    int led = get_led_pos(word[w]);
    // Light it up
    if (w < strlen(word)){
      if (timeElapsed < letter_duration){
        leds[led] = CHSV(random(255, 255), 200, BRIGHTNESS); //does this need ot be random?
        FastLED.show();
        //Serial.println("show letter");
      } else if (timeElapsed >= letter_duration && timeElapsed < letter_duration + letter_spacing){
        //delay(letter_duration);
        //Serial.println("hide letter");
        // Turn it off
        leds[led] = CHSV(0, 0, 0);
        FastLED.show();
      } else if (timeElapsed  >= letter_duration + letter_spacing){
       // Serial.println("next letter");
        w++;
        timeElapsed = 0;
      }
    } else {
      if (timeElapsed > word_spacing){
        timeElapsed = 0;
        can_do_next = true;
        phrase_counter++;
        Serial.println("next word");
        w++;
      }        
    }
  }
}

void loop() {
  if (phrase_counter == 5){
    can_do_next = false;
    if (client.available()) {
          char c = client.read();
          
          if (c == '<') { //detected start of actual output
            Serial.println("BEGIN INPUT");
            phrase = ""; //set phrase to ""
            i = 0;
          } else if (c == '|'){ //detect pipe between words
            char charBuf[phrase.length()+1]; //create a new char array to work with say()
            //phrase.toCharArray(charBuf,phrase.length()+1);
            phrases[i] = phrase;
            
            Serial.print("adding: ");
            Serial.println(phrases[i]);
            
            phrase = ""; //once we've said the phrase, set to "" again
            i++;
          } else if (c == '>'){ //detect terminator
            phrases[i] = phrase;

            i = 0;
            
            Serial.print("adding: ");
            Serial.println(phrases[i]);
            
            phrase_counter = 0;
            can_do_next = true;
            
            httpRequest();
          } else { //normal character
            phrase = phrase + String(c); //start adding to the string
            //Serial.print("phrase: ");
            //Serial.println(phrase);
          }
        } else {
          Ethernet.begin(mac);
        }       
  }
  if (can_do_next == true){
    can_do_next = false;
    Serial.print("in loop saying: ");
    Serial.println(phrases[phrase_counter]);
    
    char charBuf[phrases[phrase_counter].length()+1]; //create a new char array to work with say()
    phrases[phrase_counter].toCharArray(charBuf,phrases[phrase_counter].length()+1);
    
    say(charBuf);
  }
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.println("GET /jt HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

