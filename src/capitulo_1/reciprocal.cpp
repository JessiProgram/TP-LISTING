#include <cassert>
#include "reciprocal.hpp"

double reciprocal(int i){
	//no debe ser cero
	assert(i != 0);
	return 1.0 / i;
}