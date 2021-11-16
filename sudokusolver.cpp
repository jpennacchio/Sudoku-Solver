
#include <chrono>
#include <iostream>
#include "puzzle.hpp"
//nothing in this file references the size of the puzzle. Need to see where read-in size.
//shouldn't need to modify generic matrix.cpp and .hpp files
//will need to make changes to puzzle files, though.  

int main (int argc, char** argv) {
  auto start= std::chrono::high_resolution_clock::now();
	Puzzle p;
	if (argc<2) {
	  std::cout<<"Didn't input a puzzle."<<std::endl;
	  return -1;
	}
	p.read_from_file (argv [1]);
	std::cout<<"Starting to solve."<<std::endl;
	if(p.is_square()== true) {

	if (p.solve () == true) {
	  std::cout << "Solution is:"<<std::endl;
	  std::cout<<p<<std::endl;
	  std::cout<<p.num_guesses_ventured<<std::endl;
 auto elapsed= std::chrono::high_resolution_clock::now()-start;
auto  microseconds=std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
 auto elapsed_secs=microseconds/1000000.000;
 std:: cout<<elapsed_secs<<std::endl;
	}//end p.solve=true loop
	else  {
	  std::cout<<"Matrix has no solution."<<std::endl;
	  std::cout<<"If you forgot one entry, it treats the last entry as zero, and will check solution for that matrix."<<std::endl;
	}//end else for p.solve=true
     
	}//end if p.is_square loop
	else {
	  std::cout<<"Puzzle not square."<<std::endl;
	}//end else p.is_square


	return 0;

}


