TARGET = target/cpal
SRC = src/cpal.cc

make:
  g++ -s --std=c++11 $(SRC) -o $(TARGET)
 
