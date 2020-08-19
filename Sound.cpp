#include "Sound.h"

bool Sound::isOn()
{
  return arduboy.audio.enabled();
}

void Sound::toggle()
{
  if (arduboy.audio.enabled()) {
    arduboy.audio.off();
  } else {
    arduboy.audio.on();
  }

  arduboy.audio.saveOnOff();
}

//void playSwapSound() {
//  sound.tone(NOTE_C5, 100);
//}
//
//void playLoseHeartSound() {
//  sound.tone(NOTE_E3, 150);
//}
//
//void playConfirmSound() {
//  sound.tone(NOTE_C5, 50);
//}
//
//void playMoveSound() {
//  sound.tone(NOTE_E4, 50);
//}
