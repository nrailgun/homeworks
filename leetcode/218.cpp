// Not the best solution, but using map is OK.

class point_t {
public:
	int x, y;
	bool end;
	point_t(int x = 0, int y = 0, bool end = false) : x(x), y(y), end(end) {}

	bool operator<(const point_t&rhs) const {
		if (x != rhs.x)
			return x < rhs.x;
		if (y != rhs.y)
			return y > rhs.y;
		return !end && rhs.end;
	}
};

class Solution {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		int n = buildings.size();
		// Can't use multiset, `erase` will erase all with same value
		// multiset<int> hs;
		map<int, int> hs;
		hs[0]++;
		vector<point_t> points(2 * n);

		for (int i = 0; i < n; i++) {
			int l = buildings[i][0];
			int r = buildings[i][1];
			int h = buildings[i][2];

			point_t ps(l, h, false), pe(r, h, true);
			points[2 * i] = ps;
			points[2 * i + 1] = pe;
		}
		sort(points.begin(), points.end());

		vector<pair<int, int>> rv;
		for (int i = 0; i < 2 * n; i++) {
			const point_t &p = points[i];
			if (p.end) {
				int th = hs.rbegin()->first;
				if (--hs[p.y] == 0)
					hs.erase(p.y);
				if (p.y == th && p.y > hs.rbegin()->first) {
					rv.push_back(make_pair(p.x, hs.rbegin()->first));
				}
			}
			else {
				if (p.y > hs.rbegin()->first) {
					rv.push_back(make_pair(p.x, p.y));
				}
				hs[p.y]++;
			}
		}

		vector<pair<int, int>> rv2;
		for (int i = 0; i < rv.size();) {
			int minh = INT_MAX;
			int j = i;
			while (j < rv.size() && rv[j].first == rv[i].first) {
				minh = min(minh, rv[j].second);
				j++;
			}
			rv2.push_back(make_pair(rv[i].first, minh));
			i = j;
		}
		return rv2;
	}
};
