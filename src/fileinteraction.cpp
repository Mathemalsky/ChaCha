#include "fileinteraction.hpp"

#include <cassert>
#include <fstream>
#include <cstring>

void readFile(Data& bytes, const char* filename) {
  FILE* myfile = fopen(filename, "rb");
  if (!myfile) {
    // throw FileNotFound("read_file", filename);
  }

  size_t size = fread(bytes.bytes, 1, bytes.size, myfile) * sizeof(std::byte);
  fclose(myfile);
  assert(size == bytes.size && "Incomplete read of file!");
  (void) size;
  // std::cout << timestamp(current_duration()) << "File has been read from <" << filename << ">.\n";
}

void writeFile(const Data& bytes, const char* filename) {
  FILE* myfile = fopen(filename, "wb");
  if (!myfile) {
    // throw CannotCreateFile("write_file", filename);
  }
  fwrite(bytes.bytes, 1, bytes.size, myfile);
  fclose(myfile);
  // std::cout << timestamp(current_duration()) << "File has been written to <" << filename << ">.\n";
}

const char* nameEdit(const char* filename) {
  std::string originalname(filename);
  const unsigned int length = originalname.length();
  unsigned int pointPos     = 0;

  for (unsigned int i = length - 1; i >= 1; --i) {
    if (std::strcmp(&originalname[i], ".") == 0) {
      pointPos = i;
      break;
    }
  }

  // CONSIDER CASE WHEN filename has no point, or starts with a point

  std::string newname = originalname.substr(0, pointPos);
  newname += "crypt" + originalname.substr(pointPos + 1, length - pointPos - 1);
  return newname.c_str();
}
