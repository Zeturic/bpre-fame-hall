### Hall of Fame Expanded Pokémon Fix

Fixes an issue where expanded Pokémon above index `0x1FF` do not show up correctly in the Hall of Fame.

For example, `0x201` would normally show up as `0x1` (Bulbasaur). This is because the Hall of Fame data originally only allocated `9` bits to the species number, and `0x1FF` is the largest number that can be stored in that space; larger numbers only have their lowest `9` bits stored.

#### How do I build this?

The build script will search for adequate free space, but if you need to insert the code in a particular place, you can tell it where to start looking by modifying `start-at` in `config.ini`. If the given address is acceptable (i.e. is word-aligned and has enough bytes of free space), it will be inserted there.

Click [here](scripts/makinoa/README.md) for build instructions.

#### What about existing saves?

Existing saves with Hall of Fame data that use the vanilla data structures will have that data become corrupted when applying this. Existing saves without Hall of Fame data will be completely fine.

You can clear existing Hall of Fame data by doing `clearflag 0x82C` if you really want to support old saves. It will still remember the number of times the player had entered the Hall of Fame, but it will be inaccessible until they refight the Elite Four. `clearflag 0x82C` has no effect on players without Hall of Fame data.

#### Credits

This is largely a direct port of the [relevant Pokeemerald functions](https://github.com/pret/pokeemerald/blob/804d0a4b6a12907974ffd8cb20f6ed6c527b663b/src/hall_of_fame.c), with some tweaks to match Fire Red's behavior.