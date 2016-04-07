
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
