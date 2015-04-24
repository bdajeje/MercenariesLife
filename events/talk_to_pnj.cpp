#include "talk_to_pnj.hpp"

#include "game.hpp"

namespace events {

TalkToPNJ::TalkToPNJ( std::shared_ptr<models::PNJ>& pnj )
  : _pnj{pnj}
{}

bool TalkToPNJ::exec()
{
  if(!_pnj)
    return false;

  if( Game::instance()->_ui.startConversation( _pnj ))
    Game::instance()->setFocused( Game::Part::UI );

  return true;
}

}
