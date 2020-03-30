struct dijkstra{
	vector<ll> min_dst;
	vector<vector<P>> G;
	dijkstra(ll n){
		min_dst.resize(n);
		G.resize(n);
	}

	void append(ll u, ll v, ll cost){G[u].push_back(P(v, cost));}
	
	void run(ll s){
		priority_queue<P, vector<P>, greater<P>> que;
		fill(min_dst.begin(), min_dst.end(), -1);
		min_dst[s] = 0;
		que.push(P(0, s));
		
		while(!que.empty()){
			P p = que.top(); que.pop();
			ll at = p.second;
			if(min_dst[at] < p.first){continue;}
			for(ll i = 0; i < G[at].size(); i++){
				ll to = G[at][i].first;
				ll cost = G[at][i].second;
				if(min_dst[to] == -1 || min_dst[at] + cost < min_dst[to]){
					min_dst[to] = min_dst[at] + cost;
					que.push(P(min_dst[to], to));
				}
			}
		}	
	}
	
	ll get(ll at){return min_dst[at];}
};
