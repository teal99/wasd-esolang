# WASD-EsoLang

An optimized, completely non-serious esoteric programming language where your source code looks exactly like a player movement log from a 2D video game (don't ask why)

Built entirely in C++17, this compiler turns raw keyboard inputs into streamlined runtime execution streams, featuring an automated **Run-Length Encoding (RLE) node compression engine** and a **2D Sparse Coordinate Map Matrix** ($std::map<Coordinate, uint8_t>$) giving you an infinite, unmanaged memory grid layout that consumes 0 bytes of RAM until data cells are declared.

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

## Number Reading (Direct Multipliers Support)

You don't need to type out long streams of individual characters to set data cell values or move anymore. `wasd-esolang` natively supports **integer literal multipliers**!!

Instead of writing `click` seventy-two consecutive times to initialize a cell value, the lexer dynamically parses numbers and packages them right into the instruction node:
```text
click 72 yap
```
This keeps your source files short, elegant, and incredibly easy to maintain compared to standard uncompressed esoteric layouts!!!

---

## High-Level Assembly Shortcuts (v3.0 Additions)

### Character Literals Support
Ditch the manual ASCII table tracking lookup loops entirely because I hate it. If the compiler sees a character wrapped in single quotes, it auto-resolves it on its own during tokenization:
```text
click 'H' yap # Automatically resolves to 72 and flashes to screen
```

### Named Symbolic Constants
Assign meaningful human text aliases to raw global formatting configurations or loop counters:
```text
set space 32
set jumpby10 10
d click space # Moves Right, adds 32 dynamically
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

### Printing "Hello World!" (`examples/hello_world.wasd`)
```text
// Define easy labels for formatting offsets
set space 32
set jumpby10 10

// Write directly using characters without checking ASCII tables
click 'H' yap
d click 'e' yap
d click 'l' yap
yap
click 3 yap             // Adds 3 to land on 'o'
d click ' ' yap         
d click 'W' yap
d click 'o' yap
d click 'r' yap
d click 'l' yap
d click 'd' yap
d click '!' yap
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
