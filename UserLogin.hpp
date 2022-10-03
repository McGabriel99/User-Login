#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class UserLogin {
private:

    unordered_map< string, string > table;


public:
    UserLogin(); // default constructor

    void readIn(const string& filename); // add data from file to hash table

    size_t numberOfUsers(); // return the number of users

    string passWordCheck(const string& userName); // returns the passWord of the given user

    size_t wordBucketIdMethod1(const string& userName); // return the bucket number where the given user is located

    size_t wordBucketIdMethod2(const string& userName); // another way to find the bucket number where the given user is located

    bool validateUser(const string& userName); // look up given user

    bool authenticateUser(const string& userName, const string& passWord);// authenticate given user and password

};

UserLogin::UserLogin() {}


void UserLogin::readIn(const string& filename) {

    ifstream inputFile; //declare ifstream variable to read data IN from file
    inputFile.open(filename); //open file
    string key, value; //declare string variable for key (username), value (password)

    //safer than while(!inFile.eof()), won't accidentally reach eof inside of loop
    while (inputFile >> key >> value){
      table.insert({key, value}); //stores username and password as a pair in the unordered_map
    }

    inputFile.close(); //close file

}

size_t UserLogin::numberOfUsers() {

    return table.size();

}

string UserLogin::passWordCheck(const string& userName) {
  //iterator to find key (username) in table
  unordered_map<string, string>::const_iterator search = table.find(userName);
  //if iterator reaches end, then user does not exist in table
  if (search == table.end()){
    return "Non-existent User";
  }
  //if found, return the value of the key, the password
  else
    return search->second;

}

size_t UserLogin::wordBucketIdMethod1(const string& userName) {
  //declare size_t return type bucket_num
  size_t bucket_num = 0;
  //loop through the table at each node until end
  for (auto it = table.begin(); it != table.end(); ++it){
    //if key of node is equal to given username
    if (userName == it->first){
      //set bucket_num to the bucket # of where username is found
      bucket_num = table.bucket(it->first);
    }
  }
  return bucket_num;

}


bool UserLogin::validateUser(const string& userName) {
  //iterator to find key (username) in table
  unordered_map<string, string>::const_iterator search = table.find(userName);
  //if the username is not found, and reaches the end, then doesn't exist in table
  if (search == table.end()){
    return false;
  }
  //if found, then true
  else
    return true;

}

bool UserLogin::authenticateUser(const string& userName, const string& passWord) {
  bool result = false;
  for (auto & x: table) { //reference x is initialized to each node of table
    //if given username and password: 1) exist in table 2) match with key:value pair
    if(userName == x.first && passWord == x.second){
      //result will be set to true, if not then result is false by default
      result = true;
    }
  }
  return result;

}
