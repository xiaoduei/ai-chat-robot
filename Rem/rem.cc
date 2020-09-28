#include "rem.hpp"

int main()
{
    TuLin* tl = new TuLin();
    string msg;

    while(1){
        string message;
        cout << "你要说啥子# ";
        cin >> message;
        msg = tl->Chat(message);
        cout << "Rem# " << msg << endl;
    }
    return 0;
}
