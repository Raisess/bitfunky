#! /usr/bin/python3
# E.g.: ./magnet_database_insert_json.py /path/file.json /path/magnet_database.db

import json
import sys
from common.magnet_database import MagnetDatabase

if __name__ == "__main__":
  f = open(sys.argv[1], "r")
  data = json.load(f)
  f.close()

  magnet_database = MagnetDatabase(sys.argv[2])
  magnet_database.add(data)
  magnet_database.close()
