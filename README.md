# WASD-EsoLang

An optimized, completely non-serious esoteric programming language where your source code looks exactly like a player movement log from a video game (don't ask why)

Built entirely in C++, this compiler turns raw keyboard inputs into streamlined runtime execution streams, featuring an automated **Run-Length Encoding (RLE) node compression engine** and dynamic pre-computed loop map pipelines ($O(1)$ jump offsets)

---

## Token Movement Map


| Input Token | Standard Esoteric Equivalent | System Operation |
| :---: | :---: | :--- |
| `d` | `>` | Shifts the data pointer forward to the next memory cell. |
| `a` | `<` | Shifts the data pointer backward to the previous memory cell. |
| `w` | `+` | Increments the integer value inside the active memory cell by 1. |
| `s` | `-` | Decrements the integer value inside the active memory cell by 1. |
| `yap` | `.` | Flushes and outputs the active cell value as an ASCII character. |
| `eavesdrop` | `,` | Halts execution to read a keyboard character input string stream. |
| `grind` | `[` | **Loop Start:** Conditional guard gate boundary tracking. |
| `quit` | `]` | **Loop End:** Boundary target routing terminator block. |

---

## The Compiler Optimization Engine (RLE)

Unlike standard uncompressed interpreters that process single instructions line-by-line in a loop bottleneck, `wasd-lang` uses a customized lexical analysis pass to automatically condense repetitive inputs before they hit execution.

For example, writing `w` seventy-two consecutive times to initialize a cell value doesn't cycle through your CPU $72$ times. The lexer dynamically collapses the stream down into a single optimized abstract node block:

```text
[DEBUG] Token Stream Detail:
  Type: 2 (INCREMENT) | Count: 72 | Line: 1
  Type: 4 (OUTPUT)    | Count: 1  | Line: 1
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
// Set cell 0 to 10 as our loop multiplier
wwwwwwwwww
grind
    dwwwwwwwwww
    as
quit

dwwww yap // Cell 1 is 100 + 4 = 104 ('h')
w yap     // Cell 1 is 104 + 1 = 105 ('i')
```

### Printing "Hello World!"
```text
wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
wwwwwww yap
yap
www yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww yap
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
