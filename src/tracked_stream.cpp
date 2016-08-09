#include "tracked_stream.h"

namespace ploy
{

int TrackedStream::get()
{
  int c = this->input.get();

  if(c == '\n')
    this->line ++, this->column = 1;
  else if(c != EOF)
    this->column ++;

  return c;
}

int TrackedStream::peek() const
{
  return this->input.peek();
}

bool TrackedStream::eof() const
{
  return this->input.eof();
}

}
