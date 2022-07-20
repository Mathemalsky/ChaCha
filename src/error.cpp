#include "error.hpp"

#include <iostream>

#include "colors.hpp"

FileNotFound::FileNotFound(const std::string filename) : pFilename(filename) {
}

const char* FileNotFound::what() const noexcept {
  print_lightred("ERROR: ");
  std::cout << "File <" << pFilename << "> not found.\n";
  exit(-1);
}

CannotCreateFile::CannotCreateFile(const std::string filename) : pFilename(filename) {
}

const char* CannotCreateFile::what() const noexcept {
  print_lightred("ERROR: ");
  std::cout << "Couldn't create file <" << pFilename << ">.\n";
  exit(-1);
}
