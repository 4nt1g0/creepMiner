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

#include "mining/MinerConfig.hpp"

namespace Burst
{
	class Setup
	{
	public:
		static bool setup(MinerConfig& config);

	private:
		static const std::string exit;
		static std::string readInput(const std::vector<std::string>& options, const std::string& header,
			const std::string& defaultValue, int& index);

		static bool chooseProcessorType(std::string& processorType);
		static bool chooseCpuInstructionSet(std::string& instructionSet);
		static bool chooseGpuPlatform(int& platformIndex);
		static bool chooseGpuDevice(int platformIndex, int& deviceIndex);
		static bool choosePlots(std::vector<std::string>& plots);
		static bool chooseBufferSize(unsigned& memory);
	};
}
