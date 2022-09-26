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
