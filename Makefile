CXX=clang++ -std=c++14
EXTERNAL_LIB_LINK=/usr/local/lib/libtorrent-rasterbar.so.2.0.8

SRC_DIR=./src
LIB_SRC=$(SRC_DIR)/Download/BitTorrentDownload.cpp \
				$(SRC_DIR)/Session/BitTorrentSession.cpp
SRC=$(SRC_DIR)/main.cpp

OUT_DIR=./build
LIB_OUT=$(OUT_DIR)/bitfunky.so
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
