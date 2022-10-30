CXX=clang++ -std=c++14
EXTERNAL_LIB_LINK=/usr/local/lib/libtorrent-rasterbar.so.2.0.8

SRC_DIR=./src
LIB_SRC=$(SRC_DIR)/core/TorrentDownload.cpp \
				$(SRC_DIR)/core/TorrentSession.cpp

OUT_DIR=./build
LIB_OUT=$(OUT_DIR)/bitfunky.so

build:
	mkdir -p $(OUT_DIR)
	$(CXX) -fPIC -shared $(EXTERNAL_LIB_LINK) $(LIB_SRC) -o $(LIB_OUT)

build-test:
	$(CXX) $(LIB_OUT) $(SRC_DIR)/test.cpp -o $(OUT_DIR)/test.o

install:
	sudo mkdir -p /usr/local/include/bitfunky/core
	sudo mkdir -p /usr/local/include/bitfunky/util
	sudo cp -r ./src/core/*.h /usr/local/include/bitfunky/core
	sudo cp -r ./src/util/*.h /usr/local/include/bitfunky/util
	sudo cp $(LIB_OUT) /usr/local/lib

clean:
	rm -rf $(OUT_DIR)
