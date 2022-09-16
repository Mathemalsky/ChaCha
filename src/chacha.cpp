#include "chacha.hpp"

#include <cstring>

void ChaCha::init(const void* key, const uint32_t counterOffset) {
  std::memcpy(pState, &expand_32_byte_k[0], 16);  // copy the constant in the key
  std::memcpy(pState + 4, key, 48);               // 48 = 12 * 4 Byte
  pState[12] += counterOffset;
}

#if defined __SSE2__

#include <immintrin.h>
static inline void rotleft(__m128i& a, unsigned int count) {
#if defined __SSSE3__  // optimization for shifting by 8 or 16 bit
  // no performance cost for case distinction because inlined and compile time evaluated
  if (count == 8) {
    a = _mm_shuffle_epi8(a, _mm_set_epi8(14, 13, 12, 15, 10, 9, 8, 11, 6, 5, 4, 7, 2, 1, 0, 3));
  }
  else if (count == 16) {
    a = _mm_shuffle_epi8(a, _mm_set_epi8(13, 12, 15, 14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2));
  }
  else {
    // would also work with _mm_xor_si128 or any _mm_add function because by shifting inserted bits are cleared
    a = _mm_or_si128(_mm_slli_epi32(a, count), _mm_srli_epi32(a, 32 - count));
  }
#else
  // would also work with _mm_xor_si128 or any _mm_add function because by shifting inserted bits are cleared
  a = _mm_or_si128(_mm_slli_epi32(a, count), _mm_srli_epi32(a, 32 - count));
#endif
}

static void inline quaterRound(__m128i& a, __m128i& b, __m128i& c, __m128i& d) {
  a = _mm_add_epi32(a, b);
  d = _mm_xor_si128(d, a);
  rotleft(d, 16);

  c = _mm_add_epi32(c, d);
  b = _mm_xor_si128(b, c);
  rotleft(b, 12);

  a = _mm_add_epi32(a, b);
  d = _mm_xor_si128(d, a);
  rotleft(d, 8);

  c = _mm_add_epi32(c, d);
  b = _mm_xor_si128(b, c);
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
    b = _mm_shuffle_epi32(b, 0b00111001);
    c = _mm_shuffle_epi32(c, 0b01001110);
    d = _mm_shuffle_epi32(d, 0b10010011);

    quaterRound(a, b, c, d);

    b = _mm_shuffle_epi32(b, 0b10010011);
    c = _mm_shuffle_epi32(c, 0b01001110);
    d = _mm_shuffle_epi32(d, 0b00111001);
  }

  // load the state
  __m128i aState = _mm_load_si128((__m128i*) &pState[0]);
  __m128i bState = _mm_load_si128((__m128i*) &pState[4]);
  __m128i cState = _mm_load_si128((__m128i*) &pState[8]);
  __m128i dState = _mm_load_si128((__m128i*) &pState[12]);

  // add original state to current
  a = _mm_add_epi32(a, aState);
  b = _mm_add_epi32(b, bState);
  c = _mm_add_epi32(c, cState);
  d = _mm_add_epi32(d, dState);

  // store the data into working state
  _mm_store_si128((__m128i*) &workingState[0], a);
  _mm_store_si128((__m128i*) &workingState[4], b);
  _mm_store_si128((__m128i*) &workingState[8], c);
  _mm_store_si128((__m128i*) &workingState[12], d);

  // increase counter by one
  ++pState[12];
}

#else

// implementation related to:
// https://stackoverflow.com/questions/776508/best-practices-for-circular-shift-rotate-operations-in-c
static inline uint32_t rotleft(const uint32_t integer, unsigned int count) {
  return (integer << count | integer >> (32 - count));
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
