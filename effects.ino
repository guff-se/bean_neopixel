void plasma (float speed) {
  int m = (int)millis();
  for (int y=0; y<NUMSTRIPS; y++) {
    for (int x=0; x<pieceLen[y]; x++) {
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
  int prob=(int)((float)probability/256*NUMLEDS);
  while(prob>0) {
    if(random(0,100)<prob) {
      setPixel(random(0,NUMLEDS),color);
    }
    prob-=100;
  }
  fadeAll(fadeSpeed);
  show();
  delay(wait);
  readValues();
}

void stars2(int probability, float fadeSpeed, int wait, uint32_t color, uint32_t color2) {
  int countmax=4000/wait;
  float blendmod=1/(float)countmax;
  int i=0;
  int imod=1;
  while(!readValues()) {
    int prob=(int)((float)probability/256*NUMLEDS);
    while(prob>0) {
      if(random(0,100)<prob) {
        setPixel(random(0,NUMLEDS),colorBlend(color,color2,(float)i*blendmod));
      }
      prob-=100;
    }
    fadeAll(fadeSpeed);
    show();
    delay(wait);
    i+=imod;
    if(i==countmax-1) {
      imod=-1;
    }
    if(i==0) {
      imod=1;
    }
  }
}


void rgbShots(int dist, int wait) {
    if(iterator<dist*3) {
      for(int x=0; x<NUMLEDS;x++) {
          if((iterator+x)%(dist*3)==0)
            setPixel(x,strip.Color(255,0,0));
          else if((iterator+x)%(dist*3)==dist)
            setPixel(x,strip.Color(0,255,0));
          else if((iterator+x)%(dist*3)==dist*2)
            setPixel(x,strip.Color(0,0,255));
          else
            setPixel(x,0);
      }
      iterator++;
      show();
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
      for(i=0; i< NUMLEDS; i++) {
        setPixel(s,i, Wheel((int)((i * intensity * 25 / NUMLEDS) + fiterator) & 255));
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
      for(i=0; i< NUMLEDS; i++) {
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
      for(i=0; i< NUMLEDS; i++) {
        setPixel(s,i, Wheel(((i * 256 / NUMLEDS) + iterator) & 255));
      }
      show();
      iterator+=speed;
    }
    else
      iterator=0;
  }
}*/

void letterWipe(uint32_t color, uint16_t wait) {
    for(int l=0; l<numLetters; l++) {
        for(int i=0; i<pieceLen[l]; i++) {
                setPixel(pieceStart[l]+i, color);
        }
    show();
    if (readValues())
      return;
    delay(wait);
    }
}

void letterRainbow(uint8_t wait) {
    uint16_t i, j,l;
    for(j=0; j<256; j++) {
        for(l=0; l<numLetters; l++) {
            for(i=0; i<pieceLen[l]; i++) {
                setPixel(pieceStart[l]+i, Wheel((l*20+j) & 255));
            }
        }
    show();
    if (readValues())
      return;
    delay(wait);
    }
}



