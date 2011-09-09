#include <iostream>
#include <string>
#include "FortranFileStream.h"
using std::cout;
using std::endl;
using std::string;
using LHAPDFTOOLS::FortranFileStream;

int main(int argc, char* argv[])
{
  FortranFileStream STRM( 1, "test.txt" );

  string dummy, version;

  STRM >> dummy >> version;

  string description;
  STRM >> description;

  string type, order, code;
  STRM >> type >> order >> code;

  string listType;
  int number, repeats;
  STRM >> listType >> number >> repeats;

  double double1, double2, double3, double4;
  STRM >> double1 >> double2 >> double3 >> double4;

  double a[8];
  STRM >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6] >> a[7];

  string str1, str2;
  STRM >> str1 >> str2;

  cout << dummy << " " << version << " " << endl;
  cout << description << " " << endl;
  cout << type << " " << order << " " << code << " " << endl;
  cout << listType << " " << number << " " << repeats << " " << endl;
  cout << double1 << " " << double2 << " " << double3 << " " 
       << double3 << " " << endl;
  cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " 
       << a[4] << " " << a[5] << " " << a[6] << " " << a[7] << " " << endl;

  cout << str1 << " " << str2  << " " << endl;


  return 0;
}
