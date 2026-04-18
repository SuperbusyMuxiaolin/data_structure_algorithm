#include <iostream>
#include <vector>
using namespace std;

class Bitmap{
    vector<unsigned long> v;
    // 能存多少位
    int size;

    public:
    Bitmap(int size){
        v.resize((size>>6)+1, 0);
        this->size = size;
    }


    // 查某一位是否为1
    bool get(int bitIndex){
        if(bitIndex<0 || bitIndex >=this->size){
            throw runtime_error("索引越界");
        }
        int arrindex = bitIndex >> 6;
        int offindex = bitIndex & 63;
        return (v[arrindex] & (1ULL<<offindex) )!=0;
    }
    
    // 把某一位设置为1
    void settrue(int bitIndex){
        if(bitIndex<0 || bitIndex >=this->size){
            throw runtime_error("索引越界");
        }
        int arrindex  =bitIndex >>6;
        int offindex = bitIndex &63;

        v[arrindex] = v[arrindex] | (1ULL <<offindex);
    }


    // 把某一位设置为0
    void setfalse(int bitIndex){
        if(bitIndex <0 || bitIndex >= this->size)
            throw runtime_error("索引越界");
        int arrindex = bitIndex >>6;
        int offindex = bitIndex & 63;

        v[arrindex ] = v[arrindex] & ~(1ULL <<offindex);
    }
};

int main() {
    Bitmap bitSet(1000);

    bitSet.settrue(10);
    bitSet.settrue(100);
    bitSet.settrue(500);

    cout << "Get 10: " << (bitSet.get(10) ? "true" : "false") << endl;     // true
    cout << "Get 100: " << (bitSet.get(100) ? "true" : "false") << endl;   // true
    cout << "Get 200: " << (bitSet.get(200) ? "true" : "false") << endl;   // false

    bitSet.setfalse(100);
    cout << "Get 100 after clear: " << (bitSet.get(100) ? "true" : "false") << endl; // false

    return 0;
}
