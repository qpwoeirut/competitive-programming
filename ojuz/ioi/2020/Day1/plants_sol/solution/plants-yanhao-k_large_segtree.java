class segtree {
	final int n_bits=18;
	final int inf = (int)1e9;
	int[] arr = new int [1<<(n_bits+1)];
	int[] lazyadd = new int [1<<(n_bits+1)];
    int node = 1;
    int lazy = 0;
	int low(int i) {
		return (i<<(Integer.numberOfLeadingZeros(i)-31+n_bits))-(1<<n_bits);
	}
	int high(int i) {
		return ((i+1)<<(Integer.numberOfLeadingZeros(i)-31+n_bits))-(1<<n_bits)-1;
	}
    void build(int[] v) {
        for(int i=0; i<(1<<n_bits); i++) {
            arr[i+(1<<n_bits)] = (i<v.length ? v[i] : inf);
        }
        for(int i=(1<<n_bits)-1; i>=1; i--) {
            arr[i] = Math.min(arr[2*i], arr[2*i+1]);
        }
        for(int i=0; i<(1<<(n_bits+1)); i++) {
            lazyadd[i] = 0;
        }
    }
    int value(int node) {
        arr[node] += lazyadd[node];
        if(node<(1<<n_bits)) {
            lazyadd[2*node] += lazyadd[node];
            lazyadd[2*node+1] += lazyadd[node];
        }
        lazyadd[node] = 0;
        return arr[node];
    }
    void update(int node, int left, int right, int change) {
        if(right>=high(node) && left<=low(node)) {
            lazyadd[node] += change;
        } else if(right<low(node) || left>high(node)) {
            return;
        } else {
            update(2*node, left, right, change);
            update(2*node+1, left, right, change);
            arr[node] = Math.min(value(node*2), value(node*2+1));
        }
    }

    void decr(int left, int right) {
        update(1, left, right, -1);
    }

    int find_zero(int node, int lt, int rg) {
        if(rg<low(node) || lt>high(node)) {
            return -1;
        }
        if(value(node)!=0) {
            return -1;
        }
        if(node >= (1<<n_bits)) {
            return arr[node]==0 ? node-(1<<n_bits) : -1;
        }
        int x = find_zero(node*2, lt, rg);
        if(x!=-1) return x;
        return find_zero(node*2+1, lt, rg);
    }
};

class plants {
	int[] permutation;
	void init(int k, int[] r) {
		segtree s = new segtree();
		s.build(r);
		int n = r.length;
		permutation = new int[n];
		for(int i=0; i<n; i++) {
			int x = s.find_zero(1, 0, n-1);
			if(x < k - 1) {
				x = Math.max(s.find_zero(1, n-k+x+1, n-1), x);
			}
			s.update(1, x, x, 1<<29);
			permutation[x] = i;
			if(x>=k-1) {
				s.decr(x-k+1, x);
			} else {
				s.decr(0, x);
				s.decr(n-k+x+1, n-1);
			}
		}
	}

	int compare_plants(int x, int y) {
		return (permutation[x]<permutation[y] ? 1 : -1);
	}
}
