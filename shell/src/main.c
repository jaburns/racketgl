#include <linmath.h>

typedef struct FloatPair
{
    float first;
    float second;
}
FloatPair;

__declspec(dllexport) float add_floats(FloatPair pair)
{
    return pair.first + pair.second;
}