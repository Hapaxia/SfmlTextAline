//////////////////////////////////////////////////////////////////////////////
//
// SFML Text Aline (https://github.com/Hapaxia/SfmlTextAline)
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

// SfmlTextAline v0.1.0 (WIP)
class SfmlTextAline : public sf::Drawable, public sf::Transformable
{
public:
	SfmlTextAline();
    SfmlTextAline(const sf::Text& sfmlText);

    enum class LineAlignment
    {
        Left,
        Center,
        Right,
    };

    void operator=(const sf::Text& sfmlText);

    void setFont(const sf::Font& font);
    void setFont();
    void setString(const sf::String& string);
    void setCharacterSize(unsigned int characterSize);
    void setColor(sf::Color color);
    void setTabLength(std::size_t tabLength);
    void setGlobalLineAlignment(LineAlignment lineAlignment);
    void setLineAlignment(std::size_t lineIndex, LineAlignment lineAlignment);
    void removeLineAlignment(std::size_t lineIndex);
    void removeLineAlignments();
    void setLineOffset(std::size_t lineIndex, sf::Vector2f offset);
    void setLineOffset(std::size_t lineIndex, float offset);
    void removeLineOffset(std::size_t lineIndex);
    void removeLineOffsets();
    void setLineColor(std::size_t lineIndex, sf::Color color);
    void removeLineColor(std::size_t lineIndex);
    void removeLineColors();

private:
    const sf::Font* m_font;
    sf::String m_string;
    unsigned int m_characterSize;
    sf::Color m_color;
    std::size_t m_tabLength;
    LineAlignment m_globalLineAlignment;
    std::unordered_map<std::size_t, LineAlignment> m_lineAlignments;
    std::unordered_map<std::size_t, sf::Vector2f> m_lineOffsets;
    std::unordered_map<std::size_t, sf::Color> m_lineColors;

    struct Line
    {
        std::size_t vertexIndex;
        std::size_t numberOfQuads;
        float width;
        LineAlignment alignment;
        sf::Vector2f offset;
        sf::Color color;
    };

    mutable bool m_isUpdateRequired;
    mutable std::vector<sf::Vertex> m_vertices;
    mutable std::vector<Line> m_lines;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateVertices() const;

#endif // SFMLTEXTALINE_HPP
