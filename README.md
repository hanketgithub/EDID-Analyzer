# EDID-Analyzer

## Build Instructions

To compile the project:

```bash
make
```

This will build the executable `edid_analyzer`.

---

## Usage

Run the tool with:

```bash
./edid_analyzer [input_file]
```

- `[input_file]` should be a binary EDID file.

If no input file is provided, the tool will print a usage message and exit.

### Example

```bash
./edid_analyzer EDID_Data.bin
```

---

## Sample Console Output

```plaintext
===== EDID-Analyzer Started =====
Manufacturer: ACL
Product Code: 0x6301
Serial Number: 305419891
Manufacture Date: Week 2, Year 2025
EDID Version: 1.3
Extension Block Count: 1
CTA Revision: 3
CTA DTD Offset: 70
CTA Native DTD Count: 1

```

---

## Basic
| Name                  | Offset    | Size(bytes) | Description                                     |
| --------------------- | --------- | ----------- | -------------------------------------------- |
| Header                | 0x00      | 8           | Fixed 0x00 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF 0x00   |
| Manufacturer ID       | 0x08      | 2           | Vendor Code encoded as 5-bit ASCII             |
| Product Code          | 0x0A      | 2           | Display product identifier                     |
| Serial Number         | 0x0C      | 4           | Unique serial number for the device            |
| Week of Manufacture   | 0x10      | 1           | Manufacturing week                             |
| Year of Manufacture   | 0x11      | 1           | Year offset from 1990                          |
| EDID Version          | 0x12      | 1           | Major version                                  |
| EDID Rev              | 0x13      | 1           | Minor revision                                 |
| Extension Block Count | 0x7E      | 1           | Number of 128-byte extension blocks            |

---

## Notes
- CTA-861 extension is identified at offset 128 with tag 0x02.
- DTD Offset and Native DTD count are parsed from extension block (offsets 130, 131).
- Only the first extension block is parsed in this version.

---

## License
MIT