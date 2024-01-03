#!/bin/bash

APP_NAME="OP_v3"
INSTALL_DIR="$HOME/VU/Rokas-Sabaitis"
DESKTOP_DIR="$HOME/Desktop"

echo "Creating installation directory..."
mkdir -p "$INSTALL_DIR"
chown -R $USER "$INSTALL_DIR"  # Change ownership to the current user

if cp -r "../$APP_NAME" "$INSTALL_DIR/"; then
    echo "Copying $APP_NAME to $INSTALL_DIR..."

    # Create a desktop shortcut
    ln -s "$INSTALL_DIR/$APP_NAME/cmake-build-release/OP" "$DESKTOP_DIR/$APP_NAME"
    echo "Desktop shortcut created."
else
    echo "Error: Failed to copy $APP_NAME to $INSTALL_DIR."
    exit 1  # Exit with an error code
fi