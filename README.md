# ChaCha

This project implements the ChaCha algorithm from Daniel J. Bernstein.
A software part to use it directly as symmetric encryption sceme is also included.

## Literature
- Bernstein, Daniel J. "ChaCha, a variant of Salsa20." Workshop record of SASC. Vol. 8. No. 1. 2008.
- Bernstein, Daniel J. "The Salsa20 family of stream ciphers." New stream cipher designs. Springer, Berlin, Heidelberg, 2008. 84-97.

## Usage
The following description is for Linux. In case of using windows the initial `./` needs to be omitted. In both cases `chacha` needs to be replaced by the name of the executable you are using.
### Generating a key
`./chacha -k <dst>`
Here, `<dst>` denotes the filename (and path) where the key should be written to.
### Decrypt/ Encrypt
`./chacha <src> <dst> <key>`
Here `<src>` is the file to be decrypted/ encrypted, `<dst>` is the file to write the output to and `<key>` is the key used during decryption/ encryption.