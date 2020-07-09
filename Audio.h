#ifndef AUDIO_H
#define AUDIO_H

#include "global.h"

class Audio {
  public:
    void toggle();
    void playSwapSound();
    void playLoseHeartSound();
    void playConfirmSound();
    void playMoveSound();
  private:
    ArduboyTones sound_(arduboy.audio.enabled);
};

#endif
