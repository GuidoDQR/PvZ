#include "gameManager.hpp"
#include "Fonts.hpp"
#include "miscellaneous.hpp"
#include "textures.hpp"
Tyra::Engine* engine;

int main() {
  Tyra::Engine e;
  engine = &e;
  Load_sprite_box_collider(engine);
  Load_sprite_text_font(engine);
  Load_PeaShooter_Single_Sprites(engine);
  Game_Manager game(engine);
  e.run(&game);
  SleepThread();
  return 0;
}
