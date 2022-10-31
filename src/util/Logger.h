#pragma once

#include "../core/TorrentDownload.h"

namespace BF {

class Logger {
public:
  static void PrintTorrentState(const BF::TorrentDownloadState&);
};

}
