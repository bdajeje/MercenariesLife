#ifndef UTILS_RESOURCE_HPP
#define UTILS_RESOURCE_HPP

#include <iostream>
#include <map>
#include <string>

#include "utils/files/file.hpp"

namespace utils {

template <class T>
class Resource
{
  public:


    static void init(const std::string& directory_path)
    {
      // Initialize only once
      if(s_instance)
        return;

      s_instance.reset( new Resource<T>(directory_path) );
    }



    /*! Destructor */
    virtual ~Resource() = default;




  protected:



    /*!
     * \brief load a resource
     * \param name - of the resource to load
     */
    virtual void load(const std::string& name) = 0;

  protected:



  private:




};

//template<typename T>
//std::unique_ptr<Resource> Resource<T>::s_instance;

}

#endif // UTILS_RESOURCE_HPP
