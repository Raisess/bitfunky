# BitFunky CLI

A simple cli written in C++.

## Dependencies

- [bitfunky](https://github.com/Raisess/bitfunky)
- [cli-creator](https://github.com/Raisess/cli-creator)

## Building and Installing:

```shell
make
make install
```

Only inside the cli folder root!

## How to use:

```shell
bitfunky torrent ./path/file.torrent
bitfunky torrent ./path/file1.torrent ./path/file2.torrent
```

## Uninstalling:

```shell
make uninstall
```

Only inside the cli folder root!

## Commands

#### `torrent / -t`:

- Download torrent from a `.torrent` file:

```shell
bitfunky torrent ./path/file.torrent ./path/file.torrent
```

#### `magnet / -m`:

- Download torrent from a `magnet-uri` at your magnet database:

```shell
bitfunky magnet some-alias
```

#### `init-magnet / -im`:

- Init a magnet database at `$HOME/.magnet_database.db`:

```shell
bitfunky init-magnet
```

#### `search-magnet / -sm`:

- Search for matchs into magnet database:

```shell
bitfunky search-magnet some-alias
```

#### `merge-magnet / -mm`:

- Merge another magnet database into you current magnet database:

```shell
bitfunky merge-magnet ./path/another_magnet_database.db
```

That is all.
