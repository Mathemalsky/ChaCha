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
#include "keygen.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <limits>
#include <random>

#include "error.hpp"
#include "fileinteraction.hpp"

Data generateKey() {
// on most linux variants we can directly read from /dev/random
#ifdef __linux__
  std::ifstream stream("/dev/urandom", std::ios_base::binary | std::ios_base::in);
  if (stream) {
    std::byte* bytes = (std::byte*) std::malloc(KEYLENGTH);
    stream.read((char*) bytes, KEYLENGTH);
    return Data{bytes, KEYLENGTH};
  }
  else {
    warnNoDevRandom();
  }
#endif

  std::array<uint32_t, KEYLENGTH / sizeof(uint32_t)> key;
  std::random_device src;
  if (src.entropy() < std::numeric_limits<uint32_t>::digits) {
    // raise warning
    warnLowEntropy();
  }
  std::generate(key.begin(), key.end(), std::ref(src));
  std::byte* keyBytes = (std::byte*) std::malloc(KEYLENGTH);
  return Data{keyBytes, KEYLENGTH};
}

void keyGenHandler(const char* filename) {
  Data data = generateKey();
  writeFile(data, filename);
  free(data.bytes);
}
