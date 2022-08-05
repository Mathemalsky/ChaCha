#include "fileinteraction.hpp"

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>

#include "error.hpp"
#include "measurement.hpp"

void readFile(Data& bytes, const char* filename) {
  FILE* myfile = fopen(filename, "rb");
  if (!myfile) {
    throw FileNotFound(filename);
  }

  size_t size = fread(bytes.bytes, 1, bytes.size, myfile) * sizeof(std::byte);
  fclose(myfile);
  assert(size == bytes.size && "Incomplete read of file!");
  (void) size;
  std::cout << timestamp(current_duration()) << "File has been read from <" << filename << ">.\n";
}

void writeFile(const Data& bytes, const char* filename) {
  FILE* myfile = fopen(filename, "wb");
  if (!myfile) {
    throw CannotCreateFile(filename);
  }
  fwrite(bytes.bytes, 1, bytes.size, myfile);
  fclose(myfile);
  std::cout << timestamp(current_duration()) << "File has been written to <" << filename << ">.\n";
}

std::string nameEdit(const char* filename) {
  std::string originalname(filename);
  const unsigned int length = originalname.length();
  unsigned int pointPos     = 0;

  for (unsigned int i = length - 1; i >= 1; --i) {
    if (originalname[i] == '.') {
      pointPos = i;
      break;
    }
  }

  std::string newname;
  if (pointPos >= 6 && originalname.substr(pointPos - 6, 6) == "_crypt") {
    newname = originalname.substr(0, pointPos - 6);
    newname += originalname.substr(pointPos, length - pointPos);
  }
  else {
    newname = originalname.substr(0, pointPos);
    newname += "_crypt" + originalname.substr(pointPos, length - pointPos);
  }
  return newname;
}
