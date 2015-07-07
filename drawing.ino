void drawing() {
  size_t length = Serial.readBytes((char*)buffer, 2);   
  
  if ( length > 0 )
  {      
      // buffer[i] : Control #
      byte controlByte = buffer[0];
      // buffer[i+1] : Value
      byte valueByte = buffer[1];
      
      switch (controlByte) {
        case XYPAD_X:
          //valueByte goes from 0-255. To match the NeoPixel we divide by 32
          pixel_X = valueByte/32;
          break;
        case XYPAD_Y:
          pixel_Y = valueByte/32;
          //Invert the Y coordinates to match the NeoPixel
          pixel_Y = 7 - pixel_Y;
          break;
        case SLIDER:
          //Set the color to the slider value
          color= valueByte;
          break;
        case CHECKBOX:
          //Toggle between drawing/not drawing with the checkbox
          drawingMode=valueByte;
          break;
    }
    
      //The NeoPixel LEDs are indexed from 0-63 which corresponds to X+8*Y
      byte cursorLED = pixel_X + (8*pixel_Y);
      strip.setPixelColor(cursorLED, Wheel(color));
      strip.show();
      LEDsTurnedOn[cursorLED]=1;
  
      
      //Turn off all LEDs except for the cursorLED if not in drawingMode
      if(!drawingMode){
      for (int i = 0; i < sizeof(LEDsTurnedOn); i++ )
      {
        if(LEDsTurnedOn[i] == 1 && i not_eq cursorLED){
           strip.setPixelColor(i, strip.Color(0,0,0));
           strip.show();
           LEDsTurnedOn[i]=0;
        }
      }
    }
  }
}
