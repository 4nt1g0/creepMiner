// ==========================================================================
// 
// creepMiner - Burstcoin cryptocurrency CPU and GPU miner
// Copyright (C)  2016-2018 Creepsky (creepsky@gmail.com)
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

#include "Message.hpp"

namespace Burst
{
	struct ProgressToken
	{
		std::string character;
		TextType textType;
	};

	struct Progress
	{
		double read;
		double verify;
		double bytesPerSecondRead;
		double bytesPerSecondVerify;
		double bytesPerSecondCombined;
	};

	struct ProgressPrinter
	{
		/**
		* \brief The front delimiter.
		*/
		ProgressToken delimiterFront;

		/**
		* \brief A char that represents the filled part of the progress bar for reading.
		*/
		ProgressToken readDoneChar;

		/**
		* \brief A char that represents the filled part of the progress bar for reading.
		*/
		ProgressToken verifiedDoneChar;

		/**
		* \brief A char that represents the not filled  part of the progress bar for reading.
		*/
		ProgressToken readNotDoneChar;

		/**
		* \brief The end delimiter.
		*/
		ProgressToken delimiterEnd;

		/**
		 * \brief The size of the filled and not filled part of the progressbar combined.
		 */
		size_t totalSize;

		/**
		 * \brief Constructor.
		 */
		ProgressPrinter();

		/**
		 * \brief Prints the progress bar.
		 */
		void print(const Progress& progress) const;

		/**
		* \brief Calculates the proportion of the filled and not filled part of a progress bar.
		* \param progressRead The read progress, where 0 <= progress <= 100.
		* \param progressVerified The verification progress, where 0 <= progress <= 100.
		* \param totalSize The whole size of the progress bar.
		* It will be split it by done and not done (doneSize + notDoneSize = totalSize).
		* \param readSize The proportion of the filled part that was read.
		* \param verifiedSize The proportion of the filled part that was verified.
		* \param notDoneSize The proportion of the not filled part.
		*/
		static void calculateProgressProportions(double progressRead, double progressVerified, size_t totalSize,
												 size_t& readSize, size_t& verifiedSize, size_t& notDoneSize);
	};
}
