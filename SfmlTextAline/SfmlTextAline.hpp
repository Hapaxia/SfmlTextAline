//////////////////////////////////////////////////////////////////////////////
//
// SFML Text "Aline" (https://github.com/Hapaxia/SfmlTextAline)
//
// Copyright(c) 2023 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef SFMLTEXTALINE_HPP
#define SFMLTEXTALINE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <unordered_map>

// SfmlTextAline v0.3.1 (WIP)
class SfmlTextAline : public sf::Drawable, public sf::Transformable
{
public:
    SfmlTextAline();
    SfmlTextAline(const sf::Text& sfmlText);
    SfmlTextAline(const SfmlTextAline& sfmlTextAline);
    void operator=(const sf::Text& sfmlText);

    enum class Alignment
    {
        Left,
        Center,
        Right,
        JustifyWhitespace,
        JustifyCharacters,
    };

    void setFont(const sf::Font& font);
    void setFont();
    void setString(const sf::String& string);
    void setCharacterSize(std::size_t characterSize);
    void setColor(sf::Color color);
    void setTabLength(std::size_t tabLength);
    void setAlignment(Alignment alignment);
    void setMinWidth(float minWidth);
    void setTextStyle(sf::Uint32 textStyle); // currently only uses bold and italic; ignores others
    void setItalicShear(float italicShear);
    void setItalicShear(); // resets to default value: SFML's value

    void setLineAlignment(std::size_t lineIndex, Alignment alignment);
    void removeLineAlignment(std::size_t lineIndex);
    void removeLineAlignments();
    void setLineOffset(std::size_t lineIndex, sf::Vector2f offset);
    void setLineOffset(std::size_t lineIndex, float offset);
    void removeLineOffset(std::size_t lineIndex);
    void removeLineOffsets();
    void setLineColor(std::size_t lineIndex, sf::Color color);
    void removeLineColor(std::size_t lineIndex);
    void removeLineColors();
    void setLineBold(std::size_t lineIndex, bool bold);
    void removeLineBold(std::size_t lineIndex);
    void removeLineBolds();
    void setLineItalic(std::size_t lineIndex, bool italic);
    void removeLineItalic(std::size_t lineIndex);
    void removeLineItalics();

    std::size_t getNumberOfLines() const;
    float getLineSeparation() const;
    const sf::Font* getFont() const;
    sf::String getString() const;
    std::size_t getCharacterSize() const;
    sf::Color getColor() const;
    std::size_t getTabLength() const;
    Alignment getAlignment() const;
    float getMinWidth() const;
    sf::Uint32 getTextStyle() const;
    float getItalicShear() const;

    Alignment getLineAlignment(std::size_t lineIndex) const;
    sf::Vector2f getLineOffset(std::size_t lineIndex) const;
    sf::Color getLineColor(std::size_t lineIndex) const;
    bool getLineBold(std::size_t lineIndex) const;
    bool getLineItalic(std::size_t lineIndex) const;



private:
    const sf::Font* m_font;
    sf::String m_string;
    std::size_t m_characterSize;
    sf::Color m_color;
    std::size_t m_tabLength;
    Alignment m_globalAlignment;
    float m_minWidth;
    sf::Uint32 m_textStyle;
    float m_italicShear;

    std::unordered_map<std::size_t, Alignment> m_lineAlignments;
    std::unordered_map<std::size_t, sf::Vector2f> m_lineOffsets;
    std::unordered_map<std::size_t, sf::Color> m_lineColors;
    std::unordered_map<std::size_t, bool> m_lineBolds;
    std::unordered_map<std::size_t, bool> m_lineItalics;

    struct Line
    {
        std::size_t start;
        std::size_t length;
        std::size_t vertexIndex;
        std::size_t numberOfQuads;
        float width;
        Alignment alignment;
        sf::Vector2f offset;
        sf::Color color;
    };

    mutable bool m_isUpdateRequired;
    mutable std::vector<sf::Vertex> m_vertices;
    mutable std::vector<Line> m_lines;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateVertices() const;

};

#ifndef SFMLTEXTALINE_NO_CLASS_SHORTCUT
using Aline = SfmlTextAline;
#endif // SFMLTEXTALINE_NO_CLASS_SHORTCUT

#endif // SFMLTEXTALINE_HPP
