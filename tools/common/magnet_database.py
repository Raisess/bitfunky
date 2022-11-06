import sqlite3

class MagnetDatabase:
  def __init__(self, database_path: str):
    self.db = sqlite3.connect(database_path)

  def close(self) -> None:
    self.db.close()

  def add(self, items: list[dict[str, str]]) -> None:
    try:
      for item in items:
        self.db.execute(
          "INSERT INTO magnets(alias, magnet_uri) VALUES(?, ?)",
          [item["alias"], item["magnet_uri"]]
        )

      self.db.commit()
    except:
      self.db.rollback()
