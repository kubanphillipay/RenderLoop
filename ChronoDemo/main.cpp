#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <deque>
#include "header.h"



const int MAX = 10000;

const float FRAME_RATE = 100.0f; // In  Frames per second
const float FRAME_TIME = 1000000.0f / FRAME_RATE; // MS per frame

const long long SLEEP_MS = 1;

//Time in milli seconds, stored in a float
typedef std::chrono::duration<float,std::ratio<1,1000000>> fmilli;

//constexpr float FRAME_TIME{
//	return 1.0 / FRAME_RATE;
//}

namespace GameSpace {

	using namespace std;

	class Game {

	public:
		Game() {
		
		
		}

		void run(){
		
			loop_end_time = chrono::high_resolution_clock::now();
			delta_tick = loop_end_time - loop_begin_time;
			delta_time = (chrono::duration_cast<fmilli>(loop_end_time - loop_begin_time)).count();
		
			if (delta_time < FRAME_TIME){
				sleep_time = fmilli((FRAME_TIME - delta_time));
				sleep = true;
				//cout << "     Sleep For " << sleep_time.count() * 1e-3 << " mS" << endl;
				std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(sleep_time));
				return;
			}
			if ( sleep )
				cout << "     Sleep For " << sleep_time.count() * 1e-3 << " mS" << endl;
			
			cout << "Loop " << ++loop_count << " Do Something...." << endl;

			//std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));


			//cout << "  Loop Start: " << loop_begin_time.time_since_epoch().count() << endl;
			//cout << "  Loop Stop:  " << loop_end_time.time_since_epoch().count() << endl;
			//cout << "  Loop Delta Tick:" << delta_tick.count() << endl;

			
			cout << "  Loop Delta Time:" << delta_time << " ms" << endl;
			myCounter.push_back(delta_time);
			cout << "  Average FPS " << myCounter.getFPS() << " fps";
		

			loop_begin_time = loop_end_time;
			sleep = false;
			return;


		}

	private:
		//chrono::microseconds::rep(FRAME_TIME)
		chrono::high_resolution_clock::time_point loop_begin_time{ chrono::high_resolution_clock::now() - chrono::microseconds(chrono::microseconds::rep(FRAME_TIME)) };
		chrono::high_resolution_clock::time_point loop_end_time;
		chrono::high_resolution_clock::duration delta_tick;
		//chrono::milli delta_time;
		float delta_time;
		FPS_Counter<100,1000000> myCounter;
		int loop_count{ 0 };
		bool sleep{ false };
		fmilli sleep_time;
	};




};



using namespace std;

void main() {

	using namespace GameSpace;

	double processes{ 0.0 };

	display_precision<std::chrono::high_resolution_clock>();
	display_precision<std::chrono::system_clock>();

	auto start_time = chrono::high_resolution_clock::now();
	
	Game myGame;



	int break_count = 500;


	cout << "Begin Test" << endl;


	auto t1 = chrono::high_resolution_clock::now();
	auto t2 = chrono::high_resolution_clock::now();

	cout << "Diff = " << (chrono::duration_cast<chrono::nanoseconds>(t2 - t1)).count() << " us" << endl;

	cout << "End Test" << endl;


	int count = 0;
	while (true){

		
		cout << endl;

		//cout << "Loop Count" << count << endl;
		myGame.run();

		if (++count > MAX)
			break;


		if (!--break_count) {
			cout << "THIS IS A BREAKPOINT";
			cout << endl;
		}

	


	}

	auto stop_time = chrono::high_resolution_clock::now();

	cout << "Total Run time " << chrono::duration_cast<fmilli> (stop_time - start_time).count() << " mS";


	cout << "END OF PROGRAM" << endl;
	cin.get();

	
}
