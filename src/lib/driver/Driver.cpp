#include <cctype>
#include <fstream>
#include <cassert>

#include "lib/driver/Driver.hpp"

CSSP::Driver::~Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

int CSSP::Driver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       return EXIT_FAILURE;
   }

   return parse_helper( in_file );
}

int CSSP::Driver::parse( std::istream &stream )
{
   if( ! stream.good()  && stream.eof() )
   {
       return EXIT_FAILURE;
   }

   return parse_helper( stream );
}


int CSSP::Driver::parse_helper( std::istream &stream )
{

   delete(scanner);
   try
   {
      scanner = new CSSP::Scanner( &stream );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }

   delete(parser);
   try
   {
      parser = new CSSP::Parser( (*scanner) /* scanner */,
                                  (*this) /* driver */ );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   const int accept( 0 );
   if( parser->parse() != accept )
   {
      std::cerr << "Parse failed!!\n";
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}

void CSSP::Driver::add_upper()
{
   uppercase++;
   chars++;
   words++;
}

void CSSP::Driver::add_lower()
{
   lowercase++;
   chars++;
   words++;
}

void CSSP::Driver::add_word( const std::string &word )
{
   words++;
   chars += word.length();
   for(const char &c : word ){
      if( islower( c ) )
      {
         lowercase++;
      }
      else if ( isupper( c ) )
      {
         uppercase++;
      }
   }
}

void CSSP::Driver::add_newline()
{
   lines++;
   chars++;
}

void CSSP::Driver::add_char()
{
   chars++;
}


std::ostream& CSSP::Driver::print( std::ostream &stream )
{
   stream << red  << "Results: " << norm << "\n";
   stream << blue << "Uppercase: " << norm << uppercase << "\n";
   stream << blue << "Lowercase: " << norm << lowercase << "\n";
   stream << blue << "Lines: " << norm << lines << "\n";
   stream << blue << "Words: " << norm << words << "\n";
   stream << blue << "Characters: " << norm << chars << "\n";
   return(stream);
}
