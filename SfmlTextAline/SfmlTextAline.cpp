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

///////////////////////////////////////////////////////
//
// C++ 17
// ======
//
// Requires C++ 17 (or later) to compile this translation unit.
//
///////////////////////////////////////////////////////

#include "SfmlTextAline.hpp"

//#include <iostream>
#include <algorithm>
#include <functional>

#define SET_AND_UPDATE_MEMBER_IF_DIFFERENT_PTR(x) do { if ((m_##x) != &##x) { ((m_##x) = &##x); m_isUpdateRequired = true; } } while(0)
#define SET_AND_UPDATE_MEMBER_IF_DIFFERENT(x) do { if ((m_##x) != x) { ((m_##x) = x); m_isUpdateRequired = true; } } while(0)

namespace
{

void setGlyph(std::vector<sf::Vertex>& vertices, std::size_t& quad, const sf::Glyph& glyph, const sf::Vector2f position)
{

	float left{ position.x + glyph.bounds.left };
	float top{ position.y + glyph.bounds.top };
	float right{ left + glyph.bounds.width };
	float bottom{ top + glyph.bounds.height };

	float texLeft{ static_cast<float>(glyph.textureRect.left) };
	float texTop{ static_cast<float>(glyph.textureRect.top) };
	float texRight{ static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) };
	float texBottom{ static_cast<float>(glyph.textureRect.top + glyph.textureRect.height) };

	const std::size_t vertexStartIndex{ quad++ * 6u };
	vertices[vertexStartIndex + 0u].position = { left, top };
	vertices[vertexStartIndex + 0u].texCoords = { texLeft, texTop };
	vertices[vertexStartIndex + 1u].position = { left, bottom };
	vertices[vertexStartIndex + 1u].texCoords = { texLeft, texBottom };
	vertices[vertexStartIndex + 2u].position = { right, top };
	vertices[vertexStartIndex + 2u].texCoords = { texRight, texTop };
	vertices[vertexStartIndex + 3u].position = { right, bottom };
	vertices[vertexStartIndex + 3u].texCoords = { texRight, texBottom };
	vertices[vertexStartIndex + 4u] = vertices[vertexStartIndex + 2u];
	vertices[vertexStartIndex + 5u] = vertices[vertexStartIndex + 1u];
}

void resetToDefaultValues(SfmlTextAline& sfmlTextAline)
{
	sfmlTextAline.setFont();
	sfmlTextAline.setString("");
	sfmlTextAline.setCharacterSize(30u);
	sfmlTextAline.setColor(sf::Color::White);
	sfmlTextAline.setTabLength(4u);
	sfmlTextAline.setGlobalLineAlignment(SfmlTextAline::LineAlignment::Left);
	sfmlTextAline.removeLineAlignments();
	sfmlTextAline.removeLineOffsets();
	sfmlTextAline.removeLineColors();
}

} // namespace

SfmlTextAline::SfmlTextAline()
	: m_font{ nullptr }
	, m_string{ "" }
	, m_characterSize{ 30u }
	, m_isUpdateRequired{ true }
	, m_vertices()
	, m_color{ sf::Color::White }
	, m_tabLength{ 4u }
	, m_globalLineAlignment{ LineAlignment::Left }
	, m_lineAlignments()
	, m_lineOffsets()
	, m_lineColors()
{
}

SfmlTextAline::SfmlTextAline(const sf::Text& sfmlText)
	: SfmlTextAline()
{
	*this = sfmlText;
}

void SfmlTextAline::operator=(const sf::Text& sfmlText)
{
	resetToDefaultValues(*this);

	setFont(*sfmlText.getFont());
	setString(sfmlText.getString());
	setCharacterSize(sfmlText.getCharacterSize());
	setColor(sfmlText.getFillColor());

	setPosition(sfmlText.getPosition());
	setOrigin(sfmlText.getOrigin());
	setRotation(sfmlText.getRotation());
	setScale(sfmlText.getScale());

	m_isUpdateRequired = true;
}

void SfmlTextAline::setFont(const sf::Font& font)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT_PTR(font);
}

void SfmlTextAline::setFont()
{
	m_font = nullptr;

	m_isUpdateRequired = true;

}
void SfmlTextAline::setString(const sf::String& string)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(string);
}

void SfmlTextAline::setCharacterSize(const unsigned int characterSize)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(characterSize);
}

void SfmlTextAline::setColor(const sf::Color color)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(color);
}

void SfmlTextAline::setTabLength(const std::size_t tabLength)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(tabLength);
}

void SfmlTextAline::setGlobalLineAlignment(const LineAlignment globalLineAlignment)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(globalLineAlignment);
}

void SfmlTextAline::setLineAlignment(const std::size_t lineIndex, const LineAlignment lineAlignment)
{
	m_lineAlignments[lineIndex] = lineAlignment;

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineAlignment(const std::size_t lineIndex)
{
	m_lineAlignments.erase(lineIndex);

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineAlignments()
{
	m_lineAlignments.clear();

	m_isUpdateRequired = true;
}

void SfmlTextAline::setLineOffset(const std::size_t lineIndex, const sf::Vector2f offset)
{
	m_lineOffsets[lineIndex] = offset;

	m_isUpdateRequired = true;
}

void SfmlTextAline::setLineOffset(const std::size_t lineIndex, const float offset)
{
	setLineOffset(lineIndex, { offset, 0.f });
}

void SfmlTextAline::removeLineOffset(const std::size_t lineIndex)
{
	m_lineOffsets.erase(lineIndex);

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineOffsets()
{
	m_lineOffsets.clear();

	m_isUpdateRequired = true;
}

void SfmlTextAline::setLineColor(const std::size_t lineIndex, const sf::Color color)
{
	m_lineColors[lineIndex] = color;

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineColor(const std::size_t lineIndex)
{
	m_lineColors.erase(lineIndex);

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineColors()
{
	m_lineColors.clear();

	m_isUpdateRequired = true;
}











/// PRIVATE

void SfmlTextAline::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_isUpdateRequired)
		updateVertices();

	states.transform *= getTransform();
	states.texture = ((m_font == nullptr) ? nullptr : &(m_font->getTexture(m_characterSize)));

	target.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::Triangles, states);
}

void SfmlTextAline::updateVertices() const
{
	if (m_font == nullptr || m_string.isEmpty())
	{
		m_vertices.clear();
		m_isUpdateRequired = false;
		return;
	}
	


	m_vertices.resize(m_string.getSize() * 6u);

	std::size_t currentQuad{ 0u };
	std::size_t numberOfUnusedQuads{ 0u };

	const float spaceWidth{ m_font->getGlyph(' ', m_characterSize, false).advance };
	const float lineHeight{ m_font->getLineSpacing(m_characterSize) };
	//sf::Vector2f position{ 0.f, lineHeight };
	sf::Vector2f position{ 0.f, static_cast<float>(m_characterSize) };

	std::size_t currentLine{ 0u };
	m_lines.clear();

	float lineWidth{ 0.f };
	std::size_t lineStartIndex{ 0u };
	std::size_t lineStartQuad{ 0u };

	auto saveLine = [&](std::size_t i)
	{
		Line line;
		line.width = lineWidth;
		line.vertexIndex = lineStartQuad * 6u;
		line.numberOfQuads = currentQuad - lineStartQuad;
		if (auto it{ m_lineAlignments.find(currentLine) }; it != m_lineAlignments.end())
			line.alignment = it->second;
		else
			line.alignment = m_globalLineAlignment;
		if (auto it{ m_lineOffsets.find(currentLine) }; it != m_lineOffsets.end())
			line.offset = it->second;
		else
			line.offset = { 0.f, 0.f };
		if (auto it{ m_lineColors.find(currentLine) }; it != m_lineColors.end())
			line.color = it->second;
		else
			line.color = m_color;
		m_lines.push_back(line);
	};

	std::uint32_t prevChar{ 0u };
	for (std::size_t i{ 0u }; i < m_string.getSize(); ++i)
	{
		std::uint32_t currentChar{ m_string[i] };

		lineWidth = std::max(lineWidth, position.x);

		position.x += m_font->getKerning(prevChar, currentChar, m_characterSize);

		prevChar = currentChar;

		// whitespace
		if ((currentChar == ' ') || (currentChar == '\n') || (currentChar == '\t'))
		{
			switch (currentChar)
			{
			case ' ':
				position.x += spaceWidth;
				break;
			case '\t':
				position.x += spaceWidth * m_tabLength;
				break;
			case '\n':
				saveLine(i);
				lineWidth = 0.f;
				lineStartIndex = i + 1u;
				lineStartQuad = currentQuad;
				position.y += lineHeight;
				position.x = 0.f;
				++currentLine;
				break;
			}

			numberOfUnusedQuads += 1u;
			continue;
		}

		// glyph character
		const sf::Glyph& glyph = m_font->getGlyph(currentChar, m_characterSize, false);
		::setGlyph(m_vertices, currentQuad, glyph, position);

		position.x += glyph.advance;

		// final line
		if (i == (m_string.getSize() - 1u))
		{
			lineWidth = std::max(lineWidth, position.x);
			saveLine(i);
		}
	}

	m_vertices.resize((m_string.getSize() - numberOfUnusedQuads) * 6u);

	float maxLineWidth{ 0.f };
	std::size_t longestLine{ 0u };
	for (std::size_t i{ 0u }; i < m_lines.size(); ++i)
	{
		if (m_lines[i].width > maxLineWidth)
		{
			maxLineWidth = m_lines[i].width;
			longestLine = i;
		}
	}

	for (std::size_t l{ 0u }; l < m_lines.size(); ++l)
	{
		sf::Vector2f offset{ m_lines[l].offset };
		if (l != longestLine)
		{
			switch (m_lines[l].alignment)
			{
			case LineAlignment::Right:
				offset.x += maxLineWidth - m_lines[l].width;
				break;
			case LineAlignment::Center:
				offset.x += (maxLineWidth - m_lines[l].width) / 2.f;
				break;
			case LineAlignment::Left:
			default:
				break;
			}
		}

		for (std::size_t i{ 0u }; i < (m_lines[l].numberOfQuads * 6u); ++i)
		{
			m_vertices[m_lines[l].vertexIndex + i].position += offset;
			m_vertices[m_lines[l].vertexIndex + i].color = m_lines[l].color;
		}
	}

	m_isUpdateRequired = false;
}
