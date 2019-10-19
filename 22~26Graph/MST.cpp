/*
MST-KRUSKAL.G;w/
1 A D ;
2 for each vertex  2 G:V
3 MAKE-SET./
4 sort the edges of G:E into nondecreasing order by weight w
5 for each edge .u; / 2 G:E, taken in nondecreasing order by weight
6 if FIND-SET.u/ ¤ FIND-SET./
7 A D A [ f.u; /g
8 UNION.u; /
9 return A
 */



//간선집합 A 정보 u v w 
#include<vector>

struct edge
{
    int u;
    int v;
    int w;

    bool operator <( edge &Edge)
    {
        return this->w < Edge.w ;
    }
};

class __UNION
{

public:

void MAKE_SET(int a)
{

}
void UNION(int a)
{

}

int FIND_SET(int a)
{

}

};
void MST_KRUSKAL(std::vector<std::vector<int>> &Graph,std::vector<edge> &W)
{   
    std::vector<edge> A ;
    __UNION SET;
    const int n = Graph.size()-1;
    for(int v = 1 ; v <= n ;v++)
    {
        SET.MAKE_SET(v);
    }
    std::sort(W.begin(),W.end());
    for(int i = 1 ; i < n ;i++)
    {
        if(SET.FIND_SET(W[i].u) != SET.FIND_SET(W[i].v))
        {
            A.push_back({W[i].u,W[i].v,W[i].w});
            SET.UNION(u,v);
        }
    }
}

 /*
 
 MST-PRIM.G;w; r/
1 for each u 2 G:V
2 u:key D 1
3 u: D NIL
4 r:key D 0
5 Q D G:V
6 while Q ¤ ;
7 u D EXTRACT-MIN.Q/
8 for each  2 G:AdjOEu
9 if  2 Q and w.u; / < :key
10 : D u
11 :key D w.u; /

 */
////////////////////////////////////////////////

struct vertex
{
    int key;
    int pi;
}


#include<queue>

void MST_PRIM(std::vector<vertex> &Graph,std::vector<std::vector<int>> &W  ,vertex r)
{
    const int n = Graph.size();
    /*
    for(int i = 1 ; i < n ; i++)
    {
        
    }
     */
    r.key = 0;
    

}