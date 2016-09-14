# ploy

A toy interpreted language implementing a small subset of Scheme.

## Goals and Philosophy

This project is pedagogical rather than practical; I began development with several educational goals in mind:

1. To implement a non-trivial project in a language (C++) and in a paradigm (object-oriented programming)
that were not yet second nature to me, hence developing my skills in both areas and yielding proof of this development.

2. To deliberately and consciously implement the nuances of programming languages that had been obscured to me in my previous work.

   My introductory functional programming courses at UWaterloo culminated in implementing an interpreted Scheme-like functional language.
   However, some complexity was elided. We used the host language's garbage collector rather than implementing our own. Furthermore,
   we accepted input only in a structured, tree-like format (Racket's S-expressions), thereby eliminating the need for lexing or parsing.

   By implementing ploy from a lower level, I have the opportunity to focus on these new aspects of programming language development.

3. To gain a deeper understanding and a greater level of experience in the Scheme language, both through the implementation of the ploy language
   itself, and through the development of tooling around the language's development; moreover, to improve further my skill in functional programming
   in general.

   The extensive research and practical implementation that went into the language proved to be informative; on more than one occasion, I've found
   myself suddenly understanding some quirk of Scheme, as the direct result of having implemented some piece of the language and having encountered
   some pitfall or nuance.

   Moreover, I have learned a great deal from the existing ecosystem of Scheme languages, particularly Racket, my preferred dialect.
   I have used Racket as a loose reference implementation, and I have furthermore used it to implement an extensive test suite.
   By studying a practical, real-world functional language, and by implementing real-world tasks in a functional paradigm, I have been able
   to build on my existing academic background and expand my knowledge in this area.

## License

ploy is distributed under the MIT license, reproduced below:

Copyright (c) 2016 Adam "as3richa" Richardson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
