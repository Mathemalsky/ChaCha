#include <iostream>

#include "chacha.hpp"
#include "colors.hpp"
#include "encrypt.hpp"
#include "error.hpp"
#include "measurement.hpp"

int main(int argc, char* argv[]) {
  start_time();
  // TRY/CATCH very preliminary
  try {
    if (argc == 3) {
      // pass name of content file and keyfile
      cryptHandler(argv[1], nameEdit(argv[1]), argv[2]);
    }
    if (argc == 4) {
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
