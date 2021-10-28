#include "disk_format_factory.hpp"

#include "orbis_format.hpp"
#include "cell_phat_format.hpp"
#include "cell_slim_format.hpp"
#include "cell_decrypted_format.hpp"

namespace formats {

DiskFormatFactory::DiskFormatFactory()
{
  registerFormat(new OrbisDiskFormat());
  registerFormat(new CellPhatDiskFormat());
  registerFormat(new CellSlimDiskFormat());
  registerFormat(new CellDecryptedDiskFormat());
}

DiskFormatFactory* DiskFormatFactory::getInstance()
{
  static DiskFormatFactory g_diskDecryptFactory;
  return &g_diskDecryptFactory;
}

disk::Disk* DiskFormatFactory::detectFormat(disk::DiskConfig* config)
{
  // Eventually we will return a vector if multiple disk format are detected.
  for (const auto format : this->formats) {
    // TODO: Sector size should be detected by some disk 
    // geometry detection service
    // For now we default to a sector size of 0x200
    disk::Disk* disk = new disk::Disk(config->getStream(), 0x200);
    if (format->match(disk, config)) {
      format->build(disk, config);
      return disk;
    } else {
      delete disk;
    }
  }

  return nullptr;
}

void DiskFormatFactory::registerFormat(IDiskFormat* format)
{
  this->formats.push_back(format);
}

} /* namespace formats */
