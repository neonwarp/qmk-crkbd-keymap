# corne crkbd split

Open the cloned repo inside [QMK MSYS](https://msys.qmk.fm/)

Generate the `keymap.c` file. This will overwrite the file!

```bash
qmk json2c crkbd_rev1_layout_split_3x6_3_mine.json -o keymap.c
```

Create a named directory under the keyboards then copy the files

```bash
mkdir -p /c/Users/"$(whoami)"/qmk_firmware/keyboards/crkbd/keymaps/"$(whoami)"
cp *.c *.mk /c/Users/"$(whoami)"/qmk_firmware/keyboards/crkbd/keymaps/"$(whoami)"
```

Compile the code and flash it with [QMK Toolbox](https://qmk.fm/toolbox)

```bash
qmk compile -kb crkbd/rev1 -km "$(whoami)"
```