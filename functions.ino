
int readValues () {
   size_t length = Serial.readBytes((char*)buffer, 2);
   if( length > 0 ) {
     // buffer[i] : Control #
     if(buffer[0]>12 && buffer[0]<29) {
       effect = buffer[0];
       return 1;
     } else {
       controlByte=buffer[0];
       if (controlByte==0)
         Value[0] = buffer[1];
       else if (controlByte==2)
         Value[1] = buffer[1];
       else if (controlByte==4)
         Value[2] = buffer[1];
       else if (controlByte==6)
         Value[3] = buffer[1];
       if (controlByte==1)
         Button[0] = buffer[1];
       else if (controlByte==3)
         Button[1] = buffer[1];
       else if (controlByte==5)
         Button[2] = buffer[1];
       else if (controlByte==7)
         Button[3] = buffer[1];
       else if (controlByte==8)
         Colors[0] = Wheel(buffer[1]);
       else if (controlByte==9)
         Colors[1] = Wheel(buffer[1]);
       else if (controlByte==11)
         Colors[0] = strip.Color(buffer[1],buffer[1],buffer[1]);
 
     }
   }
   return 0;
}

void show() {
#ifdef USEDMX
for(int i=0;i<NUMLIGHTS;i++) {
  DmxSimple.write(i*3+1, dmxLights[i] >> 16);
  DmxSimple.write(i*3+2, dmxLights[i] >>  8);
  DmxSimple.write(i*3+3, dmxLights[i]);
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

//  return strip.Color(r*fade/100,g*fade/100,b*fade/100);
  return strip.Color(linear[r*fade/100],linear[g*fade/100],linear[b*fade/100]);
/*  Serial.print("pre linear:");
  r=r*fade/100;
  g=g*fade/100;
  b=b*fade/100;
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" post linear:");
  r=linear[r];
  g=linear[g];
  b=linear[b];
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.println(b);
  return strip.Color(r,g,b);
 */
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
  b=((b2-g1)*s)+b1;
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
/*
void moveAll(int num) {
  int x;
  for(x=NUMLEDS-1; x > 0 ; x--) {
    setPixel(x,getPixel(x-1));
  }
}
*/
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


