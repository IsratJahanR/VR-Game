# Stephen's Top Down Game

A simple top-down RPG-style game demo made using [raylib](https://www.raylib.com/) in C++. Control a knight character, explore a large map, and interact with props and enemies in a 2D world.

![Game Screenshot](nature_tileset/OpenWorldMap24X24.png) <!-- Replace with actual screenshot if available -->

---

## 🎮 Gameplay Overview

- Move your knight character across a top-down map.
- Encounter animated enemies like goblins.
- Interact and collide with props (e.g. rocks and logs).
- Explore freely while staying within map bounds.

---

## 📂 Project Structure

```
top-down-section/
├── .vscode/                      # VSCode settings
├── characters/                   # Character & enemy sprite sheets
│   ├── goblin_idle_spritesheet.png
│   └── goblin_run_spritesheet.png
├── nature_tileset/              # Map and prop textures
│   ├── OpenWorldMap24X24.png
│   ├── Rock.png
│   └── Log.png
├── .gitignore                   # Git ignored files
├── BaseCharacter.cpp/h         # Base class for characters
├── Character.cpp/h             # Knight class
├── Enemy.cpp/h                 # Goblin class
├── Prop.cpp/h                  # Interactable props
├── main.cpp                    # Main game loop
├── Makefile                    # For Linux builds
├── libgcc_s_dw2-1.dll          # Windows dependency
├── libstdc++-6.dll             # Windows dependency
└── main.code-workspace         # VSCode workspace
```

---

## 🛠️ Build & Run

### 🖥️ Windows

Make sure you have:
- A C++ compiler (like MinGW)
- raylib installed and linked properly
- `.dll` files present in the folder

Build & run using:

```bash
g++ main.cpp Character.cpp Prop.cpp Enemy.cpp BaseCharacter.cpp -o TopDownGame -lraylib -lopengl32 -lgdi32 -lwinmm
./TopDownGame.exe
```

> Adjust paths if raylib is installed elsewhere.

### 🐧 Linux

```bash
make
./TopDownGame
```

> Make sure raylib is installed (e.g., via apt or manually).

---

## ⌨️ Controls

| Key     | Action       |
|---------|--------------|
| `WASD`  | Move Knight  |
| `ESC`   | Exit Game    |

---

## 🧠 Features

- Character movement with map scrolling
- World space and screen space separation
- Prop collision detection
- Enemy character with tracking behavior
- Scaled tile-based map

---

## 📌 Notes

- You can expand the game with:
  - More enemies or attack behavior
  - NPC interactions
  - Health or damage system
  - Mini-map or HUD UI

---

## 📜 License

Open-source for educational use. Feel free to fork and build on top of this game.

---

### 🛡️ Made with C++, raylib, and passion.
