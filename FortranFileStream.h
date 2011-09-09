#include <string>

//FIXME take out for general compilery stuff
#define FC_FUNC(name, NAME) name ## _

namespace LHAPDFTOOLS
{
  class FortranFileStream
  {
    private:
      std::string _mkStringFromFortran(char* fstring, size_t length);
      std::string readLine();
      void popBuffer(int delimiterFindStart = 0); // is pop the right word?

      std::string self_readBuffer;
      std::string self_filePath;
      int    self_unitNumber;

    public:
      FortranFileStream(int unitNumber, std::string path);
      ~FortranFileStream();

      void open(int unitNumber, std::string path);

      //Stream Operators
      FortranFileStream& operator >> (std::string& target);
      FortranFileStream& operator >> (int& target);
      FortranFileStream& operator >> (double& target);

  };
};
