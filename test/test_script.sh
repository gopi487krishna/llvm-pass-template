# Generate build directory for storing artifacts
mkdir build

# Generate IR
clang  -S -emit-llvm -fno-discard-value-names   -flegacy-pass-manager -Xclang -load -Xclang $PWD/../build/pass/libStandardPass.so test_program.c -o "$PWD/build/test_program.ll"
clang  -fno-discard-value-names   -flegacy-pass-manager -Xclang -load -Xclang $PWD/../build/pass/libStandardPass.so test_program.c -o "$PWD/build/test_program"
                                                                                                                   