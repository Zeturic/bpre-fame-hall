## Hall of Fame Expanded Pokémon Fix

Fixes an issue where expanded Pokémon above index `0x1FF` do not show up correctly in the Hall of Fame.

For example, `0x201` would normally show up as `0x1` (Bulbasaur). This is because the Hall of Fame data originally only allocated `9` bits to the species number, and `0x1FF` is the largest number that can be stored in that space; larger numbers only have their lowest `9` bits stored.

For binary FR hacks.

### Build Instructions

See [here](https://gist.github.com/Zeturic/db1611cc7b17c3140f9b9af32e1b596b) for the prequisites and help in installing them.

#### Cloning the repo

Open your terminal to whatever folder you want to download this repo into. Then, do the following to download the repo and build the included tools:

```shell
$ git clone https://github.com/Zeturic/bpre-fame-hall.git
$ cd bpre-fame-hall
```

#### Adding your ROM

Copy your ROM to this directory and rename it `rom.gba`.

#### Configuration

The build system is smart enough to find enough free space on its own, but if you want it to be inserted at a particular address, you can specify it by updating the definition of `START_AT` in `config.mk`.

If the given address is acceptable (i.e. is word-aligned and has enough bytes of free space), it will be inserted there. Otherwise, it will just use `START_AT` to determine where in the ROM it should start looking for free space.

#### Building the project itself

Once you're ready, run `make` to actually build the project.

This won't actually modify `rom.gba`, instead your output will be in `test.gba`. Naturally, test it in an emulator.

### What about existing saves?

Existing saves with Hall of Fame data that use the vanilla data structures will have that data become corrupted when applying this. Existing saves without Hall of Fame data will be completely fine.

You can clear existing Hall of Fame data by doing `clearflag 0x82C` if you really want to support old saves. It will still remember the number of times the player had entered the Hall of Fame, but it will be inaccessible until they refight the Elite Four. `clearflag 0x82C` has no effect on players without Hall of Fame data.

### Credits

The project structure and some of the build tools are from [pokeemerald](https://github.com/pret/pokeemerald).
