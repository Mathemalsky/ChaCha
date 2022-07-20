#pragma once

/*! \file error.hpp */

#include <stdexcept>
#include <string>

class Error : std::exception {
protected:
  std::string pMessage;
};

class FileNotFound : Error {
public:
  FileNotFound(std::string filename);
  const char* what() const noexcept override;

private:
  std::string pFilename;
};

class CannotCreateFile : Error {
public:
  CannotCreateFile(std::string filename);
  const char* what() const noexcept override;

private:
  std::string pFilename;
};
