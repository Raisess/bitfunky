CXX=clang++ -std=c++14
EXTERNAL_LIB_LINK=

SRC_DIR=./src
LIB_SRC=$(SRC_DIR)/Session.cpp \
				$(SRC_DIR)/Torrent.cpp
SRC=$(SRC_DIR)/main.cpp

OUT_DIR=./build
LIB_OUT=$(OUT_DIR)/azogo.so
OUT=$(OUT_DIR)/main.o

build:
	make build-lib
	$(CXX) $(EXTERNAL_LIB_LINK) $(LIB_OUT) $(SRC) -o $(OUT)

build-lib:
	mkdir -p $(OUT_DIR)
	$(CXX) -fPIC -shared $(LIB_SRC) -o $(LIB_OUT)

run:
	$(OUT)

clean:
	rm -rf $(OUT_DIR)
