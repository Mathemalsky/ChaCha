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
  std::cout << "To short keyfile! Got " << pKeylength << ", but expected at least " << pExpected << "bytes.\n";
  exit(-1);
}
