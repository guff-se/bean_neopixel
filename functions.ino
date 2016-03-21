void show() {
#ifdef USEDMX
for(int i=0;i<NUMLEDS;i++) {
  DmxSimple.write(i*3+1, (dmxLights[i] & 0xFF0000)>>16);
  DmxSimple.write(i*3+2, (dmxLights[i] & 0x00FF00)>>8);
  DmxSimple.write(i*3+3, (dmxLights[i] & 0x0000FF));
}
#else
  strip.show();
#endif  
}

void setPixel(int num, uint32_t color) {
#ifdef USEDMX
  dmxLights[num]=color;
#else
  strip.setPixelColor(num,color);
#endif
}

void setPixel(int s, int num, uint32_t color) {
#ifdef USEDMX
  if(s%2)
    dmxLights[num]=color;
  else
    dmxLights[NUMLEDS-num-1]=color;
#else
  if(s%2)
    strip.setPixelColor(num,color);
  else
    strip.setPixelColor(NUMLEDS-num-1,color);
#endif
}

uint32_t getPixel(int n) {
#ifdef USEDMX
  return dmxLights[n];
#else
  return strip.getPixelColor(n);
#endif
}

uint32_t getPixel(int s, int num) {
#ifdef USEDMX
  if(s%2)
    return dmxLights[num];
  else
    return dmxLights[NUMLEDS-num-1];
#else
  if(s%2)
    strip.getPixelColor(num);
  else
    strip.getPixelColor(NUMLEDS-num-1);
#endif
}

uint32_t colorFade(uint32_t color, int fade) {
  uint8_t r,g,b;
    r=(color >> 16)  ;
    g=(color >>  8) ;
    b=(color);
  return strip.Color(linear[r*fade/100],linear[g*fade/100],linear[b*fade/100]);

}

uint32_t colorBlend(uint32_t color1, uint32_t color2, float s) {
  int r,r1,r2,g,g1,g2,b,b1,b2;
  r1=(color1 & 0xFF0000)>>16;
  g1=(color1 & 0x00FF00)>>8;
  b1=(color1 & 0x0000FF);
  r2=(color2 & 0xFF0000)>>16;
  g2=(color2 & 0x00FF00)>>8;
  b2=(color2 & 0x0000FF);
  r=((r2-r1)*s)+r1;
  g=((g2-g1)*s)+g1;
  b=((b2-b1)*s)+b1;
  return strip.Color(r,g,b);
}

//Function to generate a color value from the slider
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void moveAll() {
  for(int i=0;i<NUMSTRIPS;i++) {
    for(int x=STRIPLEN-1; x > 0 ; x--) {
      setPixel(i,x,getPixel(i,x-1));
    }
  }
}


void fadeAll(float fadeSpeed) {
  uint32_t color;
  uint8_t r,g,b;
  for(int x=0;x<NUMLEDS;x++) {
    color=getPixel(x);
    r=(color >> 16)  ;
    g=(color >>  8) ;
    b=(color);
    setPixel(x,strip.Color(r*fadeSpeed,g*fadeSpeed,b*fadeSpeed));
  }
}

void setAll(uint32_t color) {
  for(int i=0;i<NUMLEDS;i++)
    setPixel(i,color);
  show(); // Should this really be here?
}

uint32_t randomColor() {
      switch(random(0,5)) {
        case 0:
          return strip.Color(255,0,0);
        case 1:
          return strip.Color(255,255,0);
        case 2:
          return strip.Color(0,255,0);
        case 3:
          return strip.Color(0,255,255);
        case 4:
          return strip.Color(0,0,255);
        case 5:
          return strip.Color(255,0,255);
      }        

}


