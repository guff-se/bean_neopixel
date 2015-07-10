void theTree() {
  
}

void plasma (float speed) {
  int m = (int)millis();
  for (int y=0; y<2; y++) {
    for (int x=0; x<STRIPLEN; x++) {
      int ymod=y*3;
      uint8_t r = sintab[(( (int)(x*1.2) + sintab[ ((int)(ymod+m*.017+48)&0xFF) ] * 3 + 128 )&0xFF)];
      uint8_t g = sintab[(( (int)(x*1.5) + sintab[ ((int)(ymod+m*.014+12)&0xFF) ] * 1 + 128 )&0xFF)];
      uint8_t b = sintab[(( (int)(ymod+x) + sintab[ ((int)(x+m*0.04)&0xFF) ] * 1 + 128  )&0xFF)];
#ifdef NOLINEAR
      setPixel(y,x,strip.Color(r,g,b));
#else
      setPixel(y,x,strip.Color(linear[r],linear[g],linear[b]));
#endif
    }
  }
  show();
  readValues();
}


void strobe(int speed, uint32_t color) {
  for(int i=0;i<NUMLEDS;i++)
    setPixel(i,color);
  show();
  delay(10);
  for(int i=0;i<NUMLEDS;i++)
    setPixel(i,0);
  show();
  readValues();
  delay(speed);
}

void stars(int probability, float fadeSpeed, int wait, uint32_t color) {
  probability=(int)((float)probability/256*NUMLEDS);
  while(probability>0) {
    if(random(0,100)<probability) {
      setPixel(random(0,NUMLEDS),color);
    }
    probability-=100;
  }
  fadeAll(fadeSpeed);
  show();
  delay(wait);
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
  uint32_t color;
  moveAll();
  for(int y=0;y<NUMSTRIPS;y++) {
    if(random(0,255)<probability)
      color=c;
    else
      color=0;
    setPixel(y,0,color);
  }
  show();
  delay(wait);
  readValues();
}


void waves(uint32_t color, int dist, int speed, int first, int last) {
  int step=(int)(millis()*speed/3200) % (WAVELENGTH+dist);
  
  for(int x=first;x<last;x++) {
    int w=(step+x) % (WAVELENGTH+dist);
    if(w < WAVELENGTH)
      setPixel(x,colorFade(color,wave[w]));
    else
      setPixel(x,strip.Color(0,0,0));
  }
  show();
  readValues();
}


void rainbow(float speed, int intensity) {
  uint16_t i;
  for(int s=0;s<NUMSTRIPS;s++) {
    if(fiterator<256*5) {
      for(i=0; i< STRIPLEN; i++) {
        setPixel(s,i, Wheel((int)((i * intensity * 25 / STRIPLEN) + fiterator) & 255));
      }
      show();
      if (readValues())
        return;
      fiterator+=speed;
    }
    else
      fiterator=0;
  }
}
/*
void rainbow_old(uint8_t wait) {
  uint16_t i;
  for(int s=0;s<2;s++) {
    if(iterator<256) {
      for(i=0; i< STRIPLEN; i++) {
        setPixel(s,i, Wheel((i + iterator) & 255));
      }
      show();
      iterator++;
    }
    else
      iterator=0;
  }
  delay(wait);
}

void rainbowCycle_ol(uint8_t speed, int intensity) {
  uint16_t i;
  for(int s=0;s<2;s++) {
    if(iterator<256*5) {
      for(i=0; i< STRIPLEN; i++) {
        setPixel(s,i, Wheel(((i * 256 / STRIPLEN) + iterator) & 255));
      }
      show();
      iterator+=speed;
    }
    else
      iterator=0;
  }
}*/
