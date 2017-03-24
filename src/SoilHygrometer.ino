#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(12, 11, 10, 9, 8);  // D0=12, D1=11, CS=10, DC=9, Reset=8

/******************************************************************************************
* Global data section.                                                                    *
******************************************************************************************/

int DEBUG = 1;
int soil=0;
char Up_time[20];
//char sbuf[100];                // For debug lines
char lsbuf1[30],lsbuf2[30] ;     // For debugging

void dbgprint ( const char* p )
{
  if ( DEBUG )
  {
    Serial.print ( "[DEBUG]: " ) ;
    Serial.println ( p ) ;
  }
}


void setup() {
  Serial.begin(115200);
  upTime();
  sprintf ( lsbuf1, "Starting at: %s\n", Up_time );
  dbgprint ( lsbuf1 );
}

void loop() {
  upTime();
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  sensorValue = constrain(sensorValue, 485, 1023);

  sprintf ( lsbuf1, "Analog:  %d", sensorValue ) ;
  dbgprint ( lsbuf1 ) ;
  // print out the value you read:

  //map the value to a percentage
  soil = map(sensorValue, 485, 1023, 100, 0);

  // print out the soil water percentage you calculated:
  sprintf ( lsbuf2, "Soil:    %d%%", soil ) ;
  dbgprint ( lsbuf2 ) ;

  u8g.firstPage();
  do {
    draw();
  } while( u8g.nextPage() );

  delay(1000);        // delay in between reads for stability
}

void upTime() {
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  snprintf ( Up_time, 20, "%02d:%02d:%02d", hr, min % 60, sec % 60 );
}

void draw(void) {
  u8g.setFont(u8g_font_unifont);  // select font
  u8g.drawStr(0, 10, Up_time);
  u8g.drawStr(0, 30, lsbuf1);      // put string of display at position X, Y
  u8g.drawStr(0, 50, lsbuf2);
}
