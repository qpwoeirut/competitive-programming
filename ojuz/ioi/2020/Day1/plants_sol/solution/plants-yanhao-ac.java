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
        assert(v.length<(1<<n_bits));
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

    void decr(int left, int right) {
        node = 1;
        while(node != 0) {
            if(right>=high(node) && left<=low(node)) {
                lazyadd[node]--;
                while(node%2==0) {
                    arr[node/2] = Math.min(arr[node]+lazyadd[node], arr[node+1]+lazyadd[node+1]);
                    node = node/2;
                }
                node--;
            } else if(right<low(node) || left>high(node)) {
                while(node%2==0) {
                    arr[node/2] = Math.min(arr[node]+lazyadd[node], arr[node+1]+lazyadd[node+1]);
                    node = node/2;
                }
                node--;
            } else {
                node = node*2+1;
            }
        }
    }

    void pt_update(int x) {
        x += (1<<n_bits);
        arr[x] = (int)1e9;
        while(x!=0) {
            arr[x/2] = Math.min(arr[x]+lazyadd[x], arr[x^1]+lazyadd[x^1]);
            x = x/2;
        }
    }

    int find_zero() {
        node = 1;
        lazy = 0;
        if(lazyadd[1] + arr[1]!=0) return -1;
        while(node < (1<<n_bits)) {
            lazy += lazyadd[node];
            node *= 2;
            if(lazy + lazyadd[node] + arr[node] != 0) node++;
        }
        return node-(1<<n_bits);
    }
};

class plants {
	final int n_max = (int)2e5+5;
	int[] p_lt = new int[n_max];
	int[] p_rg = new int[n_max];
	int[] stash = new int[n_max]; // a manual queue
	int[] tallest = new int[n_max];
	int[] shortest = new int[n_max];
	void lexi_smallest(int k, int[] r, int[] ptr, int[] ord) {
		segtree s = new segtree();
		s.build(r);
		int n = r.length;
		stash[0] = n;
		ord[n] = -1;
		int front = 1;
		int back = 1;
		for(int i=0; i<r.length; i++) {
			int p = s.find_zero();
			while(p==-1) {
				s.decr(stash[front]-k+1+n, n-1);
				front++;
				p = s.find_zero();
			}
			ord[p] = i;
			s.pt_update(p);
			if(p<k-1) {
				s.decr(0, p);
				stash[back] = p;
				back++;
			} else {
				s.decr(p-k+1, p);
			}
			ptr[p] = ord[stash[front-1]];
		}
	}
	
	void init(int k, int[] r) {
		lexi_smallest(k, r, p_lt, tallest);
		for(int i=0; i<r.length; i++) {
			r[i] = k-1-r[i];
		}
		lexi_smallest(k, r, p_rg, shortest);
	}

	int compare_plants(int x, int y) {
		if(x>y) return -compare_plants(y,x);
		if(tallest[x]>tallest[y] || p_rg[y]>=shortest[x]) return -1;
		if(shortest[x]>shortest[y] || p_lt[y]>=tallest[x]) return 1;
		return 0;
	}
}