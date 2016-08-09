#ifndef _TRACKED_STREAM_H_
#define _TRACKED_STREAM_H_

#include <istream>

namespace ploy
{

struct TrackedStream
{
private:
  std::istream& input;

public:
  int line;
  int column;

  TrackedStream(std::istream& input_) : input(input_)
  {
    this->line = 1;
    this->column = 1;
  };

  int get();
  int peek() const;
  bool eof() const;
};

}

#endif
