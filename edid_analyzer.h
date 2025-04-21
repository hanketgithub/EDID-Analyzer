


typedef struct {
  uint8_t header[8];
  char manufacturer[4];   // e.g. "ACL"
  uint16_t product_code;  // e.g. 0x6301
  uint32_t serial_number;
  uint8_t week;
  uint8_t year;
  uint8_t version;
  uint8_t revision;
  uint8_t extension_block_count;
  uint8_t cta_revision;
  uint8_t dtd_offset;
  uint8_t native_dtd_count;
} EDID_T;

bool parse_edid(const uint8_t *buf, EDID_T &edid);
