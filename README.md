# Sfml Text "Aline"
 Alignable Multi-line SFML Text

Currently a work-in-progress and is in a useable state with some other features still to come.

It is a single-object multi-line text object for SFML.  
It is similar to SFML's own sf::Text object but has some extra features (but doesn't include some of sf::Text's features as yet - see below).

Features:
- Lines are alignable globally (throughout the entire object) to the left, centre, right and justified (distributed/separated characters).
- Individual lines can also be customised (including having their own alignment, colour, positional offset, bold and italic)
- Positional offset is any offset that a single line can be given (allowing each line to be moved around freely - after alignments)
- Can be assigned an sf::Text to reproduce it automatically (within its own features - so far)
- The length of a tab character can be customised to any set number of spaces
- Kerning is applied
- Some text styles (bold and italic - italic shear amount is customisable)
- A minimum width can be specified that allows for a virtual right side margin when aligning

Planned - but currently missing - features:
- Other text styles (underline and strike-through)
- Outline
- Letter spacing
- Line spacing
- Bounds
>> Note that these missing features are available in the original sf::Text but yet included here.

You now use just the shortcut class name Aline instead of its full name SfmlTextAline. If you would like to cancel the shortcut from being created, define SFMLTEXTALINE_NO_CLASS_SHORTCUT before including the class.

The alignment enum class has been renamed to make it more convenient. It is now just Align instead of LineAlignment.

So, you can access the alignment enum class by simply using it like this: `Aline::Align::Center`.
