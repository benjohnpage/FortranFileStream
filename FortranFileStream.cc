
////////////////////////////////////////////////////////////////////////
//  Ben Page 09-09-2011 
//  FortranFileStream:
//  An interface class for reading in fortran file units as a stream.
////////////////////////////////////////////////////////////////////////

#include "FortranFileStream.h"
#include <string>
#include <cstring>
#include <cstdlib>
using std::string;
using LHAPDFTOOLS::FortranFileStream;

// External fortran functions for FILE IO
extern "C"
{
  #define ffileopen FC_FUNC(fileopen, FILEOPEN)
  void ffileopen(int& unit, const char* filepath, int length);

  #define ffileclose FC_FUNC(fileclose, FILECLOSE)
  void ffileclose(int& unit);

  #define ffilereadline FC_FUNC(filereadline, FILEREADLINE)
  void ffilereadline(int& unit, char* lineBuff, int lineLength);

  //NOTE - The ordering of arguments here may well be compiler dependant
  #define fstringreadstring FC_FUNC(stringreadstring, STRINGREADSTRING)
  void fstringreadstring( const char* input, char* output, int inLen, 
                          int outLen );

  #define fstringreadinteger FC_FUNC(stringreadinteger, STRINGREADINTEGER)
  void fstringreadinteger( const char* input, int& output, int inLen);

  #define fstringreaddouble FC_FUNC(stringreaddouble, STRINGREADDOUBLE)
  void fstringreaddouble( const char* input, double& output, int inLen);
}

string FortranFileStream::_mkStringFromFortran(char* fstring, size_t length)
{
  fstring[length] = '\0';
  for (size_t i = length - 1; i >= 0; i--)
  {
    if ( fstring[i] != ' ' )
    {
      fstring[ i+1 ] ='\0';
      break;
    }
  }
  return string(fstring);
}

string FortranFileStream::readLine()
{
  // This uses Fortran to read a line up to bufferSize long.
  size_t bufferSize = 512;

  char* fortranBuffer = (char*)malloc( ( bufferSize + 1 ) * 
                                         sizeof( char ) );
  memset( fortranBuffer, 0, bufferSize );
  
  ffilereadline( self_unitNumber, fortranBuffer, bufferSize );

  string line =_mkStringFromFortran(fortranBuffer, bufferSize);
  free(fortranBuffer);

  //Make sure it finishes with a new line
  line += '\n';
  return line;
}

void FortranFileStream::popBuffer(int delimiterFindStart) 
{
  // The function takes an optional argument to define where we should
  // start looking for the next bit of data. But this is only used in
  // the string case, where it is less than obvious.

  char delimiters[] = " ,\n"; //Space, comma, new line

  size_t firstDelimiter = self_readBuffer.find_first_of( delimiters,
                                                    delimiterFindStart);
  
  // Next we need to find the next bit of data (i.e. something that's
  // not a delimiter
  size_t nonDelimPos = self_readBuffer
                        .find_first_not_of( delimiters, firstDelimiter);

  // Then either snip, or kill it completely!
  if (nonDelimPos != string::npos)
    self_readBuffer = self_readBuffer.substr( nonDelimPos );
  else
    self_readBuffer = "";
}

void FortranFileStream::open(int unitNumber, string path)
{
  self_unitNumber = unitNumber;
  self_filePath = path;
  self_readBuffer =  "";

  ffileopen( unitNumber, path.c_str(), path.length() );
}

FortranFileStream::FortranFileStream()
  : self_unitNumber(0)
{
}

FortranFileStream::FortranFileStream(int unitNumber, string path)
{
  open(unitNumber, path);
}

FortranFileStream::~FortranFileStream()
{
  if ( self_unitNumber > 0 )
    ffileclose( self_unitNumber );
}

FortranFileStream& FortranFileStream::operator >> (string& target)
{
  if ( self_unitNumber > 0 )
  {
    // Get a new line if there's nothing left
    if ( self_readBuffer == "" ) 
      self_readBuffer = readLine();

    // Prepare some memory to be our new string
    size_t targetBufferSize = 512;
    char* targetBuffer = (char*) malloc( (targetBufferSize + 1) *
                                         sizeof(char) );
    memset( targetBuffer, 0, targetBufferSize );

    fstringreadstring( self_readBuffer.c_str(), targetBuffer, 
                       self_readBuffer.length(), targetBufferSize );
    // Set the target
    target = _mkStringFromFortran(targetBuffer, targetBufferSize);

    // Free the memory
    free(targetBuffer);


    // Tell popBuffer to start cutting after our string
    size_t delimiterFindStart = 0;
    if (self_readBuffer.at(0) =='\'')
    {
      // It's a long inverted comma encapsulated string, so it might
      // contain our delimiters, lets move to the other inverted comma.
      delimiterFindStart = target.length() + 1; 
    }

    popBuffer( delimiterFindStart );

  }
  return *this;
}

FortranFileStream& FortranFileStream::operator >> (int& target)
{
  if ( self_unitNumber > 0 )
  {
    // Get a new line if there's nothing left
    if ( self_readBuffer == "" ) 
      self_readBuffer = readLine();

    // Read the integer into the target
    fstringreadinteger( self_readBuffer.c_str(), target, 
                        self_readBuffer.length() );

    popBuffer();

  }
  return *this;
}

FortranFileStream& FortranFileStream::operator >> (double& target)
{
  if ( self_unitNumber > 0 )
  {
    // Get a new line if there's nothing left
    if ( self_readBuffer == "" ) 
      self_readBuffer = readLine();

    // Read the integer into the target
    fstringreaddouble( self_readBuffer.c_str(), target, 
                       self_readBuffer.length() );

    popBuffer();

  }
  return *this;
}

