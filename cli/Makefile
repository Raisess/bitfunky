CXX=clang++ -std=c++14
NAME=bitfunky

SRC_DIR=./src
SRC=$(SRC_DIR)/main.cpp

OUT_DIR=./build
OUT=$(OUT_DIR)/$(NAME).o

LIB_PATH=/usr/local/lib/cli-creator/cli-creator.so \
				 /usr/local/lib/bitfunky.so
BIN_PATH=/usr/local/bin
BIN=$(BIN_PATH)/$(NAME)

build:
	mkdir -p $(OUT_DIR)
	$(CXX) $(LIB_PATH) $(SRC) -o $(OUT)

install:
	sudo cp $(OUT) $(BIN)

uninstall:
	sudo rm -rf $(BIN)

clean:
	rm -rf $(OUT_DIR)
