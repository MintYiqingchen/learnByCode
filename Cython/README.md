# How to Use Cython in python
## Compile
compile .c file into static library file
```
gcc -c sample.c
ar r libsample.a sample.o
```

or dynamic library file
```
gcc -c -fPIC sample.c
gcc -shared -o libsample.so sample.o
# or
gcc -fPIC -shared -o libsample.so sample.c
```

other useful compile switches
```
gcc -o dynamicApp -lsample -L.
ld dynamicApp
```
