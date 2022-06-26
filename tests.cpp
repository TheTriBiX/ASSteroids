#include <iostream>
#include <cassert>
#include "main.cpp"
#include "decl.h"

using namespace sf;
using namespace std;

void test_create_textures() {
	assert(create_textures("data\\fon.jpg") == true);
	assert(create_textures("data\\fon122.jpg") == false);
	cout << "test Ok" << endl;
}