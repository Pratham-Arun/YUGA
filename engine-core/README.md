# 🎮 YUGA Engine Core - C++ Implementation

AI-Powered Game Engine built with modern C++20.

## 🚀 Quick Start

### Prerequisites
- CMake 3.20+
- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)
- OpenGL 4.6+

### Build Instructions

#### Windows (Visual Studio)
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

### Run
```bash
./bin/YUGAEngine
```

## 📁 Project Structure

```
engine-core/
├── CMakeLists.txt
├── include/
│   ├── Core/
│   │   ├── Core.h
│   │   ├── Log.h
│   │   └── Engine.h
│   └── Math/
│       └── Vector3.h
├── src/
│   ├── Core/
│   │   └── Engine.cpp
│   └── main.cpp
└── README.md
```

## ✅ Implemented Features

### Phase 1: Foundation (Current)
- ✅ Core engine class
- ✅ Logging system
- ✅ Math library (Vector3)
- ✅ Smart pointers
- ✅ Platform detection
- ✅ Main game loop
- ✅ Delta time calculation
- ✅ FPS counter

### Coming Soon
- 🔄 Window system (GLFW)
- 🔄 Rendering system (OpenGL/Vulkan)
- 🔄 Physics system (Bullet3)
- 🔄 Audio system (OpenAL)
- 🔄 Input system
- 🔄 ECS (EnTT)
- 🔄 Scene management
- 🔄 Asset loading

## 🎯 Current Status

**Version**: 1.0.0-alpha
**Phase**: Foundation
**Build Status**: ✅ Compiling
**Tests**: ⏳ Pending

## 📊 Performance

- Target FPS: 60
- Memory: <100MB (foundation only)
- Startup: <1 second

## 🤝 Integration with YUGA AI

This C++ core will integrate with the YUGA AI backend for:
- AI-powered code generation
- Asset generation
- Auto-debugging
- Smart suggestions

## 📚 Documentation

See [ENGINE_CORE_DESIGN.md](../ENGINE_CORE_DESIGN.md) for complete design.

---

**Status**: 🟢 Active Development
**Next**: Window & Rendering System
