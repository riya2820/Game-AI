# include <iostream>
# include <string>

using namespace std;

::MyOthelloAI::MyOthelloAI()
{
} 


vector<pair<int,int>> joshirs::MyOthelloAI::possible_moves(const OthelloGameState& state)
{
    const OthelloBoard& board = state.board();
    std::vector<std::pair<int,int>> possible;

    for (int w=0; w<board.width(); w++) {
        for (int h=0; h<board.height(); h++) {
            if (state.isValidMove(w,h) == true) {
                possible.push_back(make_pair(w,h));
            }
        }
    }
    return possible;
}


int ::MyOthelloAI::eval(const OthelloGameState& state)
{
    int score = 0;
    const OthelloBoard& board = state.board();

    if (board.cellAt(board.width()-1,0) == myturn || board.cellAt(0,board.height()-1) == myturn) {
        score += 10;
    }
    if (board.cellAt(0,0) == myturn || board.cellAt(board.width()-1,board.height()-1) == myturn) {
        score += 10;
    } 
    if (myturn == OthelloCell::white) {
        score +=  state.whiteScore() - state.blackScore();
    } 
    else{ //OthelloCell::black
        score += state.blackScore() - state.whiteScore();
    }
    return score;
}


int ::MyOthelloAI::search(OthelloGameState& state, int depth)
{
    if (depth == 0) { //i.e game over at root node
    return eval(state); 
    }

    if (state.isGameOver() == true){
        return eval(state);
    }

    if ((myturn == OthelloCell::black && state.isBlackTurn()) ||(myturn == OthelloCell::white && state.isWhiteTurn())) {
        int maxEval = -1000;
        int eval;
        //int n = possible.size();

        std::vector<std::pair<int,int>> possible = possible_moves(state); 
        std::pair<int,int> currentMove;  
        unique_ptr<OthelloGameState> cloned_state;   

        for (int i=0; i <possible.size(); i++) {
            currentMove = possible.at(i);
            cloned_state = state.clone();
            cloned_state->makeMove(currentMove.first, currentMove.second);
            eval =  search(*cloned_state, depth-1);
            maxEval = max(maxEval, eval);
        }
        return maxEval; 
    } 

    else if ((myturn == OthelloCell::black && state.isWhiteTurn()) ||(myturn == OthelloCell::white && state.isBlackTurn())) {
        int minEval = 1000;
        int eval;
        // int n = possible.size();
        std::vector<pair<int,int>> possible = possible_moves(state);
        std::pair<int,int> currentMove;   
        unique_ptr<OthelloGameState> cloned_state;

        for (int i=0; i <possible.size(); i++) {
            currentMove = possible.at(i);
            cloned_state = state.clone();
            cloned_state->makeMove(currentMove.first, currentMove.second);
            eval = search(*cloned_state, depth-1);
            minEval = min(minEval, eval);
        }
        return minEval; 
    }
    return 0;
}


std::pair<int, int> joshirs::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    std::pair<int,int> bestMove = make_pair(0,0); //keep updating best move
    std::pair<int,int> currentMove;
    std::vector<std::pair<int,int>> possible = possible_moves(state);
    
    unique_ptr<OthelloGameState> cloned_state;
    int n = possible.size();
    int recursionDepth = 2;
    int currentScore;
    int highestScore = -100000;
  
    if (n < 10) {
        recursionDepth = 3;
    }

    if (state.isWhiteTurn()) {      
        myturn = OthelloCell::white;
    }
    else {//if (state.isWhiteTurn()) {
        myturn = OthelloCell::black;
    }
  
    for (int i=0; i<possible.size(); i++) {
        currentMove = possible.at(i);
        cloned_state = state.clone();
        cloned_state->makeMove(currentMove.first, currentMove.second);
        currentScore = search(*cloned_state, recursionDepth);

        if (highestScore < currentScore) { //updates highest score and best move
            highestScore = currentScore;
            bestMove = currentMove;
        }
    }
    return bestMove;
}
