#ifndef PUZZLE_HPP_
#define PUZZLE_HPP_

#include <iostream>
#include <vector>
#include <assert.h>
#include <exception>
#include <cstdlib>
#include "matrix.hpp"
#include <set>
#include <ctime>
// where the class definition goes

#include <assert.h>
#include <cstdint>
using int64=std::uint64_t;
using SetPos=std::vector<std::vector<int64>>;

//Brand New Bitwise Operations for the Sudoku Solver to replace insert, erase, and find
inline int64 hat (int n) {

  return static_cast<int64>(1)<<(n-1);
} 
inline int dehat (int64 nhat) {
  int n=1;
  int64 p=1;
  for (int counter=0; counter<64; counter++) {
    if((nhat&p)==0) {
      nhat=nhat/2;
      n++;
    }
    else {
      return n;
    }
  }//end for
    return 0;
}
  
inline int64 insert (int64 & S, int n) {
  return (S=hat(n) | S);
}

inline int64 erase (int64 & S, int n) {
  return (S=(~hat(n)) &S);
}

inline bool find (int64 S, int n) {
  return hat(n) &S;
}
inline int64 EmptySet () {
  return static_cast<int64> (0);

}
inline int num_ones(int64 V) {
  int count=0;
  while(V>0) {
    if (V&1) {
      ++count;
    }
    V>>=1;
  }//end while
  return count;
}

class Puzzle{
public:
  int num_guesses_ventured = 0;
	Matrix playfield;

  void read_from_file  (std::string filename) {
    std::ifstream fin (filename.c_str());

      if (!fin.is_open())
	   {
           std::cout << "did not find file named 'sudoku.txt'" << std::endl;
				exit(-1);
       }
      //This consists of the overloaded operator from matrix.hpp, and here the matrix is appropriately read in.
	      fin >>playfield;

	}

  friend std::ostream& operator<<(std::ostream & fout, const Puzzle & P)  {

	  fout<<P.playfield;
		return fout;
	}


	int num_emptysquares() const{
		int num = 0;
		//use playfield.num_rows() instead of 9. 
		for (unsigned int a=0; a<playfield.num_rows(); a++) {
		  for (unsigned int b=0; b<playfield.num_rows(); b++) {
				if (playfield.entry(a,b) == 0) {
					num ++;
				}
			}
		}
		return num;
	}

	void enter_number(int a, int b, int num_to_enter)
	{
		playfield.set_entry(a,b,num_to_enter);
	}

	bool solve ();


  //Don't need to copy possibilities vectors; Find all vectors as arguments, and pass by const reference whenever possible
  int hardcode (SetPos const & possibilities);
 SetPos softcode_empty_squares () const;
 SetPos softcode_all_squares () const;
  void weedout (SetPos & possibilities) const;
  void strike_from_box (int m, int n, int num_to_strike,SetPos & possibilities) const;
  void strike_from_column (int b, int num_to_strike, SetPos & possibilities) const;
  void strike_from_row (int a, int num_to_strike,SetPos & possibilities) const;
  bool venture_guess (SetPos const & possibilities);
 bool venture_guess_9 (SetPos const & possibilities);
  //Function for the minimum number of possibilities
  std::tuple <int, int> ind_min_num_possibilities (SetPos const & possibilities);
	bool is_solved () const;
	bool is_consistent() const;
  bool is_square() const;
  bool is_perfect_square() const;
  bool find_empty_possibilities_and_empty_squares(SetPos const & possibilities) const;


	bool check_row_consistency (unsigned int a) const;
	bool check_column_consistency (unsigned int b) const;
	bool check_box_consistency (unsigned int p, unsigned int q) const;
};




//void pause();
//
//void print(set< int > S);



#endif /* PUZZLE_HPP_ */



