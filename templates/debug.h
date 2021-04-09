string to_string(const char& c){return string(1, c);}
string to_string(const string& s){return '"'+s+'"';}
string to_string(const char* s){return to_string((string)s);}
string to_string(const bool& b){return (b?"true":"false");}
string to_string(const vector<bool>& v,const string& sep=" ") {
	string s = "[";
	for (int i=0; i<v.size(); i++) {if (i){s += sep;} s += to_string(v[i]);}
	return s + "]";
}
template <size_t N> string to_string(const bitset<N>& v) {
	string s = "[";
	for (size_t i=0; i<N; i++) s += v[i] ? '1' : '0';
	return s + "]";
}
template <class T1,class T2> string to_string(const pair<T1, T2>& p, const string& sep=",");
template <class T> string to_string(const T& v, const string& sep=" ") {
	bool first = true; string s = "[";
	for (const auto &x: v) {
		if (!first) s += sep;
		else first = false;
		s += to_string(x);
	}
	return s + "]";
}
template <class T> string to_string(const T& v, const int& sz, const string& sep=" ") {
	string s = "[";
	for (int i=0; i<sz; i++) {if (i){s += sep;} s += to_string(v[i]);}
	return s + "]";
}
template <class T1,class T2> string to_string(const pair<T1,T2>& p, const string& sep) {return "(" + to_string(p.first) + sep + to_string(p.second) + ")";}


void DBG() { cerr << '}' << endl; }
template<class H, class... T> void DBG(H h, T... t) {
	cerr << to_string(h); if (sizeof...(t)) cerr << ", ";
	DBG(t...); }

#define debug(...) cerr << "{" << #__VA_ARGS__ << "}: {", DBG(__VA_ARGS__)
#define debug1(obj, sz) cerr << #obj << ": " << to_string(obj, sz) << endl;
#define debug2(obj, sz1, sz2) cerr << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) cerr << to_string(obj[i], sz2) << endl;
#define debug3(obj, sz1, sz2, sz3) cerr << "-----" << #obj << "-----\n"; for (int i=0; i<sz1; i++) {for (int j=0; j<sz2; j++) cerr << to_string(obj[i][j], sz3) << " "; cerr << endl;}

