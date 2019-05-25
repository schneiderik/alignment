# Alignment
A fantasy puzzle adventure for Arduboy

## Gameplay
Gems decend one to three at a time down columns onto the play area. Swap columns along with the gems currently on them to control where they land. Align gems in groups of three or more to clear them and attack an enemy.  Each column represents a fantasy weapon. Horizontal matches attack with multiple weapons, and vertical matches trigger a more powerful attack with a single weapon. Matching more blocks create combos for more powerful attacks. The level is complete whent the enemy's health reaches zero.  A player has three health. Health is lost if gems in a column exceed the max. Additionally, all gems in that column are cleared. The game is over if all three health are lost.

## Features

### Core Game
- Render title screen.
- Add ability to press any key on the title screen to switch to game screen.
- Render a play area with default gems.
- Render an indicator for the currently selected set of adjacent columns.
- Allow selected columns (along with their gems) to be swapped.
- A single gem decends the play area in a random column at X interval.
- When a decending gem reaches another gem, it is added to the column.
- Decending gems are swapped along with the columns if the other column has a gem at the same of higher position than the decending gem.
- Decending gems are not swapped along with the columns if the other column's highest gem is at a lower position than the decending gem.
- Add indicators for three health.
- When a decending gem is added to a full column, all gems in the column are cleared, and health is decreased by one.
- When health reaches 0, show Game Over screen.
- Add ability to press any key on game over screen to return to title screen.
- At any time, if 3 or more vertical gems match, clear them, and collapse columns accordingly.
- At any time, if 3 or more horizontal gems match, clear them, and collapse columns accordingly.
- Render enemy health bar.
- When a match happens, reduce enemy health by 3.
- When enemy health reaches 0, switch to win screen.
- Add ability to press any key on win screen to return to title screen.
- Add preview of upcoming gems.

### Art/Animation
- Add weapon art under columns (Sword, Bow & Arrow, Magic Staff, Hammer)
- Add enemy art
- Add match/clear/collapse animations
- Add damage animation (flash total damage over enemy, then reduce health bar)

### Advanced Matching/Combos
- Detect matches of 4 (worth 5 damage)
- Detect matches of 5 (worth 7 damage)
- Detect multi-axis matches (total damage + 3)
- Track combos (which multiply total damage based on the combo) (For example, a 3 match followed by a 4 match would be 16 damage.  (3dmg + 5dmg) * 2combo = 16dmg)

### Advanced Damage Calculation, Enemy Vulnerabilities/Resistances
- Track what weapons inflict damage.
- Add weapon resistances and vulnerabilities to enemy
- Alter damage based on enemy properties

### Additional Enemies
- Add art for five total enemies.
- Transition between enemies on win scenario.
- Add custom poperties for each enemy (Max Health, Resistances, Vulnerabilities)

## Inspiration
- Yoshi for Gameboy
- Puzzle Quest
