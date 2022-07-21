#pragma once

/*! \file error.hpp */

#include <stdexcept>
#include <string>

/*!
 * \brief Error class as main class to bundle all error messages
 */
class Error : public std::exception {
protected:
  std::string pMessage;
};

/*!
 * \brief FileNotFound class
 */
class FileNotFound : Error {
public:
  /*!
   * \brief FileNotFound constructor
   * \param filename name of file not found
   */
  FileNotFound(std::string filename);
  /*!
   * \brief what prints error message
   * \return
   */
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

class InappropriatNumberOfArguments : Error {
public:
  InappropriatNumberOfArguments(const unsigned int expected, const unsigned int got);
  const char* what() const noexcept override;

private:
  unsigned int pExpected, pGot;
};

class ToShortKey : Error {
public:
  ToShortKey(const unsigned int keylength, const unsigned int expexcted = 48);
  const char* what() const noexcept override;

private:
  unsigned int pKeylength, pExpected;
};
