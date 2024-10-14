#pragma once
#include <array>

namespace Patterns
{
	//============Still Lifes===================
	constexpr int block_x_size{ 4 };
	constexpr int block_y_size{ 4 };
	constexpr int block[16]{
	0,0,0,0,
	0,1,1,0,
	0,1,1,0,
	0,0,0,0
	};

	constexpr int beehive_x_size = 5;
	constexpr int beehive_y_size = 6;
	constexpr int beehive[30]{
	 0,0,0,0,0,0,
	 0,0,1,1,0,0,
	 0,1,0,0,1,0,
	 0,0,1,1,0,0,
	 0,0,0,0,0,0
	};

	constexpr int rotated_beehive_x_size = 6;
	constexpr int rotated_beehive_y_size = 5;
	constexpr int rotatedBeeHive[30]{
		0,0,0,0,0,
		0,0,1,0,0,
		0,1,0,1,0,
		0,1,0,1,0,
		0,0,1,0,0,
		0,0,0,0,0
	};

	//============Oscillators===================
	constexpr int blinker_x_size = 5;
	constexpr int blinker_y_size = 5;
	constexpr int blinker1[25]{
		0,0,0,0,0,
		0,0,0,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
	};

	constexpr int blinker2[25]{
		0,0,0,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,0,0,0
	};

}