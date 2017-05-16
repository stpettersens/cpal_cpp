SRC = src/cpal.cc
TARGET = cpal
TP = $(TARGET)

CXX = g++-4.9

make:
	$(CXX) -s --std=c++11 $(SRC) -o $(TP)

upx: make
	upx -9 $(TP).exe -o $(TARGET).exe
