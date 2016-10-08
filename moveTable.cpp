#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;

int depthCounter = 0; // used in findBestWhiteMove()
int myrand (int i) { return rand()%i;} // used in shuffleMoves()
// key is xy coord, ie 11 is a1, 12 is a2...88 is h8   value is piece there, uppercase for white, e for empty
map<int,char> board = {{11,'R'},{12,'P'},{13,'e'},{14,'e'},{15,'e'},{16,'e'},{17,'p'},{18,'r'},{21,'N'},{22,'P'},{23,'e'},{24,'e'},{25,'e'},{26,'e'},{27,'p'},{28,'n'},{31,'B'},{32,'P'},{33,'e'},{34,'e'},{35,'e'},{36,'e'},{37,'p'},{38,'b'},{41,'Q'},{42,'P'},{43,'e'},{44,'e'},{45,'e'},{46,'e'},{47,'p'},{48,'q'},{51,'K'},{52,'P'},{53,'e'},{54,'e'},{55,'e'},{56,'e'},{57,'p'},{58,'k'},{61,'B'},{62,'P'},{63,'e'},{64,'e'},{65,'e'},{66,'e'},{67,'p'},{68,'b'},{71,'N'},{72,'P'},{73,'e'},{74,'e'},{75,'e'},{76,'e'},{77,'p'},{78,'n'},{81,'R'},{82,'P'},{83,'e'},{84,'e'},{85,'e'},{86,'e'},{87,'p'},{88,'r'}};

char getColor(char piece){
    if(isupper(piece)==true) return 'W';
    else if(piece=='e') return 'e';
    else return 'b';
}

vector<int> findLateralMoves(int sqr){ 
    vector<int> moves;//store moves here
    char color = getColor(board[sqr]); // color of piece ('W','b') or'e' if no piece
    if(color=='e') return moves;//return empty vector if square has no piece to move
    for(int i = sqr-1;i%10!=0;i-=1){ // get moves 'down' from square
        char someColor = getColor(board[i]); // get color of piece on square, or 'e' empty
        if(color==someColor)break; // piece is same color
        else if(someColor=='e') moves.emplace_back(i); //square is empty, add to moves
        else {moves.emplace_back(i);break;}}// square has opposing piece, add to moves
    for(int i = sqr+1;(i+1)%10!=0;i+=1){// get moves 'up' from square
        char someColor = getColor(board[i]);//get color of piece on square, or 'e' empty
        if(color==someColor)break; // piece is same color
        else if(someColor=='e') moves.emplace_back(i); //square is empty, add to moves
        else {moves.emplace_back(i);break;}} // square has opposing piece, add to moves
    for(int i = sqr-10;i>10;i-=10){// get moves 'left' from square
        char someColor = getColor(board[i]);//get color of piece on square, or 'e' empty
        if(color==someColor)break; // piece is same color
        else if(someColor=='e') moves.emplace_back(i); //square is empty, add to moves
        else {moves.emplace_back(i);break;}} // square has opposing piece, add to moves
    for(int i = sqr+10;i<89;i+=10){//get moves 'right' from square
        char someColor = getColor(board[i]);//get color of piece on square, or 'e' empty
        if(color==someColor)break; // piece is same color
        else if(someColor=='e') moves.emplace_back(i); //square is empty, add to moves
        else {moves.emplace_back(i);break;}} // square has opposing piece, add to moves
    return moves;};
vector<int> findDiagonalMoves(int sqr){
    vector<int> moves;//store moves here
    char color = getColor(board[sqr]);//color of piece ('W','b') or 'e' if no piece
    if(color=='e') return moves;//return empty vector if square has no piece to move
    for(int i = sqr-11;i%10!=0&&i>10;i-=11) {//get moves 'down' and 'left' diagonal
        char someColor = getColor(board[i]);//get color of piece on square, or 'e' if empty
        if(color==someColor)break;//piece is same color
        else if(someColor=='e') moves.emplace_back(i);//square is empty, add to moves
        else {moves.emplace_back(i);break;}}//square has opposing piece, add to moves
    for(int i = sqr-9;i>10&&(i+1)%10!=0;i-=9){//get moves 'up' and 'left' diagonal
        char someColor = getColor(board[i]);//get color of piece on square, or 'e' if empty
        if(color==someColor)break;//piece is same color
        else if(someColor=='e')moves.emplace_back(i);//square is empty, add to moves
        else {moves.emplace_back(i);break;}}//square has opposing piece, add to moves
    for(int i = sqr+11;i<89&&(i+1)%10!=0;i+=11){// get moves 'up' and 'right' diagonal
        char someColor = getColor(board[i]);//get color of piece on square, or 'e' if empty
        if(color==someColor)break;//piece is same color
        else if(someColor=='e')moves.emplace_back(i);//square is empty, add to moves
        else{moves.emplace_back(i);break;}}//square has opposing piece, add to moves
    for(int i = sqr+9;i<89&&i%10!=0;i+=9){//get moves 'down' and 'right' diagonal
        char someColor = getColor(board[i]);
        if(color==someColor)break;
        else if(someColor=='e')moves.emplace_back(i);
        else{moves.emplace_back(i);break;}}
    return moves;};
// NEED make board history for castling, en passant
// NEED castling, en passant, promotion
//////////////////////////////////////////////////////////////////////////////////////////////
vector<int> findPawnMoves(int coord){
    vector<int> vMoves;
    char color = getColor(board[coord]);
    int x = coord;
    if(color=='W'){
        if(board[x+1]=='e'){
            vMoves.emplace_back(x+1);
            if((x-2)%10==0&&board[x+2]=='e')vMoves.emplace_back(x+2);}
        if(x-9>11){if(getColor(board[x-9])=='b')vMoves.emplace_back(x-9);}
        if(x+11<89){if(getColor(board[x+11])=='b')vMoves.emplace_back(x+11);}}
    else if(color=='b'){
        if(board[x-1]=='e'){
            vMoves.emplace_back(x-1);
            if((x+3)%10==0&&board[x-2]=='e')vMoves.emplace_back(x-2);}
        if(x+9<89){if(getColor(board[x+9])=='W')vMoves.emplace_back(x+9);}
        if(x-11>10){if(getColor(board[x-11])=='W')vMoves.emplace_back(x-11);}}
    return vMoves;}
vector<int> findPawnThreats(int coord){
    vector<int> vMoves;
    char color = getColor(board[coord]);
    int x = coord;
    if(color=='W'){
        if(x-9>11)vMoves.emplace_back(x-9);
        if(x+11<89)vMoves.emplace_back(x+11);}
    else if(color=='b'){
        if(x+9<89)vMoves.emplace_back(x+9);
        if(x-11>10)vMoves.emplace_back(x-11);}
    return vMoves;}
vector<int> findKnightMoves(int coord){
    int x = coord;
    char color = getColor(board[coord]);
    vector<int> vMoves;
    if((x+21)%10!=0&&(x+22)%10!=0&&x+21<89)if(color!=getColor(board[x+21]))vMoves.emplace_back(x+21);
    if((x+19)%10!=0&&(x+20)%10!=0&&x+19<89)if(color!=getColor(board[x+19]))vMoves.emplace_back(x+19);
    if((x+12)%10!=0&&(x+13)%10!=0&&x+12<89)if(color!=getColor(board[x+12]))vMoves.emplace_back(x+12);
    if((x+8)%10!=0&&(x+9)%10!=0&&x+8<89)if(color!=getColor(board[x+8]))vMoves.emplace_back(x+8);
    if((x-8)%10!=0&&(x-7)%10!=0&&x-8>10)if(color!=getColor(board[x-8]))vMoves.emplace_back(x-8);
    if((x-12)%10!=0&&(x-11)%10!=0&&x-12>10)if(color!=getColor(board[x-12]))vMoves.emplace_back(x-12);
    if((x-18)%10!=0&&x-19>10)if(color!=getColor(board[x-19]))vMoves.emplace_back(x-19);
    if((x-21)%10!=0&&x-21>10)if(color!=getColor(board[x-21]))vMoves.emplace_back(x-21);
    return vMoves;}
vector<int> findBishopMoves(int coord){
    return findDiagonalMoves(coord);
}
vector<int> findRookMoves(int coord){
    return findLateralMoves(coord);
}
vector<int> findQueenMoves(int coord){
    vector<int> vMoves;
    vector<int> laterals = findLateralMoves(coord);
    vector<int> diags = findDiagonalMoves(coord);
    vMoves.insert(vMoves.end(),laterals.begin(),laterals.end());
    vMoves.insert(vMoves.end(),diags.begin(),diags.end());
    return vMoves;
}
vector<int> findKingPerimeter(int coord){
    int x = coord;
    vector<int> vPerim;
    if((x-1)%10!=0)vPerim.emplace_back(x-1);
    if((x-11)%10!=0&&x-11>10)vPerim.emplace_back(x-11);
    if(x-10>10)vPerim.emplace_back(x-10);
    if((x-8)%10!=0&&x-9>10)vPerim.emplace_back(x-9);
    if((x+2)%10!=0&&x+1<89)vPerim.emplace_back(x+1);
    if(x+10<89)vPerim.emplace_back(x+10);
    if((x+9)%10!=0&&x+9<89)vPerim.emplace_back(x+9);
    if((x+12)%10!=0&&x+11<89)vPerim.emplace_back(x+11);
    return vPerim;
}
// CHANGE to set, used in findKingMoves()
vector<int> findAllThreats(char player){
    vector<int> vThreats;
    if(player=='W'){
        for(pair<int,char> x:board){
            char color = getColor(board[x.first]);
                if(color==player){
                    char piece = board[x.first];
                    switch(piece){
                        case 'P':{vector<int>y=findPawnThreats(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'R':{vector<int>y=findRookMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'N':{vector<int>y=findKnightMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'Q':{vector<int>y=findQueenMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'B':{vector<int>y=findBishopMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'K':{vector<int>y=findKingPerimeter(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        default:break;
                        }}}}
    if(player=='b')
        for(pair<int,char> x:board){
                char color = getColor(board[x.first]);
                if(color==player){
                    char piece = board[x.first];
                    switch(piece){
                        case 'p':{vector<int>y=findPawnThreats(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'r':{vector<int>y=findRookMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'n':{vector<int>y=findKnightMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'q':{vector<int>y=findQueenMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'b':{vector<int>y=findBishopMoves(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        case 'k':{vector<int>y=findKingPerimeter(x.first);for(int move:y)vThreats.emplace_back(move);break;}
                        default:break;}}}
    return vThreats;}
// NEED to add castle moves
vector<int> findKingMoves(int coord){
    vector<int> vMoves;
    int x = coord;
    char color = getColor(board[x]);
    vector<int> illegalSquares = findAllThreats('b');
    if(color=='W'){vector<int> illegalSquares = findAllThreats('b');}
    else if(color=='b'){vector<int> illegalSquares = findAllThreats('W');}
// illegalSquares should be changed into a set
    if((x-1)%10!=0)if(color!=getColor(board[x-1]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x-1)!=illegalSquares.end()))vMoves.emplace_back(x-1);// down
    if((x+2)%10!=0)if(color!=getColor(board[x+1]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x+1)!=illegalSquares.end()))vMoves.emplace_back(x+1);// up
    if((x-10)>10)if(color!=getColor(board[x-10]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x-10)!=illegalSquares.end()))vMoves.emplace_back(x-10);//left
    if((x+10)<89)if(color!=getColor(board[x+10]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x+10)!=illegalSquares.end()))vMoves.emplace_back(x+10);//right
    if((x+2)%10!=0&&(x+10)<89)if(color!=getColor(board[x+11]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x+11)!=illegalSquares.end()))vMoves.emplace_back(x+11);//up right
    if((x+2)%10!=0&&(x-10)>10)if(color!=getColor(board[x-9]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x-9)!=illegalSquares.end()))vMoves.emplace_back(x-9);//up left
    if((x-1)%10!=0&&(x+10)<89)if(color!=getColor(board[x+9]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x+9)!=illegalSquares.end()))vMoves.emplace_back(x+9);//down right
    if((x-1)%10!=0&&(x-10)>10)if(color!=getColor(board[x-11]))if(!(find(illegalSquares.begin(),illegalSquares.end(),x-11)!=illegalSquares.end()))vMoves.emplace_back(x-11);//down left
    return vMoves;
}


vector<pair<int,int>> findWhiteMoves(map<int,char> &board){
    vector<pair<int,int>> vpMoves;
    for(pair<int,char> coordPair:board){
        int coord = coordPair.first;
        char piece = board[coord];
        if(islower(piece))continue;
        switch(piece){
            case 'P':{
                vector<int> vTmp = findPawnMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'R':{
                vector<int> vTmp = findRookMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'N':{
                vector<int> vTmp = findKnightMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'B':{
                vector<int> vTmp = findBishopMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'Q':{
                vector<int> vTmp = findQueenMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'K':{
                vector<int> vTmp = findKingMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}}
            }random_shuffle(vpMoves.begin(),vpMoves.end(),myrand);return vpMoves;}
// adding randness results in additional calls for depth search, expensive
vector<pair<int,int>> findBlackMoves(map<int,char> &board){
    vector<pair<int,int>> vpMoves;
    for(pair<int,char> coordPair:board){
        int coord = coordPair.first;
        char piece = board[coord];
        if(piece=='e')continue;
        if(isupper(piece))continue;
        switch(piece){
            case 'p':{
                vector<int> vTmp = findPawnMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'r':{
                vector<int> vTmp = findRookMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'n':{
                vector<int> vTmp = findKnightMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'b':{
                vector<int> vTmp = findBishopMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'q':{
                vector<int> vTmp = findQueenMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}
            case 'k':{
                vector<int> vTmp = findKingMoves(coord);
                while(!vTmp.empty()){
                    vpMoves.emplace_back(make_pair(coord,vTmp.back()));
                    vTmp.pop_back();}break;}}
            }random_shuffle(vpMoves.begin(),vpMoves.end(),myrand);return vpMoves;}


void printBoard(map<int,char> &board){
    int counter = 18;
    while(counter!=10){
        cout<<board[counter];
        counter+=10;
        if(counter>88){
            cout<<endl;
            counter-=81;}}
    cout<<endl;
}


// promote pawns here?
void movePiece(map<int,char> &board,int from,int to){
    char fromPiece = board[from];
    board[to] = fromPiece;
    board[from] = 'e';
}

int evalBoard(map<int,char> &board,char player){
    int total = 0;
    if(player=='W'){
        for(pair<int,char> elems:board){
            switch(elems.second){
                case 'P':total+=1;break;
                case 'R':total+=5;break;
                case 'N':total+=3;break;
                case 'B':total+=3;break;
                case 'Q':total+=9;break;
                case 'K':total+=50;break;
                default:break;}}}
    else if(player=='b'){
        for(pair<int,char> elems:board){
            switch(elems.second){
                case 'p':total+=1;break;
                case 'r':total+=5;break;
                case 'n':total+=3;break;
                case 'b':total+=3;break;
                case 'q':total+=9;break;
                case 'k':total+=50;break;
                default:break;}}}return total;}




pair<int,int> findBestBlackMove(map<int,char> &board){
    vector<pair<int,int>> vMoves = findBlackMoves(board);
    pair<int,int> bestMove;
    int highScore = -1;
    for(pair<int,int> move:vMoves){
        // get the score, make the move, get the score
        int oldScore = evalBoard(board,'W');
        // save the pieces to move back
        // board score only depends on white pieces
        char oldFrom = board[move.first];
        char oldTo = board[move.second];
        movePiece(board,move.first,move.second);
        int newScore = evalBoard(board,'W');
        int moveScore = oldScore-newScore;
        if(moveScore>highScore){
            bestMove = {move.first,move.second};
            highScore = moveScore;}
        //move piece back
        board[move.first] = oldFrom;
        board[move.second] = oldTo;}
    return bestMove;
}

pair<int,int> findBestWhiteMove(map<int,char> &board){
    vector<pair<int,int>> moves1 = findWhiteMoves(board);
    pair<int,int> bestMove;
    int bestScore = -3; 
    // iterate over each possible move from initial board state
    for(pair<int,int> elems:moves1){
        int whiteScore1 = evalBoard(board,'W');
        int blackScore1 = evalBoard(board,'b');
        int total = whiteScore1-blackScore1;
        // move the piece and get black response
        char oldFrom1 = board[elems.first];
        char oldTo1 = board[elems.second];
        movePiece(board,elems.first,elems.second);
        pair<int,int> response1 = findBestBlackMove(board);
        char oldFrom2 = board[response1.first];
        char oldTo2 = board[response1.second];
        movePiece(board,response1.first,response1.second);
        int whiteScore2 = evalBoard(board,'W');
        int blackScore2 = evalBoard(board,'b');
        total += whiteScore2;
        total -= blackScore2;
        if(total>bestScore){
            bestScore = total;
            bestMove = {elems.first,elems.second};}
        //move pieces back
        board[response1.first] = oldFrom2;
        board[response1.second] = oldTo2;
        board[elems.first] = oldFrom1;
        board[elems.second] = oldTo1;}
    return bestMove;
}


// for each exchange of whiteMove and blackMove, add material gained in whiteMove, 
//   subtract amount of material lost on blackMove, going N moves deep...
// Should only use findBestWhiteMove, since it calls findBestBlackMove...
pair<int,int> deepWhite(map<int,char> &board){}





int main(){
    srand ( time(0) );// rand seed
    
    
    // this test shows that more valuable moves are preferred, at least immediate material
    // moves with equal material value are chosen randomly
    movePiece(board,27,23);//move black B pawn to b3
    movePiece(board,71,76);// move white knight to g6
    pair<int,int> wmove = findBestWhiteMove(board);
    cout<<wmove.first<<" "<<wmove.second<<endl;
    movePiece(board,wmove.first,wmove.second);
    pair<int,int> bmove = findBestBlackMove(board);
    cout<<bmove.first<<" "<<bmove.second<<endl;

  
  
// Tests findWhiteMoves(), findBlackMoves(), They   
  //   vector<pair<int,int>> bmoves = findBlackMoves(board);
//     for(pair<int,int> elem:bmoves)cout<<elem.first<<" "<<elem.second<<endl;
//     vector<pair<int,int>> wmoves = findWhiteMoves(board);
//     for(pair<int,int> elem:wmoves)cout<<elem.first<<" "<<elem.second<<endl;
    

    
    
    
        
return 0;}