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

	constexpr int beehive1_x_size{ 5 };
	constexpr int beehive1_y_size{ 6 };
	constexpr int beehive1[30]{
	 0,0,0,0,0,0,
	 0,0,1,1,0,0,
	 0,1,0,0,1,0,
	 0,0,1,1,0,0,
	 0,0,0,0,0,0
	};

	constexpr int beehive2_x_size{ 6 };
	constexpr int beehive2_y_size{ 5 };
	constexpr int beehive2[30]{
		0,0,0,0,0,
		0,0,1,0,0,
		0,1,0,1,0,
		0,1,0,1,0,
		0,0,1,0,0,
		0,0,0,0,0
	};

	//============Oscillators===================
	constexpr int blinker_size{ 5 };
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

	constexpr int toad_size{ 6 };
	constexpr int toad1_1[36]{
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,1,1,1,0,
		0,1,1,1,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0
	};

	constexpr int toad1_2[36]{
		0,0,0,0,0,0,
		0,0,0,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,0,0,0,
		0,0,0,0,0,0
	};

	constexpr int toad2_1[36]{
		0,0,0,0,0,0,
		0,0,1,0,0,0,
		0,0,1,1,0,0,
		0,0,1,1,0,0,
		0,0,0,1,0,0,
		0,0,0,0,0,0
	};

	constexpr int toad2_2[36]{
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,0,0,
		0,0,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0
	};

}