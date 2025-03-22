# Blackjack Game

A cross-platform implementation of the classic Blackjack card game with both C++ backend and Java GUI using JNI (Java Native Interface).

## Architecture

This project employs a unique hybrid architecture:

- **Game Logic**: Implemented in C++ for optimal performance and memory management
- **User Interface**: Built with Java Swing for cross-platform compatibility and rich UI features
- **Integration**: Connected via JNI (Java Native Interface)

## Technologies Used

### Backend (C++)
- **C++14**: Core game logic implementation
- **CMake**: Build system for cross-platform compilation
- **JNI (Java Native Interface)**: Bridging C++ and Java code

### Frontend (Java)
- **Java 17**: Core language
- **Swing/AWT**: UI components and graphics rendering
- **Custom Font Handling**: Dynamic font loading for enhanced UI aesthetics

## Project Structure

```
demos/
├── Gamelogic/              # C++ Game Logic
│   ├── include/            # Header files
│   │   ├── Card.h
│   │   ├── Deck.h
│   │   ├── GameLogic.h
│   │   ├── Hand.h
│   │   ├── Player.h
│   │   └── Dealer.h
│   ├── src/                # Implementation files
│   │   ├── Card.cpp
│   │   ├── Deck.cpp
│   │   ├── GameLogic.cpp
│   │   ├── Hand.cpp
│   │   ├── Player.cpp
│   │   ├── Dealer.cpp
│   │   └── BlackjackJNI.cpp
│   └── CMakeLists.txt      # C++ build configuration
│
├── Frontend/               # Java GUI 
│   ├── src/                # Java source files
│   │   ├── Main.java       # Entry point
│   │   ├── GUI.java        # Base GUI class
│   │   ├── HomeGUI.java    # Home screen
│   │   ├── GameGUI.java    # Game screen
│   │   ├── Card.java       # Card representation in Java
│   │   └── BlackjackNative.java  # JNI bridge
│   └── resources/          # Assets
│       └── Oxygen/         # Custom fonts
│
└── README.md               # This file
```

## Features

- **Blackjack Game Logic**: Complete implementation of standard Blackjack rules
- **Betting System**: Place bets and earn/lose money
- **Card Handling**: Professional deck management, shuffling, and dealing
- **Player Decisions**: Hit, stand, and other player choices
- **Game State Management**: Track game progress, money, and results
- **Visual Card Representation**: Unicode playing card symbols
- **Responsive UI**: Adapts to different screen sizes

## Building and Running

### Prerequisites

- **Java JDK 17** or higher
- **C++ Compiler** with C++14 support
  - GCC 8+ (Linux)
  - Clang 10+ (macOS)
  - MSVC 2019+ (Windows)
- **CMake** 3.10 or higher

### Building the C++ Backend

```bash
# Navigate to the GameLogic directory
cd Gamelogic

# Create a build directory
mkdir -p build
cd build

# Configure and build
cmake ..
make

# For macOS ARM64 (Apple Silicon)
cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..
make
```

## License
This project is provided for educational purposes. Feel free to use and modify according to your needs.

## Credits
Card Unicode Symbols: Unicode Consortium
Oxygen Font: Open-source font for UI elements