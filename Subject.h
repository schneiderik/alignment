#ifndef SUBJECT_H
#define SUBJECT_H

#include "global.h"

class Subject {
  public:
    void addObserver(Observer* observer) {
      observers_[observerCount_] = observer;
      observerCount_++;
    };

  protected:
    void notify(const Weapon& weapon, Event event) {
      for (int i = 0; i < numObservers_; i++) {
        observers_[i]->onNotify(weapon, event);
      }
    };

    void notify(const Gem& gem, Event event) {
      for (int i = 0; i < numObservers_; i++) {
        observers_[i]->onNotify(gem, event);
      }
    };

    void notify(const Enemy& enemy, Event event) {
      for (int i = 0; i < numObservers_; i++) {
        observers_[i]->onNotify(enemy, event);
      }
    };

    void notify(const Player& player, Event event) {
      for (int i = 0; i < numObservers_; i++) {
        observers_[i]->onNotify(player, event);
      }
    };

  private:
    Observer* observers_[MAX_OBSERVERS];
    int observerCount_ = 0;
};

#endif
