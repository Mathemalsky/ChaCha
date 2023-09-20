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

/*! \file chacha.hpp */

#include <cstdint>
#include <cstdlib>

/*!
 * class ChaCha
 * \brief implemnts the csprng ChaCha
 * \details compare implementation to: BERNSTEIN, Daniel J., et al. ChaCha, a variant of Salsa20. In: Workshop record of
 * SASC. 2008. S. 3-5.
 */
class ChaCha {
private:
  uint32_t pState[16]; /**< compile time fixed memory size according to Bernsteins algorithm **/
  static constexpr unsigned int DOUBLE_ROUNDS   = 10; /**< constant for number of rounds **/
  static constexpr uint32_t expand_32_byte_k[4] = {
    0x61707865, 0x3320646e, 0x79622d32, 0x6b206574}; /**< nothing in the sleeve number **/

public:
  ChaCha() = default;

  /*!
   * \brief init sets the initial state
   * \details The first 4 * 4 bytes are set to the nothing in the sleeve constant defined by "expand 32-byte k".
   * The following 12 * 4 bytes are set to the given key.
   * \param key has to be 48 byte to initialize the state of the chacha algorithm
   * \param counterOffset is added to the counter after copying the key
   */
  void init(const void* key, const uint32_t counterOffset = 0);

  /*!
   * \brief operator() computes 64 bytes from the current state
   * \details perfoms the rounds on the current internal state (without changing it) and ticks the counter of the
   * internal state once.
   * \param workingState the 64 output bytes will be written to this address
   */
  void operator()(uint32_t* workingState);

  ~ChaCha() = default;
};
