#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

vector<vector<char>> createRiverMap(int jumlahKayu, int jumlahBeri, int row, int column){
    vector<vector<char>> riverSectors (row, vector<char>(column,'!'));
    while (jumlahKayu > 0){
        int r = rand() % row;
        int c = rand() % column;
        if(riverSectors[r][c] == '!'){
            riverSectors[r][c] = '=';
            jumlahKayu--;
        }
    }

    while (jumlahBeri > 0){
        int r = rand() % row;
        int c = rand() % column;
        if(riverSectors[r][c] == '!'){
            riverSectors[r][c] = '*';
            jumlahBeri--;
        }
    }
    return riverSectors;
}
void mapRiver(vector<vector<char>> &river, int row, int column){
    for (int r=0; r<row; r++){
        for (int c=0; c<column; c++){
            cout<<river[r][c]<<" ";
        }
        cout<<endl;
    }
}

void digAround(vector<vector<char>> &river, int r, int c, int row, int column){
    int jumlahW =0;
    int jumlahB =0;
    int baris[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int kolom[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for (int i=0; i<8; i++){
        int hitungRow = r + baris[i];
        int hitungColumn = c + kolom[i];
        if (hitungRow >= 0 && hitungRow < row && hitungColumn >= 0 && hitungColumn < column){
            if (river[hitungRow][hitungColumn]=='=') jumlahW++;
            if (river[hitungRow][hitungColumn]=='*') jumlahB++;
        }
    }
    cout<<"!!   Terdapat " << jumlahW << " Kayu didekatmu!   !!"<<endl;
    cout<<"!!   Terdapat " << jumlahB << " Bunga didekatmu!   !!"<<endl;
}
int main(){
    char opsi;
    int r,c;
    int row, column;
    int poin=0;
    cout<<endl<<"   Welcome to BeaverSweep! ʕ•ᴥ•ʔ🍓"<<endl;
    cout<<R"(
    ===========================
            ~~~     ~~~~~~
         ~~    /\_/\  ~~~
        ~~~   ( •O• )  ~~~~~~
      ~~~    /|     |__ 
      ~~~     \_____/___) ~~~~~~
        ~~~   /      \       ~~~
           ~~~     ~~~~~~
    ===========================)";
    cout<<R"(
          ENTER TO START
    ===========================
    )"<<endl;cin.get();
    cout<<"Masukkan dimensi map untuk memulai! (row column): ";
    cin>>row>>column;
    vector<vector<char>> river;
    vector<vector<char>> visibleRiver;
    srand(time(0));
    int jumlahKayu = 0.2*(row*column);
    int jumlahBeri = 0.15*(row*column);
    river = createRiverMap(jumlahKayu, jumlahBeri, row, column);
    visibleRiver = vector<vector<char>>(row, vector<char>(column, '~'));
    mapRiver(river, row, column);
    mapRiver(visibleRiver, row, column);
    int jumlahLife = 5;
    while (jumlahLife>0 && poin!=jumlahKayu){
        cout<<"Masukkan baris dan kolom yang mau kamu cek (row column): ";
        cin>>r>>c;
        if(r < 0 || r >= row || c < 0 || c >= column){
            cout << "Koordinat ini tidak valid!!" << endl;
            continue;
        }
        if (visibleRiver[r][c] != '~') {
            cout << "Kamu kan udah ngecek bagian sini!" << endl;
            continue;
        }
        visibleRiver[r][c]=river[r][c];    
        mapRiver(river, row, column);
        cout<<"--------------------------------"<<endl;
        cout<<" = : Kayu | * : Bunga | ! : Bom"<<endl;
        cout<<"--------------------------------"<<endl;
        mapRiver(visibleRiver, row, column);
        if(river[r][c]=='='){
            cout<<"Kamu menemukan Kayu!"<<endl;
            digAround(river,r,c,row,column);
            poin++;
        }else if(river[r][c]=='*'){
            cout<<"Bunga! Bunganya kamu makan? +1 life"<<endl;
            digAround(river,r,c,row,column);
            jumlahLife++;
        }else if(river[r][c]=='!'){
            cout<<"Waduh ada jebakan!"<<endl;
            digAround(river,r,c,row,column);
            jumlahLife--;
        }
        int sisaKayu = jumlahKayu - poin;
        cout << string(20, '=') << endl;
        cout<<"Lives left: "<<jumlahLife<<endl;
        cout<<"Poin: "<<poin<<endl;
        cout<<"Sepertinya ada "<<sisaKayu<<" lagi disekitar sini deh.."<<endl;
        cout << string(20, '=') << endl;
    }
    if(poin == jumlahKayu){
        cout<<"Yay! Bendungannya berhasil terbentuk!"<<endl;
        cout<<R"(
            **************************
            |==|      ~~~     ~~~ ~~
            |==|    ~~    /\_/\  ~~~
            |==|   ~~~   ( •O• )  ~~~~
            |==|  ~~    /|     |__ 
            |==|  ~~     \_____/___) ~
            |==|   ~~~   /     \  ~~
            |==|     ~~~     ~~~~~~
            **************************)";
    }
    if(jumlahLife==0){
        cout<<"Si beaver terbawa arus..."<<endl;
        cout<<R"(
            **************************
                  ~~~     ~~~ ~~
               ~~    /\_/\  ~~~
              ~~~   ( X-X )  ~~~~~~
             ~~    /|     |__ 
             ~~     \_____/___) ~~~~
              ~~~   /      \       ~~~
                ~~~     ~~~~~~
            **************************)";
    }
}