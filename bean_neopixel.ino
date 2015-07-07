#include <Adafruit_NeoPixel.h>

#define numOfLEDs 272
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numOfLEDs, 4, NEO_GRB + NEO_KHZ800);

//The control # from the Sandbox X-Y trackpad screen
#define XYPAD_X 2
#define XYPAD_Y 150
#define SLIDER 11
#define CHECKBOX 12

//If drawingMode=true LEDs won't turn off when you change position on the X-Y trackpad
bool drawingMode=true;
int LEDsTurnedOn[numOfLEDs]; 
uint32_t color=0;
byte pixel_X = 0;
byte pixel_Y = 0;   
byte buffer[10];

#define STRIPLEN 136

#define WAVELENGTH 10
int wave[WAVELENGTH];

const unsigned char linear[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,9,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,13,13,13,14,14,14,15,15,15,16,16,16,17,17,17,18,18,19,19,20,20,20,21,21,22,22,23,23,24,25,25,26,26,27,28,28,29,29,30,31,32,32,33,34,34,35,36,37,38,39,39,40,41,42,43,44,45,46,47,48,49,50,51,53,54,55,56,57,59,60,61,63,64,66,67,69,70,72,73,75,77,78,80,82,84,86,87,89,91,93,96,98,100,102,104,107,109,111,114,116,119,122,124,127,130,133,136,139,142,145,148,151,155,158,162,165,169,173,177,180,184,188,193,197,201,206,210,215,220,225,229,235,240,245,250};

uint8_t sintab[256];

unsigned long time;
uint32_t Colors[2];
//uint32_t tColors[2];
int Value[]={3,1,1,1};
bool Button[]={0,1,1,1};
int iterator=0;
float fiterator=0;
bool locked=false;

   byte effect=16, controlByte, valueByte;
 
void setup() 
{
  	Bean.setBeanName("Dadada");
	Bean.enableWakeOnConnect(true);

  
  Serial.begin(57600);
  Serial.setTimeout(5);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for(int i=0;i<WAVELENGTH;i++) {
    wave[i]=(sin(6.283/WAVELENGTH/2*i))*100;
  }

  Colors[0]=strip.Color(255,0,0);
  Colors[1]=strip.Color(0,255,0);

  for (int i=0; i<256; i++) 
    sintab[i] = (uint8_t)(sin(i/256.0*PI*2)*127+127);


}
 
void loop() {
  switch(effect) {
      case 13:
        rainbow((float)Value[0]/32,(int)(Value[1]/8));
        break;
      case 14:
        waves(Colors[0],Value[0]/2,Value[1],0,STRIPLEN);
        waves(Colors[1],Value[2]/2,Value[3],STRIPLEN,strip.numPixels());
        break;
      case 15:
        rgbShots(Value[0],Value[1]);
        break;
      case 16:
        if(Button[0])
          stars(Value[0]*3,.96,randomColor()); // (float)Value[1]/255
        else
          stars(Value[0]*3,.96,Colors[0]);
        break;
      case 17:
        if(Button[0])
          shots(Value[0]/8,Value[1],randomColor());
        else
          shots(Value[0]/8,Value[1],Colors[0]);
        break;
      case 18:
        strobe(Value[0]*2+10,Colors[0]);
        break;
      case 19:
        plasma();
        break;
      default:
        readValues();
    }

}