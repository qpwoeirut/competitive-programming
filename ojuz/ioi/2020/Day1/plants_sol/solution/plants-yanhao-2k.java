import java.util.TreeMap;
import java.util.ArrayList;

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
	int[] ans;
	int[] lt;
	int[] rg;
	int[][] jump_lt;
	int[][] jump_rg;
	int k_global;
	segtree s = new segtree();
	int ctr = 0;
	int n;
	int[] permutation;
	int blocking(int rg, int k) {
		int lt = rg - k + 1;
		if(lt<0) {
			int p = s.find_zero(1, lt+n, n-1);
			if(p!=-1) {
				return p;
			}
			return s.find_zero(1,0,rg);
		} else {
			return s.find_zero(1,Math.max(0,lt),rg);
		}
	}

	void pull(int idx, int k) {
		int x;
		while((x=blocking(idx,k))!=idx) {
			pull(x,k);
		}
		permutation[idx] = ctr;
		ctr++;
		// decrement the k values before it, and push value in
		if(idx >= k-1) {
			s.update(1, idx-(k-1), idx, -1);
		} else {
			s.decr(0, idx);
			s.decr(idx-(k-1)+n, n-1);
		}
		s.update(1, idx, idx, 1<<29);
	}

	void init(int k, int[] r) {
		k_global = k;
		s.build(r);
		n = r.length;
		lt = new int[n+1];
		rg = new int[n+1];
		permutation = new int[n];
		while(ctr<n) {
			int p = s.find_zero(1,0,n-1);
			assert(p!=-1);
			pull(p,k);
		}
		TreeMap<Integer, Integer> m = new TreeMap<>();
		for (int i=0; i<k; i++) {
			m.put(permutation[i], i);
		}
		m.put(1<<20, n);
		ans = new int[n+1];
		for(int i=0; i<n; i++) {
			rg[i] = m.higherEntry(permutation[i]).getValue();
			lt[(i+k-1)%n] = m.higherEntry(permutation[(i+k-1)%n]).getValue();
			m.remove(permutation[i]);
			m.put(permutation[(i+k)%n], (i+k)%n);
		}
		jump_lt = new int[18][n];
		jump_rg = new int[18][n];
		for(int i=0; i<n; i++) {
			jump_lt[0][i] = lt[i]==n ? 0 : (i+n-lt[i])%n;
			jump_rg[0][i] = rg[i]==n ? 0 : (rg[i]+n-i)%n;
		}
		for(int i=1; i<18; i++) {
			for(int j=0; j<n; j++) {
				jump_lt[i][j] = jump_lt[i-1][j] + jump_lt[i-1][(j+n-jump_lt[i-1][j])%n];
				jump_rg[i][j] = jump_rg[i-1][j] + jump_rg[i-1][(j+n+jump_rg[i-1][j])%n];
				if(jump_lt[i][j]>n) {
					jump_lt[i][j] = 0;
				}
				if(jump_rg[i][j]>n) {
					jump_rg[i][j] = 0;
				}
			}
		}		
	}
	
	int compare_plants(int x, int y) {
		// check for the direct x->y path
		int z = x;
		for(int i=17; i>=0; i--) {
			if(jump_rg[i][z] < y-z) {
				z = z + jump_rg[i][z];
			}
		}
		if(permutation[z] < permutation[y] && (y-z+n)%n < k_global) return 1;
		// direct y->x path
		z = y;
		for(int i=17; i>=0; i--) {
			if(jump_lt[i][z] < z-x) {
				z = z - jump_lt[i][z];
			}
		}
		if(permutation[z] < permutation[x] && (z-x+n)%n < k_global) return -1;
		
		// look for x->y wraparounds
		z = x;
		for(int i=17; i>=0; i--) {
			if(jump_lt[i][z] < (z+n-y)%n) {
				z = (z + n - jump_lt[i][z])%n;
			}
		}
		if(permutation[z] < permutation[y] && (z-y+n)%n < k_global) return 1;
		
		// look for y->x wraparounds
		z = y;
		for(int i=17; i>=0; i--) {
			if(jump_rg[i][z] < (x+n-z)%n) {
				z = (z + jump_rg[i][z])%n;
			}
		}
		if(permutation[z] < permutation[x] && (x-z+n)%n < k_global) return -1;
		
		return 0;
	}
}
