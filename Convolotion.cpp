#include<iostream>
#include<vector>
#include<sys/time.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> matrix;

const int N = 100;
const int M = 100;

// Utility Function
void generateRandomImage(matrix &img) {
	srand(time(NULL));
	vi domain = { -1, 0, 1};
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			img[i][j] = domain[rand() % 3];
		}
	}
}


matrix convo(matrix &image, vector<int> &kernel) {
	int n = image.size();   // image size
	int m = image[0].size();

	int f = 3; // filter size
	int s = 1;
	int p = 0;

	int nOut = ((n + (p * 2) - f) / s) + 1;
	int mOut = ((m + (p * 2) - f) / s) + 1;

	matrix featureMap(nOut, vector<int>(mOut, 0));

	for (int i = 0; i + f <= n; ++i) {
		for (int j = 0; j + f <= m; ++j) {


			// without flat kernel
			// int sum = (image[i][j] * kernel[0][0]) + (image[i][j + 1] * kernel[0][1]) + (image[i][j + 2] * kernel[0][2]);
			// sum += (image[i + 1][j] * kernel[1][0]) + (image[i + 1][j + 1] * kernel[1][1]) + (image[i + 1][j + 2] * kernel[1][2]);
			// sum += (image[i + 2][j] * kernel[2][0]) + (image[i + 2][j + 1] * kernel[2][1]) + (image[i + 2][j + 2] * kernel[2][2]);

			// with flat kernel
			int sum = (image[i][j] * kernel[0]) + (image[i][j + 1] * kernel[1]) + (image[i][j + 2] * kernel[2]);
			sum += (image[i + 1][j] * kernel[3]) + (image[i + 1][j + 1] * kernel[4]) + (image[i + 1][j + 2] * kernel[5]);
			sum += (image[i + 2][j] * kernel[6]) + (image[i + 2][j + 1] * kernel[7]) + (image[i + 2][j + 2] * kernel[8]);

			// naive approach
			// int sum = 0;
			// for (int _i = 0; _i < f; ++_i) {
			// 	for (int _j = 0; _j < f; ++_j) {
			// 		sum += (kernel[_i][_j] * image[i + _i][j + _j]);
			// 	}
			// }
			featureMap[i][j] = sum;
		}
	}
	return featureMap;
}


int main() {

	matrix img(N, vector<int>(M));
	generateRandomImage(img);

	vector<vi> kernel = {
		{1, 2, 1},
		{0, 0, 0},
		{ -1, -2, -1}
	};
	vector<int> flatKernel = {1, 2, 1, 0, 0, 0, -1, -2, -1};

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	// Convo Operation
	matrix featureMap = convo(img, flatKernel);

	// Stop measuring time and calculate the elapsed time
	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;

	cout << "Time measured: " << elapsed << " seconds\n";


	// Output Feature map
	for (vector<int> &v : featureMap) {
		for (int &it : v) {
			cout << it << ' ';
		} cout << '\n';
	}

	return 0;
}