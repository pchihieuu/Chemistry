#include <iostream>
#include <map>

using namespace std;

long long a[100][100];
long long b[100];
long long B[100];
long long c[100];
map <string, int> mp[100];
int m = 0, n = 0;
string s[100];

void in();
void solve();
void rutGon();

void in(){
    cout << endl;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

string intToString(int n){
    string s = "";
    while (n > 0){
        s = char (n % 10 + '0') + s;
        n /= 10;
    }
    return s;
}

long long ucln(long long a, long long b){
    if (a == 0 && b == 0)
        return 0;
    if (a * b == 0)
        return (a == 0) ? a : b;
    while (a % b != 0){
        long long d =  a % b;
        a = b;
        b = d;
    }
    return b;
}

void swap(int l, int r){
    int t;
    for (int j = 0; j < n; j++){
        t = a[l][j];
        a[l][j] = a[r][j];
        a[r][j] = t;
    }
}

void mul(int i, int k){
    for (int j = 0; j < n; j++)
        a[i][j] *= k;
}

void sub(int i1, int i2){
    for (int j = 0; j < n; j++)
        a[i1][j] -= a[i2][j];
}

void matrix(string str){
    str = str + "+";
    n = 0;
    int k = 1;
    string S = "";
    for (int i = 0; i < str.length(); i++){
        if (str[i] == ' ')
            continue;
        if (str[i] == '+'){
            b[n] = k;
            s[n++] = S;
            S = "";
        } else if (str[i] == '='){
            b[n] = k;
            s[n++] = S;
            S = "";
            k = -1;
        } else
            S = S + str[i];
    }
    for (int i = 0; i < n; i++)
        B[i] = b[i];
    string nt = "";
    for (int V = 0; V < n; V++){
        k = 1;
        nt = "";
        for (int i = s[V].length() - 1; i >= 0; i--){
            if (s[V][i] >= '0' && s[V][i] <= '9'){
                if (k == 1 && s[V].find('(') < s[V].length() && s[V].find('(') >= 0)
                    k = s[V][i] - '0';
                else{
                    int t = 1;
                    int k2 = 0;
                    while (s[V][i] >= '0' && s[V][i] <= '9'){
                        k2 += t * (s[V][i] - '0');
                        t *= 10;
                        i--;
                    }
                    while (s[V][i] >= 'a' && s[V][i] <= 'z'){
                        nt = s[V][i] + nt;
                        i--;
                    }
                    nt = s[V][i] + nt;
                    mp[V][nt] += k * k2 * b[V];
                    // cout << k << "---" << k2 << "---" << nt << endl;
                    nt = "";
                }   
            } else if (s[V][i] >= 'a' && s[V][i] <= 'z'){
                    while (s[V][i] >= 'a' && s[V][i] <= 'z'){
                        nt = s[V][i] + nt;
                        i--;
                    }
                    nt = s[V][i] + nt;
                    mp[V][nt] += k * b[V];
                    nt = "";
                    // cout << k << "---2--   " << nt << endl;
            } else if (s[V][i] >= 'A' && s[V][i] <= 'Z'){
                nt = s[V][i] + nt;
                mp[V][nt] = k * b[V];
                nt = "";
            } else if (s[V][i] == '(')
                k = 1;
        }
        // for (map <string, int> :: iterator it = mp[V].begin(); it != mp[V].end(); it++)
        //     cout << it->first << " " << it->second << endl; 
        // cout << "---------------------" << endl;
    }
    map <string, int> M;
    m = 0;
    for (int V = 0; V < n; V++){
        for (map <string, int> :: iterator it = mp[V].begin(); it != mp[V].end(); it++){
            if (M[it->first] != 123){
                for (int j = 0; j < n; j++)
                    a[m][j] = mp[j][it->first];
                m++;
                M[it->first] = 123;
            }
        }
    }
}

void solve(){
    for (int v = 0; v < n - 1; v++){
        int k = m - 1;
        while (a[k][v] == 0)
            k--;
        for (int i = k - 1; i >= v; i--)
            if (a[i][v] == 0){
                swap(i, k);
                k--;
            }
        // in();
        for (int i = m - 1; i >= v + 1; i--)
            if (a[i][v] != 0){
                int t = a[v][v];
                mul(v, a[i][v]);
                mul(i, t);
                sub(i, v);
            }
        // in();
        rutGon();
    }
    // in();
    m = n - 1;

    for (int v = n - 2; v >= 1; v--){
        for (int i = 0; i < v; i++)
            if (a[i][v] != 0){
                int t = a[v][v];
                mul(v, a[i][v]);
                mul(i, t);
                sub(i, v);
            }
        rutGon();
    }
    c[n - 1] = 1;
    for (int i = 0; i < n - 1; i++)
        c[n - 1] *= a[i][i];
    for (int i = 0; i < n - 1; i++)
        c[i] = -c[n - 1] * a[i][n - 1] / a[i][i];
    for (int i = 0; i < n; i++)
        if (c[i] < 0)
            c[i] = -c[i];
    long long k = c[0];
    for (int i = 1; i < n; i++)
        k = ucln(k, c[i]);
    for (int i = 0; i < n; i++)
        c[i] /= k;
    // for (int i = 0; i < n; i++)
    //     cout << c[i] << " ";
}

void rutGon(){
    long long k;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
            if (a[i][j] != 0){
                k = a[i][j];
                break;
            }
        for (int j = 0; j < n; j++)
            if (a[i][j] != 0)
                k = ucln(k, a[i][j]);
        for (int j = 0; j < n; j++)
            a[i][j] /= k;
    }
}

void thanhPhan(map <string, int> m){
    int n = 0;
    for (map <string, int> :: iterator it = m.begin(); it != m.end(); it++)
        if (it->second > 0)
            n++;
    cout << "{";
    int k = 0;
    for (map <string, int> :: iterator it = m.begin(); it != m.end(); it++)
    if (it->second > 0) {
        k++;
        cout <<  it->first << "=" << it->second;
        if (k < n)
            cout << ", ";
    }
    cout << "}";
}

string PTHH(string str){
    matrix(str);
    solve();
    string st = "";
    if (c[0] > 1)
        cout << c[0];
    cout << s[0];
    for (int i = 1; i < n; i++){
        if (B[i] > 0){
            st = st + " + ";
            if (c[i] > 1)
                st = st + intToString(c[i]);
            st = st + s[i];
        } else {
            if (B[i - 1] > 0)
                st = st + " = ";
            if (c[i] > 1)
                st = st + intToString(c[i]);
            st = st + s[i];
            if (i != n - 1)
                st = st + " + ";
        }
    }
    return st;
}

int main(){
    cout << endl;
    string s;
    getline(cin, s);
    cout << PTHH(s);
    cout << endl << endl << " ";
    return 0;
}