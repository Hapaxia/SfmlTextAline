# SfmlTextAline
 Alignable Multi-line SFML Text

Currently a work-in-progress and is in an incomplete - but still useable - state.

It is a single-object multi-line text object for SFML.  
It is similar to SFML's own sf::Text object but has some extra features (but doesn't include some of sf::Text's features as yet - see below).

Features:
- Lines are alignable globally (throughout the entire object) to the left, centre or right.
- Individual lines can also be customised (including having their own alignment, colour, and positional offset)
- Positional offset is any offset that a single line can be given (allowing each line to be moved around freely - after alignments)
- Can be assigned an sf::Text to reproduce it automatically (within its own features - so far)
- The length of a tab character can be customised to any set number of spaces
- Kerning is applied

Planned - but currently missing - features:
- Text style (bold, italic, underline and strike-through)
- Outline
- Letter spacing
- Line spacing
- Bounds
>> Note that these missing features are available in the original sf::Text but yet included here.
