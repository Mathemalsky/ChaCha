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

/*! \file fileinteraction.hpp */

#include <cstddef>
#include <fstream>
#include <string>

/*!
 * \struct Data
 * \brief The struct Data is a simple array and it's length.
 * \details It's intended to contain the complete information from a file.
 */
struct Data {
  std::byte* bytes;    /**< an array of bytes (unsigned chars) */
  const uint64_t size; /**< the length of the array */
};

/** \def Assuming we are compiling with at least gcc 8.0 we can use std::filesystem and it's c++17
 * features. */
#if defined(__GNUC)
#include <features.h>
#if __GNUC_PREREQ(8, 0)
#include <filesystem>
/*!
 * \brief detects how large the file is
 * \param filename name of the considered file
 * \return a size_t that is the size of the file in bytes
 */
inline size_t fileSize(const char* filename) {
  std::filesystem::path p{filename};
  return std::filesystem::file_size(p);
}
#else
/*!
 * \brief detects how large the file is
 * \param filename Name of the considered file.
 * \return size_t that is the size of the file in bytes.
 */
inline size_t fileSize(const char* filename) {
  std::ifstream myfile(filename, std::ios::binary);
  if (!myfile) {
    // throw FileNotFound(std::string(filename), "file_size");
  }
  myfile.seekg(0, std::ios::end);
  const size_t size = myfile.tellg();
  return size;
}
#endif
#else
/*!
 * \brief detects how large the file is
 * \param filename Name of the considered file.
 * \return A size_t that is the size of the file in bytes.
 */
inline size_t fileSize(const char* filename) {
  std::ifstream myfile(filename, std::ios::binary);
  myfile.seekg(0, std::ios::end);
  const size_t size = myfile.tellg();
  return size;
}
#endif

/*!
 * \brief readFile reads given number of bytes from file into bytes
 * \param bytes contains a byte pointer and a size
 * \param filename to be read
 */
void readFile(Data& bytes, const char* filename);

/*!
 * \brief writeFile writes bytes in given filename
 * \param bytes data to be written
 * \param filename name of file to be created
 */
void writeFile(const Data& bytes, const char* filename);

/*!
 * \brief nameEdit infers a output name for a given input file name
 * \param filename name of the input file
 * \return
 */
std::string nameEdit(const char* filename);
