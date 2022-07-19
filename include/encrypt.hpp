#pragma once

/*! \file encrypt.hpp */

#include "fileinteraction.hpp"

/*!
 * \brief crypt encrypts/ decrypts data with the given key
 * \param data  given data to be encrypted/ decrypted
 * \param key 48 bytes to initialize the chacha CSPRNG
 */
void crypt(Data& data, const void* key);

/*!
 * \brief cryptHandler reads all neccesary files invokes the crypt function and writes the processed data to file
 * \param contentFile file to read from
 * \param outputFile file to write to
 * \param keyFile file to read the key from
 */
void cryptHandler(const char* contentFile, const char* outputFile, const char* keyFile);
