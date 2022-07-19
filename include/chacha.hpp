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
  uint32_t pState[16];                     /**< compile time fixed memory size according to Bernsteins algorithm **/
  const unsigned int DOUBLE_ROUNDS   = 10; /**< constant for number of rounds **/
  const uint32_t expand_32_byte_k[4] = {
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
   * internal state once. \param workingState the 64 output bytes will be written to this address
   */
  void operator()(uint32_t* workingState);

  ~ChaCha() = default;
};
