/*
 * ChaCha is a CSPRNG introduced by Daniel J.Bernstein. This project
 * uses it as base for a symmetric encryption sceme.
 * Copyright (C) 2022 Mathemalsky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

/*! \file error.hpp */

#include <stdexcept>
#include <string>

/*!
 * \brief Error class as main class to bundle all error messages
 */
class Error : public std::exception {};

/*!
 * \brief FileNotFound class
 */
class FileNotFound : public Error {
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

/*!
 * \brief CannotCreateFile class
 */
class CannotCreateFile : public Error {
public:
  /*!
   * \brief CannotCreateFile constructor
   * \param filename name of the file failed to create
   */
  CannotCreateFile(std::string filename);
  /*!
   * \brief what prints error message
   * \return
   */
  const char* what() const noexcept override;

private:
  std::string pFilename;
};

/*!
 * \brief InappropriatNumberOfArguments class
 */
class InappropriatNumberOfArguments : public Error {
public:
  /*!
   * \brief InappropriatNumberOfArguments
   * \param expected number of arguments expected
   * \param got number of arguments in the user input
   */
  InappropriatNumberOfArguments(const unsigned int expected, const unsigned int got);
  /*!
   * \brief what
   * \return
   */
  const char* what() const noexcept override;

private:
  unsigned int pExpected, pGot;
};

/*!
 * \brief The ToShortKey class
 */
class ToShortKey : public Error {
public:
  /*!
   * \brief ToShortKey
   * \param keylength length of the key file
   * \param expexcted length needed to initialize the block
   */
  ToShortKey(const unsigned int keylength, const unsigned int expexcted = 48);
  /*!
   * \brief what
   * \return
   */
  const char* what() const noexcept override;

private:
  unsigned int pKeylength, pExpected;
};

/*!
 * \brief syntaxHelp displays the semantic of the program call
 */
void syntaxHelp();
