#include "t_example.h"

TExample::TExample() {}
TExample::~TExample() {}

void TExample::_process(double delta) {}

void TExample::_bind_methods() {}

void TExample::_ready()
{
    UtilityFunctions::print("hello world");
}