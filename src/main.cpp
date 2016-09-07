#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include "executor.h"
#include "exceptions.h"

void usage(const char *program_name);

int main(int argc, const char** argv)
{
  std::string source;

  try
  {
    if(argc == 1 || (argc == 2 && strcmp("-", argv[1]) == 0))
    {
      source = "<standard input>";
      ploy::execute(std::cin);
    }
    else if(argc == 2)
    {
      source = argv[1];
      std::ifstream input;
      input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      input.open(argv[1]);
      ploy::execute(input);
    }
    else if(argc == 3 && strcmp("-c", argv[1]) == 0)
    {
      source = "<command line argument>";
      std::istringstream input;
      input.exceptions(std::istringstream::failbit | std::istringstream::badbit);
      input.str(argv[2]);
      ploy::execute(input);
    }
    else
    {
      usage(argv[0]);
      return 1;
    }
  }
  catch(const ploy::Error& e)
  {
    std::cerr << source << ":" << e.what() << '\n';
    return 1;
  }
  catch(const std::exception& e)
  {
    std::cerr << source << ": " << strerror(errno) << '\n';
    return 1;
  }

  return 0;
}

void usage(const char *program_name)
{
  std::cout << "usage:\n" <<
    program_name << "                     execute ploy scheme program from stdin\n" <<
    program_name << " -                   execute ploy scheme program from stdin\n" <<
    program_name << " <source file>       execute ploy scheme program from file\n" <<
    program_name << " -c <source string>  execute ploy scheme program from command line argument\n";
}
