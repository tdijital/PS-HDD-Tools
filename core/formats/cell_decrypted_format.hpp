#ifndef CELL_DECRYPTED_FORMAT_HPP
#define CELL_DECRYPTED_FORMAT_HPP

#include "cell_format.hpp"

namespace formats {
  
/**
 * @brief Detects and loads a decrypted PS3 disk format.
 */
class CellDecryptedDiskFormat  : public CellDiskFormat
{
public:
  CellDecryptedDiskFormat() {}

  bool match(disk::Disk* disk, disk::DiskConfig* config) override;
  void build(disk::Disk* disk, disk::DiskConfig* config) override;

private:
  bool checkDiskLabel(io::data::DataProvider* dataProvider);
};

} /* namespace formats */

#endif /* CELL_DECRYPTED_FORMAT_HPP */
