#!/bin/bash

INSTALL_DIR="$HOME/.config/.cppc"
ZSHRC="$HOME/.zshrc"
LINE="export PATH=\"\$PATH:$INSTALL_DIR\""

echo "Creating install directory: $INSTALL_DIR"
mkdir -p "$INSTALL_DIR"

echo "Adding io_23.h to $INSTALL_DIR"
cp io_23.h "$INSTALL_DIR"

if ! grep -Fxq "$LINE" "$ZSHRC"; then
  echo "$LINE" >> "$ZSHRC"
  echo "Added $INSTALL_DIR to PATH in $ZSHRC"
  echo "Restart terminal or run: source ~/.zshrc"
else
  echo "$INSTALL_DIR already exists in PATH"
fi

echo "Installation Complete!"
