#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct node
{
  string state;
  int weight;
};

struct star_node
{
  string state;
  int weight;
  int actual_weight;
};

map < string, vector<struct node> > graph;
map < string, vector<struct node> >::iterator it;


map <string,int> sun_graph;
map <string,int>::iterator sun_it;

map <string,struct node> parent;
map <string,struct node>::iterator it_parent;

bool bfs_search(string start_state, string goal_state)
{
  vector <struct node>::iterator it1;
  queue <struct node> q;
  struct node ss;
  ss.state = start_state;
  ss.weight = 0;
  q.push(ss);

  parent.insert(pair<string,struct node>(start_state, ss));

  while(!q.empty())
  {
    struct node curr_node = q.front();
    q.pop();

    if(curr_node.state == goal_state)
      return true;

    it = graph.find(curr_node.state);
    if(it != graph.end())
    {
      it1 = it->second.begin();

      if(it1 != it->second.end())
      {
        while(it1 != it->second.end())
        {
          it_parent = parent.find(it1->state);
          if(it_parent == parent.end())
          {
            struct node nn;
            nn.state = it1->state;
            nn.weight = 1 + curr_node.weight;
            q.push(nn);
            struct node np;
            np.state = curr_node.state;
            np.weight = nn.weight;
            parent.insert(pair<string,struct node>(it1->state, np));
          }
          it1++;
        }
      }
    }
  }
  return false;
}

bool dfs_search(string start_state, string goal_state)
{
  vector <struct node>::iterator it1;

  string temp_node;
  stack <struct node> s;
  struct node ss;
  ss.state = start_state;
  ss.weight = 0;
  s.push(ss);

  parent.insert(pair<string,struct node>(start_state, ss));

  while(!s.empty())
  {
    struct node curr_node = s.top();
    s.pop();

    if(curr_node.state == goal_state)
      return true;

    it = graph.find(curr_node.state);
    if(it != graph.end())
    {
      it1 = it->second.begin();
      vector <string> temp;
      vector <string>::reverse_iterator tt;

      if(it1 != it->second.end())
      {
        while(it1 != it->second.end())
        {
          temp.push_back(it1->state);
          it1++;
        }
      }

      it1 = it->second.begin();
      if(it1 != it->second.end())
      {
        for(tt=temp.rbegin();tt != temp.rend();tt++)
        {
          string temp_node = *tt;
          it_parent = parent.find(temp_node);
          if(it_parent == parent.end())
          {
            struct node nn;
            nn.state = temp_node;
            nn.weight = 1 + curr_node.weight;
            s.push(nn);
            struct node np;
            np.state = curr_node.state;
            np.weight = nn.weight;
            parent.insert(pair<string,struct node>(temp_node, np));
          }
        }
      }
    }
  }
  return false;
}

bool operator<(const struct node& x, const struct node& y)
{
  return x.weight > y.weight;
}

bool ucs_search(string start_state, string goal_state)
{
  map <string,int> explored;
  vector <struct node>::iterator it1;
  map <string,int> backup;
  map <string,int>::iterator it_backup;
  map <string,int>::iterator it_explored;


  priority_queue <struct node> pq;
  struct node ss;
  ss.state = start_state;
  ss.weight = 0;

  pq.push(ss);
  backup.insert(pair<string,int>(start_state,0));

  parent.insert(pair<string,struct node>(start_state, ss));

  while(!pq.empty())
  {
    struct node curr_node = pq.top();
    pq.pop();
    backup.erase(curr_node.state);
    explored.insert(pair<string,int>(curr_node.state,curr_node.weight));

    if(curr_node.state == goal_state)
      return true;

    it = graph.find(curr_node.state);
    if(it != graph.end())
    {
      it1 = it->second.begin();
      if(it1 != it->second.end())
      {
        while(it1 != it->second.end())
        {
          it_explored = explored.find(it1->state);
          it_backup = backup.find(it1->state);
          it_parent = parent.find(it1->state);

          if(it_explored == explored.end() && (it_backup == backup.end()))
          {
            struct node nn;
            nn.state = it1->state;
            nn.weight = it1->weight + curr_node.weight;
            pq.push(nn);
            backup.insert(pair<string,int>(it1->state,nn.weight));
            struct node np;
            np.state = curr_node.state;
            np.weight = nn.weight;
            parent.insert(pair<string,struct node>(it1->state, np));
          }
          else if(it_backup != backup.end())
          {
            if(it_backup->second > (it1->weight + curr_node.weight))
            {
                struct node nn;
                nn.state = it1->state;
                nn.weight = curr_node.weight + it1->weight;
                it_backup->second = nn.weight;
                it_parent->second.state = curr_node.state;
                it_parent->second.weight = nn.weight;

                stack <struct node> temp;
                struct node check = pq.top();
                while(check.state != nn.state)
                {
                    temp.push(check);
                    pq.pop();
                    check = pq.top();
                }
                pq.pop();

                while(!temp.empty())
                {
                check = temp.top();
                pq.push(check);
                temp.pop();
                }
                pq.push(nn);
            }
          }
          else if(it_explored != explored.end())
          {
            if(it_explored->second > (it1->weight + curr_node.weight))
            {
              struct node nn;
              nn.state = it1->state;
              nn.weight = it1->weight + curr_node.weight;
              explored.erase(it_explored);
              it_parent->second.state = curr_node.state;
              it_parent->second.weight = nn.weight;
              pq.push(nn);
              backup.insert(pair<string,int>(it1->state,nn.weight));
            }

          }
          it1++;
        }
      }
    }
  }
  return false;
}

bool operator<(const struct star_node& x, const struct star_node& y)
{
  return x.weight > y.weight;
}

bool astar_search(string start_state, string goal_state)
{
  map <string,int> explored;
  vector <struct node>::iterator it1;
  map <string,int> backup;
  map <string,int>::iterator it_backup;
  map <string,int>::iterator it_explored;

  priority_queue <struct star_node> pq;
  struct node ss;
  ss.state = start_state;
  ss.weight = 0;

  struct star_node st_ss;
  st_ss.state = start_state;
  st_ss.actual_weight = 0;

  sun_it = sun_graph.find(start_state);
  if(sun_it != sun_graph.end())
  {
    st_ss.weight = sun_it->second;
  }
  pq.push(st_ss);

  backup.insert(pair<string,int>(start_state,st_ss.weight));
  parent.insert(pair<string,struct node>(start_state, ss));

  while(!pq.empty())
  {
    struct star_node curr_node = pq.top();
    pq.pop();
    backup.erase(curr_node.state);
    explored.insert(pair<string,int>(curr_node.state,curr_node.weight));

    if(curr_node.state == goal_state)
      return true;

    it = graph.find(curr_node.state);
    if(it != graph.end())
    {
      it1 = it->second.begin();
      if(it1 != it->second.end())
      {
        while(it1 != it->second.end())
        {
          //cout<<it1->state<<" ";
          it_explored = explored.find(it1->state);
          it_backup = backup.find(it1->state);
          it_parent = parent.find(it1->state);
          int heuristic;
          sun_it = sun_graph.find(it1->state);
            if(sun_it != sun_graph.end())
            {
              heuristic = sun_it->second;
            }

          if(it_explored == explored.end() && it_backup == backup.end())
          {
            struct star_node nn;
            nn.state = it1->state;
            nn.actual_weight = it1->weight + curr_node.actual_weight;
            nn.weight = curr_node.actual_weight + it1->weight + heuristic;
            pq.push(nn);
            backup.insert(pair<string,int>(it1->state,nn.weight));

            struct node np;
            np.state = curr_node.state;
            np.weight = nn.actual_weight;
            parent.insert(pair<string,struct node>(it1->state, np));
          }
          else if(it_backup != backup.end())
          {
            if(it_backup->second > (curr_node.actual_weight + it1->weight + heuristic))
            {
              struct star_node nn;
              nn.state = it1->state;
              nn.weight = curr_node.actual_weight + it1->weight + heuristic;
              nn.actual_weight = curr_node.actual_weight + it1->weight;

              it_backup->second = nn.weight;
              it_parent->second.state = curr_node.state;
              it_parent->second.weight = nn.actual_weight;

              stack <struct star_node> temp;
              struct star_node check = pq.top();
              while(check.state != nn.state)
              {
                  temp.push(check);
                  pq.pop();
                  check = pq.top();
              }
              pq.pop();

              while(!temp.empty())
              {
                check = temp.top();
                pq.push(check);
                temp.pop();
              }
              pq.push(nn);
            }
          }
            else if(it_explored != explored.end())
            {
              if(it_explored->second > (it1->weight + curr_node.actual_weight + heuristic))
              {
                struct star_node nn;
                nn.state = it1->state;
                nn.weight = it1->weight + curr_node.actual_weight + heuristic;
                nn.actual_weight = it1->weight + curr_node.actual_weight;
                explored.erase(it1->state);
                it_parent->second.state = curr_node.state;
              	it_parent->second.weight = nn.actual_weight;
                pq.push(nn);
                backup.insert(pair<string,int>(it1->state,nn.weight));

              }
            }
          it1++;
        }
      }
    }
  }
  return false;
}

int main()
{
  ifstream ifile;
  ifile.open("input.txt");
  ofstream ofile("output.txt");
  string line;
  bool flag;
  string algo, start_state, goal_state, num, state1, state2;
  int live_traffic, sunday_traffic, distance;

  if(ifile.is_open())
  {
    getline(ifile,algo);
    getline(ifile,start_state);
    getline(ifile,goal_state);
    getline(ifile,num);
    stringstream convert(num);
    convert>>live_traffic;

    for(int i = 0; i<live_traffic; i++)
    {
      getline(ifile,line);

      istringstream sub(line);
      sub>>state1;
      sub>>state2;
      sub>>num;
      stringstream convert(num);
      convert>>distance;
      struct node n1;
      n1.state = state2;
      n1.weight = distance;

      it = graph.find(state1);
      if(it == graph.end())
      {
        vector <struct node> connection;
       	connection.push_back(n1);
        graph.insert(pair< string,vector<struct node> >(state1,connection));
      }
      else
      {
        it->second.push_back(n1);
      }
    }
    getline(ifile,num);
    stringstream convert2(num);
    convert2>>sunday_traffic;

    for(int i = 0; i<sunday_traffic; i++)
    {
      getline(ifile,line);
      istringstream sub(line);
      sub>>state1;
      sub>>num;
      stringstream convert(num);
      convert>>distance;

      sun_it = sun_graph.find(state1);
      if(sun_it == sun_graph.end())
      {
        sun_graph.insert(pair<string,int>(state1,distance));
      }
      else
      {
        sun_it->second = distance;
      }
    }

    if(algo.compare("BFS") == 0)
    {
      map <string,struct node>::iterator it_parent;
      if(bfs_search(start_state, goal_state))
      {
        stack <string> p;
        stack <int> q;
        int count = 0;
        it_parent = parent.find(goal_state);
        if(it_parent != parent.end())
        {
          while(it_parent->first != start_state)
          {
            p.push(it_parent->first);
            q.push(it_parent->second.weight);
            it_parent = parent.find(it_parent->second.state);
          }
          p.push(it_parent->first);
          q.push(it_parent->second.weight);
          while((!p.empty()) && ofile.is_open())
          {
            ofile<<p.top()<<" "<<q.top()<<"\n";
            p.pop();
            q.pop();
          }
          ofile.close();
        }
      }
    }
    else if(algo.compare("DFS") == 0)
    {
      map <string,struct node>::iterator it_parent;
      if(dfs_search(start_state, goal_state))
      {
        stack <string> p;
        stack <int> q;
        it_parent = parent.find(goal_state);
        if(it_parent != parent.end())
        {
          while(it_parent->first != start_state)
          {
            p.push(it_parent->first);
            q.push(it_parent->second.weight);
            it_parent = parent.find(it_parent->second.state);
          }
          p.push(it_parent->first);
          q.push(it_parent->second.weight);
          while((!p.empty()) && ofile.is_open())
          {
            ofile<<p.top()<<" "<<q.top()<<"\n";
            p.pop();
            q.pop();
          }
          ofile.close();
        }
      }
    }
    else if(algo.compare("UCS") == 0)
    {
      map <string,struct node>::iterator it_parent;
      if(ucs_search(start_state, goal_state))
      {
        stack <string> p;
        stack <int> q;
        it_parent = parent.find(goal_state);
        if(it_parent != parent.end())
        {
          while(it_parent->first != start_state)
          {
            p.push(it_parent->first);
            q.push(it_parent->second.weight);
            it_parent = parent.find(it_parent->second.state);
          }
          p.push(it_parent->first);
          q.push(it_parent->second.weight);
          while((!p.empty()) && ofile.is_open())
          {
            ofile<<p.top()<<" "<<q.top()<<"\n";
            p.pop();
            q.pop();
          }
          ofile.close();
        }
      }
    }
    else if(algo.compare("A*") == 0)
    {
      map <string,struct node>::iterator it_parent;
      if(astar_search(start_state, goal_state))
      {
        stack <string> p;
        stack <int> q;
        it_parent = parent.find(goal_state);
        if(it_parent != parent.end())
        {
          while(it_parent->first != start_state)
          {
            p.push(it_parent->first);
            q.push(it_parent->second.weight);
            it_parent = parent.find(it_parent->second.state);
          }
          p.push(it_parent->first);
          q.push(it_parent->second.weight);
          while((!p.empty()) && ofile.is_open())
          {
            ofile<<p.top()<<" "<<q.top()<<"\n";
            p.pop();
            q.pop();
          }
          ofile.close();
        }
      }
    }
    ifile.close();
  }
  return 0;
}

