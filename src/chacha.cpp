#include "chacha.hpp"

#include <cstring>

void ChaCha::init(const void* key, const uint32_t counterOffset) {
  std::memcpy(pState, &expand_32_byte_k[0], 16);  // copy the constant in the key
  std::memcpy(pState + 4, key, 48);               // 48 = 12 * 4 Byte
  pState[12] += counterOffset;
}

#ifdef __SSE3__

#include <immintrin.h>
static inline void rotleft(__m128i& a, unsigned int count) {
  // can be optimized in case  count is divisible by 8
  a = _mm_or_epi32(_mm_slli_epi32(a, count), _mm_srli_epi32(a, 32 - count));
}

static void inline quaterRound(__m128i& a, __m128i& b, __m128i& c, __m128i& d) {
  a = _mm_add_epi32(a, b);
  d = _mm_xor_si128(d, a);
  rotleft(d, 16);

  c = _mm_add_epi32(c, d);
  b = _mm_xor_epi32(b, c);
  rotleft(b, 12);

  a = _mm_add_epi32(a, b);
  d = _mm_xor_si128(d, a);
  rotleft(d, 8);

  c = _mm_add_epi32(c, d);
  b = _mm_xor_epi32(b, c);
  rotleft(b, 7);
}

void ChaCha::operator()(uint32_t* workingState) {
  std::memcpy(&workingState[0], &pState[0], 64);

  __m128i a = _mm_load_si128((__m128i*) &workingState[0]);
  __m128i b = _mm_load_si128((__m128i*) &workingState[4]);
  __m128i c = _mm_load_si128((__m128i*) &workingState[8]);
  __m128i d = _mm_load_si128((__m128i*) &workingState[12]);

  for (unsigned int i = 0; i < DOUBLE_ROUNDS; ++i) {
    // uneven rounds

    quaterRound(a, b, c, d);

    // even rounds

    // maybe fatser with shuffle
    _mm_store_si128((__m128i*) &workingState[0], a);
    _mm_store_si128((__m128i*) &workingState[4], b);
    _mm_store_si128((__m128i*) &workingState[8], c);
    _mm_store_si128((__m128i*) &workingState[12], d);

    a = _mm_set_epi32(workingState[0], workingState[5], workingState[10], workingState[15]);
    b = _mm_set_epi32(workingState[1], workingState[6], workingState[11], workingState[12]);
    c = _mm_set_epi32(workingState[2], workingState[7], workingState[8], workingState[13]);
    d = _mm_set_epi32(workingState[3], workingState[4], workingState[9], workingState[14]);

    quaterRound(a, b, c, d);

    _mm_store_si128((__m128i*) &workingState[0], a);
    _mm_store_si128((__m128i*) &workingState[4], b);
    _mm_store_si128((__m128i*) &workingState[8], c);
    _mm_store_si128((__m128i*) &workingState[12], d);
  }

  // add original state to current
  for (unsigned int i = 0; i < 16; ++i) {
    workingState[i] += pState[i];
  }

  // increase counter by one
  ++pState[12];
}

#else

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

#endif
