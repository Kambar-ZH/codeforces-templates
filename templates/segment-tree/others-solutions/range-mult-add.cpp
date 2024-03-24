// LUOGU_RID: 151500964
#include <bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long n,Q,l,r,x,t,b[200005],a[800005],add[800005],mul[800005];
long long pow(long long a,long long b)
{
    long long ans=1,base=a;
    while(b>0)
    {
        if(b&1)
        {
            ans=(ans*base)%mod;
        }
        base=(base*base)%mod;
        b>>=1;
    }
	return ans;
}
void build(long long x,long long l,long long r)
{
	mul[x]=1,add[x]=0;
	if(l==r)
	{
		a[x]=b[l]%mod;
		return;
	}
	long long mid=(l+r)>>1;
	build(x<<1,l,mid),build((x<<1)+1,mid+1,r);
	a[x]=(a[x<<1]+a[(x<<1)+1])%mod;
}
void pushdown(long long x,long long l,long long r,long long mid)
{
	a[x<<1]=(a[x<<1]*mul[x]+(mid-l+1)*add[x])%mod,a[(x<<1)+1]=(a[(x<<1)+1]*mul[x]+(r-mid)*add[x])%mod;
	mul[x<<1]*=mul[x],mul[(x<<1)+1]*=mul[x];
	add[x<<1]=(add[x<<1]*mul[x]+add[x])%mod,add[(x<<1)+1]=(add[(x<<1)+1]*mul[x]+add[x])%mod;
	mul[x]=1,add[x]=0,mul[x<<1]%=mod,mul[(x<<1)+1]%=mod;
}
void update(long long x,long long l,long long r,long long tl,long long tr,long long k,long long flag)
{
	if(tl<=l&&r<=tr)
	{
		if(flag==1)
		{
			a[x]=a[x]*k%mod,add[x]=add[x]*k%mod,mul[x]=mul[x]*k%mod;
		}
		else 
		{
			a[x]=(a[x]+(r-l+1)*k)%mod,add[x]=(add[x]+k)%mod;	
		}
		return;
	}
	long long mid=(l+r)>>1;
	pushdown(x,l,r,mid);
	if(tl<=mid)
	{
		update(x<<1,l,mid,tl,tr,k,flag);
	}
	if(tr>mid)
	{
		update((x<<1)+1,mid+1,r,tl,tr,k,flag);
	}
	a[x]=(a[x<<1]+a[(x<<1)+1])%mod;
}
long long query(long long x,long long l,long long r,long long tl,long long tr)
{
	if(tl<=l&&r<=tr)
	{
		return a[x];
	}
	long long mid=(l+r)>>1,sum=0;
	pushdown(x,l,r,mid);
	if(tl<=mid)
	{
		sum=(sum+query(x<<1,l,mid,tl,tr))%mod;
	}
	if(tr>mid)
	{
		sum=(sum+query((x<<1)+1,mid+1,r,tl,tr))%mod;
	}
	return sum;
}
int main()
{
	cin>>n>>Q;
	for(long long i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	build(1,1,n);
	while(Q--)
	{
		cin>>l>>r>>x;
		t=pow(r-l+1,mod-2);
		update(1,1,n,l,r,(r-l)*t%mod,1);
		update(1,1,n,l,r,x*t%mod,2);
	}
	for(long long i=1;i<=n;i++)
	{
		cout<<query(1,1,n,i,i)<<" ";
	}
	return 0;
}