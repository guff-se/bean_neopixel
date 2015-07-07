

void plasma () {
  int m = (int)millis();
  for (int y=0; y<2; y++) {
    for (int x=0; x<STRIPLEN; x++) {
      int ymod=y*3;
      uint8_t r = sintab[(( (int)(x*1.2) + sintab[ ((int)(ymod+m*.017+48)&0xFF) ] * 3 + 128 )&0xFF)];
      uint8_t g = sintab[(( (int)(x*1.5) + sintab[ ((int)(ymod+m*.014+12)&0xFF) ] * 1 + 128 )&0xFF)];
      uint8_t b = sintab[(( (int)(ymod+x) + sintab[ ((int)(x+m*.04)&0xFF) ] * 1 + 128  )&0xFF)];
      setPixel(y,x,strip.Color(linear[r],linear[g],linear[b]));
    }
  }
  strip.show();
  readValues();
}


void strobe(int speed, uint32_t color) {
  for(int i=0;i<strip.numPixels();i++)
    strip.setPixelColor(i,color);
  strip.show();
  delay(10);
  for(int i=0;i<strip.numPixels();i++)
    strip.setPixelColor(i,0);
  strip.show();
  readValues();
  delay(speed);
}

void stars(int probability, float fadeSpeed, uint32_t color) {
  while(probability>0) {
    if(random(0,100)<probability) {
      strip.setPixelColor(random(0,strip.numPixels()),color);
    }
    probability-=100;
  }
  fadeAll(fadeSpeed);
  strip.show();;
  readValues();
}


void rgbShots(int dist, int wait) {
    if(iterator<dist*3) {
      for(int x=0; x<strip.numPixels();x++) {
          if((iterator+x)%(dist*3)==0)
            strip.setPixelColor(x,strip.Color(255,0,0));
          else if((iterator+x)%(dist*3)==dist)
            strip.setPixelColor(x,strip.Color(0,255,0));
          else if((iterator+x)%(dist*3)==dist*2)
            strip.setPixelColor(x,strip.Color(0,0,255));
          else
            strip.setPixelColor(x,0);
      }
      iterator++;
      strip.show();
      if (readValues())
        return;
      delay(wait);
    }
    else {
      iterator=0;
    }
}


void shots(int probability, int wait, uint32_t c) {
  int color, x;
  moveAll2(1);
  for(int y=0;y<2;y++) {
    if(random(0,99)<probability)
      color=c;
    else
      color=0;
    setPixel(y,0,color);
  }
  strip.show();
  delay(wait);
  readValues();
}


void waves(uint32_t color, int dist, int speed, int first, int last) {
  int step=(int)(millis()*speed/3200) % (WAVELENGTH+dist);
  
  for(int x=first;x<last;x++) {
    int w=(step+x) % (WAVELENGTH+dist);
    if(w < WAVELENGTH)
      strip.setPixelColor(x,colorFade(color,wave[w]));
    else
      strip.setPixelColor(x,strip.Color(0,0,0));
  }
  strip.show();
  if (readValues())
    return;
}


void rainbow(float speed, int intensity) {
  uint16_t i;
  for(int s=0;s<2;s++) {
    if(fiterator<256*5) {
      for(i=0; i< STRIPLEN; i++) {
        setPixel(s,i, Wheel((int)((i * intensity / 10) + fiterator) & 255));
      }
      strip.show();
      if (readValues())
        return;
      fiterator+=speed;
    }
    else
      fiterator=0;
  }
}
/*
void rainbow(uint8_t wait) {
  uint16_t i;
  for(int s=0;s<2;s++) {
    if(iterator<256) {
      for(i=0; i< STRIPLEN; i++) {
        setPixel(s,i, Wheel((i + iterator) & 255));
      }
      strip.show();
      iterator++;
    }
    else
      iterator=0;
  }
  delay(wait);
}

void rainbowCycle(uint8_t speed, int intensity) {
  uint16_t i;
  for(int s=0;s<2;s++) {
    if(iterator<256*5) {
      for(i=0; i< STRIPLEN; i++) {
        setPixel(s,i, Wheel(((i * 256 / STRIPLEN) + iterator) & 255));
      }
      strip.show();
      iterator+=speed;
    }
    else
      iterator=0;
  }
}
*/
/*
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}*/
/*
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t speed) {
  uint16_t i;

  if(iterator<256*5) {
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + iterator) & 255));
    }
    strip.show();
    iterator+=speed;
  }
  else
    iterator=0;
}
*/

