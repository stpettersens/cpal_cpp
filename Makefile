SRC = src/cpal.cc
TARGET = cpal
TP = $(TARGET)

make:
	g++ -s --std=c++11 $(SRC) -o $(TP)

upx : make
	upx -9 $(TP).exe -o $(TARGET).exe
