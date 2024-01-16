//////////////////////////////////////////////////////////////////////////////
//
// SFML Text "Aline" (https://github.com/Hapaxia/SfmlTextAline)
//
// Copyright(c) 2023-2024 M.J.Silk
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
#include <cmath>

#define SET_AND_UPDATE_MEMBER_IF_DIFFERENT_PTR(x) do { if ((m_##x) != &##x) { ((m_##x) = &##x); m_isUpdateRequired = true; } } while(0)
#define SET_AND_UPDATE_MEMBER_IF_DIFFERENT(x) do { if ((m_##x) != x) { ((m_##x) = x); m_isUpdateRequired = true; } } while(0)

namespace
{

constexpr float defaultItalicShear{ 0.20944f }; // matches SFML's value: 12 degrees as radians

void setGlyph(std::vector<sf::Vertex>& vertices, std::size_t& quad, const sf::Glyph& glyph, const sf::Vector2f position, const float italicShear)
{
	const float left{ position.x + glyph.bounds.left };
	const float right{ left + glyph.bounds.width };
	float top{ glyph.bounds.top };
	float bottom{ top + glyph.bounds.height };
	const float shearTop{ top * italicShear };
	const float shearBottom{ bottom * italicShear };
	top += position.y;
	bottom += position.y;

	const float texLeft{ static_cast<float>(glyph.textureRect.left) };
	const float texTop{ static_cast<float>(glyph.textureRect.top) };
	const float texRight{ static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) };
	const float texBottom{ static_cast<float>(glyph.textureRect.top + glyph.textureRect.height) };

	const std::size_t vertexStartIndex{ quad++ * 6u };
	vertices[vertexStartIndex + 0u].position = { left - shearTop, top };
	vertices[vertexStartIndex + 0u].texCoords = { texLeft, texTop };
	vertices[vertexStartIndex + 1u].position = { left - shearBottom, bottom };
	vertices[vertexStartIndex + 1u].texCoords = { texLeft, texBottom };
	vertices[vertexStartIndex + 2u].position = { right - shearTop, top };
	vertices[vertexStartIndex + 2u].texCoords = { texRight, texTop };
	vertices[vertexStartIndex + 3u].position = { right - shearBottom, bottom };
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
	sfmlTextAline.setAlignment(SfmlTextAline::Alignment::Left);
	sfmlTextAline.setMinWidth(0.f);
	sfmlTextAline.setTextStyle(sf::Text::Style::Regular);
	sfmlTextAline.setItalicShear(defaultItalicShear);
	sfmlTextAline.setLetterSpacingMultiplier(0.f);
	sfmlTextAline.setLineHeightMultiplier(1.f);
	sfmlTextAline.setIsRoundingApplied(true);
	sfmlTextAline.removeLineAlignments();
	sfmlTextAline.removeLineOffsets();
	sfmlTextAline.removeLineColors();
	sfmlTextAline.removeLineBolds();
	sfmlTextAline.removeLineItalics();
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
	, m_globalAlignment{ Alignment::Left }
	, m_minWidth{ 0.f }
	, m_textStyle{ sf::Text::Style::Regular }
	, m_italicShear{ defaultItalicShear }
	, m_lineAlignments()
	, m_lineOffsets()
	, m_lineColors()
	, m_lineBolds()
	, m_lineItalics()
	, m_lineHeightMultiplier{ 1.f }
	, m_letterSpacingMultiplier{ 0.f }
	, m_isRoundingApplied{ true }
{
}

SfmlTextAline::SfmlTextAline(const sf::Text& sfmlText)
	: SfmlTextAline()
{
	*this = sfmlText;
}

SfmlTextAline::SfmlTextAline(const SfmlTextAline& sfmlTextAline)
{
	*this = sfmlTextAline;
}

void SfmlTextAline::operator=(const sf::Text& sfmlText)
{
	resetToDefaultValues(*this);

	setFont(*sfmlText.getFont());
	setString(sfmlText.getString());
	setCharacterSize(sfmlText.getCharacterSize());
	setColor(sfmlText.getFillColor());
	setTextStyle(sfmlText.getStyle());

	setPosition(sfmlText.getPosition());
	setOrigin(sfmlText.getOrigin());
	setRotation(sfmlText.getRotation());
	setScale(sfmlText.getScale());

	setLineHeightMultiplier(sfmlText.getLineSpacing());
	setLetterSpacingMultiplier((sfmlText.getLetterSpacing() - 1.f) / 3.f);

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

void SfmlTextAline::setCharacterSize(const std::size_t characterSize)
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

void SfmlTextAline::setAlignment(const Alignment globalAlignment)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(globalAlignment);
}

void SfmlTextAline::setMinWidth(const float minWidth)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(minWidth);
}

void SfmlTextAline::setTextStyle(const sf::Uint32 textStyle)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(textStyle);
}

void SfmlTextAline::setItalicShear(const float italicShear)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(italicShear);
}

void SfmlTextAline::setItalicShear()
{
	const float italicShear{ defaultItalicShear };
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(italicShear);
}

void SfmlTextAline::setLineHeightMultiplier(const float lineHeightMultiplier)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(lineHeightMultiplier);
}

void SfmlTextAline::setLetterSpacingMultiplier(const float letterSpacingMultiplier)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(letterSpacingMultiplier);
}

void SfmlTextAline::setIsRoundingApplied(const bool isRoundingApplied)
{
	SET_AND_UPDATE_MEMBER_IF_DIFFERENT(isRoundingApplied);
}

void SfmlTextAline::setLineAlignment(const std::size_t lineIndex, const Alignment alignment)
{
	m_lineAlignments[lineIndex] = alignment;

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

void SfmlTextAline::setLineBold(const std::size_t lineIndex, const bool bold)
{
	m_lineBolds[lineIndex] = bold;

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineBold(const std::size_t lineIndex)
{
	m_lineBolds.erase(lineIndex);

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineBolds()
{
	m_lineBolds.clear();

	m_isUpdateRequired = true;
}

void SfmlTextAline::setLineItalic(const std::size_t lineIndex, const bool italic)
{
	m_lineItalics[lineIndex] = italic;

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineItalic(const std::size_t lineIndex)
{
	m_lineItalics.erase(lineIndex);

	m_isUpdateRequired = true;
}

void SfmlTextAline::removeLineItalics()
{
	m_lineItalics.clear();

	m_isUpdateRequired = true;
}









std::size_t SfmlTextAline::getNumberOfLines() const
{
	if (m_isUpdateRequired)
		updateVertices();

	return m_lines.size();
}

float SfmlTextAline::getLineSeparation() const
{
	return (m_font == nullptr) ? 0.0f : m_font->getLineSpacing(static_cast<unsigned int>(m_characterSize));
}

const sf::Font* SfmlTextAline::getFont() const
{
	return m_font;
}

sf::String SfmlTextAline::getString() const
{
	return m_string;
}

std::size_t SfmlTextAline::getCharacterSize() const
{
	return m_characterSize;
}

sf::Color SfmlTextAline::getColor() const
{
	return m_color;
}

std::size_t SfmlTextAline::getTabLength() const
{
	return m_tabLength;
}

SfmlTextAline::Alignment SfmlTextAline::getAlignment() const
{
	return m_globalAlignment;
}

float SfmlTextAline::getMinWidth() const
{
	return m_minWidth;
}

sf::Uint32 SfmlTextAline::getTextStyle() const
{
	return m_textStyle;
}

float SfmlTextAline::getItalicShear() const
{
	return m_italicShear;
}

float SfmlTextAline::getLineHeightMultiplier() const
{
	return m_lineHeightMultiplier;
}

float SfmlTextAline::getLetterSpacingMultiplier() const
{
	return m_letterSpacingMultiplier;
}

bool SfmlTextAline::getIsRoundingApplied() const
{
	return m_isRoundingApplied;
}


SfmlTextAline::Alignment SfmlTextAline::getLineAlignment(const std::size_t lineIndex) const
{
	auto it{ m_lineAlignments.find(lineIndex) };
	return (it != m_lineAlignments.end()) ? it->second : m_globalAlignment;
}

sf::Vector2f SfmlTextAline::getLineOffset(const std::size_t lineIndex) const
{
	auto it{ m_lineOffsets.find(lineIndex) };
	return (it != m_lineOffsets.end()) ? it->second : sf::Vector2f{ 0.f, 0.f };
}

sf::Color SfmlTextAline::getLineColor(const std::size_t lineIndex) const
{
	auto it{ m_lineColors.find(lineIndex) };
	return (it != m_lineColors.end()) ? it->second : m_color;
}

bool SfmlTextAline::getLineBold(const std::size_t lineIndex) const
{
	auto it{ m_lineBolds.find(lineIndex) };
	return (it != m_lineBolds.end()) ? it->second : ((m_textStyle & sf::Text::Style::Bold) == sf::Text::Style::Bold);
}

bool SfmlTextAline::getLineItalic(const std::size_t lineIndex) const
{
	auto it{ m_lineItalics.find(lineIndex) };
	return (it != m_lineItalics.end()) ? it->second : ((m_textStyle & sf::Text::Style::Italic) == sf::Text::Style::Italic);
}

sf::FloatRect SfmlTextAline::getLocalBounds() const
{
	updateVertices();
	return m_localBounds;
}

sf::FloatRect SfmlTextAline::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}











/// PRIVATE

void SfmlTextAline::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_isUpdateRequired)
		updateVertices();

	states.transform *= getTransform();
	states.texture = ((m_font == nullptr) ? nullptr : &(m_font->getTexture(static_cast<unsigned int>(m_characterSize))));

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

	// calculate global styles
	const bool globalBold{ (m_textStyle & sf::Text::Style::Bold) == sf::Text::Style::Bold };
	const bool globalItalic{ (m_textStyle & sf::Text::Style::Italic) == sf::Text::Style::Italic };
	
	const float lineHeight{ m_font->getLineSpacing(static_cast<unsigned int>(m_characterSize)) * m_lineHeightMultiplier };
	sf::Vector2f position{ 0.f, static_cast<float>(m_characterSize) };

	std::size_t currentLine{ 0u };
	m_lines.clear();

	float lineWidth{ 0.f };
	std::size_t lineStartIndex{ 0u };
	std::size_t lineStartQuad{ 0u };

	auto saveLine = [&](std::size_t i)
	{
		Line line;
		line.start = lineStartIndex;
		line.length = i - lineStartIndex;
		line.width = lineWidth;
		line.vertexIndex = lineStartQuad * 6u;
		line.numberOfQuads = currentQuad - lineStartQuad;
		if (auto it{ m_lineAlignments.find(currentLine) }; it != m_lineAlignments.end())
			line.alignment = it->second;
		else
			line.alignment = m_globalAlignment;
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

		// kerning
		position.x += m_font->getKerning(prevChar, currentChar, static_cast<unsigned int>(m_characterSize));
		prevChar = currentChar;

		// calculate bold
		bool bold{ globalBold };
		if (auto it{ m_lineBolds.find(currentLine) }; it != m_lineBolds.end())
			bold = it->second;

		// calculate italic
		bool italic{ globalItalic };
		if (auto it{ m_lineItalics.find(currentLine) }; it != m_lineItalics.end())
			italic = it->second;

		// calculate spacing
		const float spaceWidth{ m_font->getGlyph(' ', static_cast<unsigned int>(m_characterSize), bold).advance };
		const float letterSpacing{ spaceWidth * m_letterSpacingMultiplier };

		// whitespace
		if ((currentChar == ' ') || (currentChar == '\n') || (currentChar == '\t'))
		{
			switch (currentChar)
			{
			case ' ':
				position.x += spaceWidth + letterSpacing;
				break;
			case '\t':
				position.x += (spaceWidth * m_tabLength) + letterSpacing;
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
		const sf::Glyph& glyph = m_font->getGlyph(currentChar, static_cast<unsigned int>(m_characterSize), bold);
		::setGlyph(m_vertices, currentQuad, glyph, position, italic ? m_italicShear : 0.f);

		position.x += glyph.advance + letterSpacing;

		// final line
		if (i == (m_string.getSize() - 1u))
		{
			lineWidth = std::max(lineWidth, position.x);
			saveLine(i);
		}
	}

	// remove unused quads from vector
	m_vertices.resize((m_string.getSize() - numberOfUnusedQuads) * 6u);

	// calculate which line (or minimum width) is longest
	float maxLineWidth{ m_minWidth };
	std::size_t longestLine{ m_lines.size() };
	for (std::size_t i{ 0u }; i < m_lines.size(); ++i)
	{
		if (m_lines[i].width > maxLineWidth)
		{
			maxLineWidth = m_lines[i].width;
			longestLine = i;
		}
	}

	// apply offset and align by modifying quads' positions
	for (std::size_t l{ 0u }; l < m_lines.size(); ++l)
	{
		sf::Vector2f offset{ m_lines[l].offset };
		float justifyOffset{ 0.f };
		if (l != longestLine)
		{
			switch (m_lines[l].alignment)
			{
			case Alignment::Right:
				offset.x += m_isRoundingApplied ? std::round(maxLineWidth - m_lines[l].width) : maxLineWidth - m_lines[l].width;
				break;
			case Alignment::Center:
				offset.x += m_isRoundingApplied ? std::round((maxLineWidth - m_lines[l].width) / 2.f) : (maxLineWidth - m_lines[l].width) / 2.f;
				break;
			case Alignment::Left:
			case Alignment::JustifyCharacters:
			case Alignment::JustifyWhitespace:
			default:
				break;
			}
		}

		if (m_lines[l].alignment == Alignment::JustifyWhitespace)
		{
			bool inWhiteSpaceBlock{ false };
			std::size_t numberOfWhitespaceBlocks{ 0u };
			for (std::size_t i{ 0u }; i < m_lines[l].length; ++i)
			{
				const std::size_t currentIndex{ m_lines[l].start + i };
				const std::uint32_t currentChar{ m_string[currentIndex] };
				if (currentChar == ' ' || currentChar == '\t')
				{
					if (!inWhiteSpaceBlock)
						++numberOfWhitespaceBlocks;
					inWhiteSpaceBlock = true;
				}
				else
					inWhiteSpaceBlock = false;
			}

			justifyOffset = (numberOfWhitespaceBlocks > 0u) ? (maxLineWidth - m_lines[l].width) / (static_cast<float>(numberOfWhitespaceBlocks)) : 0.f;

			std::size_t q{ 0u };
			inWhiteSpaceBlock = false;
			float justifyAccumulation{ 0.f };
			for (std::size_t i{ 0u }; i < m_lines[l].length; ++i)
			{
				const std::size_t currentIndex{ m_lines[l].start + i };
				const std::uint32_t currentChar{ m_string[currentIndex] };
				
				if (currentChar == ' ' || currentChar == '\t')
				{
					if (!inWhiteSpaceBlock)
						justifyAccumulation += justifyOffset;
					inWhiteSpaceBlock = true;
				}
				else
				{
					for (std::size_t v{ 0u }; v < 6u; ++v)
					{
						m_vertices[m_lines[l].vertexIndex + q * 6u + v].position += { offset.x + (m_isRoundingApplied ? std::round(justifyAccumulation) : justifyAccumulation), offset.y };
						m_vertices[m_lines[l].vertexIndex + q * 6u + v].color = m_lines[l].color;
					}
					++q;
					inWhiteSpaceBlock = false;
				}
			}
		}
		else if (m_lines[l].alignment == Alignment::JustifyCharacters)
		{
			justifyOffset = (m_lines[l].length > 2u) ? (maxLineWidth - m_lines[l].width) / (static_cast<float>(m_lines[l].length) - 1.f) : 0.f;

			std::size_t q{ 0u };
			float justifyAccumulation{ 0.f };
			for (std::size_t i{ 0u }; i < m_lines[l].length; ++i)
			{
				const std::size_t currentIndex{ m_lines[l].start + i };
				const std::uint32_t currentChar{ m_string[currentIndex] };

				if (!(currentChar == ' ' || currentChar == '\t'))
				{
					for (std::size_t v{ 0u }; v < 6u; ++v)
					{
						m_vertices[m_lines[l].vertexIndex + q * 6u + v].position += { offset.x + (m_isRoundingApplied ? std::round(justifyAccumulation) : justifyAccumulation), offset.y };
						m_vertices[m_lines[l].vertexIndex + q * 6u + v].color = m_lines[l].color;
					}
					++q;
				}
				justifyAccumulation += justifyOffset;
			}
		}
		else
		{
			for (std::size_t q{ 0u }; q < (m_lines[l].numberOfQuads); ++q)
			{
				for (std::size_t v{ 0u }; v < 6u; ++v)
				{
					m_vertices[m_lines[l].vertexIndex + q * 6u + v].position += offset;
					m_vertices[m_lines[l].vertexIndex + q * 6u + v].color = m_lines[l].color;
				}
			}
		}
	}

	// calculate local bounds
	m_localBounds.left = static_cast<float>(m_characterSize);
	m_localBounds.top = static_cast<float>(m_characterSize);
	sf::Vector2f max{ 0.f, 0.f };
	for (auto& vertex : m_vertices)
	{
		m_localBounds.left = std::min(m_localBounds.left, vertex.position.x);
		m_localBounds.top = std::min(m_localBounds.top, vertex.position.y);
		max.x = std::max(max.x, vertex.position.x);
		max.y = std::max(max.y, vertex.position.y);
	}
	m_localBounds.width = max.x - m_localBounds.left;
	m_localBounds.height = max.y - m_localBounds.top;

	// all done
	m_isUpdateRequired = false;
}
