#ifndef INTERVAL_H
#define INTERVAL_H

class Interval
  public:
    void init();
    void run();
    void reset();
    void update();
    bool isActive();

  private:
    int getInterval_();

    bool active_ = false;
    int frame_ = 0;
    int interval_ = 0;
    int intervalMin_ = 0;
    int intervalMax_ = 0;
}

#endif
