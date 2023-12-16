#include <utility> // for std::pair

// In C++, the function can return only one value even if that value consists of the array.
// So, we use data structure of std which has two values, aka "Pair"
std::pair<bool, bool> case_only_one_color(char input_RGB, char input_direction, char Sensor_RGB) {
bool L_Flag;
bool R_Flag;

if (input_RGB == Sensor_RGB) {
L_Flag = 1;
R_Flag = 1;
} else {
// The case that input direction is Left and vehicle is located in the right lane
if (input_direction == 'L') {
L_Flag = 1;
R_Flag = 0;
}
// The case that input direction is Right and vehicle is located in the Left lane
else {
R_Flag = 1;
L_Flag = 0;
}
}

return std::make_pair(L_Flag, R_Flag);
}