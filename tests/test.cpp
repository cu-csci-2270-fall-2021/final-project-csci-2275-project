// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, TestInsert){
    
    
    string result;
    string expected;
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    result = test_insert(commits, len, tabSize);
    expected = "0|| science(1,4,)\n1|| \n2|| \n3|| \n4|| difficult(3,)-->fun(2,)-->computer(0,)\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

	string commits1[] = {"run", "initial", "test", "version", "brown", "work", "error"};
	len = 7;
	tabSize = 7;
	result = test_insert(commits1, len, tabSize);
	expected = "0|| test(2,)\n1|| error(6,)\n2|| \n3|| work(5,)\n4|| version(3,)-->initial(1,)\n5|| run(0,)\n6|| brown(4,)\n";
	ASSERT_EQ(expected, result);
    add_points_to_grade(6);

	string commits2[] = {"aaa", "bbb", "ccc"};
	len = 3;
	tabSize = 3;
	result = test_insert(commits2, len, tabSize);
	expected = "0|| ccc(2,)-->bbb(1,)-->aaa(0,)\n1|| \n2|| \n";
	ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}

TEST_F(test_x, TestSearch){
	string result;
    string expected;
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    result = test_search(commits, len, tabSize, "fun");
    expected = "2,";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

	string* commits2 = NULL;
    tabSize = 5;
    result = test_search(commits2, len, tabSize, "lmao");
    expected = "";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

	string commits3[] = {"tests", "computer", "bug", "tests", "fun", "bug", "fixed", "error", "fixed", "science", "fun", "difficult", "science"};
    tabSize = 5;
	len = 13;
    result = test_search(commits3, len, tabSize, "fixed");
    expected = "6,8,";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}

//TODO add more tests for insert. Design tests for search from hashTable.
