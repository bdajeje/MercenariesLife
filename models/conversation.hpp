#ifndef MODELS_CONVERSATION_HPP
#define MODELS_CONVERSATION_HPP

#include <memory>
#include <string>

namespace models {

class Conversation
{
  public:

    /*! Constructor
     *  \param conversation_file - file where to file the conversation
     */
    Conversation(const std::string& conversation_file);

    /*! Load and create a conversation object
     *  \param filename - of the conversation
     */
    static std::shared_ptr<Conversation> loadConversation(const std::string& filename);
};

}

#endif // MODELS_CONVERSATION_HPP
