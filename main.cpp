#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>

using namespace std;


void print(int board[]){
    //ofstream out("out.out");
    for( int i = 0; i < 81; i++){
        cout << board[i] << " ";
        if(i%9 == 2 || i%9 == 5){
            cout << "| ";
        }
        else if(i%9 == 8){
            cout << endl;
        }
        if(i==26 || i==26+27){
            cout << "- - - - - - - - - - -" << endl;
        }
    }
    cout << endl;
}

void printvec(vector<int> p ){
    for(size_t i = 0; i < p.size(); ++i){
        cout << p[i] << " ";
    }
    cout << endl;
}

bool check_rows(int board[]){
    //ignore all zeros

    //check to make sure one of same # per row
    vector<int> check;
    for(int i = 0; i < 9 ; i++){
        for(int k = 0; k < 9; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
        //printvec(check);
        for(size_t j = 0; j < check.size(); j++){
            for(size_t m = 0; m < check.size(); m++){
                if(m == j){
                    continue;
                }
                if(check[m] == check[j]){
                    return false;
                }
            }
        }
        check.clear();
    }
    // end check row
    return true;

}


bool check_cols(int board[]){
    //ignore all zeros

    //check to make sure one of same # per cols
    vector<int> check;
    for(int i = 0; i < 9 ; i++){
        for(int k = 0; k < 9; k++){
            if(board[i + 9*k] != 0){
                check.push_back(board[i + 9*k]);
            }
        }
        //printvec(check);
        for(size_t j = 0; j < check.size(); j++){
            for(size_t m = 0; m < check.size(); m++){
                if(m == j){
                    continue;
                }
                if(check[m] == check[j]){
                    return false;
                }
            }
        }
        check.clear();
    }
    // end check cols
    return true;

}
bool check_vec(vector<int> &v){
    bool ret = true;
    //printvec(v);                        // investigate vectors
    for(size_t j = 0; j < v.size(); j++){
        for(size_t m = 0; m < v.size(); m++){
            if(m == j){
                continue;
            }
            if(v[m] == v[j]){
                ret = false;
            }
        }
    }
    v.clear();
    return ret;
}

bool check_box(int board[]){
    //ignore all zeros

    //top left
    vector<int> check;
    for(int i = 0; i < 3 ; i++){
        for(int k = 0; k < 3; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }
    //mid left
    for(int i = 3; i < 6 ; i++){
        for(int k = 0; k < 3; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }
    //bot left
    for(int i = 6; i < 9 ; i++){
        for(int k = 0; k < 3; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }

    //top mid
    for(int i = 0; i < 3 ; i++){
        for(int k = 3; k < 6; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }
    //mid mid
    for(int i = 3; i < 6 ; i++){
        for(int k = 3; k < 6; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }
    //bot mid
    for(int i = 6; i < 9 ; i++){
        for(int k = 3; k < 6; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }


    //right mid
    for(int i = 0; i < 3 ; i++){
        for(int k = 6; k < 9; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }
    //right mid
    for(int i = 3; i < 6 ; i++){
        for(int k = 6; k < 9; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }
    //right mid
    for(int i = 6; i < 9 ; i++){
        for(int k = 6; k < 9; k++){
            if(board[9*i + k] != 0){
                check.push_back(board[9*i + k]);
            }
        }
    }
    if(!check_vec(check)){
        return false;
    }
    // end check cols
    return true;

}

bool check_all(int board[]){
    return(check_box(board) && check_cols(board) && check_rows(board));
}

bool check_finished(int board[]){
    for(int i = 0; i < 81; i++){
        if(board[i] == 0){
            return false;
        }
    }
    return true;
}
vector<int> get_zero_index(int board[]){
    vector<int> r;
    for(int i = 0; i < 81; ++i){
        if(board[i] == 0){
            r.push_back(i);
        }
    }
    return r;
}

void guess(int board[], vector<int> v, int i, int k, bool &s){
    //if we end up past the end of the board stop
    //..
    //cout << i << "     " << v.size() << endl;
    if(check_finished(board) && check_all(board)){
        cout << "Solution:" << endl << endl;
        print(board);
        s = true;
        return;
    }
    //check 1-9 to see if they do / dont break the board
    for(; k <= 9; k++){
        //cout << "poop" <<endl;
        //print(board);
        if(s){
            break;
        }
        //cout << i << endl;
        //cout <<"5";
        board[(v.at(i))] = k;   
        //cout <<"6" << endl;
        //cout << "hi" << endl;
        if(check_all(board)){ //if the tested digit worked
            ++i;
            return guess(board, v, i, 1, s);       
        }
    }
    
    
    if(!check_all(board)){
        board[v.at(i)] = 0;
        --i;
        k = board[v.at(i)];
        while(k == 9){
            board[v.at(i)] = 0;
            i--;
            k = board[v.at(i)];
        }
        ++k;
        return guess(board,v,i,k,s);
    }


}



int main(){

    int board[9*9];
    string file; //file name w board

    cout << "Enter filename containing a board: " << endl;
    cin >> file;

    ifstream in(file);

    if(!in.is_open()){
        cout << "Couldn't find board. Try a different file" << endl;
        return 1;
    }

    string ins;

    // fill up board
    int index = 0;
    while(in >> ins){
        if(ins == "_" || ins == "|" || ins == "-"){
            continue;
        }
        else{
            board[index] = stoi(ins);
            index ++;
        }
    }
    // end fill up board


    cout << "Solving this board:" << endl << endl;
    print(board);
    cout << "Solving..." << endl;
    //printvec(get_zero_index(board));
    bool s = false;
    guess(board, get_zero_index(board),  0 , 1, s);

    //cout << "Solution:" << endl << endl;
    
    
    return 1;
}