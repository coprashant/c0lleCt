# c0lleCt

`c0lleCt` is a simple SFML-based game where players control a basket to catch falling eggs. The game features increasing difficulty levels, sound effects, and a restart/exit option when the game is over.

## Features

- **Gameplay**: Move the basket left and right to catch falling eggs.
- **Difficulty**: The game speed increases as you score more points.
- **Sound**: Includes background music and sound effects for catching and missing eggs.
- **Game Over Screen**: Displays when the game ends with options to restart or exit.

## Requirements

- **SFML**: The game is built using the Simple and Fast Multimedia Library (SFML). You need to have SFML installed on your system.
- **C++ Compiler**: A compatible C++ compiler (e.g., MinGW, GCC, Clang).


## Built With

- C++

### Installation

1. Clone the repo

```sh
git clone https://github.com/coprashant/c0lleCt.git

```

2.Install SFML

Windows: Follow the SFML installation guide for MinGW.
macOS: Use Homebrew: brew install sfml
Linux: Use your package manager, e.g., sudo apt-get install libsfml-dev

3.Configure the Project

Ensure that SFML is correctly installed and its paths are properly configured in your CMakeLists.txt

4. Build the Project

```sh
mkdir build
cd build
cmake ..
make

```
5.Run the Game

```sh
./egg-catcher
```

## Contributing

1.Fork the Repository

Click the "Fork" button at the top right of this repository page on GitHub.

2.Create a New Branch

```sh
git checkout -b <branch_name>
```
3.Make Your Changes

Edit, add, or remove files as needed.

4.Commit Your Changes

```sh
git commit -m 'Describe your changes'
```

5.Push to Your Fork

```sh
git push origin <branch_name>
```
6.Open a Pull Request

Go to the original repository on GitHub and open a pull request from your branch.
