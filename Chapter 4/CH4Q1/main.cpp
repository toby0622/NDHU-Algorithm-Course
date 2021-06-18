/*
ask user for car and parking lot positions
P = list(map(int,input("Enter parking lot positions:").strip().spilt()))
# let's assume that the maximum position of car is not more than 1000
# initially no car is parked
parked = [0]*1001
# to store the final answer
minSum = 0
# for every parking lot in P
for p in P;
curr_min_car_pos = 1000;
for c in C;
# only check if it is not parked
if parked[c] != 1;
# check for minimum
if(curr_min_car_pos > c):
curr_min_car_pos = c
# update the parked array with the minimum car pos as parked
parked[curr_min_car_pos] =1
minSum +=abs(p-curr_min_car_pos)
print(f"minimumtime to park all cars = {minSum}")
 */

#include <iostream>
using namespace std;

int main() {

}

/*
 * Test Case:
 * parking slot position: 2, 3, 5, 7, 8
 * car position: 1, 2, 3, 4, 5
 * result minimum time: 10
 */