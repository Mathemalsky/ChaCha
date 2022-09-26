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
#include "encrypt.hpp"

#include <iostream>

#include "chacha.hpp"
#include "measurement.hpp"

static inline void pad(std::byte* position, ChaCha& rng) {
  uint32_t paddingInts[16];
  rng(paddingInts);

  uint32_t* dataInts = (uint32_t*) position;

  for (unsigned int i = 0; i < 16; ++i) {
    dataInts[i] ^= paddingInts[i];
  }
}

static void padEnd(std::byte* position, ChaCha& rng, const unsigned int length) {
  const unsigned int multiple4length = length / 4;
  const unsigned int remainder       = length - 4 * multiple4length;

  uint32_t paddingInts[16];
  rng(paddingInts);

  uint32_t* databytes = (uint32_t*) position;

  for (unsigned int i = 0; i < multiple4length; ++i) {
    databytes[i] ^= paddingInts[i];
  }

  std::byte* paddingBytes = (std::byte*) paddingInts;
  for (unsigned int i = 0; i < remainder; ++i) {
    position[4 * multiple4length + i] ^= paddingBytes[4 * multiple4length + i];
  }
}

void crypt(Data& data, const void* key) {
  // set up rng
  ChaCha rng;
  rng.init(key);

  const uint64_t lenghtRoundDown = data.size / 64;  // number of full 64 byte blocks fitting in the length
  const uint64_t lengthTail      = data.size - 64 * lenghtRoundDown;

  // pad blocks of 64 bytes
  for (unsigned int i = 0; i < lenghtRoundDown; ++i) {
    pad(data.bytes + 64 * i, rng);
  }

  // pad the end of the file
  padEnd(data.bytes + 64 * lenghtRoundDown, rng, lengthTail);
  std::cout << timestamp(current_duration()) << "File has been encrypted/ decrypted.\n";
}

void cryptHandler(const char* contentFile, const char* outputFile, const char* keyFile) {
  // read content
  const size_t contentSize = fileSize(contentFile);
  std::byte* contentBytes  = (std::byte*) malloc(contentSize);
  Data content{contentBytes, contentSize};
  readFile(content, contentFile);

  // read key
  const size_t keySize = fileSize(keyFile);
  std::byte* keyBytes  = (std::byte*) malloc(keySize);
  Data key{keyBytes, keySize};
  readFile(key, keyFile);

  // encrypt the data
  crypt(content, key.bytes);

  // write the file
  writeFile(content, outputFile);

  // free the allocated memory
  free(keyBytes);
  free(contentBytes);
}
