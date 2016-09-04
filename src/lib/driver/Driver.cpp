#include <cctype>
#include <fstream>

#include "lib/driver/Driver.hpp"

CSSP::Driver::~Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

int CSSP::Driver::parse( const char * const filename)
{
   if ( filename == nullptr ) {
       this->error
            << "Failed to read from file"
            << std::endl;
       return EXIT_FAILURE;
   }
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       this->error
            << "Failed to read from file"
            << std::endl;
       return EXIT_FAILURE;
   }

   return parse_helper( in_file );
}

int CSSP::Driver::parse( std::istream &stream )
{
   if( ! stream.good()  && stream.eof() )
   {
       this->error
            << "Failed to read from stream"
            << std::endl;
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
      this->error
            << "Failed to allocate scanner: ("
            << ba.what()
            << ")"
            << std::endl;

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
      this->error
            << "Failed to allocate parser: ("
            << ba.what()
            << ")"
            << std::endl;
      exit( EXIT_FAILURE );
   }

   if( parser->parse() != EXIT_SUCCESS )
   {

      this->error
            << "Parser failed - parser end in non-acceptable state"
            << std::endl;
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
