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

  printf("\n===== EDID Summary =====\n");
  printf("%-25s : %s\n",  "Manufacturer", info.manufacturer);
  printf("%-25s : 0x%04X\n", "Product Code", info.product_code);
  printf("%-25s : 0x%08X\n", "Serial Number", info.serial_number);
  printf("%-25s : Week %02d, Year %d\n", "Manufacture Date", info.week, info.year);
  printf("%-25s : %d.%d\n", "EDID Version", info.version, info.revision);
  printf("%-25s : %d\n", "Extension Block Count", info.extension_block_count);

  bool has_cta_extension = (buffer[128] == 0x02);
  if (has_cta_extension) {
    printf("%-25s : %d\n", "CTA Revision", info.cta_revision);
    printf("%-25s : %d\n", "CTA DTD Offset", info.dtd_offset);
    printf("%-25s : %d\n", "CTA Native DTD Count", info.native_dtd_count);
  }
  else {
    printf("%-25s : %s\n", "CTA Extension", "Not Present");
  }

  printf("===== EDID-Analyzer Finished =====\n");

  return 0;
}