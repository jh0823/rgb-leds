#include <FastLED.h>
#define LED_PIN 2 // DATA PIN 
#define NUM_LEDS 300 // TOTAL NUMBER OF LEDS TO USE
#define UPDATE_LEDS 10 // NUMBER OF LEDS TO CHANGE AT A TIME
#define SOUND_PIN 0 // ANALOG PIN 

//Defines the array of leds
CRGB leds[NUM_LEDS];

//Defines color structure of RGB
struct color {
  int r;
  int g;
  int b;
};
typedef struct color Color;

//Variable for voltage reading from SOUND_PIN
int bufferValue = 0;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS); 
  FastLED.clear();
  pinMode(A0,INPUT);
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(0,0,0);
  }
  delay(40);
  FastLED.show();
  FastLED.setBrightness(50);
}

void loop() {
   
    Color newcolor;
    //Read voltage level
    bufferValue = analogRead(SOUND_PIN);
    bufferValue = bufferValue/2;
    //Serial.println(bufferValue);

    
 //Shifts all LEDS to the right by UPDATE_LEDS number each time 
    for (int i = NUM_LEDS - 1; i >= UPDATE_LEDS; i--) {
      leds[i] = leds[i-UPDATE_LEDS];  
    }
   
  //Generate new color
  newcolor = colorGen(bufferValue);
  
  //Sets left most UPDATE_LEDS with new color
  for (int i = 0; i < UPDATE_LEDS; i++){
      leds[i] = CRGB(newcolor.r, newcolor.g, newcolor.b);
    }
    FastLED.show();
    //printColor(newcolor);
    delay(5);
    
}

//Sets color depending on voltage reading. Currently, only displays around 5 colors without a pitch reader.
Color colorGen(int a)
{
  Color c;
 
  if (a > 5 && a < 50)
  {
    setColor(&c, 255,0,0); // red
  } 
  else if (a >= 25 && a <= 100)
  {
    setColor(&c, 255, 98,0); // orange
  }
  else if (a > 100 && a <= 175)
  {
    setColor(&c, 255,231,0); // yellow
  }
  else if (a > 175 && a <= 250)
  {
    setColor(&c, 0,255,0); //green
  } 
  else if (a > 250 && a <= 325)
  {
    setColor(&c, 0,255,255); //cyan
  }
  else if (a > 325 && a <= 400)
  {
    setColor(&c, 0,0,255); //blue
  }
  else if (a > 400 && a <= 470)
  {
    setColor(&c, 119,0,255); // purple
  }
  else
  {
    setColor(&c, 0,0,0); //no color

  }
  setColor(&c, c.r, c.g, c.b);

  return c;
  
}
void printColor (Color c){
  Serial.print("( ");
  Serial.print(c.r);
  Serial.print(", ");
  Serial.print(c.g);
  Serial.print(", ");
  Serial.print(c.b);
  Serial.println(" )");
}
void setColor(Color *c, int r, int g, int b)
{
  c->r = r;
  c->g = g;
  c->b = b;
}
