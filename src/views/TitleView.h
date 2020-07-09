#ifndef TITLE_VIEW_H
#define TITLE_VIEW_H

#include "../../global.h"
#include "View.h"

#define TITLE_STATE_PLAY 0
#define TITLE_STATE_INFO 1
#define TITLE_STATE_SFX 2

#define TITLE_STATE_COUNT 3
#define LAST_TITLE_STATE TITLE_STATE_COUNT - 1

class TitleView: public View {
  public:
    void handleInput(const Game&) override;
    void render(const Game&) override;

  private:
    void decrementState_(const Game&);
    void incrementState_(const Game&);
    void selectOption_(const Game&);

    void renderMainImage_();
    void renderPlayOption_();
    void renderInfoOption_();
    void renderSfxOption_();
    void renderCursor_(int, int, int);

    int state = TITLE_STATE_PLAY;
};

#endif
