#ifndef GEM_H
#define GEM_H

class Gem {
  public:
    Gem& operator=(const Gem& gem) {
      if (this != &gem) {
        type = gem.type;
        row = gem.row;
        x = gem.x;
        y = gem.y;
      }
      return *this;
    }
    
    int type;
    int row;
    int x;
    int y; 
};

#endif
