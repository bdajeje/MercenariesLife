#include "end_talk_to_pnj.hpp"

#include "game.hpp"

namespace events {

bool EndTalkToPNJ::exec()
{
  Game::instance()->_ui.endConversation();
  Game::instance()->setFocused(Game::Part::Map);

  return true;
}

}
