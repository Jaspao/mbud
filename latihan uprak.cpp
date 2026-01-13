#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

vector<vector<char>> createRiverMap(int row, int column){
    vector<vector<char>> riverSectors (row, vector<char>(column,'!'));

    int jumlahKayu = 4;
    while (jumlahKayu > 0){
        int r = rand() % row;
        int c = rand() % column;
        if(riverSectors[r][c] == '!'){
            riverSectors[r][c] = '=';
            jumlahKayu--;
        }
    }

    int jumlahBeri = 3;
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

int digAround(vector<vector<char>> &river, int r, int c, int row, int column){
    int jumlah =0;
    int baris[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int kolom[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for (int i=0; i<8; i++){
        int hitungRow = r + baris[i];
        int hitungColumn = c + kolom[i];
        if (hitungRow >= 0 && hitungRow < row && hitungColumn >= 0 && hitungColumn < column){
            if (river[hitungRow][hitungColumn]=='W') jumlah++;
        }
    }
    return jumlah;
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
    cout<<"Enter the map dimensions to start (row column): ";
    cin>>row>>column;
    vector<vector<char>> river;
    vector<vector<char>> visibleRiver;
    srand(time(0));

    river = createRiverMap(row, column);
    visibleRiver = vector<vector<char>>(row, vector<char>(column, '~'));
    mapRiver(river, row, column);
    mapRiver(visibleRiver, row, column);
    int jumlahLife = 5;
    while (jumlahLife>0 && poin!=4){
        cout<<"Masukkan baris dan kolom yang mau kamu cek(row column): ";
        cin>>r>>c;
        if(r < 0 || r >= row || c < 0 || c >= column){
            cout << "Invalid coordinates!" << endl;
            continue;
        }
        if (visibleRiver[r][c] != '~') {
            cout << "You already checked this tile!" << endl;
            continue;
        }
        visibleRiver[r][c]=river[r][c];    
        mapRiver(river, row, column);
        mapRiver(visibleRiver, row, column);
        if(river[r][c]=='='){
            cout<<"Wood for your dam!"<<endl;
            poin++;
        }else if(river[r][c]=='@'){
            cout<<"You found a berry!"<<endl;
            jumlahLife++;
        }else if(river[r][c]=='!'){
            cout<<"Mau cek sekitar?(cost: 1 life, y/n): ";cin>>opsi;
            if(toupper(opsi)=='Y'){
                int jumlahSekitar = digAround(river,r,c,row,column);
                cout<<"!!   Terdapat " << jumlahSekitar << " didekatmu!   !!"<<endl;
                jumlahLife--;
            }else{
                cout<<"You continue to swim.."<<endl;
            }
            jumlahLife--;
        }
        cout << string(20, '=') << endl;
        cout<<"Lives left: "<<jumlahLife<<endl;
        cout<<"Poin: "<<poin<<endl;
        cout << string(20, '=') << endl;
    }
    if(poin == 4){
        cout<<R"(
            **************************
            ==      ~~~     ~~~ ~~
            ==   ~~    /\_/\  ~~~
            ==  ~~~   ( •O• )  ~~~~~~
            == ~~    /|     |__ 
            == ~~     \_____/___) ~~~~~~
            ==  ~~~   /      \       ~~~
            ==    ~~~     ~~~~~~
            **************************)";
    }
}
