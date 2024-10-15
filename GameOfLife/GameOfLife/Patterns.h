#pragma once
#include <array>

using namespace std;

namespace Patterns
{
	//============Still Lifes===================
	constexpr int block_x_size{ 2 };
	constexpr int block_y_size{ 2 };
	constexpr int block[4]{
	1,1,
	1,1
	};

	constexpr int beehive1_x_size{ 3 };
	constexpr int beehive1_y_size{ 4 };
	constexpr int beehive1[12]{
	 0,1,1,0,
	 1,0,0,1,
	 0,1,1,0
	};

	constexpr int beehive2_x_size{ 4 };
	constexpr int beehive2_y_size{ 3 };
	constexpr int beehive2[12]{
		0,1,0,
		1,0,1,
		1,0,1,
		0,1,0
	};

	//============Oscillators===================
	constexpr int blinker_size{ 3 };
	constexpr int blinker1[9]{
		0,0,0,
		1,1,1,
		0,0,0
	};

	constexpr int blinker2[9]{
		0,1,0,
		0,1,0,
		0,1,0
	};

	constexpr int toad_size{ 4 };
	constexpr int toad1_1[16]{
		0,0,0,0,
		0,1,1,1,
		1,1,1,0,
		0,0,0,0
	};

	constexpr int toad1_2[16]{
		0,0,1,0,
		1,0,0,1,
		1,0,0,1,
		0,1,0,0
	};

	constexpr int toad2_1[16]{
		0,1,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,1,0
	};

	constexpr int toad2_2[16]{
		0,1,1,0,
		1,0,0,0,
		0,0,0,1,
		0,1,1,0
	};

	//============Spaceships===================
	constexpr int glider_size{ 3 };
	constexpr pair<int, int> glider1Move[4]{
		{1,0}, {0,0}, {0,1}, {0,0}
	};
	constexpr int glider1_1[9]{
		0,1,0,
		0,0,1,
		1,1,1
	};
	constexpr int glider1_2[9]{
		1,0,1,
		0,1,1,
		0,1,0
	};
	constexpr int glider1_3[9]{
		0,0,1,
		1,0,1,
		0,1,1
	};
	constexpr int glider1_4[9]{
		1,0,0,
		0,1,1,
		1,1,0
	};
	constexpr const int* gliders1[4] = {
		glider1_1,
		glider1_2,
		glider1_3,
		glider1_4
	};

}