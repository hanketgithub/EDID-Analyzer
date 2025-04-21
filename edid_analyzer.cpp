#include <cstdint>

#include "edid_analyzer.h"

bool parse_edid(const uint8_t *buf, EDID_T &edid) {
  // chk header
  if (buf[0] != 0x00 || buf[7] != 0x00 || buf[1] != 0xFF || buf[2] != 0xFF || buf[3] != 0xFF || buf[4] != 0xFF || buf[5] != 0xFF) {
    return false;
  }

  // Manufacturer ID: 2 bytes → decode to 3 ASCII chars
  uint16_t mfg = (buf[8] << 8) | buf[9];
  edid.manufacturer[0] = ((mfg >> 10) & 0x1F) + 'A' - 1;
  edid.manufacturer[1] = ((mfg >> 5) & 0x1F) + 'A' - 1;
  edid.manufacturer[2] = (mfg & 0x1F) + 'A' - 1;
  edid.manufacturer[3] = '\0';

  edid.product_code = buf[10] | (buf[11] << 8);
  edid.serial_number = buf[12] | (buf[13] << 8) | (buf[14] << 16) | (buf[15] << 24);
  edid.week = buf[16];
  edid.year = buf[17];
  edid.version = buf[18];
  edid.revision = buf[19];
  edid.extension_block_count = buf[126];

  if (buf[128] == 0x02) { // CTA-861 extension tag
    edid.cta_revision = buf[129];
    edid.dtd_offset = buf[130];
    edid.native_dtd_count = buf[131] & 0x0F;
  }
  else {
    edid.cta_revision = 0;
    edid.dtd_offset = 0;
    edid.native_dtd_count = 0;
  }

  return true;
}
