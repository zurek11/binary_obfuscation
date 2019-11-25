cmake_minimum_required(VERSION 3.15)
project(Projekt C)

set(CMAKE_C_COMPILER gcc)

set(
        MethodAFiles
        binary_obfuscation/pe.c
        binary_obfuscation/mem.c
        binary_obfuscation/cypher.c
        method_A/method_A.c
)
set(
        MethodBFiles
        binary_obfuscation/pe.c
        binary_obfuscation/mem.c
        binary_obfuscation/cypher.c
        method_B/method_B.c
)
set(
        MethodCFiles
        binary_obfuscation/pe.c
        binary_obfuscation/mem.c
        binary_obfuscation/cypher.c
        method_C/method_C.c
)
set(
        MethodDFiles
        binary_obfuscation/pe.c
        binary_obfuscation/mem.c
        binary_obfuscation/cypher.c
        method_C/method_C.c
)
set(
        BinaryObfuscationFiles
        binary_obfuscation/pe.c
        binary_obfuscation/cypher.c
        binary_obfuscation/binary_obfuscation.c
)
add_library(
        Projekt
        binary_obfuscation/binary_obfuscation.c
        binary_obfuscation/cypher.c
        binary_obfuscation/cypher.h
        binary_obfuscation/err.h
        binary_obfuscation/pe.c
        binary_obfuscation/pe.h
        binary_obfuscation/mem.c
        binary_obfuscation/mem.h
        method_A/method_A.c
        method_B/method_B.c
        method_C/method_C.c
        method_D/method_D.c
)

ADD_EXECUTABLE(MakeMethodA ${MethodAFiles})
ADD_EXECUTABLE(MakeMethodB ${MethodBFiles})
ADD_EXECUTABLE(MakeMethodC ${MethodCFiles})
ADD_EXECUTABLE(MakeMethodD ${MethodDFiles})
ADD_EXECUTABLE(RunBinaryObfuscation ${BinaryObfuscationFiles})
