#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <chrono>

template <class Clock>
void
display_precision()
{
	typedef std::chrono::duration<double, std::nano> NS;
	NS ns = typename Clock::duration(1);
	std::cout << ns.count() << " ns\n";
}

template< size_t n , size_t t >
class FPS_Counter{
public:
	FPS_Counter(){}
	FPS_Counter& push_back(float new_time){		
		times.push_back(new_time);
		average += new_time;
		while (times.size() > MAX) {			
			average -= times.front();
			times.pop_front();			
		}	
		return *this;
	}
	float getFPS(){
		if ( !times.empty() && average > 0 )
			return ( 1 / ( average / times.size() ) ) * t;
		else
			return 0.0f;
	}
	void print_average(){
		std::cout << "Average : " << average << endl;
	}

private:
	std::deque<float> times;
	const size_t MAX{ n };
	float average{ 0.0 };
};


#endif