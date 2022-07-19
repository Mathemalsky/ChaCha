#include "chacha.hpp"

#include <cstring>

// implementation related to:
// https://stackoverflow.com/questions/776508/best-practices-for-circular-shift-rotate-operations-in-c
static inline uint32_t rotleft(const uint32_t integer, unsigned int count) {
  const unsigned int cutof = 31;
  count &= cutof;  // shifts larger than 31 bits are not needed in a 32 bit integer
  return (integer << count | integer >> ((-count) & cutof));
}

static inline void quaterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
  a += b;
  d ^= a;
  d = rotleft(d, 16);

  c += d;
  b ^= c;
  b = rotleft(b, 12);

  a += b;
  d ^= a;
  d = rotleft(d, 8);

  c += d;
  b ^= c;
  b = rotleft(b, 7);
}

void ChaCha::init(const void* key, const uint32_t counterOffset) {
  std::memcpy(pState, &expand_32_byte_k[0], 16);  // copy the constant in the key
  std::memcpy(pState + 4, key, 48);               // 48 = 12 * 4 Byte
  pState[12] += counterOffset;
}

void ChaCha::operator()(uint32_t* workingState) {
  std::memcpy(&workingState[0], &pState[0], 64);

  for (unsigned int i = 0; i < DOUBLE_ROUNDS; ++i) {
    // uneven rounds
    quaterRound(workingState[0], workingState[4], workingState[8], workingState[12]);
    quaterRound(workingState[1], workingState[5], workingState[9], workingState[13]);
    quaterRound(workingState[2], workingState[6], workingState[10], workingState[14]);
    quaterRound(workingState[3], workingState[7], workingState[11], workingState[15]);

    // even rounds
    quaterRound(workingState[0], workingState[5], workingState[10], workingState[15]);
    quaterRound(workingState[1], workingState[6], workingState[11], workingState[12]);
    quaterRound(workingState[2], workingState[7], workingState[8], workingState[13]);
    quaterRound(workingState[3], workingState[4], workingState[9], workingState[14]);
  }

  // add original state to current
  for (unsigned int i = 0; i < 16; ++i) {
    workingState[i] += pState[i];
  }

  // increase counter by one
  ++pState[12];
}
