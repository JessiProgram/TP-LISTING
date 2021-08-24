#include <cassert>
#include "reciproco.hpp"

double reciproco(int i){
	//no debe ser cero
	assert(i != 0);
	return 1.0 / i;
}