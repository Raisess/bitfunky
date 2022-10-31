#pragma once

#include "../core/TorrentDownload.h"

namespace BF {
namespace Util {

class Logger {
public:
  static void PrintTorrentState(const BF::TorrentDownloadState&);
};

}
}
