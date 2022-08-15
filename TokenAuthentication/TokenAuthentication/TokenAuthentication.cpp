/*
Author: Matas Kimtys

Test idea given by a recruiter

There are no token until a command starting with 0 is given, followed by token_id, and then at what time interval T e.g. 0,1,1
token is then created at T = 1, with token_id = 1, expiry_Limit = T+expiry_Limit which in this example is 4
if a command starting with 1 is given, then reset token at time T and set its expiry_Limit to T+expiry_limit which is 4 as mentioned above.

finally its task is to return how many tokens are still not expired and return the total number of them.
*/

#include <iostream>
#include <vector>
#include <chrono>



using namespace std;
void dereferencingPointers();
int test(int expiryLimit, vector<vector<int>> commands);

int main()
{

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    vector<vector<int>> commands = { {0, 1, 1}, { 1, 1, 4 }, { 1,2,5 } };
    cout << "Hi! \n";
    cout << test(4, commands);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "\n\nTime taken = " << chrono::duration_cast<chrono::microseconds> (end - begin).count() << " microseconds" << endl;
    return 0;
}


int test(int expiryLimit, vector<vector<int>> commands) {
    //commands[i][0]-0get/1reset
    //commands[i][1]-token_id
    //commands[i][2]-execute at T
    int check = 0;

    vector<vector<int>> command_list = commands;
    int number_of_tokens{ 0 };
    int T_to_do{ 0 };
    for (int i = 0; i < command_list.size(); ++i) {
        if (T_to_do < command_list.at(i).at(2)) {
            T_to_do = command_list.at(i).at(2);
        }
    }

    //tokens[i][0]-token-id
    //tokens[i][1]-expiry_limit
    //tokens[i][2]-current_token_T
    //tokens[i][3]-is_expired (0-false, 1-true)
    vector<vector<int>> tokens{ {0,0,0,1} };

    int T = 0; // current_T
    while (T <= T_to_do) {

        for (int i = 0; i < tokens.size(); i++) {
            if (tokens.at(i).at(2) >= tokens.at(i).at(1) && tokens.at(i).at(3) == 0) {
                tokens.at(i).at(3) = 1;
                tokens.erase(tokens.begin() + i);
            }
        }
        if (command_list.size() > 0) {
            for (int i = 0; i < command_list.size(); ++i) {
                if (command_list.at(i).at(2) == T) {
                    if (command_list.at(i).at(0) == 0) { //Get token_id T
                        bool exists = false;
                        for (int j = 0; j < tokens.size(); j++) {
                            if (tokens.at(j).at(0) == command_list.at(i).at(1)) {
                                exists = true;
                            }
                        }
                        if (exists == false) {
                            vector<int> temporary_vector = { command_list.at(i).at(1), T + expiryLimit, T, 0 };
                            tokens.push_back(temporary_vector);
                        }
                    }
                    if (command_list.at(i).at(0) == 1) { // Reset token_id T
                        for (int j = 0; j < tokens.size(); ++j) {
                            // Check if token_id matches and if is expired

                            if (tokens.at(j).at(0) == command_list.at(i).at(1) && tokens.at(j).at(3) == 0) {

                                tokens.at(j).at(1) = T + expiryLimit;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < tokens.size(); ++i) {
            tokens.at(i).at(2)++;
        }
        ++T;
    }
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens.at(i).at(3) == 0) {
            number_of_tokens++;
        }
    }
    return number_of_tokens;
    //return check;
}
void dereferencingPointers() {

    int s1[3][3]{ {0, 1, 1}, { 1, 1, 4 }, { 1,2,5 } };

    int* aptr = new int;

    int** aptrarr;
    aptrarr = new int* [3];
    for (int i = 0; i < 3; ++i) {
        aptrarr[i] = new int[3];
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            aptrarr[i][j] = s1[i][j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (aptrarr[i][j] >= 0) {
                //cout << "\n aptrarr[" << i << "][" << j << "] = " << aptrarr[i][j];
            }

        }
    }


    ////

    int number_of_tokens{ 0 };
    int commands_rows{ 2 };
    int commands_columns{ 3 };
    int expiry_Limit{ 4 };

    int T_to_do{ aptrarr[0][2] };
    for (int i = 0; i < 3; ++i) {
        if (T_to_do < aptrarr[i][2]) {
            T_to_do = aptrarr[i][2];
        }
    }
    //commands [0] - 0get/1reset, [1] - token id, [2] - do at T
    // [i][0] - token_id, [i][1] - expiry_limit, [i][2] - T, [i][3] -  is_expired(0-false, 1-true)
    vector<vector<int>> tokens{ {0,0,0,1} };
    int T = 0; // current time
    while (T <= T_to_do) {
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens.at(i).at(2) >= tokens.at(i).at(1) && tokens.at(i).at(3) == 0) {
                tokens.at(i).at(3) = 1;
            }
        }
        if (commands_rows > 0) {
            for (int i = 0; i < commands_rows; ++i) {
                if (aptrarr[i][2] == T) {
                    if (aptrarr[i][0] == 0) { // get token_id at time T
                        bool exists = false;
                        for (int j = 0; j < tokens.size(); ++j) {
                            if (tokens.at(j).at(0) == aptrarr[i][1]) {
                                exists = true;
                            }
                        }
                        if (exists == false) {
                            vector<int> temp_array = { aptrarr[i][1], T + expiry_Limit, T, 0 };
                            tokens.push_back(temp_array);
                        }
                    }
                    if (aptrarr[i][0] == 1) { // reset token_id at time T
                        for (int j = 0; j < tokens.size(); j++) {
                            // checks if token_id matches and if it is expired
                            if (tokens.at(j).at(0) == aptrarr[i][1] && tokens.at(j).at(3) == 0) {
                                tokens.at(j).at(1) = T + 4;
                            }
                        }
                    }
                }
            }
        }
        else {

        }
        for (int i = 0; i < tokens.size(); ++i) {
            tokens.at(i).at(2)++;
        }
        ++T;
    }
    //check how many still active
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens.at(i).at(3) == 0) {
            number_of_tokens++;
        }
    }
    cout << "\nNumber of tokens still active: " << number_of_tokens;
}
