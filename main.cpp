#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <iostream>

#include "edid_analyzer.h"

using namespace std;

int main(int argc, const char *argv[]) {
  cout << "===== EDID-Analyzer Started =====" << endl;

  if (argc < 2) {
    cerr << "[ERROR] Usage: " << argv[0] << " [input_file]" << endl;
    return EXIT_FAILURE;
  }

  int ifd = open(argv[1], O_RDONLY);
  if (ifd < 0)
  {
    cerr << "[ERROR] Failed to open file: " << strerror(errno) << endl;
    return EXIT_FAILURE;
  }

  uint8_t buffer[256] = {0};
  read(ifd, buffer, sizeof(buffer));
  close(ifd);

  EDID_T info;

  parse_edid(buffer, info);

  printf("Manufacturer: %s\n", info.manufacturer);
  printf("Product Code: 0x%04X\n", info.product_code);
  printf("Serial Number: %08d\n", info.serial_number);
  printf("Manufacture Date: Week %d, Year %d\n", info.week, info.year + 1990);
  printf("EDID Version: %d.%d\n", info.version, info.revision);
  printf("Extension Block Count: %d\n", info.extension_block_count);
  printf("CTA Revision: %d\n", info.cta_revision);
  printf("CTA DTD Offset: %d\n", info.dtd_offset);
  printf("CTA Native DTD Count: %d\n", info.native_dtd_count);

  return 0;
}