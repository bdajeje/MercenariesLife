#ifndef MODELS_CONVERSATION_HPP
#define MODELS_CONVERSATION_HPP

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "events/keyboard_listener.hpp"

namespace models {

struct SubConversationChoice
{
  SubConversationChoice(unsigned int id, sf::Text text)
    : to_id{id}
    , text{text}
  {}

  /*! Choice leads to this subconversation ID */
  unsigned int to_id;

  /*! Choice text */
  sf::Text text;
};

/*! A SubConversation is a part of a conversation */
struct SubConversation
{
  /*! Offset of texts currently displayed */
  size_t current_text_offset {0};

  /*! SubConversation texts */
  std::vector<sf::String> texts;

  /*! Possible choices for this SubConversation */
  std::vector<SubConversationChoice> choices;

  /*! Currently displayed text */
  const sf::String& text() const { return texts[current_text_offset]; }
};

class Conversation final : public events::KeyboardListener
{
  public:

    /*! Constructor
     *  \param conversation_id  - id of the conversation
     *  \param portrait texture - to display
     */
    Conversation(const std::string& conversation_id, const sf::Texture& portrait);

    /*! Draw the conversation
     * \param target - where to draw
     */
    void draw(sf::RenderTarget& target);

    /*! See KeyboardListener */
    virtual void keyPress(sf::Keyboard::Key key_code);
    virtual void keyboardAction();

  private:

    /*! Create conversation from file
     *  \param filepath - where to find the conversation
     */
    void createConversation(const std::string& filepath);

    /*! Look at conversation state file to load the conversation to its previous state
     *  \param filepath - where to find the conversation state file
     */
    void loadConversation(const std::string& filepath);

    /*! Show a sub conversation
     *  \param id - of the sub conversation to show
     */
    void showSubConversation(unsigned int id);

    /*! Wrap text into multilines, respecting a maximum width in pixels
     *  \param text      - to wrap
     *  \param max_width - to respect in pixels
     *  \param max_lines - maximum number of lines
     *  \return wrapped text into multiple strings to we respect max_lines per element
     */
    std::vector<sf::String> wrapText(const std::string& text, unsigned int max_width, unsigned int max_lines);

    /*! Is all subtext drawn ?
     *  \return true if every characters of the subconversation are actually shown
     */
    bool isAllSubTextDrawn() const;

    /*! Is all sub conversation drawn, ie, all texts of the sub conversation has been shown ?
     *  \return true if every texts of the sub conversation have been shown and isAllSubTextDrawn() == true
     */
    bool isAllSubConversationDrawn() const;

    /*! Add some characters to displayed text, depending on elapsed time */
    void addCharacters();

    /*! Show all current subconversation text */
    void showAllCharacters();

    /*! Show a sub conersation specific text part
     *  \param text_offset - of the text to show
     */
    void showSubConversationText(size_t text_offset);

    /*! Focus a choice
     *  \param choice_offset - offset of the choice to focus
     */
    void focusChoice(int choice_offset);

    /*! Select focused choice, so change subconversation */
    void selectChoice();

  private:

    /*! Background sprites */
    sf::Sprite m_background_target;
    sf::Sprite m_background_player;

    /*! Portrait of people we are talking to */
    sf::Sprite m_portrait;

    /*! Indicator to indicate conversation is not finished */
    sf::Sprite m_continue_indicator;

    /*! Currently displayed text */
    sf::Text m_displayed_text;

    /*! Currently used subconversation */
    SubConversation* m_current_subconversation {nullptr};

    /*! Each subconversation ID to a subconversation
     *  \note ID 0 is reserved for "quit conversation"
     */
    std::map<unsigned int, SubConversation> m_sub_conversations;

    /*! Current offset of text, needed to display text letter by letter */
    size_t m_text_offset;

    /*! Currently focused choice */
    size_t m_focused_choice_offset;

    /*! Clock to display character per character */
    sf::Clock m_character_clock;

    /*! Padding between text and background borders */
    static const unsigned int s_text_padding {15};

    /*! Choice colors */
    static const sf::Color s_normal_choice_color;
    static const sf::Color s_selected_choice_color;
};

}

#endif // MODELS_CONVERSATION_HPP
