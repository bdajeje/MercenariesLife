#include "file.hpp"

#include <boost/regex.hpp>
#include <iostream>
#include <fstream>

namespace utils {
namespace files {

bool read( const std::string& filepath, std::string& result )
{
  std::ifstream file(filepath.c_str());
  if( !file.is_open() )
    return false;

  // Get length of file
  file.seekg(0, file.end);
  const int length = file.tellg();
  file.seekg(0, file.beg);

  // If file content is empty, exit
  if( length < 1 )
    return true;

  // Read the file
  result.resize( length );
  file.read(&result[0], length);

  // Close the file and return good read
  file.close();
  return true;
}

bool create( const std::string& filepath, const std::string& content, bool override )
{
  if( !override && exists(filepath) )
    return false;

  // Try to open the file
  std::ofstream new_file(filepath, std::ios::trunc);
  if( !new_file.is_open() )
    return false;

  // Write content into
  new_file << content;

  // Closing file
  new_file.close();

  return true;
}

std::vector<std::string> listFilesInDir(const std::string& dir_path, const std::string& regex_str)
{
  namespace fs = boost::filesystem;
  fs::path directory {dir_path};
  std::vector<std::string> results;

  if( !fs::is_directory(directory) )
    return results;

  const boost::regex regex(regex_str);
  fs::directory_iterator end_iter;

  for( fs::directory_iterator dir_iter(directory); dir_iter != end_iter; ++dir_iter)
  {
    if(fs::is_regular_file(dir_iter->status()) )
    {
      const std::string& file_path = dir_iter->path().string();
      if( boost::regex_match( file_path, regex ) )
        results.push_back(file_path);
    }
  }

  return results;
}

std::string ensureDirEnd(std::string filepath)
{
  return (filepath.back() == '/') ? filepath : filepath + '/';
}

} // namespace files
} // namespace utils

