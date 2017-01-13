#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "homework.h"
#include "y.tab.h"
#include <ctime>

using namespace std;

//map < string, vector<string> > kb;
//map < string, vector<string> >::iterator it_kb;

//queue<string> kb;
map <string,int> kb;
map <string,int>::iterator it_kb;
char str5[1001];
//string clause;
//char expr1[1001];
//char expr2[1001];
map <string,int>kbase;

int resolve(string clausei,string clausej,char* new_clause)
{
    char key[1001];
    char neg_key[1001];
    char temp1[10001];
    char temp2[10001];
    int idx1,idx2;
    strcpy(new_clause,"");
    int unified = 0;
    int tautology = 0;
    int i,j,k;
    i = 0;
    int cannot_unify = 0;
    //cout<<"new clause "<<new_clause<<endl;
    //cout<<"clause i "<<clausei<<endl;
    //cout<<"clause j "<<clausej<<endl;

    while(clausei[i] != '\0')
    {
        if(clausei[i] == '|')
            i++;
        j = i;
        k = 0;
        while(clausei[j] != '(')
        {
            key[k] = clausei[j];
            k++;
            j++;
        }
        //strcpy(key,clause+i);
        key[k] = '\0';
        if(key[0] != '~')
        {
            strcpy(neg_key,(const char*)"~");
            strcat(neg_key,key);
        }
        else
        {
            strcpy(neg_key,key+1);
        }

        //cout<<neg_key<<endl;

        int p,q,r;
        cannot_unify = 0;
        char temp_key[1001];
        p = 0;
        while(clausej[p] != '\0')
        {
            if(clausej[p] == '|')
                p++;
            q = p;
            r = 0;
            while(clausej[q] != '(')
            {
                temp_key[r] = clausej[q];
                r++;
                q++;

            }
            //strcpy(key,clause+i);
            temp_key[r] = '\0';
            //cout<<temp_key<<endl;

            //cout<<"TEMP KEY IN ANOTHER EXPRESSION "<<temp_key<<endl;
            if(!strcmp(temp_key,neg_key))
            {
                //cout<<"entered strcmp\n";
                //cout<<"clause i "<<clausei<<endl;
                //cout<<"clause j "<<clausej<<endl;
                idx1 = j+1;
                idx2 = q+1;
                map <string,string> unify;
                map <string,string>::iterator it_unify;
                map <string,string>::iterator it_unify1;
                map <string,string>::iterator it_unify2;
                string a,b,c,d;

                while((clausej[idx2] != ')') || (clausei[idx1] != ')'))
                {
                    //cout<<"entered while loop \n";
                    if(((clausei[idx1+1] == ',') || (clausei[idx1+1] == ')')) && ((clausej[idx2+1] == ',') || (clausej[idx2+1] == ')')))
                    {
                        //cout<<"A\n";
                        //already = 1;
                        if(clausei[idx1] != clausej[idx2])
                        {
                            //string a,b,c,d;
                            a = clausej[idx2];
                            a[1]='\0';
                            b = clausei[idx1];
                            //int l = b.length();
                            b[1] = '\0';
                            it_unify1 = unify.find(a);
                            it_unify2 = unify.find(b);
                            if((it_unify1 == unify.end()) && (it_unify2 == unify.end()))
                            {
                                unify.insert(pair<string,string>(a,b));
                            }
                            else if((it_unify1 != unify.end()) && (it_unify2 == unify.end()))
                            {
                                c = it_unify1->second;
                                unify.insert(pair<string,string>(b,c));

                            }
                            else if((it_unify1 == unify.end()) && (it_unify2 != unify.end()))
                            {
                                c = it_unify2->second;
                                unify.insert(pair<string,string>(a,c));
                            }
                            if((it_unify1 != unify.end()) && (it_unify2 != unify.end()))
                            {
                                c = it_unify1->second;
                                d = it_unify2->second;
                                if((c.length() == 1) && (d.length() == 1))
                                {
                                    unify.erase(b);
                                    //unify.insert(pair<string,string>(a,b));
                                    unify.insert(pair<string,string>(b,c));
                                    //unified = 1;
                                    //break;

                                }
                                else if((c.length() != 1) && (d.length() == 1))
                                {
                                    unify.erase(b);
                                    //unify.insert(pair<string,string>(a,b));
                                    unify.insert(pair<string,string>(b,c));
                                }
                                else if((c.length() == 1) && (d.length() != 1))
                                {
                                    unify.erase(a);
                                    //unify.insert(pair<string,string>(a,b));
                                    unify.insert(pair<string,string>(a,d));
                                }
                                else
                                {
                                    cannot_unify = 1;
                                    break;
                                }
                            }
                        }
                        idx1++;
                        idx2++;
                        if(clausei[idx1] == ')')
                            break;
                        else
                        {
                            idx1++;
                            idx2++;
                        }
                    }
                    else if((((clausei[idx1+1] == ',') || (clausei[idx1+1] == ')')) && ((clausej[idx2+1] != ',') || (clausej[idx2+1] != ')'))))
                    {
                        // unify constant and variable x John
                        //parent.insert(pair<string,struct node>(start_state, n3))
                        //cout<<"B condition \n";
                        //cout<<clausei[idx1]<<endl;
                        //cout<<clausej[idx2]<<endl;
                        //cout<<idx1<<endl;
                        //cout<<idx2<<endl;
                        //already = 1;
                        int ff = 0;
                        while((clausej[idx2] != ',') && (clausej[idx2] != ')'))
                        {
                            temp1[ff] = clausej[idx2];
                            ff++;
                            idx2++;
                        }

                        temp1[ff] = '\0';
                        //idx2++;

                        //string a,b,c;
                        a = clausei[idx1];
                        a[1]='\0';
                        b = temp1;
                        it_unify = unify.find(a);
                        if(it_unify == unify.end())
                        {
                            unify.insert(pair<string,string>(a,b));
                            //unified = 1;
                            //break;
                        }
                        else
                        {
                            c = it_unify->second;
                            if(c.length() == 1)
                            {
                                unify.erase(a);
                                unify.insert(pair<string,string>(a,b));
                                unify.insert(pair<string,string>(c,b));
                                //unified = 1;
                                //break;

                            }
                            else
                            {
                                cannot_unify = 1;
                                break;
                            }
                        }
                        if(clausej[idx2] == ')')
                        {
                            idx1++;
                            break;
                        }
                        idx1 = idx1+2;
                        idx2++;

                    }
                    else if(((clausei[idx1+1] != ',') || (clausei[idx1+1] != ')')) && ((clausej[idx2+1] == ',') || (clausej[idx2+1] == ')')))
                    {
                        // unify constant and variable x John
                        //cout<<"Condition C\n";

                        int ff = 0;
                        while((clausei[idx1] != ',') && (clausei[idx1] != ')'))
                        {
                            temp1[ff] = clausei[idx1];
                            idx1++;
                            ff++;
                        }


                        temp1[ff] = '\0';
                        //idx1++;
                        //string a,b,c;
                        a = clausej[idx2];
                        a[1]='\0';
                        b = temp1;
                        //cout<<a<<endl;
                        //cout<<b<<endl;
                        it_unify = unify.find(a);
                        if(it_unify == unify.end())
                        {
                            //cout<<"1\n";
                            unify.insert(pair<string,string>(a,b));
                            //unified = 1;
                            //break;
                        }
                        else
                        {

                            c = it_unify->second;
                            if(c.length() == 1)
                            {
                                //cout<<"2\n";
                                unify.erase(a);
                                unify.insert(pair<string,string>(a,b));
                                unify.insert(pair<string,string>(c,b));
                                //unified = 1;
                                //break;

                            }
                            else
                            {
                                //cout<<"3\n";
                                cannot_unify = 1;
                                break;
                            }
                        }
                        if(clausei[idx1] == ')')
                        {
                            idx2++;
                            break;
                        }
                        idx2 = idx2+2;
                        idx1++;
                        //cout<<clausej[idx2+1]<<endl;
                        //cout<<clausei[idx1+1]<<endl;
                    }
                    else if(((clausei[idx1+1] != ',') || (clausei[idx1+1] != ')')) && ((clausej[idx2+1] != ',') || (clausej[idx2+1] != ')')))
                    {
                        //cout<<"D\n";
                        //cout<<idx1<<endl;
                        //cout<<idx2<<endl;
                        //cout<<clausei[idx1]<<endl;
                        //cout<<clausej[idx2]<<endl;

                        while(((clausei[idx1] != ',') && (clausei[idx1] != ')')) && ((clausej[idx2] != ',') && (clausej[idx2] != ')')))
                        {
                            //cout<<"Hey\n";
                            if((clausei[idx1] != clausej[idx2]))
                                break;
                            idx1++;
                            idx2++;
                        }
                        if(((clausei[idx1] == ',') || (clausei[idx1] == ')')) && ((clausej[idx2] == ',') || (clausej[idx2] == ')')))
                        {
                            //cout<<"11111\n";
                            if((clausei[idx1] == ')') && ((clausej[idx2] == ')')))
                            {
                                break;
                            }
                            idx1++;
                            idx2++;

                        }
                        else
                        {
                            //cout<<"22222\n";
                            cannot_unify = 1;
                            break;
                        }
                    }
                }
                if(cannot_unify == 1)
                {
                    //cout<<"cannot unify\n";
                    break;
                }
                else if((clausei[idx1] == ')') && (clausej[idx2] == ')'))
                {
                    // create newclause
                    //cout<<"Unified\n";
                    char abc[1001];
                    char temp3[1001];
                    char aaa[100001];
                    char *t_new_clause = (char*)malloc(sizeof(char)*100001);
                    strcpy(aaa,clausei.c_str());
                    int I,J,K;

                    I = 0;
                    while(aaa[I] != '\0')
                    {
                        if(aaa[I] == '|')
                            I++;
                        J = I;
                        K = 0;
                        while(aaa[J] != '(')
                        {
                            abc[K] = aaa[J];
                            K++;
                            J++;
                        }
                        //strcpy(key,clause+i);
                        abc[K] = '\0';
                        //cout<<abc<<endl;
                        if(!strcmp(abc,key))
                        {
                            strcpy(t_new_clause,aaa);
                            if(I == 0)
                                t_new_clause[I] = '\0';
                            else
                                t_new_clause[I-1] = '\0';
                            //cout<<new_clause<<endl;
                            while(aaa[J] != ')')
                            {
                                J++;
                            }
                            I = J++;
                            break;
                        }

                        while(aaa[J] != ')')
                        {
                            J++;
                        }
                        I = J+1;
                    }

                    if(aaa[I] == ')')
                    {
                        I++;
                    }
                    strcat(t_new_clause,aaa+I);
                    if(t_new_clause[0] == '|')
                    {
                        strcpy(t_new_clause,t_new_clause+1);
                    }

                    /*strcat(t_new_clause,aaa+I);
                    if(t_new_clause[0] == '|')
                    {
                        strcpy(t_new_clause,t_new_clause+1);
                    }*/

                    //cout<<"New clause first expression "<<t_new_clause<<endl;

                    /////////////////////////////////////////////////////////
                    char def[1001];
                    char temp4[1001];
                    char bbb[100001];
                    strcpy(bbb,clausej.c_str());
                    char *temp_new_clause = (char*)malloc(sizeof(char)*100001);
                    //int I,J,K;

                    I = 0;
                    while(bbb[I] != '\0')
                    {
                        if(bbb[I] == '|')
                            I++;
                        J = I;
                        K = 0;
                        while(bbb[J] != '(')
                        {
                            def[K] = bbb[J];
                            K++;
                            J++;
                        }
                        //strcpy(key,clause+i);
                        def[K] = '\0';
                        //cout<<abc<<endl;
                        if(!strcmp(def,neg_key))
                        {
                            strcpy(temp_new_clause,bbb);
                            if(I == 0)
                                temp_new_clause[I] = '\0';
                            else
                                temp_new_clause[I-1] = '\0';
                            //cout<<new_clause<<endl;
                            while(bbb[J] != ')')
                            {
                                J++;
                            }
                            I = J++;
                            break;
                        }

                        while(bbb[J] != ')')
                        {
                            J++;
                        }
                        I = J+1;
                    }

                    if(bbb[I] == ')')
                    {
                        I++;
                    }
                    strcat(temp_new_clause,bbb+I);
                    if(temp_new_clause[0] == '|')
                    {
                        strcpy(temp_new_clause,temp_new_clause+1);
                    }

                    /*strcat(temp_new_clause[0] == '|')
                    {
                        strcpy(temp_new_clause,temp_new_clause+1);
                    }*/

                    //cout<<"New clause second expression "<<temp_new_clause<<endl;

                    //////////////////////////////////////////////////////////////
                    ///////////////// unify second clause/////////////////////////
                    char temp5[1001];
                    //int i,j,k;
                    I = 0;J=0;
                    char final_clause[100001] = {'\0'};

                    while(temp_new_clause[I] != '\0')
                    {
                        J = 0;
                        while(temp_new_clause[I] != '(')
                        {
                            temp5[J] = temp_new_clause[I];
                            J++;I++;
                        }
                        temp5[J] = temp_new_clause[I];
                        temp5[J+1] = '\0';
                        strcat(final_clause,temp5);

                        I++;
                        while((temp_new_clause[I] != ',') && (temp_new_clause[I] != ')'))
                        {
                            //cout<<"entered while loop\n";
                            if((temp_new_clause[I+1] == ',') || (temp_new_clause[I+1] == ')'))
                            {
                                temp5[0] = temp_new_clause[I];
                                temp5[1] = '\0';
                                //strcat(final_clause,clause);

                                it_unify = unify.find(temp5);
                                if(it_unify != unify.end())
                                {
                                    //cout<<"Inside map \n";
                                    string g = it_unify->second;
                                    strcat(final_clause,g.c_str());
                                }
                                else
                                {
                                    strcat(final_clause,temp5);
                                }
                                I++;
                                if(temp_new_clause[I] == ',')
                                    strcat(final_clause,(const char*)",");
                                else
                                    strcat(final_clause,(const char*)")");
                                if(temp_new_clause[I] == ')')
                                    break;
                                else
                                    I++;
                            }
                            else
                            {
                                //cout<<"entered constant condition \n";
                                J = 0;
                                while((temp_new_clause[I] != ',') && (temp_new_clause[I] != ')'))
                                {
                                    temp5[J] = temp_new_clause[I];
                                    J++;
                                    I++;
                                }
                                temp5[J] = temp_new_clause[I];
                                temp5[J+1] = '\0';
                                strcat(final_clause,temp5);
                                //here i is automatically pointing to comma or brace
                                if(temp_new_clause[I] == ')')
                                    break;
                                else
                                    I++;
                            }
                        }
                        I++;
                    }
                    //cout<<"Substituted clause is "<<final_clause<<endl;
                    //strcpy(new_clause,final_clause);
                    //cout<<"New clause is "<<new_clause<<endl;


                    if((!strcmp(t_new_clause,"")) && (!strcmp(temp_new_clause,"")))
                    {
                        //cout<<"Contradiction achieved\n";
                        strcpy(new_clause,"");
                    }
                    else if((strcmp(t_new_clause,"")) && (!strcmp(temp_new_clause,"")))
                    {
                        strcpy(new_clause,t_new_clause);
                    }
                    else if((!strcmp(t_new_clause,"")) && (strcmp(temp_new_clause,"")))
                    {
                        strcpy(new_clause,final_clause);
                    }
                    else if((strcmp(t_new_clause,"")) && (strcmp(temp_new_clause,"")))
                    {
                        strcpy(new_clause,t_new_clause);
                        strcat(new_clause,(const char*)"|");
                        strcat(new_clause,final_clause);
                    }

                    ///////////again check for tautology/////////////////////////////////
                    char k1[1001];
                    char neg_k1[1001];
                    char k2[1001];
                    tautology = 0;
                    I = 0;
                    int P,Q,R;
                    while(new_clause[I] != '\0')
                    {
                        if(new_clause[I] == '|')
                            I++;
                        J = I;
                        K = 0;
                        while(new_clause[J] != '(')
                        {
                            k1[K] = new_clause[J];
                            K++;
                            J++;
                        }
                        //strcpy(key,clause+i);
                        k1[K] = '\0';
                        //cout<<k1<<endl;
                        if(k1[0] != '~')
                        {
                            strcpy(neg_k1,(const char*)"~");
                            strcat(neg_k1,k1);
                        }
                        else
                        {
                            strcpy(neg_k1,k1+1);
                        }
                        //cout<<neg_k1<<endl;

                        //int P,Q,R;
                        P = 0;
                        //cout<<final_clause<<endl;
                        while(new_clause[P] != '\0')
                        {
                            //cout<<"entered first while \n";
                            if(new_clause[P] == '|')
                                P++;
                            Q = P;
                            R = 0;
                            //cout<<"P "<<P<<endl;
                            //cout<<"Q "<<Q<<endl;
                            //cout<<"R "<<R<<endl;
                            while(new_clause[Q] != '(')
                            {
                                k2[R] = new_clause[Q];
                                //cout<<k2[R]<<endl;
                                //cout<<final_clause[Q]<<endl;
                                Q++;
                                R++;

                            }
                            //strcpy(key,clause+i);
                            k2[R] = '\0';
                            //cout<<k2<<endl;
                            if(!strcmp(neg_k1,k2))
                            {
                                //cout<<"entered strcmp\n";
                                //cout<<neg_k1<<endl;
                                //cout<<k2<<endl;
                                tautology = 1;
                                break;
                            }
                            //cout<<"after while key is "<<key<<endl;
                            while(new_clause[Q] != ')')
                            {
                                Q++;
                            }
                            P = Q+1;
                        }
                        if(tautology == 1)
                            break;
                        while(new_clause[J] != ')')
                        {
                            J++;
                        }
                        I = J+1;
                    }

                    if(tautology == 1)
                    {
                        strcpy(new_clause,"");
                       	//cout<<"Tautology found\n";
                        //cout<<"New clause is "<<new_clause<<endl;
                    }
                    //cout<<"Tautology found "<<tautology<<endl;

                    //cout<<"Finalllllllyyyyyyyyyyy new clause is "<<new_clause<<endl;


                    unified = 1;
                    break;
                }
            }
            while(clausej[q] != ')')
            {
                q++;
            }
            p = q+1;
        }
        while(clausei[j] != ')')
        {
            j++;
        }
        i = j+1;
        if(unified == 1)
            break;
    }
    if(unified == 1)
    {
        //cout<<"I am unified\n";
        if(tautology == 1)
        {
            //cout<<"tautology found  ";
            //ofile<<"TAUTOLOGY FOUND \n"
            //cout<<"new clause is "<<new_clause<<endl;
            return 0;
        }
        if(!strcmp(new_clause,""))
        {
            //cout<<"unuuuuuuuuuuuuu Contradiction new clause is "<<new_clause<<endl;
            //cout<<"New clause "<<new_clause<<endl;
            return 1;
        }
        else
        {
            //cout<<"AAAAAAAAAAAA new clause formed"<<new_clause<<endl;;
            //cout<<"New clause "<<new_clause<<endl;
            // remove tautology here


            /*char k1[1001];
            char neg_k1[1001];
            char k2[1001];
            int taut = 0;
            int I,J,K;
            I = 0;
            int P,Q,R;
            while(new_clause[I] != '\0')
            {
                if(new_clause[I] == '|')
                    I++;
                J = I;
                K = 0;
                while(new_clause[J] != '(')
                {
                    k1[K] = new_clause[J];
                    K++;
                    J++;
                }
                //strcpy(key,clause+i);
                k1[K] = '\0';
                //cout<<k1<<endl;
                if(k1[0] != '~')
                {
                    strcpy(neg_k1,(const char*)"~");
                    strcat(neg_k1,k1);
                }
                else
                {
                    strcpy(neg_k1,k1+1);
                }
                //cout<<neg_k1<<endl;

                //int P,Q,R;
                P = 0;
                //cout<<final_clause<<endl;
                while(new_clause[P] != '\0')
                {
                    //cout<<"entered first while \n";
                    if(new_clause[P] == '|')
                        P++;
                    Q = P;
                    R = 0;
                    //cout<<"P "<<P<<endl;
                    //cout<<"Q "<<Q<<endl;
                    //cout<<"R "<<R<<endl;
                    while(new_clause[Q] != '(')
                    {
                        k2[R] = new_clause[Q];
                        //cout<<k2[R]<<endl;
                        //cout<<final_clause[Q]<<endl;
                        Q++;
                        R++;

                    }
                    //strcpy(key,clause+i);
                    k2[R] = '\0';
                    //cout<<k2<<endl;
                    if(!strcmp(neg_k1,k2))
                    {
                        //cout<<"entered strcmp\n";
                        //cout<<neg_k1<<endl;
                        //cout<<k2<<endl;
                        taut = 1;
                        break;
                    }
                    //cout<<"after while key is "<<key<<endl;
                    while(new_clause[Q] != ')')
                    {
                        Q++;
                    }
                    P = Q+1;
                }
                if(taut == 1)
                    break;
                while(new_clause[J] != ')')
                {
                    J++;
                }
                I = J+1;
            }

            if(taut == 1)
            {
                cout<<"Tautology found "<<endl;
            	cout<<"New clause "<<new_clause<<endl;
            }*/

            return 0;
        }
    }
    //cout<<"Not resolved \n";
    //strcpy(new_clause,"");
    return 0;
}

int process_query(string query)
{


    //cout<<"QUERY is "<<query<<endl;
    queue <string> sos;
    map<string, int> sos_map;

    //char *neg_query = (char*)malloc(sizeof(char)*1001);
    char neg_query[1001];
    //char clausei[1001];
    //char clausej[1001];
    string clausei;
    string clausej;
    int result,found;
    result = 1;
    found = 0;
    char* new_clause = (char*)malloc(sizeof(char)*100001);
    //string new_clause;


    if(query[0] != '~')
    {
        strcpy(neg_query,(const char*)"~");
        strcat(neg_query,query.c_str());
    }
    else
    {
        char hh[1001];
        strcpy(hh,query.c_str());
        strcpy(neg_query,hh+1);
    }

    sos.push(neg_query);


    clock_t begin = clock();
    //cout<<"begin "<<begin<<endl;

    while(!sos.empty())
    {
        clausei = sos.front();
        //cout<<"CLAUSE I "<<clausei<<"   ";
        sos.pop();
        //cout<<"CLAUSES IN KB PROCESSED\n";
        for(it_kb=kb.begin();it_kb != kb.end();it_kb++)
        {
            clausej = it_kb->first;
            //cout<<"clause j "<<clausej<<"   "<<endl;
            result = resolve(clausei,clausej,new_clause);
            //cout<<"New clause returned is "<<new_clause<<endl;
            //ofile<<"New clause returned is "<<new_clause<<endl;

            clock_t end = clock();
            //cout<<"end  "<<end<<endl;
            //cout<<"seconds "<<seconds<<endl;
            double seconds = double(end - begin) / CLOCKS_PER_SEC;
            if(seconds > 10)
            {
                found = 0;
                break;
            }
            if(result == 1)
            {
                found = 1;
                break;
            }
            else
            {
                // new_clause is not empty
                map<string,int>::iterator it_find;
                string temp_clause;

                if(strcmp(new_clause,""))
                {
                    temp_clause = new_clause;

                    //cout<<"New clause in query function "<<new_clause<<endl;
                    //cout<<"Temp Clause in query function "<<temp_clause<<endl;
                }
                //cout<<"Till here\n";

                //it_find = kb.find(temp_clause);

                if(strcmp(new_clause,""))
                {
                    //it_find = kb.find(temp_clause);
                    if(it_find == kb.end())
                    {
                        kb.insert(pair<string,int>(temp_clause,1));
                    }
                    it_find = sos_map.find(temp_clause);
                    if(it_find == sos_map.end())
                    {
                        sos_map.insert(pair<string,int>(temp_clause,1));
                        sos.push(new_clause);
                    }
                }
            }

        }
        if(found == 1)
            break;
    }
    //cout<<"1\n";
    if(found == 1)
    {
        //cout<<"True"<<endl;
        return 1;
    }
    else
    {
        //cout<<"False"<<endl;
        return 0;
    }
    //cout<<"End of process_query function\n";
    free(new_clause);
    new_clause = NULL;

}

char* to_cnf(char *expr, vector <string>* vct)
{
    if(expr[0] != '(')
    {
        return expr;
    }
    else
    {
        if(expr[1] == '~')
        {
            strcpy(str5,expr+1);
            int l = strlen(expr);
            str5[l-2] = '\0';
            return str5;
        }
        else
        {
            int top = -1;
            int i = 1;
            while(1)
            {
                if((expr[i] == '|') || (expr[i] == '&'))
                {
                    if(top == -1)
                        break;
                }
                else if(expr[i] == '(')
                {
                    top++;
                }
                else if(expr[i] == ')')
                {
                    top--;
                }
                i++;
            }

            char *expr1 = (char*)malloc(sizeof(char)*1001);
            char *expr2 = (char*)malloc(sizeof(char)*1001);
            char op = expr[i];

            strcpy(expr1,expr+1);
            expr1[i-1] = '\0';
            strcpy(expr2,expr+i+1);
            int g = strlen(expr2);
            expr2[g-1] = '\0';
            char *val1 = (char*)malloc(sizeof(char)*1001);
            char *val2 = (char*)malloc(sizeof(char)*1001);
            vector <string> vector1;
            vector <string> vector2;


            strcpy(val1, to_cnf(expr1,&vector1));
            //cout<<"came\n";
            strcpy(val2, to_cnf(expr2,&vector2));

            vector <string>::iterator it1;
            vector <string>::iterator it2;
            if(op == '|')
            {
                //cout<<"11111111\n";
                if((val1[0] != '#') && (val2[0] != '#'))
                {
                    //cout<<"A\n";
                    strcpy(str5,val1);
                    strcat(str5,(const char*)"|");
                    strcat(str5,val2);
                    vct->push_back(str5);
                }
                else if((val1[0] != '#') && (val2[0] == '#'))
                {
                    //cout<<"B\n";
                    for(it2 = vector2.begin(); it2 != vector2.end(); it2++)
                    {
                        string a = *it2;
                        strcpy(str5,a.c_str());
                        strcat(str5,(const char*)"|");
                        strcat(str5,val1);
                        vct->push_back(str5);
                    }


                }
                else if((val1[0] == '#') && (val2[0] != '#'))
                {
                    //cout<<"C\n";
                    for(it1 = vector1.begin();it1 != vector1.end();it1++)
                    {
                        string a = *it1;
                        strcpy(str5,a.c_str());
                        strcat(str5,(const char*)"|");
                        strcat(str5,val2);
                        vct->push_back(str5);
                    }
                }
                else if((val1[0] == '#') && (val2[0] == '#'))
                {
                    //cout<<"D\n";
                    for(it1 = vector1.begin();it1 != vector1.end(); it1++)
                    {
                        for(it2 = vector2.begin();it2 != vector2.end();it2++)
                        {
                            string a = *it2;
                            strcpy(str5,a.c_str());
                            strcat(str5,(const char*)"|");
                            string b = *it1;
                            strcat(str5,b.c_str());
                            vct->push_back(str5);
                        }
                    }
                }
            }
            else if(op == '&')
            {
                //cout<<"222222\n";
                if((val1[0] != '#') && (val2[0] != '#'))
                {
                    //cout<<"Case 1\n";
                    //vct.reserve(1000);
                    //cout<<"E\n";
                    vct->push_back((string)val1);
                    vct->push_back((string)val2);

                }
                else if((val1[0] != '#') && (val2[0] == '#'))
                {
                    //cout<<"F\n";
                    vct->push_back(val1);
                    for(it2 = vector2.begin();it2 != vector2.end();it2++)
                    {
                        vct->push_back(*it2);
                    }
                }
                else if((val1[0] == '#') && (val2[0] != '#'))
                {
                    //cout<<"G\n";
                    vct->push_back(val2);
                    for(it1 = vector1.begin();it1 != vector1.end();it1++)
                    {
                        vct->push_back(*it1);
                    }
                }
                else if((val1[0] == '#') && (val2[0] == '#'))
                {
                    //cout<<"H\n";
                    for(it1 = vector1.begin();it1 != vector1.end();it1++)
                    {
                        vct->push_back(*it1);
                    }
                    for(it2 = vector2.begin();it2 != vector2.end();it2++)
                    {
                        vct->push_back(*it2);
                    }
                }
            }
            //cout<<"here\n";
            strcpy(str5,"####");
            return str5;
        }
    }
}

int main()
{
  ifstream ifile;
  ifile.open("input.txt");
  ofstream ofile("output.txt");
  string line;
  bool flag;
  string q, sentence;
  int query_num, sentence_num,i;
  string num;
  string query[100];
  string clause;
  char st[1001] = {'\0'};

  if(ifile.is_open())
  {
    getline(ifile,num);
    stringstream convert(num);
    convert>>query_num;

    for(i=0;i<query_num;i++)
    {
        getline(ifile,q);
        q.erase(std::remove(q.begin(),q.end(),' '),q.end());
        //cout<<"QUERIES\n";
        //cout<<q<<endl;
        query[i] = q;
    }

    getline(ifile,num);
    stringstream convert1(num);
    convert1>>sentence_num;
	//cout<<"SENTENCES\n";
    for(i=0;i<sentence_num;i++)
    {
        getline(ifile,sentence);
        sentence.erase(std::remove(sentence.begin(),sentence.end(),' '),sentence.end());

        //cout<<sentence<<endl;
        strcpy(st,sentence.c_str());
        strcat(st,(const char*)"\0");
        YY_BUFFER_STATE buffer = yy_scan_buffer(st,sizeof(st));
        yy_switch_to_buffer(buffer);
        yyparse();
        yy_delete_buffer(buffer);
    }
  }
    vector <string> vct;
    vector <string>::iterator it;

    map <string,int>::iterator iter;
    char final_str[1001];
    for(iter=kbase.begin(); iter != kbase.end();iter++)
    {
        string fs = iter->first;
        strcpy(final_str,fs.c_str());
        if(final_str[0] != '(')
        {
            //add_to_kb(final_string);
            kb.insert(pair< string,int >(final_str,1));
        }
        else if((final_str[0] == '(') && (final_str[1] == '~'))
        {
            int k = strlen(final_str);
            strcpy(final_str,final_str+1);
            final_str[k-2] = '\0';
            //add_to_kb(final_string);
            kb.insert(pair< string,int >(final_str,1));
        }
        else
        {
            to_cnf(final_str,&vct);
            for(it=vct.begin();it != vct.end();it++)
            {
                //add_to_kb(*it);
                kb.insert(pair< string,int >(*it,1));
            }
        }
    }

    /*cout<<"PREDICATES STARTED\n";
    for(iter=kbase.begin(); iter != kbase.end();iter++)
    {
        //cout<<iter->first;
        //cout<<endl;
        //ofile<<iter->first<<endl;
    }
    cout<<"predicates received\n";*/

    /*cout<<"New kb\n";
    for(it_kb=kb.begin(); it_kb != kb.end();it_kb++)
    {
        cout<<it_kb->first;
        cout<<endl;
        ofile<<it_kb->first<<endl;
    }
    cout<<"End of kb\n";*/

    int z = 0;
    for(z=0;z<query_num;z++)
    {
        int rs = process_query(query[z]);
        if(rs == 1)
        {
            ofile<<"TRUE\n";
        }
        else
        {
            ofile<<"FALSE\n";
        }
    }

    //int rs = 1;
    /*int rs = process_query("Frustrated(Bill)");
    if(rs == 1)
    {
        ofile<<"TRUE\n";
        cout<<"TRUE\n";
    }
    else
    {
        ofile<<"FALSE\n";
        cout<<"FALSE\n";
    }*/


    ofile.close();
    return 0;
}

