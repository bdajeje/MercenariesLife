#include "end_talk_to_pnj.hpp"

#include "game.hpp"

namespace events {

bool EndTalkToPNJ::exec()
{
  Game::instance()->_ui.endConversation();
  Game::instance()->_focused_object = &Game::instance()->_map;

  return true;
}

}
