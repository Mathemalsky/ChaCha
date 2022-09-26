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
#include <iostream>

#include "chacha.hpp"
#include "colors.hpp"
#include "encrypt.hpp"
#include "error.hpp"
#include "measurement.hpp"

int main(int argc, char* argv[]) {
  start_time();
#ifdef _WIN32
  enable_windows_virtual_terminal_sequence();
#endif
  // TRY/CATCH very preliminary
  try {
    if (argc == 3) {
      // pass name of content file and keyfile
      cryptHandler(argv[1], nameEdit(argv[1]).c_str(), argv[2]);
    }
    else if (argc == 4) {
      // pass name of content file, file to write and keyfile
      cryptHandler(argv[1], argv[2], argv[3]);
    }
    else {
      throw InappropriatNumberOfArguments(4, argc);
    }
  } catch (Error& error) {
    error.what();
  }

  std::cout << timestamp(current_duration());
  print_lightgreen("Done!\n");
  return 0;
}
