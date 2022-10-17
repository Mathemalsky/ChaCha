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

#include <cstring>
#include <iostream>

#include "colors.hpp"
#include "measurement.hpp"

#ifdef _WIN32
static const std::string PROJECT_NAME = "chacha.exe";
#else
static const std::string PROJECT_NAME = "./chacha";
#endif

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
  std::cout << "Type " << PROJECT_NAME << " help to see syntax help.\n";
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

void warnLowEntropy() {
  std::cout << timestamp(current_duration());
  print_yellow("WARNING: ");
  std::cout << "Key geneeration is about to draw random data from determenistic RNG.\n";
  std::cout << "Do you want to continue anyway? [yN]\n";
  std::string answer;
  std::cin >> answer;
  if (answer == "yes" || answer == "y" || answer == "Y" || answer == "Yes" || answer == "YES") {
    return;
  }
  else {
    exit(-1);
  }
}

void printCryptSyntax() {
  std::cout << "-" << PROJECT_NAME << " <src> <dst> <key>\n";
  std::cout << "           <src> : file to read from\n";
  std::cout << "           <dst> : file to write to\n";
  std::cout << "           <key> : file to read the key from\n";
}

void printKeyGenSyntax() {
  std::cout << "-" << PROJECT_NAME << " <flag> <dst>>\n";
  std::cout << "          <flag> : -k or -keygen for generating a key\n";
  std::cout << "           <dst> : file to write the key to\n";
}

void syntaxHelp(const char* topic) {
  std::cout << "Syntax\n======\n";
  if (std::strcmp(topic, "keygen") == 0) {
    printKeyGenSyntax();
  }
  else if (std::strcmp(topic, "crypt") == 0) {
    printCryptSyntax();
  }
  else {
    printCryptSyntax();
    printKeyGenSyntax();
  }
}
