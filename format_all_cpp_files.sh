#!/bin/bash

# Directory to search for C++ files
PROJECT_DIR="."

# Clang format style (you can use "file" if you have a .clang-format file)
STYLE="file"

# Exclude the "build" folder and find C++ source and header files
find "$PROJECT_DIR" -path "$PROJECT_DIR/build" -prune -o \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' -o -name '*.c' \) -print | while read -r file; do
    echo "Formatting $file"
    clang-format -i -style="$STYLE" "$file"
done

echo "All files formatted!"

