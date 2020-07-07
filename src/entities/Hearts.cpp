
void Hearts::render(int x, int y) {
  for (int i = 0; i < HEALTH_MAX; i++) {  
    sprites.drawErase(
      x + (i * (heartSprite[0] + 1)),
      y,
      heartSprite,
      i < game.getPlayer().getHealth() ? 0 : 1
    );
  }  
}
