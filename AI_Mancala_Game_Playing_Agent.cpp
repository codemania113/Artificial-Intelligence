#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct movee
{
    int row;
    int col;
    string movetype;
};

void evaluate_stake(char board[27][27], char new_board[27][27], int values[26][26], int n, int* nyou_score, int* nopp_score, int row, int col, char player)
{
    int i,j;
    char oplayer;
    int you_score = *nyou_score;
    int opp_score = *nopp_score;

    if(player == 'X')
        oplayer = 'O';
    else
        oplayer = 'X';

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            new_board[i][j] = board[i][j];
        }
    }
    i = row;
    j = col;

    new_board[i][j] = player;
    you_score = you_score + values[i][j];

    *nyou_score = you_score;
}

void evaluate_raid(char board[27][27], char new_board[27][27], int values[26][26], int n, int* nyou_score, int* nopp_score, int row, int col, char player, int *stake)
{
    int i,j;
    char oplayer;
    int you_score = *nyou_score;
    int opp_score = *nopp_score;

    if(player == 'X')
        oplayer = 'O';
    else
        oplayer = 'X';

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            new_board[i][j] = board[i][j];
        }
    }

    i = row;
    j = col;

    new_board[i][j] = player;
    you_score = you_score + values[i][j];

    if((j-1 >= 0) && (new_board[i][j-1] == player))
    {
        if((j+1 < n) && (new_board[i][j+1] == oplayer))
        {
            new_board[i][j+1] = player;
            you_score = you_score + values[i][j+1];
            opp_score = opp_score - values[i][j+1];
            *stake = 0;
        }
        if((i-1 >= 0) && (new_board[i-1][j] == oplayer))
        {
            new_board[i-1][j] = player;
            you_score = you_score + values[i-1][j];
            opp_score = opp_score - values[i-1][j];
            *stake = 0;
        }
        if((i+1 < n) && (new_board[i+1][j] == oplayer))
        {
            new_board[i+1][j] = player;
            you_score = you_score + values[i+1][j];
            opp_score = opp_score - values[i+1][j];
            *stake = 0;
        }
    }
    else if((j+1 < n) && (new_board[i][j+1] == player))
    {
        if((j-1 >= 0) && (new_board[i][j-1] == oplayer))
        {
            new_board[i][j-1] = player;
            you_score = you_score + values[i][j-1];
            opp_score = opp_score - values[i][j-1];
            *stake = 0;

        }
        if((i-1 >= 0) && (new_board[i-1][j] == oplayer))
        {
            new_board[i-1][j] = player;
            you_score = you_score + values[i-1][j];
            opp_score = opp_score - values[i-1][j];
            *stake = 0;
        }
        if((i+1 < n) && (new_board[i+1][j] == oplayer))
        {
            new_board[i+1][j] = player;
            you_score = you_score + values[i+1][j];
            opp_score = opp_score - values[i+1][j];
            *stake = 0;
        }
    }
    else if((i-1 >= 0) && (new_board[i-1][j] == player))
    {
        if((j-1 >= 0) && (new_board[i][j-1] == oplayer))
        {
            new_board[i][j-1] = player;
            you_score = you_score + values[i][j-1];
            opp_score = opp_score - values[i][j-1];
            *stake = 0;
        }
        if((j+1 < n) && (new_board[i][j+1] == oplayer))
        {
            new_board[i][j+1] = player;
            you_score = you_score + values[i][j+1];
            opp_score = opp_score - values[i][j+1];
            *stake = 0;
        }
        if((i+1 < n) && (new_board[i+1][j] == oplayer))
        {
            new_board[i+1][j] = player;
            you_score = you_score + values[i+1][j];
            opp_score = opp_score - values[i+1][j];
            *stake = 0;
        }
    }
    else if((i+1 < n) && (new_board[i+1][j] == player))
    {
        if((j-1 >= 0) && (new_board[i][j-1] == oplayer))
        {
            new_board[i][j-1] = player;
            you_score = you_score + values[i][j-1];
            opp_score = opp_score - values[i][j-1];
            *stake = 0;
        }
        if((j+1 < n) && (new_board[i][j+1] == oplayer))
        {
            new_board[i][j+1] = player;
            you_score = you_score + values[i][j+1];
            opp_score = opp_score - values[i][j+1];
            *stake = 0;
        }
        if((i-1 >= 0) && (new_board[i-1][j] == oplayer))
        {
            new_board[i-1][j] = player;
            you_score = you_score + values[i-1][j];
            opp_score = opp_score - values[i-1][j];
            *stake = 0;
        }
    }
    *nyou_score = you_score;
    *nopp_score = opp_score;
}

void evaluate(char board[27][27], char new_board[27][27], int values[26][26], int n, int* nyou_score, int* nopp_score, int row, int col, char player)
{
    int i,j;
    char oplayer;
    int you_score = *nyou_score;
    int opp_score = *nopp_score;

    if(player == 'X')
        oplayer = 'O';
    else
        oplayer = 'X';

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            new_board[i][j] = board[i][j];
        }
    }
    i = row;
    j = col;

    new_board[i][j] = player;
    you_score = you_score + values[i][j];

    if((j-1 >= 0) && (new_board[i][j-1] == player))
    {
        if((j+1 < n) && (new_board[i][j+1] == oplayer))
        {
            new_board[i][j+1] = player;
            you_score = you_score + values[i][j+1];
            opp_score = opp_score - values[i][j+1];
        }
        if((i-1 >= 0) && (new_board[i-1][j] == oplayer))
        {
            new_board[i-1][j] = player;
            you_score = you_score + values[i-1][j];
            opp_score = opp_score - values[i-1][j];
        }
        if((i+1 < n) && (new_board[i+1][j] == oplayer))
        {
            new_board[i+1][j] = player;
            you_score = you_score + values[i+1][j];
            opp_score = opp_score - values[i+1][j];
        }
    }
    else if((j+1 < n) && (new_board[i][j+1] == player))
    {
        if((j-1 >= 0) && (new_board[i][j-1] == oplayer))
        {
            new_board[i][j-1] = player;
            you_score = you_score + values[i][j-1];
            opp_score = opp_score - values[i][j-1];
        }
        if((i-1 >= 0) && (new_board[i-1][j] == oplayer))
        {
            new_board[i-1][j] = player;
            you_score = you_score + values[i-1][j];
            opp_score = opp_score - values[i-1][j];
        }
        if((i+1 < n) && (new_board[i+1][j] == oplayer))
        {
            new_board[i+1][j] = player;
            you_score = you_score + values[i+1][j];
            opp_score = opp_score - values[i+1][j];
        }
    }
    else if((i-1 >= 0) && (new_board[i-1][j] == player))
    {
        if((j-1 >= 0) && (new_board[i][j-1] == oplayer))
        {
            new_board[i][j-1] = player;
            you_score = you_score + values[i][j-1];
            opp_score = opp_score - values[i][j-1];
        }
        if((j+1 < n) && (new_board[i][j+1] == oplayer))
        {
            new_board[i][j+1] = player;
            you_score = you_score + values[i][j+1];
            opp_score = opp_score - values[i][j+1];
        }
        if((i+1 < n) && (new_board[i+1][j] == oplayer))
        {
            new_board[i+1][j] = player;
            you_score = you_score + values[i+1][j];
            opp_score = opp_score - values[i+1][j];
        }
    }
    else if((i+1 < n) && (new_board[i+1][j] == player))
    {
        if((j-1 >= 0) && (new_board[i][j-1] == oplayer))
        {
            new_board[i][j-1] = player;
            you_score = you_score + values[i][j-1];
            opp_score = opp_score - values[i][j-1];
        }
        if((j+1 < n) && (new_board[i][j+1] == oplayer))
        {
            new_board[i][j+1] = player;
            you_score = you_score + values[i][j+1];
            opp_score = opp_score - values[i][j+1];
        }
        if((i-1 >= 0) && (new_board[i-1][j] == oplayer))
        {
            new_board[i-1][j] = player;
            you_score = you_score + values[i-1][j];
            opp_score = opp_score - values[i-1][j];
        }
    }
    *nyou_score = you_score;
    *nopp_score = opp_score;
}

int minimax(char board[27][27], int values[26][26], int depth, int n, int you_score, int opp_score, char player, char youplay, char opponent)
{
    int i,j;
    int max_val, min_val, val;
    int move_left = 0;

    if(depth == 0)
    {
        if(player == youplay)
            return you_score - opp_score;
        else
            return  opp_score - you_score;
    }

    // maximizing player
    if(player == youplay)
    {
        max_val = -1000000;
        val = 0;
        int nyou_score;
        int nopp_score;
        char new_board[27][27];
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score = you_score;
                    nopp_score = opp_score;
                    evaluate(board,new_board,values,n,&nyou_score,&nopp_score,i,j,youplay);
                    val = minimax(new_board,values,depth-1,n,nopp_score,nyou_score,opponent,youplay,opponent);
                    if(val > max_val)
                    {
                        max_val = val;
                    }
                    move_left = 1;
                }
            }
        }
        return max_val;
    }
    else
    {
        min_val = 1000000;
        val = 0;
        int nyou_score;
        int nopp_score;
        char new_board[27][27];
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score = you_score;
                    nopp_score = opp_score;
                    //int stake = 1;
                    evaluate(board,new_board,values,n,&nyou_score,&nopp_score,i,j,opponent);
                    val = minimax(new_board,values,depth-1,n,nopp_score,nyou_score,youplay,youplay,opponent);
                    if(val < min_val)
                    {
                        min_val = val;
                    }
                    move_left = 1;
                }
            }
        }
        return min_val;
    }
}

int alphabeta(char board[27][27], int values[26][26], int depth, int n, int you_score, int opp_score, char player, char youplay, char opponent, int alpha, int beta)
{
    int i,j;
    int max_val, min_val, val;

    if(depth == 0)
    {
        if(player == youplay)
        {
            return you_score - opp_score;
        }
        else
        {
            return opp_score - you_score;
        }
    }

    // maximizing player
    if(player == youplay)
    {
        max_val = -1000000;
        val = 0;
        int nyou_score;
        int nopp_score;
        char new_board[27][27];
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score = you_score;
                    nopp_score = opp_score;
                    evaluate(board,new_board,values,n,&nyou_score,&nopp_score,i,j,youplay);
                    val = minimax(new_board,values,depth-1,n,nopp_score,nyou_score,opponent,youplay,opponent);
                    if(val > max_val)
                    {
                        max_val = val;
                    }
                    if(max_val > alpha)
                    {
                        alpha = max_val;
                    }
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return max_val;
    }
    else
    {
        min_val = 1000000;
        val = 0;
        int nyou_score;
        int nopp_score;
        char new_board[27][27];
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score = you_score;
                    nopp_score = opp_score;
                    evaluate(board,new_board,values,n,&nyou_score,&nopp_score,i,j,opponent);
                    val = minimax(new_board,values,depth-1,n,nopp_score,nyou_score,youplay,youplay,opponent);
                    if(val < min_val)
                    {
                        min_val = val;
                    }
                    if(min_val < beta)
                    {
                        beta = min_val;
                    }
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return min_val;
    }
}

int main()
{
  ifstream ifile;
  ifile.open("input.txt");
  ofstream ofile("output.txt");
  string line;
  string mode, num;
  char youplay, opponent;
  int alpha1, alpha2, beta;
  int n, depth;
  int x_score = 0;
  int o_score = 0;
  int you_score = 0;
  int opp_score = 0;
  int max_val = -1000000;
  int val,val1,val2;
  char board[27][27];
  int values[26][26];
  int stake;
  int total_moves = 0;

  if(ifile.is_open())
  {
    getline(ifile,num);
    stringstream convert(num);
    convert>>n;
    getline(ifile,mode);
    getline(ifile,num);
    youplay = num[0];
    getline(ifile,num);
    stringstream convert1(num);
    convert1>>depth;

    for(int i = 0; i < n; i++)
    {
      getline(ifile,line);
      istringstream sub(line);
      for(int j = 0; j < n; j++)
      {
          sub>>num;
          stringstream convert(num);
          convert>>values[i][j];
      }
    }

    for(int i = 0; i < n; i++)
    {
      getline(ifile,line);
      istringstream sub(line);
      for(int j = 0; j < n; j++)
      {
          sub>>board[i][j];
          if(board[i][j] == '.')
            total_moves++;
      }
    }

    if(depth > total_moves)
        depth = total_moves;

    if(youplay == 'X')
        opponent = 'O';
    else
        opponent = 'X';

    if(mode.compare("ALPHABETA") == 0)
    {
        struct movee best;
        best.row = -1;
        best.col = -1;
        best.movetype = "";

        struct movee best1;
        best1.row = -1;
        best1.col = -1;
        best1.movetype = "";

        struct movee best2;
        best2.row = -1;
        best2.col = -1;
        best2.movetype = "";

        int i,j;
        x_score = 0;
        o_score = 0;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == 'X')
                    x_score = x_score + values[i][j];
                else if(board[i][j] == 'O')
                    o_score = o_score + values[i][j];
            }
        }
        if(youplay == 'X')
        {
            you_score = x_score;
            opp_score = o_score;
        }
        else
        {
            you_score = o_score;
            opp_score = x_score;
        }

        max_val = -1000000;
        val1 = -1000000;
        val2 = -1000000;
        int nyou_score1 = you_score;
        int nopp_score1 = opp_score;
        int nyou_score2 = you_score;
        int nopp_score2 = opp_score;
        char new_board1[27][27],new_board2[27][27];
        alpha1 = -1000000;
        alpha2 = -1000000;
        beta = 1000000;

        //local_stake = 0;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score1 = you_score;
                    nopp_score1 = opp_score;
                    evaluate_stake(board,new_board1,values,n,&nyou_score1,&nopp_score1,i,j,youplay);
                    val1 = alphabeta(new_board1,values,depth-1,n,nopp_score1,nyou_score1,opponent,youplay,opponent,alpha1,beta);
                    if(val1 > max_val)
                    {
                        best1.row = i;
                        best1.col = j;
                        max_val = val1;
                        best1.movetype = "Stake";
                    }
                    if(max_val > alpha1)
                    {
                        alpha1 = max_val;
                    }
                }
            }
        }

        val1 = max_val;
        max_val = -1000000;

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score2 = you_score;
                    nopp_score2 = opp_score;
                    stake = 1;
                    evaluate_raid(board,new_board2,values,n,&nyou_score2,&nopp_score2,i,j,youplay,&stake);
                    if(stake == 0)
                    {
                        val2 = alphabeta(new_board2,values,depth-1,n,nopp_score2,nyou_score2,opponent,youplay,opponent,alpha2,beta);
                        if(val2 > max_val)
                        {
                            best2.row = i;
                            best2.col = j;
                            max_val = val2;
                            best2.movetype = "Raid";
                        }
                        if(max_val > alpha2)
                        {
                            alpha2 = max_val;
                        }
                    }
                }
            }
        }

        val2 = max_val;
        //string movetype;

        if((val1 > val2) || (val1 == val2))
        {
            best.row = best1.row;
            best.col = best1.col;
            best.movetype = best1.movetype;
        }
        else
        {
            best.row = best2.row;
            best.col = best2.col;
            best.movetype = best2.movetype;
        }

        board[best.row][best.col] = youplay;
        // to display board
        char c = best.col + 65;
        ofile<<c;
        ofile<<best.row+1<<" ";
        ofile<<best.movetype<<"\n";
        i = best.row;
        j = best.col;

        if(best.movetype.compare("Raid") == 0)
        {
            if((j-1 >= 0) && (board[i][j-1] == opponent))
            {
                board[i][j-1] = youplay;
            }
            if((j+1 < n) && (board[i][j+1] == opponent))
            {
                board[i][j+1] = youplay;
            }
            if((i-1 >= 0) && (board[i-1][j] == opponent))
            {
                board[i-1][j] = youplay;
            }
            if((i+1 < n) && (board[i+1][j] == opponent))
            {
                board[i+1][j] = youplay;
            }
        }

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                ofile<<board[i][j];
            }
            ofile<<"\n";
        }
        ofile.close();

    }
    else if(mode.compare("MINIMAX") == 0)
    {
        struct movee best;
        best.row = -1;
        best.col = -1;
        best.movetype = "";

        struct movee best1;
        best1.row = -1;
        best1.col = -1;
        best1.movetype = "";

        struct movee best2;
        best2.row = -1;
        best2.col = -1;
        best2.movetype = "";

        int i,j;
        x_score = 0;
        o_score = 0;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == 'X')
                    x_score = x_score + values[i][j];
                else if(board[i][j] == 'O')
                    o_score = o_score + values[i][j];
            }
        }
        if(youplay == 'X')
        {
            you_score = x_score;
            opp_score = o_score;
        }
        else
        {
            you_score = o_score;
            opp_score = x_score;
        }

        max_val = -1000000;
        val1 = -1000000;
        val2 = -1000000;
        int nyou_score1 = you_score;
        int nopp_score1 = opp_score;
        int nyou_score2 = you_score;
        int nopp_score2 = opp_score;
        char new_board1[27][27],new_board2[27][27];

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score1 = you_score;
                    nopp_score1 = opp_score;

                    evaluate_stake(board,new_board1,values,n,&nyou_score1,&nopp_score1,i,j,youplay);
                    val1 = minimax(new_board1,values,depth-1,n,nopp_score1,nyou_score1,opponent,youplay,opponent);
                    if(val1 > max_val)
                    {
                        best1.row = i;
                        best1.col = j;
                        max_val = val1;
                        best1.movetype = "Stake";
                    }
                }
            }
        }
        val1 = max_val;
        max_val = -1000000;

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(board[i][j] == '.')
                {
                    nyou_score2 = you_score;
                    nopp_score2 = opp_score;
                    stake = 1;
                     // important
                    evaluate_raid(board,new_board2,values,n,&nyou_score2,&nopp_score2,i,j,youplay, &stake);
                    if(stake == 0)
                    {
                        val2 = minimax(new_board2,values,depth-1,n,nopp_score2,nyou_score2,opponent,youplay,opponent);
                        if(val2 > max_val)
                        {
                            best2.row = i;
                            best2.col = j;
                            max_val = val2;
                            best2.movetype = "Raid";
                        }
                    }
                }
            }
        }
        val2 = max_val;

        //string movetype;
        if((val1 > val2) || (val1 == val2))
        {
            best.row = best1.row;
            best.col = best1.col;
            best.movetype = best1.movetype;
        }
        else
        {
            best.row = best2.row;
            best.col = best2.col;
            best.movetype = best2.movetype;
        }

        board[best.row][best.col] = youplay;
        // to display board
        char c = best.col + 65;
        ofile<<c;
        ofile<<best.row+1<<" ";
        ofile<<best.movetype<<"\n";
        i = best.row;
        j = best.col;

        if(best.movetype.compare("Raid") == 0)
        {
            if((j-1 >= 0) && (board[i][j-1] == opponent))
            {
                board[i][j-1] = youplay;
            }
            if((j+1 < n) && (board[i][j+1] == opponent))
            {
                board[i][j+1] = youplay;
            }
            if((i-1 >= 0) && (board[i-1][j] == opponent))
            {
                board[i-1][j] = youplay;
            }
            if((i+1 < n) && (board[i+1][j] == opponent))
            {
                board[i+1][j] = youplay;
            }
        }

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                ofile<<board[i][j];
            }
            ofile<<"\n";
        }
        ofile.close();
    }
    ifile.close();
  }
  return 0;
}
