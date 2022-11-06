CXX=clang++ -std=c++14
EXTERNAL_LIB_LINK=/usr/local/lib/libtorrent-rasterbar.so.2.0.8 \
									/usr/lib/libsqlite3.so.0.8.6

SRC_DIR=./src
LIB_SRC=$(SRC_DIR)/core/Torrent.cpp \
				$(SRC_DIR)/core/TorrentSession.cpp \
				$(SRC_DIR)/core/MagnetDatabase.cpp \
				$(SRC_DIR)/database/SqLite.cpp \
				$(SRC_DIR)/util/File.cpp \
				$(SRC_DIR)/util/Util.cpp

OUT_DIR=./build
LIB_OUT=$(OUT_DIR)/bitfunky.so

build:
	mkdir -p $(OUT_DIR)
	$(CXX) -fPIC -shared $(EXTERNAL_LIB_LINK) $(LIB_SRC) -o $(LIB_OUT)

build-test:
	$(CXX) $(LIB_OUT) $(SRC_DIR)/test.cpp -o $(OUT_DIR)/test.o

install:
	sudo mkdir -p /usr/local/include/bitfunky/core
	sudo mkdir -p /usr/local/include/bitfunky/database
	sudo mkdir -p /usr/local/include/bitfunky/util
	sudo cp -r ./src/core/*.h /usr/local/include/bitfunky/core
	sudo cp -r ./src/database/*.h /usr/local/include/bitfunky/database
	sudo cp -r ./src/util/*.h /usr/local/include/bitfunky/util
	sudo cp $(LIB_OUT) /usr/local/lib

clean:
	rm -rf $(OUT_DIR)

auto:
	make clean
	make build
	make install
	make -C ./cli clean
	make -C ./cli build
	make -C ./cli install
