#include "conversation.hpp"

#include <boost/algorithm/string.hpp>

#include "events/end_talk_to_pnj.hpp"
#include "graphics/fonts.hpp"
#include "graphics/textures.hpp"
#include "utils/files/file.hpp"
#include "utils/resources/game_config.hpp"

namespace models {

const sf::Color Conversation::s_normal_choice_color = sf::Color::White;
const sf::Color Conversation::s_selected_choice_color = sf::Color::Yellow;

Conversation::Conversation(const std::string& conversation_id, const sf::Texture& portrait)
  : m_displayed_text{"", *graphics::Fonts::get(graphics::Fonts::Type::Conversation), 20}
{
  const auto window_width  = utils::GameConfig::windowWidth();
  const auto window_height = utils::GameConfig::windowHeight();

  // Portrait
  m_portrait.setTexture(portrait);
  m_portrait.setScale( 100.f / portrait.getSize().x, 100.f / portrait.getSize().y );

  // Background textures
  const sf::Texture* background_texture = graphics::Textures::get("conversations/background.png");
  m_background_target.setTexture( *background_texture );
  m_background_player.setTexture( *background_texture );
  const auto x_padding      = 50;
  const float desired_width  = window_width / 2.f - x_padding;
  const float desired_height = window_height / 5.f;
  const float x_scaling      = desired_width / background_texture->getSize().x;
  const float y_scaling      = desired_height / background_texture->getSize().y;
  m_background_target.scale( x_scaling, y_scaling );
  m_background_player.scale( x_scaling, y_scaling );

  // Continue next text indicator
  const sf::Texture& indicator_texture = *graphics::Textures::get("conversations/continue_indicator.png");
  m_continue_indicator.setTexture( indicator_texture );
  m_continue_indicator.setScale( 20.f / indicator_texture.getSize().x, 20.f / indicator_texture.getSize().y );

  // Placement
  m_background_target.setPosition( x_padding, window_height - desired_height - 50 );
  m_background_player.setPosition( window_width - desired_width - x_padding, m_background_target.getPosition().y );
  m_displayed_text.setPosition( m_background_target.getPosition().x + s_text_padding, m_background_target.getPosition().y + s_text_padding );
  m_portrait.setPosition( x_padding, m_background_target.getPosition().y - m_portrait.getGlobalBounds().height );
  m_continue_indicator.setPosition( m_background_target.getPosition().x + (desired_width - m_continue_indicator.getGlobalBounds().width) / 2,
                                    m_background_target.getPosition().y + desired_height - m_continue_indicator.getGlobalBounds().height - 20 );

  // Load conversation
  const std::string filepath = "resources/conversations/" + conversation_id;
  createConversation(filepath);
  loadConversation(filepath);
}

void Conversation::createConversation(const std::string& filepath)
{
  // Read file
  std::string file_content;
  if( !utils::files::read(filepath + "/texts", file_content) )
  {
    std::cerr << "Can't read conversation file: " << filepath << std::endl;
    throw;
  }

  // Parse conversation file to create subconversations
  std::vector<std::string> lines;
  boost::algorithm::split(lines, file_content, boost::is_any_of("\n"));

  const auto max_text_width     = m_background_target.getGlobalBounds().width - 2 * s_text_padding;
  const auto choice_start_pos_y = m_background_player.getGlobalBounds().top + s_text_padding;
  const auto choice_pos_x       = m_background_player.getGlobalBounds().left + s_text_padding;
  const unsigned int choice_character_size = 15;
  const unsigned int choice_y_padding      = 10;

  // Create subconversations
  size_t i = 0;
  const size_t nbr_lines = lines.size();
  float choice_pos_y;
  while(i < nbr_lines)
  {
    if(lines[i].empty())
      continue;

    // ID and Text
    SubConversation& subconversation = m_sub_conversations[std::stoi(lines[i++])];
    subconversation.texts = wrapText(lines[i++], max_text_width, 6);

    // Choices
    while(true)
    {
      const std::string& choice_to_id = lines[i++];
      if( choice_to_id.empty() )
        break;

      choice_pos_y = choice_start_pos_y + subconversation.choices.size() * (choice_character_size + choice_y_padding);
      subconversation.choices.emplace_back( std::stoi(choice_to_id), sf::Text{lines[i++], *graphics::Fonts::get(graphics::Fonts::Type::Conversation), choice_character_size} );
      subconversation.choices.back().text.setPosition(choice_pos_x, choice_pos_y);
      subconversation.choices.back().text.setColor( s_normal_choice_color );
    }
  }
}

void Conversation::loadConversation(const std::string& filepath)
{
  // Read file
  std::string file_content;
  if( !utils::files::read(filepath + "/state", file_content) )
  {
    std::cerr << "Can't read conversation file: " << filepath << std::endl;
    throw;
  }

  std::vector<std::string> lines;
  boost::algorithm::split(lines, file_content, boost::is_any_of("\n"));

  showSubConversation( std::stoi(lines[0]) );
}

void Conversation::showSubConversation(unsigned int id)
{
  // Selection subconversation 0 means quitting conversation
  if(id == 0)
  {
    events::Events::addEvent( new events::EndTalkToPNJ() );
    return;
  }

  m_current_subconversation = &m_sub_conversations[id];
  showSubConversationText(0);
  focusChoice(0);
}

void Conversation::draw(sf::RenderTarget& target)
{
  // Draw backgroungs
  target.draw(m_background_target);

  // Add some characters to the text
  addCharacters();

  // Draw text
  target.draw(m_displayed_text);

  // Draw portrait
  target.draw(m_portrait);

  // Draw choices
  if(isAllSubConversationDrawn())
  {
    target.draw(m_background_player);
    for( const SubConversationChoice& choice : m_current_subconversation->choices )
      target.draw(choice.text);
  }
  // Draw indicator, more text is waiting
  else if( isAllSubTextDrawn() )
    target.draw(m_continue_indicator);
}

void Conversation::addCharacters()
{
  if(isAllSubTextDrawn())
    return;

  unsigned int elapsed_time = m_character_clock.getElapsedTime().asMilliseconds();
  const size_t nbr_characters_to_add = elapsed_time * (utils::GameConfig::conversationCharactersPerSecond() / 1000);
  if( nbr_characters_to_add == 0 )
    return;

  m_text_offset += nbr_characters_to_add;
  m_displayed_text.setString( m_current_subconversation->text().toAnsiString().substr(0, m_text_offset) );
  m_character_clock.restart();
}

void Conversation::showSubConversationText(size_t text_offset)
{
  m_current_subconversation->current_text_offset = text_offset;
  m_text_offset = 0;
  m_character_clock.restart();
}

void Conversation::showAllCharacters()
{
  m_text_offset = m_current_subconversation->text().getSize();
  m_displayed_text.setString( m_current_subconversation->text() );
}

bool Conversation::isAllSubTextDrawn() const
{
  return m_text_offset == m_current_subconversation->text().getSize();
}

bool Conversation::isAllSubConversationDrawn() const
{
  return m_current_subconversation->current_text_offset == m_current_subconversation->texts.size() - 1 && isAllSubTextDrawn();
}

std::vector<sf::String> Conversation::wrapText(const std::string& text, unsigned int max_width, unsigned int max_lines)
{
  std::vector<sf::String> results(1);
  const unsigned int character_size = m_displayed_text.getCharacterSize() / 2; // \todo I have no idea why I need to divise character size per 2

  // Split text by words
  std::vector<std::string> words;
  boost::algorithm::split(words, text, boost::is_any_of(" "));

  unsigned int current_width = 0, word_width, lines = 0;
  size_t result_offset = 0;
  for( const std::string& word : words )
  {
    word_width = character_size * (word.size() + 1); // +1 for the space
    if( current_width + word_width > max_width )
    {
      current_width = 0;
      lines++;
      if(lines == max_lines)
      {
        result_offset++;
        results.resize( result_offset + 1 );
        lines = 0;
      }
      else results[result_offset] += '\n';
    }

    results[result_offset] += word + ' ';
    current_width += word_width;
  }

  return results;
}

void Conversation::focusChoice(int choice_offset)
{
  // Respect limits
  const int nbr_choices = m_current_subconversation->choices.size();
  if( choice_offset >= nbr_choices )
    choice_offset = 0;
  else if( choice_offset < 0 )
    choice_offset = nbr_choices - 1;

  for(int i = 0; i < nbr_choices; ++i)
  {
    sf::Text& choice_text = m_current_subconversation->choices[i].text;

    if( i == choice_offset )
      choice_text.setColor( s_selected_choice_color );
    else
      choice_text.setColor( s_normal_choice_color );
  }

  m_focused_choice_offset = choice_offset;
}

void Conversation::selectChoice()
{
  showSubConversation( m_current_subconversation->choices[m_focused_choice_offset].to_id );
}

void Conversation::keyPress(sf::Keyboard::Key key_code)
{
  if( isAllSubConversationDrawn() )
  {
    if( key_code == utils::GameConfig::keyboardKey( utils::KeyboardActions::ConversationChoiceUp ) )
      focusChoice(m_focused_choice_offset - 1);
    else if( key_code == utils::GameConfig::keyboardKey( utils::KeyboardActions::ConversationChoiceDown ) )
      focusChoice(m_focused_choice_offset + 1);
    else if( key_code == utils::GameConfig::keyboardKey( utils::KeyboardActions::ConversationSelectChoice ) ||
             key_code == utils::GameConfig::keyboardKey( utils::KeyboardActions::ShowAllConversation ) )
      selectChoice();
  }
  else if(isAllSubTextDrawn())
  {
    if( key_code == utils::GameConfig::keyboardKey( utils::KeyboardActions::ShowAllConversation ) )
      showSubConversationText( m_current_subconversation->current_text_offset + 1 );
  }
  else
  {
    if( key_code == utils::GameConfig::keyboardKey( utils::KeyboardActions::ShowAllConversation ) )
      showAllCharacters();
  }
}

void Conversation::keyboardAction()
{

}

}
