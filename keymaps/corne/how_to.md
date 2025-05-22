Useful links:

- [guide](https://www.josean.com/posts/how-to-use-code-with-qmk)

# Procedure to correctly flash a Corne 42-keys slit keyboard

> [!NOTE] The flashing procedure is valid in MacOs systems

## Prepare the environment

### QMK-CLI

Assuming Homebrew is already present in the system, to install QMK CLI via homebrew run the following command:

> ```bash
> brew install qmk/qmk/qmk
> ```

### QMK Toolbox

The QMK Toolbox tool is necessary to easily erase and flash the chip built-in to the split keyboard with a new firmware.
To install such application, visit the [GitHub page](https://github.com/qmk/qmk_toolbox/releases) and install the latest `QMK.Toolbox.pkg` asset.
Run the installer and proceed with the next instructions.

## Initial setup

Just in case this is the first time qmk has been installed, a setup step is needed:

> ```bash
> qmk setup
> ```

An interactive prompt will showcase. In most of the cases, just answer `y` to each question.

## Keyboard name

In case of Corne split keyboard, the corresponding name is `crkbd/rev1` in qmk (to get all available options for this keyboard, run `bash qmk list-keyboards | grep -iF "crkbd"` or `bash qmk list-keyboards | grep -iF "corne"`)

### Create a backup of the default keyboard configuration

After finding the proper keyboard name, it's good practice to create a copy of its default layout as follows:

> ```bash
> qmk new-keymap -kb crkbd/rev1 -km <keymap-layout-name>
> ```

This will create a new folder named `your-name` containing a working copy of the default layout.

# Edit the layout file

Under the just created folder, open the `keymap.c` file which contains a customizable layout.
Each key is label with a specific tag, i.e. a sort of enum. An exhaustive list can be found [here](https://docs.qmk.fm/keycodes)

# Compile your firmware

To flash the keyboard with a firmware, a loadable binary file is needed. To generate an `hex` file, run the following command:

```bash
qmk compile -kb crkbd -km <keymap-layout-name>
```

# Load the firmware

To load the firmware into the uC built-in to the keyboard, QMK Toolbox is used.
First thing to do is assessing the path of the binary file created in the previous step.
After this, follow the following procedure:

1. Open the QMK Toolbox app
2. Select the path leading to the binary file
3. Reset your keyboard (some keyboards have soldered reset buttons. In other cases, qmk provides alternative methods to achieve the same result (take a look [here](https://docs.qmk.fm/newbs_flashing#put-your-keyboard-into-dfu-bootloader-mode)))
4. Once the keyboard enters bootloader mode, the application should recognize it. Press flash and the erasing and loading procedure should start

When the flashing procedure has finished, the following message should appear:

> Flash complete
> DFU device disconnected: ...

> [!TIP] I do the flashing procedure on both keyboard sides for safety
