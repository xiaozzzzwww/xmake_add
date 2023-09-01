#include <iostream>
#include <Eigen/Dense>

using namespace std;

int main(int argc, char** argv)
{
	
	Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;
    a.setOnes();
    cout << a << endl;
    cout << "hello world!" << endl;
    return 0;
}
