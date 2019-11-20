#include<queue>
//http://blog.naver.com/PostView.nhn?blogId=ndb796&logNo=220829142548
struct node
{
    node *left;
    node *right;
    int freq;
    char alp;
}
/*
HUFFMAN : 트리생성 
FUNC 1 : 문자열 -> 압축 생성 INPUT 문자열 OUT 압축
FUNC 2 : 문자열 비트 출력
FUNC 3 : 압축 비트 출력
FUNC 4 : 압축해제 INPUT 압축 -> 문자열
FUNC 5 : 빈도수 계산
FUNC 6 : 각 문자 / 빈도수 출력
*/

class HUFFMAN
{
    public:
struct cmp{
    bool operator()(node *t, node *u){
        return t->freq > u->freq;
    }
};
node* HUFFMAN(char Alp[], int Alp_freq[])
{
    const int n =  ;

    std::priority_queue<node*,std::vector<node*>, cmp> Q;
    for(int i = 0 ; i < n ; i++)
    {
        node *x = new node;
        x->alp = Alp[i];
        x->freq = Alp_freq[i];
        Q.push(x);
    }


    for(int i = 1 ; i < n ; i++)
    {
        node* z = new node;

        z->left = Q.top();
        Q.pop();
        z->right = Q.top();
        Q.pop();
        z->freq = z->right->freq + z->left->freq;
        Q.pushs(z);
    }
    return Q.top();
}
void string_to_bit_print(char *line)
{

}
void char_to_bit_print(char c)
{
    
    const char * hi = get_4bit_str(str[i], 1);
    const char* lo = get_4bit_str(str[i],0);
    printf("%s%s ", hi, lo);
}

const char * get_4bit_str(const char chara, const int high = 0)
{
    char bit = (chara >> (high * 4)) & 0x0F;
    return lut[bit];
}


private:

const char * lut[16] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};

}
