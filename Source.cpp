#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

float Rosenbrok_function(vector <float> X0)
{
	return (100 * pow(X0[1] - pow(X0[0], 2), 2) + pow(1 - X0[0], 2));
}

vector <float> neighborhood_search(vector <float> X0, float delta)
{
	//cout << "neighborhood_search: (" << X0[0] << ", " << X0[1] << ") delta: " << delta << endl;

	vector <float> point_x2_fixed = { X0[0] + delta, X0[1] };
	vector <float> newPoint;

	if (Rosenbrok_function(point_x2_fixed) < Rosenbrok_function(X0))
		newPoint.push_back(point_x2_fixed[0]);
	else
	{
		point_x2_fixed[0] = X0[0] - delta;
		if (Rosenbrok_function(point_x2_fixed) < Rosenbrok_function(X0))
			newPoint.push_back(point_x2_fixed[0]);
		else
			newPoint.push_back(X0[0]);
	}

	vector <float> point_x1_fixed = { newPoint[0], X0[1] + delta };

	if (Rosenbrok_function(point_x1_fixed) < Rosenbrok_function(X0))
		newPoint.push_back(point_x1_fixed[1]);
	else
	{
		point_x1_fixed[1] = X0[1] - delta;
		if (Rosenbrok_function(point_x1_fixed) < Rosenbrok_function(X0))
			newPoint.push_back(point_x1_fixed[1]);
		else
			newPoint.push_back(X0[1]);
	}

	return newPoint;
}

int main()
{
	vector <float> X0 = { -1.1, -1.5 };

	float delta = 1;
	int step_reduction_coef = 2;
	float end_point_param = 0.0000001;

	vector <float> X1 = X0;
	vector <float> X2;
	vector < vector <float> > X_array;
	X_array.push_back(X0);
	bool stopPoint = false;
	bool nextStepFlag = true;

	cout << "Start point: (" << X0[0] << ", " << X0[1] << ") Q(X) = " << Rosenbrok_function(X0) << endl;
	int counter = 0;
	while (delta > end_point_param)
	{
		X1 = neighborhood_search(X1, delta);
		if (X1[0] == X0[0] && X1[1] == X0[1])
		{
			delta = delta / step_reduction_coef;
			cout << "X1 = X0 = (" << X0[0] << ", " << X0[1] << "), new delta: " << delta << endl;
		}
		else if (find(X_array.begin(), X_array.end(), X1) != X_array.end()) {
			delta = delta / step_reduction_coef;
			cout << "same value: (" << X1[0] << ", " << X1[1] << "), new delta: " << delta << endl;
		}
		else {
			X_array.push_back(X1);
			if (counter == 0)
			{
				cout << "iteration " << counter + 1 << ": X = (" << X1[0] << ", " << X1[1] << ") Q(X) = " << Rosenbrok_function(X1) << " delta : " << delta << endl;
				counter++;

			}

			X2 = { X_array[X_array.size() - 1][0] + X_array[X_array.size() - 1][0] - X_array[X_array.size() - 2][0],
				X_array[X_array.size() - 1][1] + X_array[X_array.size() - 1][1] - X_array[X_array.size() - 2][1] };

			X_array.push_back(X2);

			X0 = X1;
			X1 = X2;

			cout << "iteration " << counter + 1 << " (" << X2[0] << ", " << X2[1] << ") Q(X) = " << Rosenbrok_function(X2) << " delta: " << delta << endl;

			counter++;
		}
	}

	cout << "\n\nend of program\nX = (" << X1[0] << ", " << X1[1] << ")\nQ(X) = " << Rosenbrok_function(X1) << "\ndelta = " << delta << endl;

	return 0;
}