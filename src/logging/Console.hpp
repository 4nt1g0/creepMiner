// ==========================================================================
// 
// creepMiner - Burstcoin cryptocurrency CPU and GPU miner
// Copyright (C)  2016-2017 Creepsky (creepsky@gmail.com)
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110 - 1301  USA
// 
// ==========================================================================

#pragma once

#include "channels/ColoredPriorityConsoleChannel.hpp"
#include <mutex>
#include <memory>
#include <iostream>
#include <Poco/Format.h>

namespace Burst
{
	/**
	 * \brief Colors for the console.
	 */
	enum class ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};

	/**
	 * \brief A pair of fore- and background.
	 */
	struct ConsoleColorPair
	{
		ConsoleColor foreground, background;
	};

	/**
	 * \brief A print block for the console.
	 * This class is not thread-safe and should not be used in concurrent way!
	 */
	class PrintBlock
	{
	public:
		/**
		 * \brief Constructor.
		 * Locks the console mutex.
		 * \param stream The output stream.
		 * \param mutex The console mutex.
		 */
		explicit PrintBlock(std::ostream& stream);

		/**
		 * \brief Destructor.
		 */
		~PrintBlock();

		PrintBlock(PrintBlock&& rhs) noexcept = default;
		PrintBlock(const PrintBlock& rhs) = default;
		PrintBlock& operator=(const PrintBlock& rhs) = default;
		PrintBlock& operator=(PrintBlock&& rhs) noexcept = default;

		/**
		 * \brief Prints a value to output.
		 * \tparam T The type of the value.
		 * \param text The value.
		 * \return The print block instance.
		 */
		template <typename T>
		const PrintBlock& operator<< (const T& text) const
		{
			*stream_ << text;
			return *this;
		}

		template <typename T>
		const PrintBlock& print(const T& text) const
		{
			return (*this << text);
		}

		const PrintBlock& print(const std::string& text) const;

		template <typename ...T>
		const PrintBlock& print(const std::string& format, const T&... args) const
		{
			return print(Poco::format(format, std::forward<const T&>(args)...));
		}

		/**
		 * \brief Changes the current color of the font.
		 * \param color The font color.
		 * \return The print block instance.
		 */
		const PrintBlock& operator<< (ConsoleColor color) const;

		/**
		 * \brief Changes he current color of the font.
		 * \param color The font color.
		 * \return The print block instance.
		 */
		const PrintBlock& operator<< (ConsoleColorPair color) const;

		/**
		 * \brief Prints the current local time.
		 * The format will be HH:MM:SS.
		 * \return The print block instance.
		 */
		const PrintBlock& addTime() const;

		/**
		 * \brief Prints a line break.
		 * \return The print block instance.
		 */
		const PrintBlock& nextLine() const;

		/**
		 * \brief Resets the current line.
		 * \param wipe If true, the line will be erased,
		 * otherwise only the cursor will be set to the beginning of the line.
		 */
		const PrintBlock& clearLine(bool wipe = true) const;

		/**
		 * \brief Flushes the current console buffer.
		 */
		const PrintBlock& flush() const;

		/**
		 * \brief Resets the font color.
		 */
		const PrintBlock& resetColor() const;
		
		const PrintBlock& setColor(ConsoleColor color) const;

	private:
		std::ostream* stream_;
	};

	/**
	 * \brief A static abstraction class for the console/terminal.
	 * These functions are not thread-safe and should not be used in concurrent way!
	 */
	class Console
	{
	public:
		Console() = delete;
		~Console() = delete;
		Console(const Console& rhs) = delete;
		Console(Console&& rhs) = delete;

		Console& operator=(const Console& rhs) = delete;
		Console& operator=(Console&& rhs) = delete;

		/**
		 * \brief Changes the color of the font in the console.
		 * \param foreground The new foreground color.
		 * \param background The new background color.
		 */
		static void setColor(ConsoleColor foreground, ConsoleColor background = ConsoleColor::Black);

		/**
		 * \brief Changes the color of the font in the console.
		 * \param color The new back- and foreground color.
		 */
		static void setColor(ConsoleColorPair color);

		/**
		 * \brief Changes the color of the font in the console back to the default value.
		 */
		static void resetColor();

		/**
		 * \brief Returns an ANSI color escape code for the terminal.
		 * Only useful for Unix systems.
		 * \param color The color, for which the ANSI color escape code will be returned.
		 * \return The ANSI color escape code.
		 */
		static std::string getUnixConsoleCode(ConsoleColor color);

		/**
		 * \brief Creates a print block for the console for console output.
		 * \return The shared_ptr for a newly created print block.
		 */
		static PrintBlock print();

		/**
		 * \brief Resets the current line.
		 * \param wipe If true, the line will be erased,
		 * otherwise only the cursor will be set to the beginning of the line.
		 */
		static void clearLine(bool wipe = true);

		/**
		 * \brief Prints a line break.
		 */
		static void nextLine();
	};
}
