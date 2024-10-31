#include<cstdio>
#include<algorithm>
#define db double
namespace Acc{
    const int N = 5e4+10;
    struct node{
        int x,y;
    }a[N],stk[N];
    db cmp(node a,node b,node c){return 1.*(c.x-a.x)*(c.y-b.y)-1.*(c.x-b.x)*(c.y-a.y);}
    int dis(node a,node b){return ((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
    int n,tp,ans;
    void work(){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
        std::sort(a+1,a+n+1,[=](node a,node b)->bool{return a.x<b.x || (a.x==b.x && a.y<b.y);});
        stk[1]=a[1],tp=1;
        for(int i=2;i<=n;i++){
            while(tp>1 && cmp(stk[tp-1],stk[tp],a[i])<=0)tp--;
            stk[++tp]=a[i];
        }
        int tmp=tp;
        for(int i=n-1;i>=1;i--){
            while(tp>tmp && cmp(stk[tp-1],stk[tp],a[i])<=0)tp--;
            stk[++tp]=a[i];
        }
        for(int i=1,j=3;i<tp;i++){
            while(cmp(stk[i],stk[i+1],stk[j])<cmp(stk[i],stk[i+1],stk[j+1]))j=j%(tp-1)+1;
            ans=std::max(ans,std::max(dis(stk[i],stk[j]),dis(stk[i+1],stk[j])));
        }
        printf("%d",ans);
    }
}
int main(){
    return Acc::work(),0;
}