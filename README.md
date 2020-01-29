# Alignment
A fantasy puzzle adventure for Arduboy

## Gameplay
Gems decend one to three at a time down columns onto the play area. Swap columns along with the gems currently on them to control where they land. Align gems in groups of three or more to clear them and attack an enemy.  Each column represents a fantasy weapon. Horizontal matches attack with multiple weapons, and vertical matches trigger a more powerful attack with a single weapon. Matching more blocks create combos for more powerful attacks. The level is complete whent the enemy's health reaches zero.  A player has three health. Health is lost if gems in a column exceed the max. Additionally, all gems in that column are cleared. The game is over if all three health are lost.

## Features

### Core Game
- [x] Render title screen.
- [x] Add ability to press any key on the title screen to switch to game screen.
- [x] Render a play area with default gems.
- [x] Render an indicator for the currently selected set of adjacent columns.
- [x] Allow selected columns (along with their gems) to be swapped.
- [x] A single gem decends the play area in a random column at X interval.
- [x] When a decending gem reaches another gem, it is added to the column.
- [x] Decending gems are swapped along with the columns if the other column has a gem at the same of higher position than the decending gem.
- [x] Decending gems are not swapped along with the columns if the other column's highest gem is at a lower position than the decending gem.
- [x] Add indicators for three health.
- [x] When a decending gem is added to a full column, all gems in the column are cleared, and health is decreased by one.
- [x] When health reaches 0, show Game Over screen.
- [x] Add ability to press any key on game over screen to return to title screen.
- [x] When 2 Gems in a column match they are cleared.
- [x] Render enemy health bar.
- [x] When a match happens, reduce enemy health.
- [x] When enemy health reaches 0, switch to win screen.
- [x] Add ability to press any key on win screen to return to title screen.
- [x] Add preview of upcoming gems.

### Art/Animation
- [x] Add weapon art under columns (Sword, Bow & Arrow, Magic Staff, Hammer)
- [x] Add enemy art
- [ ] Add match animation
- [ ] Add weapon clear animation
- [ ] Add damage animation (flash total damage over enemy, then reduce health bar)

### Advanced Damage Calculation, Enemy Vulnerabilities/Resistances
- [ ] Track what weapons inflict damage.
- [ ] Add weapon resistances and vulnerabilities to enemy
- [ ] Alter damage based on enemy properties

### Additional Enemies
- [x] Add art for five total enemies.
- [x] Transition between enemies on win scenario.
- [x] Add custom poperties for each enemy (Max Health, Resistances, Vulnerabilities)

## Inspiration
- Yoshi for Gameboy
- Puzzle Quest
