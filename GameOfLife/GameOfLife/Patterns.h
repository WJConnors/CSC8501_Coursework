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

	constexpr pair<int, int> glider2Move[4]{
		{0,-1}, {0,0}, {1,0}, {0,0}
	};
	constexpr int glider2_1[9]{
		1,0,0,
		1,0,1,
		1,1,0
	};
	constexpr int glider2_2[9]{
		0,0,1,
		1,1,0,
		0,1,1
	};
	constexpr int glider2_3[9]{
		0,1,0,
		1,0,0,
		1,1,1
	};
	constexpr int glider2_4[9]{
		1,0,1,
		1,1,0,
		0,1,0
	};
	constexpr const int* gliders2[4] = {
		glider2_1,
		glider2_2,
		glider2_3,
		glider2_4
	};

	constexpr pair<int, int> glider3Move[4]{
		{-1,0}, {0,0}, {0,-1}, {0,0}
	};
	constexpr int glider3_1[9]{
		1,1,1,
		1,0,0,
		0,1,0
	};
	constexpr int glider3_2[9]{
		0,1,0,
		1,1,0,
		1,0,1
	};
	constexpr int glider3_3[9]{
		1,1,0,
		1,0,1,
		1,0,0
	};
	constexpr int glider3_4[9]{
		0,1,1,
		1,1,0,
		0,0,1
	};
	constexpr const int* gliders3[4] = {
		glider3_1,
		glider3_2,
		glider3_3,
		glider3_4
	};

	constexpr pair<int, int> glider4Move[4]{
		{0,1}, {0,0}, {-1,0}, {0,0}
	};
	constexpr int glider4_1[9]{
		0,1,1,
		1,0,1,
		0,0,1
	};
	constexpr int glider4_2[9]{
		1,1,0,
		0,1,1,
		1,0,0
	};
	constexpr int glider4_3[9]{
		1,1,1,
		0,0,1,
		0,1,0
	};
	constexpr int glider4_4[9]{
		0,1,0,
		0,1,1,
		1,0,1
	};
	constexpr const int* gliders4[4] = {
		glider4_1,
		glider4_2,
		glider4_3,
		glider4_4
	};

	constexpr int sc1_x_size{ 4 };
	constexpr int sc1_y_size{ 5 };
	constexpr pair<int, int> sc1Move[4]{
		{1,-1}, {0,0}, {-1,-1}, {0,0}
	};
	constexpr int sc1_1[20]{
		0,1,0,0,1,
		1,0,0,0,0,
		1,0,0,0,1,
		1,1,1,1,0
	};
	constexpr int sc1_2[20]{
		0,1,1,0,0,
		1,1,0,1,1,
		0,1,1,1,1,
		0,0,1,1,0
	};
	constexpr int sc1_3[20]{
		1,1,1,1,0,
		1,0,0,0,1,
		1,0,0,0,0,
		0,1,0,0,1
	};
	constexpr int sc1_4[20]{
		0,0,1,1,0,
		0,1,1,1,1,
		1,1,0,1,1,
		0,1,1,0,0
	};
	constexpr const int* scs1[4] = {
		sc1_1,
		sc1_2,
		sc1_3,
		sc1_4
	};

	constexpr int sc2_x_size{ 4 };
	constexpr int sc2_y_size{ 5 };
	constexpr pair<int, int> sc2Move[4]{
		{1,1}, {0,0}, {-1,1}, {0,0}
	};
	constexpr int sc2_1[20]{
		1,0,0,1,0,
		0,0,0,0,1,
		1,0,0,0,1,
		0,1,1,1,1
	};
	constexpr int sc2_2[20]{
		0,0,1,1,0,
		1,1,0,1,1,
		1,1,1,1,0,
		0,1,1,0,0
	};
	constexpr int sc2_3[20]{
		0,1,1,1,1,
		1,0,0,0,1,
		0,0,0,0,1,
		1,0,0,1,0
	};
	constexpr int sc2_4[20]{
		0,1,1,0,0,
		1,1,1,1,0,
		1,1,0,1,1,
		0,0,1,1,0
	};
	constexpr const int* scs2[4] = {
		sc2_1,
		sc2_2,
		sc2_3,
		sc2_4
	};

	constexpr int sc3_x_size{ 5 };
	constexpr int sc3_y_size{ 4 };
	constexpr pair<int, int> sc3Move[4]{
		{-1,1}, {0,0}, {-1,-1}, {0,0}
	};
	constexpr int sc3_1[20]{
		0,1,1,1,
		1,0,0,1,
		0,0,0,1,
		0,0,0,1,
		1,0,1,0
	};
	constexpr int sc3_2[20]{
		0,1,0,0,
		1,1,1,0,
		1,0,1,1,
		0,1,1,1,
		0,1,1,0
	};
	constexpr int sc3_3[20]{
		1,1,1,0,
		1,0,0,1,
		1,0,0,0,
		1,0,0,0,
		0,1,0,1
	};
	constexpr int sc3_4[20]{
		0,0,1,0,
		0,1,1,1,
		1,1,0,1,
		1,1,1,0,
		0,1,1,0
	};
	constexpr const int* scs3[4] = {
		sc3_1,
		sc3_2,
		sc3_3,
		sc3_4
	};

	constexpr int sc4_x_size{ 5 };
	constexpr int sc4_y_size{ 4 };
	constexpr pair<int, int> sc4Move[4]{
		{0,0}, {0,0}, {0,0}, {0,0}
	};
	constexpr int sc4_1[20]{
		0,1,0,1,
		1,0,0,0,
		1,0,0,0,
		1,0,0,1,
		1,1,1,0
	};
	constexpr int sc4_2[20]{
		0,1,1,0,
		1,1,1,0,
		1,1,0,1,
		0,1,1,1,
		0,0,1,0
	};
	constexpr int sc4_3[20]{
		1,0,1,0,
		0,0,0,1,
		0,0,0,1,
		1,0,0,1,
		0,1,1,1
	};
	constexpr int sc4_4[20]{
		0,1,1,0,
		0,1,1,1,
		1,0,1,1,
		1,1,1,0,
		0,1,0,0,
	};
	constexpr const int* scs4[4] = {
		sc4_1,
		sc4_2,
		sc4_3,
		sc4_4
	};
}