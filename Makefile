CXX=g++

SRC_DIR=./src
SRC=$(SRC_DIR)/main.cpp

OUT_DIR=./build
OUT=$(OUT_DIR)/out.o

build:
	mkdir -p $(OUT_DIR)
	$(CXX) $(SRC) -o $(OUT)

run:
	$(OUT)

clean:
	rm -rf $(OUT_DIR)
