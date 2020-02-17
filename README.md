# Alignment
A fantasy puzzle adventure for Arduboy

## Gameplay
Gems decend two at a time down rows onto the play area. Swap rows along with the gems currently on them to control where they land. Match two gems to clear them and attack an enemy.  Each row represents a fantasy weapon which affect enemies differently. The level is complete when the enemy's health reaches zero. A player has three health. Health is lost if gems in a column exceed the max. Additionally, all gems in that column are cleared. The game is over if all three health are lost or the player defeats the evil sorcerer.

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
- [x] Add match animation
- [x] Add weapon clear animation
- [x] Make sure multiple weapons can clear at the same time.
- [x] Add damage animation (flash enemy, display damage over enemy (ex. -5))
- [x] Make sure double matches display correct damage in single indicator (ex. -10 instead of -5)

### Advanced Damage Calculation, Enemy Vulnerabilities/Resistances
- [x] Track what weapons inflict damage.
- [x] Add weapon resistances and vulnerabilities to enemy
- [x] Alter damage based on enemy properties

### Additional Enemies
- [x] Add art for five total enemies.
- [x] Transition between enemies on win scenario.
- [x] Add custom poperties for each enemy (Max Health, Resistances, Vulnerabilities)

### Game Dev
- [x] Manage Gems as class instances instead of arrays.
- [x] Manage Weapons as class instances instead of arrays.
- [x] Separate Game States into classes with handleInput, update, and render instance methods.

### Enemy Updates
- [ ] Add idle animation to Skeleton
- [ ] Add take damage image to Skeleton
- [ ] Allow Skeleton to pop a random gem
- [ ] Add slash animation to Skeleton
- [ ] Add idle animation to Orc
- [ ] Add take damage image to Orc
- [ ] Allow Orc to randomly send 3 gems
- [ ] Add smash animation to Orc
- [ ] Add idle animation to Golem
- [ ] Add take damage image to Golem
- [ ] Randomly turn a top gem to stone.
- [ ] Add Golem spell animation
- [ ] Add idle animation to Demon
- [ ] Add take damage image to Demon
- [ ] Allow Demon to speed up game for 15 seconds.
- [ ] Add attack animation to Demon
- [ ] Add idle animation to Sorcerer
- [ ] Add take damage image to Sorcerer
- [ ] Allow Sorcerer to randomly teleport falling gems to new positions.
- [ ] Add spell animation to Sorcerer

## Inspiration
- Yoshi for Gameboy
- Puzzle Quest
