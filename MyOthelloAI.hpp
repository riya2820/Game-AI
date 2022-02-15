# ifndef MYOTHELLOAI_HPP
# define MYOTHELLOAI_HPP

# include "OthelloAI.hpp" // provided
# include <vector>

using namespace std;

namespace joshirs
{

  class MyOthelloAI : public OthelloAI  // OthelloAI base class provided. DSAOthello creates AI algorithm to play game. 
  {
    
  public:

    /** Default constructor for DSAOthello AI alg
     */
    MyOthelloAI();
    
    
    /** Returns vector of pairs holding coordinates for possible moves
     */
    vector<pair<int,int>> possible_moves(const OthelloGameState& state);


    /** Evaluates current gamestate board 
     */ 
    int eval(const OthelloGameState& state);
    
    
    /** Searches down tree to evaluate what the ideal move is
     */
    int search(OthelloGameState& state, int depth);


    /** Keeps track of best move as algorithm checks all valid moves
     */
    //pair<int,int> best_move(const OthelloGameState& state,
    //                        pair<int,int> current_move);
 
    
    /** Built on base class function in OthelloAI
     */
    virtual std::pair<int, int> chooseMove(const OthelloGameState& state);


  private:
    OthelloCell myturn;
    
  };
 
}

# endif 
