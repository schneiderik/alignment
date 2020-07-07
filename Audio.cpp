#include "./Audio.h"

void Audio::toggle() {
  if (arduboy.audio.enabled()) {
    arduboy.audio.off();
  } else {
    arduboy.audio.on();
  }

  arduboy.audio.saveOnOff();
}

void Audio::playSwapSound() {
  sound_.tone(NOTE_C5, 100);
}

void Audio::playLoseHeartSound() {
  sound_.tone(NOTE_E3, 150);
}

void Audio::playConfirmSound() {
  sound_.tone(NOTE_C5, 50);
}

void Audio::playMoveSound() {
  sound_.tone(NOTE_E4, 50);
}
