#!/usr/bin/env bash
set -euo pipefail

KEYMAP="${1:-$(whoami)}"
QMK_DIR="/c/Users/$(whoami)/qmk_firmware"
TARGET="${QMK_DIR}/keyboards/crkbd/keymaps/${KEYMAP}"

echo "Keymap: ${KEYMAP}"

if [ ! -d "${QMK_DIR}" ]; then
  echo "Error: qmk_firmware not found at ${QMK_DIR}"
  exit 1
fi

if [ -d "${TARGET}" ]; then
  echo "Directory exists: ${TARGET}"
else
  echo "Creating: ${TARGET}"
  mkdir -p "${TARGET}"
fi

find . -maxdepth 1 \( -name "*.c" -o -name "*.h" \) -exec cp -f {} "${TARGET}/" \;

echo "Linting..."
if ! qmk lint -kb crkbd/rev1 -km "${KEYMAP}"; then
  echo "Lint failed."
  exit 2
fi

echo "Compiling..."
qmk compile -kb crkbd/rev1 -km "${KEYMAP}"
echo "Done."