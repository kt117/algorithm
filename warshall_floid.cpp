void warshall_floid(){
	for(ll k = 1; k <= n; k++)
		for(ll i = 1; i <= n; i++)
			for(ll j = 1; j <= n; j++)
				dst[i][j] = min(dst[i][k]+dst[k][j], dst[i][j]);
}