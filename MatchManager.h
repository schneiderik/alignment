#ifndef MATCHMANAGER_H
#define MATCHMANAGER_H

#include "global.h"

class MatchManager {
  public:
    MatchManger();

  private:
    int matchesLength_ = 0;
    Match* matches_;
};

#endif
