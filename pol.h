#include <iostream>
#include <cmath>
#include <string>

using namespace std;

const double EPS = 0.000001;
struct Stack{
    double number;
    char znak;
    Stack* next;
};
Stack *top1 = nullptr, *top2 = nullptr;

void push(Stack* &t, double number, char znak) {
    Stack * p = new Stack;
    p -> number = number;
    p -> znak = znak;
    p -> next = t;
    t = p;
}

Stack pop(Stack* &t) {
    Stack temp = *t;
    t = t -> next;
    return temp;
}

int prior(char s) {
    if (s == '+' || s == '-') {
        return 1;
    }
    if (s == '^') {
        return 3;
    }
    if (s == 'L' || s == 'S' || s == 'C' || s == 'T' || s == 'Q') {
        return 4;
    }
    if (s == '*' || s == '/') {
        return 2;
    }
    if (s == '(') {
        return 0;
    }
}
int f = 0;
void apply(char znak) {
    double b = pop(top1).number;
    double c;
    f = 0;
    if (znak == '+') {
        double a = pop(top1).number;
        c = a + b;
    }
    if (znak == '-') {
        double a = pop(top1).number;
        c = a - b;
    }
    if (znak == '^') {
        double a = pop(top1).number;
        c = pow(a, b);
    }
    if (znak == 'S') {
        c = sin(b);
    }
    if (znak == 'C') {
        c = cos(b);
    }
    if (znak == 'T') {
        c = tan(b);
    }
    if (znak == 'L') {
        if (b > 0) {
            c = log(b);
        } else {
            f = 1;
        }
    }
    if (znak == 'Q') {
        if (b >= 0) {
            c = sqrt(b);
        } else {
            f = 1;
        }
    }
    if (znak == '*') {
        double a = pop(top1).number;
        c = a * b;
    }
    if (znak == '/' && abs(b) >= EPS) {
        double a = pop(top1).number;
        c = a / b;
    } else if (znak == '/' && abs(b) < EPS) {
        f = 1;
    }
    if (f == 0) {
        push(top1, c , '@');
    }
}

int error(string s) {
    int a = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            a++;
        }
        if (s[i] == ')') {
            a--;
        }
    }
    if (a != 0) {
        return 1;
    }
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == 'S' || s[i] == 'C' || s[i] == 'T'
|| s[i] == 'Q' || s[i] == 'L') && s[i + 1] != '(' ) {
            return 1;
        }
    }
    int c = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '+' || s[i] == '*' || s[i] == '-' || s[i] == '/' || s[i] == '^') {
            if (c == 0) {
                c++;
            } else {
                return 1;
            }
        } else {
            c = 0;
        }
    }
    if (s[0] == '*' || s[0] == '/' || s[0] == '^') {
        return 1;
    }
    if (s[s.size() - 1] == '*' || s[s.size() - 1] == '/' ||
        s[s.size() - 1] == '+' || s[s.size() - 1] == '-' ||
        s[s.size() - 1] == '^' ) {
        return 1;
    }
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '*' && s[i] != '/' && s[i] != '+'
            && s[i] != '-' && s[i] != ')' && s[i] != '('
&& s[i] != '0' && s[i] != '1' && s[i] != '2'
&& s[i] != '3' && s[i] != '4' && s[i] != '5'
&& s[i] != '6' && s[i] != '7' && s[i] != '8'
&& s[i] != '9' && s[i] != 'S' && s[i] != 'C'
&& s[i] != 'T' && s[i] != 'Q' && s[i] != '^'
&& s[i] != 'L' && s[i] != '.') {
            return 1;
        }
    }
    s += ' ';
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(' && s[i + 1] == ')') {
            return 1;
        }
        if (s[i] == ')' && s[i + 1] == '(') {
            return 1;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(' && (s[i + 1] == '*'
|| s[i + 1] == '/' || s[i + 1] == '-' || s[i + 1] == '^')) {
            return 1;
        } else if (s[i+1] == ')' && (s[i] == '+'
|| s[i] == '*' || s[i] == '/' || s[i] == '-' || s[i] == '^')) {
            return 1;
        }
    }
}
static const size_t npos = -1;
void replaceall(string &s, string s1, string s2) {
        size_t ind = s.find(s1);
        while (ind != npos) {
            s.replace(ind, s1.size(), s2);
            ind = s.find(s1, ind + s2.size());
        }
}
int calc(string s, double &rez) {
    string ss;
    if (s[0] == '-') {
        s = '0' + s;
    }

    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '(' && s[i + 1] == '-') {
            ss = ss + '(';
            ss += '0';
        } else {
            ss = ss + s[i];
        }
    }
    ss += s[s.size() - 1];
    s = ss;
    replaceall(s, "sin", "S");
    replaceall(s, "cos", "C");
    replaceall(s, "tg", "T");
    replaceall(s, "sqrt", "Q");
    replaceall(s, "ln", "L");

    if (error(s) == 1) {
        return -1;
    }
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            double x = 0;
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                x = x * 10 + (s[i] - '0');
                i++;
            }
            if (s[i] == '.') {
                i++;
                double y = 0;
                int m = 1;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                    y +=(s[i]-'0')/(pow(10, m));
                    m +=  1;
                    i++;
                }
                x += y;
            }
            push(top1, x, '@');
            i--;
        } else if (s[i] == '(') {
            push(top2, 0.0, s[i]);
        } else if (s[i] == ')') {
            while ((*top2).znak != '(') {
                apply(pop(top2).znak);
                if (f != 0) {
                    return -1;
                }
            }
            pop(top2);
        } else {
            while (top2 != nullptr && prior(s[i]) <= prior((*top2).znak)) {
                apply(pop(top2).znak);
                if (f != 0) {
                    return -1;
                }
            }
            push(top2, 0.0, s[i]);
        }
    }
    while (top2 != nullptr) {
        apply(pop(top2).znak);
        if (f != 0) {
            return -1;
        }
    }
    rez = pop(top1).number;
    top1 = nullptr, top2 = nullptr, top1 = nullptr;
    return 0;
}
double rez = 0;

