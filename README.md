# WASD-EsoLang

An optimized, completely non-serious esoteric programming language where your source code looks exactly like a player movement log from a 2D video game (don't ask why)

Built entirely in C++17, this compiler turns raw keyboard inputs into streamlined runtime execution streams, featuring an automated **Run-Length Encoding (RLE) node compression engine** and a **2D Sparse Coordinate Map Matrix** ($std::map<Coordinate, uint8_t>$), giving you an infinite, unmanaged memory grid layout that consumes 0 bytes of RAM until data cells are declared!

---

## Token Movement Map



| Input Token | Standard Esoteric Equivalent | Infinite 2D Matrix Operation |
| :---: | :---: | :--- |
| `w` | N/A | Moves your player location cursor **UP** ($Y + 1$) |
| `s` | N/A | Moves your player location cursor **DOWN** ($Y - 1$) |
| `a` | `<` | Moves your player location cursor **LEFT** ($X - 1$) |
| `d` | `>` | Moves your player location cursor **RIGHT** ($X + 1$) |
| `click` | `+` | Increments the integer value inside the active coordinate block by 1. |
| `miss` | `-` | Decrements the integer value inside the active coordinate block by 1. |
| `yap` | `.` | Flushes and outputs the active cell value as an ASCII character. |
| `eavesdrop` | `,` | Halts execution to read a keyboard character input string stream. |
| `grind` | `[` | **Loop Start:** Conditional guard gate boundary tracking. |
| `quit` | `]` | **Loop End:** Boundary target routing terminator block. |

---

## Numbers (Direct Multipliers Support)

You don't need to type out long streams of individual characters to set data cell values or move anymore. `wasd-esolang` natively supports **integer literal multipliers**!!

Instead of writing `click` seventy-two consecutive times to initialize a cell value, the lexer dynamically parses numbers and packages them right into the instruction node:
```text
click 72 yap
```
This keeps your source files short, elegant, and incredibly easy to maintain compared to standard uncompressed esoteric layouts...

---

## The Compiler Optimization Engine (RLE)

Unlike standard uncompressed interpreters that process single instructions line-by-line in a loop bottleneck, `wasd-lang` uses a customized lexical analysis pass to automatically condense repetitive inputs before they hit execution.

For example, writing `d` four times to move right doesn't cycle through your CPU $4$ times. The lexer dynamically collapses the stream down into a single optimized abstract node block:

```text
[DEBUG] Token Stream Detail:
  Type: 0 (MOVE_RIGHT) | Count: 4 | Line: 1
```

---

## Project Configurations (`config.json`)

You can control active background telemetry outputs directly inside the root file configuration parameters without altering any critical files:

```json
{
  "enableFileDebug": false,
  "enableTokenDebug": false,
  "enableExecutionDebug": true
}
```

---

## Scripting examples! (pls don't compare to brainf)

### Printing "hi"
```text
// Set cell (0,0) to 10 as our loop multiplier
click 10
grind
    d click 10      // Move Right to (1,0), add 10
    a miss          // Move Left back to (0,0), subtract 1
quit

d click 4 yap       // Go to (1,0) -> 100 + 4 = 104 ('h') -> YAP!
w click 105 yap     // Move UP to Cell (1,1) -> 105 ('i') -> YAP!
```

### Printing "Hello World!"
```text
// Perfect 2D Isolated Hello World - 100% Freeze-Proof
click 72 yap        // Cell (0,0) = 72 ('H') -> YAP!
d click 101 yap     // Move Right to (1,0) = 101 ('e') -> YAP!
d click 108 yap     // Move Right to (2,0) = 108 ('l') -> YAP!
yap                 // Print 'l' again
click 3 yap         // 108 + 3 = 111 ('o') -> YAP!
d click 32 yap      // Move Right to (3,0) = 32 (Space) -> YAP!
d click 87 yap      // Move Right to (4,0) = 87 ('W') -> YAP!
d click 111 yap     // Move Right to (5,0) = 111 ('o') -> YAP!
d click 114 yap     // Move Right to (6,0) = 114 ('r') -> YAP!
d click 108 yap     // Move Right to (7,0) = 108 ('l') -> YAP!
d click 100 yap     // Move Right to (8,0) = 100 ('d') -> YAP!
d click 33 yap      // Move Right to (9,0) = 33 ('!') -> YAP!
```

---

## Building and Execution

Compile the source architecture dynamically through your terminal using CMake:

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Execute a target script by passing its folder variable path:
```powershell
.\build\wasd.exe .\examples\hello_world.wasd
```
