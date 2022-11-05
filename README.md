# BitFunky

A small BitTorrent client API and CLI.

## Dependencies

- [libtorrent](http://www.libtorrent.org/index.html)
- [sqlite3](https://www.sqlite.org/index.html)

## Building and Installing

After installed dependencies, build the lib running this command on your terminal:

```shell
make
```

To install:

```shell
make install
```

- Installed shared object path: `/usr/local/lib/bitfunky.so`.

## Official Clients

### CLI

A simple cli written in C++, using [cli-creator](https://github.com/Raisess/cli-creator).
You can check how to install and use the cli here: [./cli/README.md](./cli/README.md).

### GUI

- TODO

## Features

- Download torrents from `.torrent` files and `magnet` links;
- TODO: Upload torrens;
- Magnet database, manage locally stored magnet links to create downloads.
