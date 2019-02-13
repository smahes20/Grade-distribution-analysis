//part1: to  compute  and  output  the  grade  distribution
//all  classes  in  the  college;  percentages  are  computed  based  on  the  total  #  of  A,  B,  C,  D  and  F  grades  
//part 2: tocompute based in departments
//for part 3: the classes listed have to be in ascending order of their number

// Grade Analysis program in modern C++.

// Sakshi Maheshwari
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 01
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std; 
 
class Course
{
private:
  string Dept;
  int Number;
  string Title, Instructor;
  int A, B, C, D, E, F, I, NR, S, U, W;

public:
  Course(string Dept, string Title, string Instructor, int Number, int A, int B,int C,int D,int F,int I ,int NR,int S,int U,int W)
  :Dept(Dept), Title(Title), Instructor (Instructor),Number(Number), A(A), B(B), C(C), D(D), F(F), I(I) , NR(NR), S(S), U(U), W(W)
  {}

  string getDept()
	{
	  return Dept;
	}
  int NumGrade(){
    return A+B+C+D+F;
  }
  int getGradeA(){
    return A;
  }
  int getGradeB(){
    return B;
  }
  int getGradeC(){
    return C;
  }
  int getGradeD(){
    return D;
  }
  int getGradeF(){
    return F;
  }
  int getGradeW(){
    return W;
  }
  int getDFWNum(){
    return D+F+W;
  }
  int getDFWDen(){
    return A+B+C+D+F+W;
  }
  string getInstructor(){
    return Instructor;
  }
  int getcourse(){
    return Number;
  }
  int getStudents(){
    return A+B+C+D+F+S+U+W+I+NR;
  }
  
};//end of course class


double getPercentage(vector<Course> courses,char ch){
  int total = 0;
  int sum = 0;
	
	//for (vector<Course>::iterator it = courses.begin(); it != courses.end(); ++it){
    for (auto &it: courses){
    	switch(ch)
    	{
    		case 'A':
    			total+=it.getGradeA();
				break;
			case 'B':
    			total+=it.getGradeB();
				break;
			case 'C':
    			total+=it.getGradeC();
				break;
			case 'D':
    			total+=it.getGradeD();
				break;
			case 'F':
    			total+=it.getGradeF();
				break;		
		}
			
		sum+=it.NumGrade();
	}
  if(sum == 0)
    return 0;
  double percentage = (total / (sum*1.0))*100;
  return percentage;
}


int getCourses(vector<Course> courses){
  int numCourses = 0;
  for (auto &x: courses) 
	{
		numCourses++;	
	}
  return numCourses;
}

double getDFWrate(vector<Course> courses){
  double num;
  double den;
  for(auto &x:courses){
    num += x.getDFWNum();
    den += x.getDFWDen();
  }
  if(den == 0)
    return 0;
  double rate = (num/(den*1.0)) * 100;
  return rate;
}


int main()
{
  string  filename;
  //comma separate strings for files
  string line, Dept, Title, Instructor;
  string Number, A, B, C, D, F,I , NR, S, U, W; 
  
  //cout << "enter input filename: ";
  cin >> filename;
  

  ifstream file(filename);
  cout << std::fixed;
  cout << std::setprecision(2);

  if (!file.good()){
      cout << "cannot open file!" << endl;
      return -1;
  }
  cout << filename << endl;

  vector<Course> courses;  
  set<string> courseName;
 
  //skip header
  getline(file, line);

  //read until the end of the movies file
  while(getline(file, line)){

   //holds the entire line 
   stringstream ss(line);

   //parse lines
    getline(ss, Dept, ',');
    getline(ss, Number, ',');
    getline(ss, Title, ',');
    getline(ss, A, ',');
    getline(ss, B, ',');
    getline(ss, C, ',');
    getline(ss, D, ',');
    getline(ss, F, ',');
    getline(ss, I, ',');
    getline(ss, NR, ',');
    getline(ss, S, ',');
    getline(ss, U, ',');
    getline(ss, W, ',');
    getline(ss, Instructor);

    //store the data in an object, by converting it into the right type
    Course info(Dept, Title, Instructor, stoi(Number), stoi(A), stoi(B), stoi(C), stoi(D), stoi(F), stoi(I), stoi(NR), stoi(S), stoi(U), stoi(W));
    
    //insert object at the end of vector
    courses.push_back(info);
    courseName.insert(info.getDept());

  }
  int numCourses = 0;
	int sum=0;

	//for (vector<Course>::iterator it = courses.begin(); it != courses.end(); ++it){
	for(auto &it: courses){
      sum+=it.NumGrade();
	}
  
  //part1
  cout << "\n";
  cout << "College of Engineering:"<< endl;
  cout << "Num courses:  "<< getCourses(courses) <<endl; //gets all courses
  cout << "Num grades:   " << sum <<endl; //get the addition of the values from the coulmn a-f
  cout << "Distribution: "<< getPercentage(courses,'A')<<"%, "<<getPercentage(courses,'B')<<"%, "<<getPercentage(courses,'C')<<"%, "<<getPercentage(courses,'D')<<"%, "<<getPercentage(courses,'F')<<"%" << endl;
	cout << "\n";
  
  //part 2
	//for(set<string>::iterator it=courseName.begin();it!=courseName.end();++it)//iterator along with course name
	for(auto &it: courseName){		
		numCourses=0;
		sum=0;
		cout<<it<<":"<<endl;
		vector<Course> deptCourse;
		//for (vector<Course>::iterator it1 = courses.begin(); it1 != courses.end(); ++it1)//foreach courses 
		for(auto &it1: courses){
			string str1=it;
			string str2=it1.getDept();
			if(str1.compare(str2)==0)//compare each course name
			{
				deptCourse.push_back(it1);//create seperate vector for each course name 
				numCourses++;
				sum+=it1.NumGrade();
			}
		}
		cout << "Num courses:  "<< numCourses <<endl; //gets all courses
		cout << "Num grades:   " << sum <<endl; //get the addition of the values from the coulmn a-f
		cout << "Distribution: "<< getPercentage(deptCourse,'A')<<"%, "<<getPercentage(deptCourse,'B')<<"%, "<<getPercentage(deptCourse,'C')<<"%, "<<getPercentage(deptCourse,'D')<<"%, "<<getPercentage(deptCourse,'F')<<"%" << endl;	
  }

  //part 3
  string choice;
  while(choice != "#")
  {
    cout<< "\n";
    cout << "Please enter instructor's name (or prefix or #)> ";
    cin >> choice;
    cout << "\n";
    if (choice == "#"){
      //cout << "Exiting program" << endl;
      break;
    }
    int flag = 0;
    for (auto & x: courses){
      
      string check = " " + choice + " ";//given check variable to check for last name
      if(string(x.getInstructor()).find(choice) == 0  || x.getInstructor().find(check) != string::npos )//check last name || check prefix
      {
        flag = 1;
        cout << x.getDept() << " "<<  x.getcourse() << " ("<<  x.getInstructor() << "):" << endl;
        cout << "Num students: " << x.getStudents() << endl;
        
        if((x.getGradeA() && x.getGradeB() && x.getGradeC() && x.getGradeD()&& x.getGradeF()) == '0'){
          //string result = "no report";
          cout << "Distribution: " << "no report" << endl;
        }
        
        vector<Course> singleCourse;
        singleCourse.push_back(x);

        double gradeA = getPercentage(singleCourse , 'A');
        double gradeB = getPercentage(singleCourse , 'B');
        double gradeC = getPercentage(singleCourse , 'C');
        double gradeD = getPercentage(singleCourse , 'D');
        double gradeF = getPercentage(singleCourse , 'F');

        if(gradeA == 0 && gradeB == 0 && gradeC == 0 && gradeD == 0 && gradeF == 0)
        {
          cout << "Distribution: no report" << endl;
        }
        else
        {
          //cout << "Distribution: " << gradeA << "%, "<< gradeB << "%, "<< gradeC << "%, "<< gradeD << "%, "<< gradeF << "%"<< endl; 
          cout << "Distribution: "<< getPercentage(singleCourse,'A')<<"%, "<<getPercentage(singleCourse,'B')<<"%, "<<getPercentage(singleCourse,'C')<<"%, "<<getPercentage(singleCourse,'D')<<"%, "<<getPercentage(singleCourse,'F')<<"%" << endl;	
        }  
        cout << "DFW rate: " << getDFWrate(singleCourse) <<  "%"<< endl;
      }   
    }
    if(flag == 0){
        cout<<"";
    }
 
  }
  return 0;
}

// run: g++ -std=c++14 proj1.cpp && ./a.out