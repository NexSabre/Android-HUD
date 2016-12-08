#include "U8glib.h"
const int xAxis = A0;  //red axis
  const int yAxis = A1;  //green axis
  const int zAxis = A2;  //blue axis

  int sensorX =0;
  int sensorY =0;
  int sensorZ =0;


U8GLIB_SSD1306_128X64 u8g(5, 4, 10, 2, 3);
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Kutacz6000!!");
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
                Serial.begin(9600);

  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  pinMode (xAxis, INPUT);
pinMode (yAxis, INPUT);
pinMode (zAxis, INPUT);
}

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    draw();
  } while( u8g.nextPage() );

  sensorX = analogRead (xAxis);  // read the accelerometer
          sensorY = analogRead (yAxis);
          sensorZ = analogRead (zAxis);
          sensorX = constrain (sensorX, 261, 399);  // keep the numbers within a range so it doesn't take huge
          sensorY = constrain (sensorY, 261, 399);  // jolts to get bright colors
          sensorZ = constrain (sensorZ, 264, 400);  // the values returned for resting rotation through the range of motion are
                                                    // X [266-400] Y [263-395] z [264-395]  so 395 is 1g

          sensorX = map (sensorX, 260, 400, 100, 240);  // analogWrite wants values from 0 - 255
          sensorY = map (sensorY, 260, 400, 100, 255);  // so this keeps the values returned by analogRead (sensorXYZ)
          sensorZ = map (sensorZ, 263, 401, 100, 255);  // from rolling over and making weird flashes

          Serial.print(sensorX, DEC );  // this is unnecessary to the operation of the code
          Serial.print("\t");           // but it helps to figure out which colors are responding.
          Serial.print(sensorY, DEC  );
          Serial.print("\t");
          Serial.println(sensorZ, DEC  );

  // rebuild the picture after some delay
  delay(50);
}
