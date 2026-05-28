# rPICO — Raspberry Pi Pico Experiments

A collection of bare-metal C projects for the Raspberry Pi Pico W (RP2040), exploring GPIO, I/O, sorting algorithms, flash memory management, and WiFi networking. Each project strips the Pico SDK examples down to their bare minimum to isolate one concept at a time.

---

## Project Structure

```
project/
|-> 1.morse/        # Hardcoded morse code blinker
|-> 2.io/           # Interactive ASCII-to-morse converter
|-> 3.sort/         # Quicksort on integers and byte strings in RAM
|-> 4.m2/           # Flash read/write with sorted data validation
|-> 5.wifi/         # Access point with DHCP/DNS (stripped from SDK example)
|-> CMakeLists.txt
```

---

## Assignments

### 1. Morse — Hardcoded LED Blinker

**File:** `1.morse/`

Blinks the onboard LED in morse code from a hardcoded bit array. Handles both standard GPIO LED (Pico) and the CYW43 wireless chip LED (Pico W) via compile-time conditionals.

- Encodes 3 bytes of morse data as raw binary integers
- A `1` bit → long blink (dash), a `0` bit → short blink (dot)
- Iterates bits MSB-first, loops continuously with inter-character and inter-word pauses
- Timing controlled by `LED_DELAY_MS` (default 250 ms); a dash is 3×, word gap is 7×

**Key idea:** morse timing ratios (1:3:7) encoded purely through `sleep_ms` multipliers.

---

### 2. IO — Interactive ASCII-to-Morse Converter

**File:** `2.io/`

Takes user input over serial (UART/USB) and blinks the corresponding morse code on the LED.

- Accepts a string via `scanf`, maps each character to its morse pattern
- `txt[]` — a 26-byte lookup table (a–z) where each byte encodes both the morse pattern and its length in the upper 3 bits
- `getmorse(i)` macro normalises upper/lower case to a 0–25 index
- `prnt()` extracts the length, then shifts through the bits to blink dots and dashes
- Prints `.` and `_` to serial alongside the LED output

**Key idea:** packs morse length + pattern into a single byte — upper 3 bits = symbol count, lower 5 bits = dot/dash sequence.

---

### 3. Sort — Quicksort Benchmark

**File:** `3.sort/`

Generates a large random array and sorts it in-place, repeatedly, while blinking status updates.

- Allocates a 250,000-byte array (`char num[len]`) in RAM
- Fills it with `rand() % 255` values
- Sorts using an in-place quicksort (partition-by-first-element) that works on both raw byte values (integers 0–254) and arbitrary byte sequences (e.g. ASCII strings), since comparison is byte-value based
- Blinks LED before and after each sort pass; prints sorted output over serial
- Loops indefinitely — useful as a stress/timing benchmark

**Key idea:** the sort operates on `char[]`, so it naturally handles any byte data — integers, ASCII characters, or packed structs — making it reusable beyond pure numeric sorting.

---

### 4. M2 — Flash Memory Read/Write

**File:** `4.m2/`

Writes sorted random data to Pico's flash memory page by page, then validates each write by reading back and comparing.

- Targets the upper half of flash (offset 512 KB → 2 MB), safely away from the program itself
- For each 256-byte page: generates random bytes, sorts them, writes to flash, reads back, validates
- Uses `flash_safe_execute()` to handle flash writes safely (disables XIP cache, suspends the second core if present)
- `call_flash_range_erase` and `call_flash_range_program` are passed as callbacks to `flash_safe_execute`
- Reads back via the XIP memory-mapped window (`XIP_BASE + offset`) and compares byte-for-byte
- Blinks LED on each page write; prints page number, offset, and pass/fail status over serial

**Key idea:** demonstrates the full flash erase → program → verify cycle using the Pico SDK's safe execution wrappers, with sorted data as a simple integrity check.

---

### 5. WiFi — Access Point & Station Mode

**File:** `5.wifi/access_point/`

Covers both sides of WiFi on the Pico W, each stripped to the minimum required to function.

**`ap.c` / `just_AP.c` — Access Point mode**

Turns the Pico W into a WPA2 access point with its own DHCP and DNS servers. Both files do the same thing; `just_AP.c` retains a `TCP_SERVER_T` state struct and an IPv4/IPv6 conditional macro from the SDK original, while `ap.c` removes all of that:

```
init → enable AP mode → set gateway IP + mask → start DHCP server → start DNS server → spin
```

- SSID `vish_pico`, WPA2-AES auth
- Gateway and mask set from `CYW43_DEFAULT_IP_AP_ADDRESS` / `CYW43_DEFAULT_IP_MASK`
- DHCP and DNS servers from local `dhcpserver/` and `dnsserver/` dirs (from SDK)
- `lwipopts.h` configures lwIP (from SDK, trimmed)

**`station.c` — Station mode (client)**

Connects the Pico W to an existing access point as a client — the other side of the same picture:

```
init → enable STA mode → connect with timeout → spin
```

- Calls `cyw43_arch_enable_sta_mode()` then `cyw43_wifi_connect_timeout_ms()` with a 5-second timeout
- WPA2-AES auth; no DHCP/DNS handling needed since the router provides it
- At ~10 lines it's the most minimal possible WiFi client

**Key idea:** together, `ap.c` and `station.c` show both roles a Pico W can play on a network. The SDK examples for each bury the essential calls under TCP server scaffolding, state structs, and IPv6 guards — stripped out, each role is 4–5 function calls.

---

## Building

Standard Pico SDK CMake build:

```bash
mkdir build && cd build
cmake .. -DPICO_BOARD=pico_w   # or pico for non-W
make
```

Flash the resulting `.uf2` to the board by holding BOOTSEL and copying the file to the mounted drive.

Serial output (115200 baud) is available on projects 2, 3, and 4 via USB or UART.

---

## Notes

- All projects use `pico/stdlib.h`; projects targeting Pico W additionally include `pico/cyw43_arch.h` for the wireless chip's GPIO
- The morse encoding scheme in project 2 is compact but assumes input is strictly a–z or A–Z
- The sort in project 3 and 4 is a recursive quicksort; for very large or adversarial inputs on the Pico's limited stack, iterative or hybrid approaches would be more robust
