#include "chacha.hpp"
#include "encrypt.hpp"

int main(int argc, char* argv[]) {
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
  } catch (...) {
    exit(-1);
  }
  return 0;
}
