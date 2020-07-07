void PlayerPanel::init(Player player) {
  hearts_.init(player);
  score_.init(player);
  player_ = &player;
}

void PlayerPanel::render(int x, int y) {
  arduboy.fillRect(x, y, PANEL_WIDTH, PANEL_HEIGHT);
  score_.render(x + SCORE_X, y + SCORE_Y, ALIGN_RIGHT, BLACK);
  hearts_.render(x + HEARTS_X, y + HEARTS_Y);
}
