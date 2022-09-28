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

class CannotCreateFile : public Error {
public:
  CannotCreateFile(std::string filename);
  const char* what() const noexcept override;

private:
  std::string pFilename;
};

class InappropriatNumberOfArguments : public Error {
public:
  InappropriatNumberOfArguments(const unsigned int expected, const unsigned int got);
  const char* what() const noexcept override;

private:
  unsigned int pExpected, pGot;
};

class ToShortKey : public Error {
public:
  ToShortKey(const unsigned int keylength, const unsigned int expexcted = 48);
  const char* what() const noexcept override;

private:
  unsigned int pKeylength, pExpected;
};

void syntaxHelp(const std::string topic = "");
