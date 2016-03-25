#include <SoftwareSerial.h>
#include <MP3.h>

int INFRARED_PIN = 3;
int MUSIC_TIME = 5000;

/** define mp3 class */
MP3 mp3;
boolean canPlay = false;

void setup(){

  Serial.begin(9600);

  /* INFRARED CONFIG */
  pinMode(INFRARED_PIN,INPUT);
  digitalWrite(INFRARED_PIN, HIGH);

  /* MP3 CONFIG */
  canPlay = false;

  /** begin function */
  //mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  mp3.begin();                       // select hardware serial(or mp3.begin(MP3_HARDWARE_SERIAL);)

  /** set volum to the MAX */
  mp3.volume(0xA);

  /** set MP3 Shield CYCLE mode */
  //enum {SINGLE=0, REPEAT=1, CYCLE=2, RANDOM=3};
  mp3.set_mode(MP3::REPEAT);

  /** play music in sd, '0001' for first music */
  //mp3.play_sd(0x0001);

  /** play music in USB-disk */
  //mp3.play_usb_disk(0x0001);

  /** play music in SPI FLASH */
  //mp3.play_spi_flash(0x0001);
}

void loop()
{
     canPlay = readInfraRed();

     if(canPlay){
         mp3.play_usb_disk(0x0001);
         Serial.println("Play");
         delay(MUSIC_TIME);
     }else if(!canPlay){
         mp3.stop();
         Serial.println("Stop");
     }
}

boolean readInfraRed(){

  int infrared = digitalRead(INFRARED_PIN);

  if(infrared == 0){

    // relay bounce time ?
    delay(50);
    infrared = digitalRead(INFRARED_PIN);

    if(infrared == 0){
        return true;
    }
  }

  return false;
}

