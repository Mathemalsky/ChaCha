#include "error.hpp"

#include <iostream>

#include "colors.hpp"
#include "measurement.hpp"

FileNotFound::FileNotFound(const std::string filename) : pFilename(filename) {
}

const char* FileNotFound::what() const noexcept {
  std::cout << timestamp(current_duration());
  print_lightred("ERROR: ");
  std::cout << "File <" << pFilename << "> not found.\n";
  exit(-1);
}

CannotCreateFile::CannotCreateFile(const std::string filename) : pFilename(filename) {
}

const char* CannotCreateFile::what() const noexcept {
  std::cout << timestamp(current_duration());
  print_lightred("ERROR: ");
  std::cout << "Couldn't create file <" << pFilename << ">.\n";
  exit(-1);
}

InappropriatNumberOfArguments::InappropriatNumberOfArguments(const unsigned int expected, const unsigned int got)
  : pExpected(expected), pGot(got) {
}

const char* InappropriatNumberOfArguments::what() const noexcept {
  std::cout << timestamp(current_duration());
  print_lightred("ERROR: ");
  std::cout << "Inappropriat number of arguments: Got <" << pGot << ", but expected " << pExpected << ">.\n";
  exit(-1);
}

ToShortKey::ToShortKey(const unsigned int keylength, const unsigned int expected)
  : pKeylength(keylength), pExpected(expected) {
}

const char* ToShortKey::what() const noexcept {
  std::cout << timestamp(current_duration());
  print_lightred("ERROR: ");
  std::cout << "To short keyfile! Expected at least " << pExpected << "bytes.\n";
  exit(-1);
}
