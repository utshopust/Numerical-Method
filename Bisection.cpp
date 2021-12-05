#include<bits/stdc++.h>
using namespace std;
#define MAX_DEGREE 100

string eqn;
int coef[MAX_DEGREE + 1]; //* It can handle an equation of maximum 100 degree

int converter(string num) {
    int res = 0;
    reverse(num.begin(), num.end());
    for (int i = 0; i < num.size(); ++i) {
        res += (int) (num[i] - '0')*pow(10, i);
    }
    return res;
}

double f(double x) {
    double res = 0.0;
    for (int i = 0; i <= MAX_DEGREE; ++i) {
        if (coef[i] == 0) continue;
        res += coef[i]*pow(x, i);
    }
    return res;
}

double bisection(double a, double b, double epsilon = 1e-9) {
    //* at root f(x) = 0
    //* b > a
    //double prevY = 0;
    while (true) {
        double f_a = f(a);
        double f_b = f(b);
        double mid = (a + b)/2;
        double f_mid = f(mid);

        //cout << "a: " << a << "," << f_a << " b: " << b << ","<< f_b << " mid: " << f_mid << "\n";

        //if (fabs(f_mid - prevY) <= epsilon) return mid;
        if (fabs(f_mid) <= epsilon) return mid;
        if (f_mid > 0) {
            if(f_a > 0) a = mid;
            if (f_b > 0) b = mid;

        }
        if (f_mid < 0) {
            if(f_a < 0) a = mid;
            if (f_b < 0) b = mid;
        }
        //prevY = f_mid;
    }
}

int main() {
    //* -4x^4 + 121x^3 - x^2 - 12x + 120
    //* x^3 + 6x^2 + 11x + 6
    getline(cin, eqn);
    string temp = "";
    for (char c : eqn) {
        if (c == ' ') continue;
        temp += c;
    }
    eqn = temp + "+";

    bool sign = true; //* true -> '+', false -> '-'
    bool flag = true; //* true -> coefficient, false -> power
    string currentNum = "";
    string currentPow = "";
    for (int i = 0; i < eqn.size(); ++i) {
        char c = eqn[i];
        //cout << c << " -> " << "  num: "<< currentNum << " , pow: " << currentPow << "\n";
        if (c == 'x') {
            if (i == 0) currentNum = "1";
            else if (eqn[i-1] == '+' or eqn[i-1] == '-') currentNum = "1";
            continue;
        }
        if (c == '^') {
            flag = false;
            continue;
        }
        if (c == '+' or c == '-') {
            flag = true;
            if (eqn[i-1] == 'x') currentPow = "1";
            int x = converter(currentNum);
            int y = converter(currentPow);
            if (sign) coef[y] = x;
            else coef[y] = -x;
            if (c == '+') sign = true;
            else sign = false;
            currentNum = "";
            currentPow = "";
        }
        else {
            if (flag) currentNum += c;
            else currentPow += c;
        }
    }
    //if (sign) coef[converter(currentPow)] = converter(currentNum);
    //else coef[converter(currentPow)] = -converter(currentNum);

    double a, b, epsilon = .00001;
    cin >> a >> b;
    if (f(a)*f(b) >= 0) cout << "f(a) and f(b) have same sign!" << "\n";
    else cout << setprecision(10) << bisection(a, b) << "\n";

    //for (int i = 3; i >= 0; --i) cout << coef[i] << " " << i << "\n";


}
